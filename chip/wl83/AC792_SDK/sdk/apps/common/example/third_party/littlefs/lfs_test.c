#include "system/includes.h"
#include "lfs.h"
#include "fs/fs.h"
#include "string.h"
#include "app_config.h"


#ifdef CONFIG_LITTLEFS_ENABLE

/*
 * littlefs -> VFS adapter (plus version)
 *
 * 说明：
 * 1. 删除 audio/sdram 历史接口，仅保留 VFS 适配 littlefs。
 * 2. 支持 fopen("w"/"w+") 自动创建多级目录。
 * 3. 增加 frename / ftruncate / 按后缀过滤的 fscan。
 * 4. 保留基础文件读写/删除/容量查询/递归扫描测试。
 */

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a)   (sizeof(a) / sizeof((a)[0]))
#endif

#define LFS_VFS_NAME_MAX            128
#define LFS_VFS_PATH_MAX            256
#define LFS_VFS_SCAN_MAX_FILES      128
#define LFS_VFS_EXT_MAX             16
#define LFS_VFS_EXT_LEN             16

#ifndef FNO_ERR
#define FNO_ERR                     0
#endif
#ifndef FNO_FILE_NOT_EXIST
#define FNO_FILE_NOT_EXIST          (-2)
#endif
#ifndef FNO_DIR_NOT_EXIST
#define FNO_DIR_NOT_EXIST           (-3)
#endif
#ifndef FNO_DECODE_FAIL
#define FNO_DECODE_FAIL             (-4)
#endif

typedef struct {
    lfs_file_t file;
    char path[LFS_VFS_PATH_MAX];
    char name[LFS_VFS_NAME_MAX];
    u8 opened;
} lfs_vfs_file_ctx_t;

typedef struct {
    u16 file_total;
    u16 file_index;
    char root[LFS_VFS_PATH_MAX];
    char names[LFS_VFS_SCAN_MAX_FILES][LFS_VFS_NAME_MAX];
    char rel_paths[LFS_VFS_SCAN_MAX_FILES][LFS_VFS_PATH_MAX];
} lfs_vfs_scan_ctx_t;

static lfs_t *g_lfs;

static int lfs_mode_convert(const char *mode)
{
    if (!mode) {
        return -1;
    }

    if (!strcmp(mode, "r")) {
        return LFS_O_RDONLY;
    }
    if (!strcmp(mode, "w")) {
        return LFS_O_WRONLY | LFS_O_CREAT | LFS_O_TRUNC;
    }
    if (!strcmp(mode, "w+")) {
        return LFS_O_RDWR | LFS_O_CREAT | LFS_O_TRUNC;
    }

    printf("[lfs_vfs] unsupported mode=%s\n", mode);
    return -1;
}

static int lfs_mode_need_create_dirs(const char *mode)
{
    if (!mode) {
        return 0;
    }
    return (!strcmp(mode, "w") || !strcmp(mode, "w+"));
}

static const char *lfs_vfs_trim_path(const char *path)
{
    const char *p;

    if (!path) {
        return NULL;
    }

    if (!strcmp(path, "C") || !strcmp(path, "/C")) {
        return "";
    }

    p = strstr(path, "/C/");
    if (p) {
        return p + 3;
    }

    p = strstr(path, "C/");
    if (p == path || (p > path && *(p - 1) == '/')) {
        return p + 2;
    }

    if (path[0] == '/') {
        return path + 1;
    }

    return path;
}

static void lfs_vfs_get_basename(const char *path, char *name, u32 name_len)
{
    const char *base;

    if (!name || !name_len) {
        return;
    }

    name[0] = '\0';
    if (!path || !path[0]) {
        return;
    }

    base = strrchr(path, '/');
    base = base ? (base + 1) : path;

    strncpy(name, base, name_len - 1);
    name[name_len - 1] = '\0';
}

static lfs_vfs_file_ctx_t *lfs_vfs_fp_ctx(FILE *file)
{
    if (!file) {
        return NULL;
    }
    return (lfs_vfs_file_ctx_t *)file->private_data;
}

static int lfs_vfs_join_path(char *out, u32 out_len, const char *dir, const char *name)
{
    if (!out || !out_len) {
        return -1;
    }

    if (!dir || !dir[0]) {
        snprintf(out, out_len, "%s", name ? name : "");
    } else if (!name || !name[0]) {
        snprintf(out, out_len, "%s", dir);
    } else {
        snprintf(out, out_len, "%s/%s", dir, name);
    }

    out[out_len - 1] = '\0';
    return 0;
}

static char lfs_vfs_tolower(char c)
{
    if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 'a';
    }
    return c;
}

static int lfs_vfs_stricmp(const char *a, const char *b)
{
    char ca;
    char cb;

    if (!a || !b) {
        return -1;
    }

    while (*a && *b) {
        ca = lfs_vfs_tolower(*a++);
        cb = lfs_vfs_tolower(*b++);
        if (ca != cb) {
            return (int)(unsigned char)ca - (int)(unsigned char)cb;
        }
    }

    return (int)(unsigned char)lfs_vfs_tolower(*a) -
           (int)(unsigned char)lfs_vfs_tolower(*b);
}

static void lfs_vfs_get_ext(const char *name, char *ext, u32 ext_len)
{
    const char *dot;

    if (!ext || !ext_len) {
        return;
    }

    ext[0] = '\0';
    if (!name || !name[0]) {
        return;
    }

    dot = strrchr(name, '.');
    if (!dot || !dot[1]) {
        return;
    }

    strncpy(ext, dot + 1, ext_len - 1);
    ext[ext_len - 1] = '\0';
}

static int lfs_vfs_parse_ext_filters(const char *ftype,
                                     char exts[LFS_VFS_EXT_MAX][LFS_VFS_EXT_LEN],
                                     int *ext_num)
{
    int count = 0;
    char token[LFS_VFS_EXT_LEN];
    int ti = 0;
    const char *p;

    if (!ext_num) {
        return -1;
    }

    *ext_num = 0;
    if (!ftype || !ftype[0]) {
        return 0;
    }

    memset(exts, 0, LFS_VFS_EXT_MAX * LFS_VFS_EXT_LEN);
    memset(token, 0, sizeof(token));

    for (p = ftype; ; p++) {
        char c = *p;
        int split = (c == '\0' || c == ',' || c == ';' || c == '|' || c == ' ' || c == '/');

        if (!split) {
            if (c == '.') {
                continue;
            }
            if (ti < (int)sizeof(token) - 1) {
                token[ti++] = lfs_vfs_tolower(c);
            }
            continue;
        }

        if (ti > 0) {
            token[ti] = '\0';
            strncpy(exts[count], token, LFS_VFS_EXT_LEN - 1);
            exts[count][LFS_VFS_EXT_LEN - 1] = '\0';
            count++;
            if (count >= LFS_VFS_EXT_MAX) {
                break;
            }
            memset(token, 0, sizeof(token));
            ti = 0;
        }

        if (c == '\0') {
            break;
        }
    }

    *ext_num = count;
    return 0;
}

static int lfs_vfs_match_ext(const struct vfscan *fsn, const char *name)
{
    char exts[LFS_VFS_EXT_MAX][LFS_VFS_EXT_LEN];
    int ext_num = 0;
    int i;
    char file_ext[LFS_VFS_EXT_LEN];

    if (!fsn || !fsn->ftype[0]) {
        return 1;
    }

    if (lfs_vfs_parse_ext_filters(fsn->ftype, exts, &ext_num) < 0 || ext_num <= 0) {
        return 1;
    }

    lfs_vfs_get_ext(name, file_ext, sizeof(file_ext));
    if (!file_ext[0]) {
        return 0;
    }

    for (i = 0; i < ext_num; i++) {
        if (!lfs_vfs_stricmp(file_ext, exts[i])) {
            return 1;
        }
    }

    return 0;
}

static int lfs_vfs_ensure_dir(const char *dir)
{
    int ret;
    char tmp[LFS_VFS_PATH_MAX];
    char *p;

    if (!g_lfs || !dir) {
        return -1;
    }

    if (!dir[0] || !strcmp(dir, "/")) {
        return 0;
    }

    strncpy(tmp, dir, sizeof(tmp) - 1);
    tmp[sizeof(tmp) - 1] = '\0';

    if (tmp[0] == '/') {
        memmove(tmp, tmp + 1, strlen(tmp));
    }

    for (p = tmp; *p; p++) {
        if (*p != '/') {
            continue;
        }
        *p = '\0';
        if (tmp[0]) {
            ret = lfs_mkdir(g_lfs, tmp);
            if (ret < 0 && ret != LFS_ERR_EXIST) {
                return ret;
            }
        }
        *p = '/';
    }

    ret = lfs_mkdir(g_lfs, tmp);
    if (ret < 0 && ret != LFS_ERR_EXIST) {
        return ret;
    }

    return 0;
}

static int lfs_vfs_ensure_parent_dirs(const char *file_path)
{
    int ret;
    char dir[LFS_VFS_PATH_MAX];
    char *p;

    if (!file_path || !file_path[0]) {
        return 0;
    }

    strncpy(dir, file_path, sizeof(dir) - 1);
    dir[sizeof(dir) - 1] = '\0';

    p = strrchr(dir, '/');
    if (!p) {
        return 0;
    }

    *p = '\0';
    if (!dir[0]) {
        return 0;
    }

    ret = lfs_vfs_ensure_dir(dir);
    if (ret < 0) {
        printf("[lfs_vfs] ensure_dir fail path=%s ret=%d\n", dir, ret);
    }
    return ret;
}

static int lfs_vfs_scan_collect(struct vfscan *fsn, lfs_vfs_scan_ctx_t *scan,
                                const char *root, u8 max_depth)
{
    int ret;
    lfs_dir_t dir;
    struct lfs_info info;
    char cur[LFS_VFS_PATH_MAX];
    char rel[LFS_VFS_PATH_MAX];
    u8 next_depth;

    if (!scan || !g_lfs) {
        return -1;
    }

    strncpy(cur, root ? root : "", sizeof(cur) - 1);
    cur[sizeof(cur) - 1] = '\0';

    ret = lfs_dir_open(g_lfs, &dir, cur[0] ? cur : "/");
    if (ret < 0) {
        ret = lfs_dir_open(g_lfs, &dir, cur);
    }
    if (ret < 0) {
        return ret;
    }

    while (1) {
        ret = lfs_dir_read(g_lfs, &dir, &info);
        if (ret < 0) {
            lfs_dir_close(g_lfs, &dir);
            return ret;
        }
        if (ret == 0) {
            break;
        }

        if (!strcmp(info.name, ".") || !strcmp(info.name, "..")) {
            continue;
        }

        lfs_vfs_join_path(rel, sizeof(rel), cur, info.name);

        if (info.type == LFS_TYPE_REG) {
            if (!lfs_vfs_match_ext(fsn, info.name)) {
                continue;
            }
            if (scan->file_total >= LFS_VFS_SCAN_MAX_FILES) {
                break;
            }
            strncpy(scan->names[scan->file_total], info.name, LFS_VFS_NAME_MAX - 1);
            scan->names[scan->file_total][LFS_VFS_NAME_MAX - 1] = '\0';
            strncpy(scan->rel_paths[scan->file_total], rel, LFS_VFS_PATH_MAX - 1);
            scan->rel_paths[scan->file_total][LFS_VFS_PATH_MAX - 1] = '\0';
            scan->file_total++;
            continue;
        }

        if (info.type == LFS_TYPE_DIR && max_depth > 0) {
            next_depth = max_depth - 1;
            ret = lfs_vfs_scan_collect(fsn, scan, rel, next_depth);
            if (ret < 0) {
                lfs_dir_close(g_lfs, &dir);
                return ret;
            }
            if (scan->file_total >= LFS_VFS_SCAN_MAX_FILES) {
                break;
            }
        }
    }

    lfs_dir_close(g_lfs, &dir);
    return 0;
}

static int __lfs_mount(struct imount *mt, int cache_num)
{
    struct vfs_partition *part;

    (void)cache_num;

    if (!mt) {
        return -1;
    }

    g_lfs = lfs_dev_mount();
    if (!g_lfs) {
        printf("[lfs_vfs] lfs_dev_mount fail\n");
        return -1;
    }

    part = &mt->part;
    memset(part, 0, sizeof(*part));
    mt->part_num = 1;
    part->offset = 0;
    part->dir[0] = 'C';
    part->dir[1] = '\0';
    return 0;
}

static int __lfs_unmount(struct imount *mt)
{
    (void)mt;
    g_lfs = NULL;
    return 0;
}

static int __lfs_fopen(FILE *file, const char *path, const char *mode)
{
    int ret;
    int lfs_mode;
    const char *real_path;
    lfs_vfs_file_ctx_t *ctx;

    if (!file || !path || !mode || !g_lfs) {
        return -1;
    }

    lfs_mode = lfs_mode_convert(mode);
    if (lfs_mode < 0) {
        return -1;
    }

    real_path = lfs_vfs_trim_path(path);
    if (!real_path) {
        return -1;
    }

    if (lfs_mode_need_create_dirs(mode)) {
        ret = lfs_vfs_ensure_parent_dirs(real_path);
        if (ret < 0) {
            return -1;
        }
    }

    ctx = zalloc(sizeof(*ctx));
    if (!ctx) {
        return -1;
    }

    strncpy(ctx->path, real_path, sizeof(ctx->path) - 1);
    ctx->path[sizeof(ctx->path) - 1] = '\0';
    lfs_vfs_get_basename(ctx->path, ctx->name, sizeof(ctx->name));

    ret = lfs_file_open(g_lfs, &ctx->file, ctx->path, lfs_mode);
    if (ret < 0) {
        free(ctx);
        return -1;
    }

    ctx->opened = 1;
    file->private_data = ctx;
    return 0;
}

static int __lfs_fread(FILE *file, void *buf, u32 len)
{
    lfs_vfs_file_ctx_t *ctx = lfs_vfs_fp_ctx(file);

    if (!ctx || !ctx->opened || !buf || !g_lfs) {
        return -1;
    }
    return lfs_file_read(g_lfs, &ctx->file, buf, len);
}

static int __lfs_fwrite(FILE *file, void *buf, u32 len)
{
    lfs_vfs_file_ctx_t *ctx = lfs_vfs_fp_ctx(file);

    if (!ctx || !ctx->opened || !buf || !g_lfs) {
        return -1;
    }
    return lfs_file_write(g_lfs, &ctx->file, buf, len);
}

static int __lfs_fseek(FILE *file, u32 offset, int orig)
{
    lfs_vfs_file_ctx_t *ctx = lfs_vfs_fp_ctx(file);

    if (!ctx || !ctx->opened || !g_lfs) {
        return -1;
    }
    return lfs_file_seek(g_lfs, &ctx->file, offset, orig);
}

static u32 __lfs_flen(FILE *file)
{
    lfs_vfs_file_ctx_t *ctx = lfs_vfs_fp_ctx(file);

    if (!ctx || !ctx->opened || !g_lfs) {
        return (u32) - 1;
    }
    return lfs_file_size(g_lfs, &ctx->file);
}

static u32 __lfs_fpos(FILE *file)
{
    lfs_vfs_file_ctx_t *ctx = lfs_vfs_fp_ctx(file);

    if (!ctx || !ctx->opened || !g_lfs) {
        return (u32) - 1;
    }
    return lfs_file_tell(g_lfs, &ctx->file);
}

static int __lfs_fclose(FILE *file)
{
    lfs_vfs_file_ctx_t *ctx = lfs_vfs_fp_ctx(file);

    if (!ctx || !g_lfs) {
        return -1;
    }

    if (ctx->opened) {
        lfs_file_close(g_lfs, &ctx->file);
        ctx->opened = 0;
    }

    free(ctx);
    file->private_data = NULL;
    return 0;
}

static int __lfs_fdelete(FILE *file)
{
    int ret;
    char path[LFS_VFS_PATH_MAX];
    lfs_vfs_file_ctx_t *ctx = lfs_vfs_fp_ctx(file);

    if (!ctx || !g_lfs) {
        return -1;
    }

    strncpy(path, ctx->path, sizeof(path) - 1);
    path[sizeof(path) - 1] = '\0';

    if (ctx->opened) {
        lfs_file_close(g_lfs, &ctx->file);
        ctx->opened = 0;
    }

    free(ctx);
    file->private_data = NULL;
    ret = lfs_remove(g_lfs, path);
    return ret;
}

static int __lfs_frename(FILE *file, const char *path)
{
    int ret;
    char old_path[LFS_VFS_PATH_MAX];
    const char *new_path;
    lfs_vfs_file_ctx_t *ctx = lfs_vfs_fp_ctx(file);

    if (!ctx || !path || !g_lfs) {
        return -1;
    }

    new_path = lfs_vfs_trim_path(path);
    if (!new_path || !new_path[0]) {
        return -1;
    }

    ret = lfs_vfs_ensure_parent_dirs(new_path);
    if (ret < 0) {
        return ret;
    }

    strncpy(old_path, ctx->path, sizeof(old_path) - 1);
    old_path[sizeof(old_path) - 1] = '\0';

    if (ctx->opened) {
        ret = lfs_file_close(g_lfs, &ctx->file);
        if (ret < 0) {
            return ret;
        }
        ctx->opened = 0;
    }

    ret = lfs_rename(g_lfs, old_path, new_path);
    if (ret < 0) {
        return ret;
    }

    strncpy(ctx->path, new_path, sizeof(ctx->path) - 1);
    ctx->path[sizeof(ctx->path) - 1] = '\0';
    lfs_vfs_get_basename(ctx->path, ctx->name, sizeof(ctx->name));
    return 0;
}

static int __lfs_ftruncate(FILE *file, u32 size)
{
    lfs_vfs_file_ctx_t *ctx = lfs_vfs_fp_ctx(file);

    if (!ctx || !ctx->opened || !g_lfs) {
        return -1;
    }
    return lfs_file_truncate(g_lfs, &ctx->file, size);
}

static int __lfs_fget_name(FILE *file, u8 *name, int len)
{
    int n;
    lfs_vfs_file_ctx_t *ctx = lfs_vfs_fp_ctx(file);

    if (!ctx || !name || len <= 0) {
        return -1;
    }

    n = strlen(ctx->name);
    if (n >= len) {
        n = len - 1;
    }

    memcpy(name, ctx->name, n);
    name[n] = '\0';
    return n;
}

static int __lfs_fget_path(FILE *file, struct vfscan *fsn, u8 *name, int len, u8 is_relative_path)
{
    int n;
    char abs_path[LFS_VFS_PATH_MAX + 16];
    lfs_vfs_file_ctx_t *ctx = lfs_vfs_fp_ctx(file);
    const char *src;

    (void)fsn;
    if (!ctx || !name || len <= 0) {
        return -1;
    }

    if (is_relative_path) {
        src = ctx->path;
    } else {
        snprintf(abs_path, sizeof(abs_path), "C/%s", ctx->path);
        src = abs_path;
    }

    n = strlen(src);
    if (n >= len) {
        n = len - 1;
    }

    memcpy(name, src, n);
    name[n] = '\0';
    return n;
}

static int __lfs_fget_attr(FILE *file, int *attr)
{
    (void)file;
    if (!attr) {
        return -1;
    }
    *attr = F_ATTR_ARC | F_ATTR_RW;
    return 0;
}

static int __lfs_fget_attrs(FILE *file, struct vfs_attr *attr)
{
    if (!file || !attr) {
        return -1;
    }

    memset(attr, 0, sizeof(*attr));
    attr->attr = F_ATTR_ARC | F_ATTR_RW;
    attr->fsize = __lfs_flen(file);
    return 0;
}

static int __lfs_fget_free_space(struct vfs_devinfo *dev, struct vfs_partition *part, u32 *space)
{
    lfs_ssize_t used_blocks;
    u32 total_blocks;
    u32 block_size;

    (void)dev;
    (void)part;

    if (!g_lfs || !space || !g_lfs->cfg) {
        return -1;
    }

    used_blocks = lfs_fs_size(g_lfs);
    if (used_blocks < 0) {
        *space = 0;
        return -1;
    }

    total_blocks = g_lfs->cfg->block_count;
    block_size = g_lfs->cfg->block_size;
    if ((u32)used_blocks > total_blocks) {
        used_blocks = total_blocks;
    }

    *space = (total_blocks - used_blocks) * block_size;
    return 0;
}

static int __lfs_fscan(struct vfscan *fsn, const char *path, u8 max_deepth)
{
    int ret;
    lfs_vfs_scan_ctx_t *scan;
    const char *real_path;

    if (!fsn || !g_lfs) {
        return -1;
    }

    scan = zalloc(sizeof(*scan));
    if (!scan) {
        return -1;
    }

    real_path = lfs_vfs_trim_path(path ? path : "C");
    strncpy(scan->root, real_path ? real_path : "", sizeof(scan->root) - 1);
    scan->root[sizeof(scan->root) - 1] = '\0';

    ret = lfs_vfs_scan_collect(fsn, scan, scan->root, max_deepth ? (max_deepth - 1) : 0);
    if (ret < 0) {
        free(scan);
        return -1;
    }

    memset(fsn->filt_dir, 0, sizeof(fsn->filt_dir));
    fsn->file_number = scan->file_total;
    fsn->file_counter = 0;
    fsn->priv = scan;
    return 0;
}

static int __lfs_fscan_interrupt(struct vfscan *fsn, const char *path, u8 max_deepth,
                                 int (*callback)(void))
{
    int ret = __lfs_fscan(fsn, path, max_deepth);
    if (callback) {
        callback();
    }
    return ret;
}

static void __lfs_fscan_release(struct vfscan *fsn)
{
    if (!fsn) {
        return;
    }
    if (fsn->priv) {
        free(fsn->priv);
        fsn->priv = NULL;
    }
}

static int __lfs_fsel(struct vfscan *fsn, int sel_mode, FILE *file, int num)
{
    int index = -1;
    int ret;
    char full_path[LFS_VFS_PATH_MAX + 16];
    lfs_vfs_scan_ctx_t *scan;

    if (!fsn || !file || !fsn->priv) {
        return -1;
    }

    scan = (lfs_vfs_scan_ctx_t *)fsn->priv;
    if (!scan->file_total) {
        return -1;
    }

    switch (sel_mode) {
    case FSEL_FIRST_FILE:
        index = 0;
        break;
    case FSEL_LAST_FILE:
        index = scan->file_total - 1;
        break;
    case FSEL_NEXT_FILE:
        index = fsn->file_counter;
        if (index >= scan->file_total) {
            index = 0;
        }
        break;
    case FSEL_PREV_FILE:
        if (fsn->file_counter == 0) {
            index = scan->file_total - 1;
        } else {
            index = fsn->file_counter - 1;
        }
        break;
    case FSEL_CURR_FILE:
        index = (fsn->file_counter < scan->file_total) ? fsn->file_counter : 0;
        break;
    case FSEL_BY_NUMBER:
        if (num <= 0 || num > scan->file_total) {
            return -1;
        }
        index = num - 1;
        break;
    default:
        return -1;
    }

    snprintf(full_path, sizeof(full_path), "mnt/lfs/C/%s", scan->rel_paths[index]);
    ret = __lfs_fopen(file, full_path, "r");
    if (ret < 0) {
        return -1;
    }

    fsn->file_counter = index;
    return 0;
}

static int __lfs_ioctl(void *priv, int cmd, int arg)
{
    (void)priv;
    (void)cmd;
    (void)arg;
    return -1;
}

REGISTER_VFS_OPERATIONS(lfs_vfs_ops) = {
    .fs_type            = "lfs",
    .mount              = __lfs_mount,
    .unmount            = __lfs_unmount,
    .fget_free_space    = __lfs_fget_free_space,
    .fopen              = __lfs_fopen,
    .fread              = __lfs_fread,
    .fwrite             = __lfs_fwrite,
    .fseek              = __lfs_fseek,
    .flen               = __lfs_flen,
    .fpos               = __lfs_fpos,
    .fget_name          = __lfs_fget_name,
    .fget_path          = __lfs_fget_path,
    .frename            = __lfs_frename,
    .fclose             = __lfs_fclose,
    .fdelete            = __lfs_fdelete,
    .fscan              = __lfs_fscan,
    .fscan_interrupt    = __lfs_fscan_interrupt,
    .fscan_release      = __lfs_fscan_release,
    .fsel               = __lfs_fsel,
    .fget_attr          = __lfs_fget_attr,
    .fget_attrs         = __lfs_fget_attrs,
    .ftruncate          = __lfs_ftruncate,
    .ioctl              = __lfs_ioctl,
};

/* ---------------- minimal test code ---------------- */

static void lfs_vfs_plus_test_task(void *priv)
{
    struct imount *mt;
    FILE *fp;
    FILE sel_fp = {0};
    struct vfscan fsn = {0};
    char buf[128];
    u32 free_space = 0;
    int ret;

    (void)priv;
    os_time_dly(3);

    mt = mount(NULL, "mnt/lfs", "lfs", 0, NULL);
    if (!mt) {
        printf("[lfs_vfs] mount fail\n");
        goto __exit;
    }

    fp = fopen("mnt/lfs/C/dirA/dirB/dirC/test_auto.txt", "w+");
    if (!fp) {
        printf("[lfs_vfs] fopen auto mkdir fail\n");
        goto __exit;
    }

    fwrite("auto mkdir ok\n1234567890\n", 1, strlen("auto mkdir ok\n1234567890\n"), fp);
    fseek(fp, 0, SEEK_SET);
    ret = ftruncate(fp, 14);
    printf("[lfs_vfs] ftruncate ret=%d flen=%u\n", ret, flen(fp));
    fclose(fp);

    fp = fopen("mnt/lfs/C/dirA/dirB/dirC/test_auto.txt", "r");
    if (!fp) {
        printf("[lfs_vfs] reopen auto mkdir file fail\n");
        goto __exit;
    }

    memset(buf, 0, sizeof(buf));
    ret = fread(buf, 1, sizeof(buf) - 1, fp);
    printf("[lfs_vfs] read ret=%d data=%s\n", ret, buf);

    ret = frename(fp, "mnt/lfs/C/dirA/dirB/dirC/test_renamed.txt");
    printf("[lfs_vfs] frename ret=%d\n", ret);
    fclose(fp);

    fp = fopen("mnt/lfs/C/dirA/dirB/dirC/other.bin", "w+");
    if (fp) {
        fwrite("bin-data", 1, 8, fp);
        fclose(fp);
    }

    ret = fget_free_space("mnt/lfs", &free_space);
    printf("[lfs_vfs] free_space ret=%d space=%u\n", ret, free_space);

    memset(&fsn, 0, sizeof(fsn));
    strncpy(fsn.ftype, "txt", sizeof(fsn.ftype) - 1);
    ret = __lfs_fscan(&fsn, "mnt/lfs/C", 4);
    printf("[lfs_vfs] txt fscan ret=%d file_number=%u\n", ret, fsn.file_number);
    if (!ret && fsn.file_number) {
        ret = __lfs_fsel(&fsn, FSEL_FIRST_FILE, &sel_fp, 0);
        printf("[lfs_vfs] fsel first ret=%d\n", ret);
        if (!ret) {
            memset(buf, 0, sizeof(buf));
            ret = __lfs_fread(&sel_fp, buf, sizeof(buf) - 1);
            printf("[lfs_vfs] selected txt read ret=%d data=%s\n", ret, buf);
            __lfs_fclose(&sel_fp);
        }
        __lfs_fscan_release(&fsn);
    }

    fp = fopen("mnt/lfs/C/dirA/dirB/dirC/test_renamed.txt", "r");
    if (fp) {
        ret = fdelete(fp);
        printf("[lfs_vfs] fdelete txt ret=%d\n", ret);
    }

    fp = fopen("mnt/lfs/C/dirA/dirB/dirC/other.bin", "r");
    if (fp) {
        ret = fdelete(fp);
        printf("[lfs_vfs] fdelete bin ret=%d\n", ret);
    }

__exit:
    while (1) {
        os_time_dly(100);
    }
}

int lfs_vfs_plus_test(void)
{
    puts("lfs_vfs_plus_test\n");
    return thread_fork("lfs_vfs_plus_test", 11, 3072, 32, 0,
                       lfs_vfs_plus_test_task, NULL);
}

/* late_initcall(lfs_vfs_plus_test); */

#endif
