#ifndef __BSPATCH_USER_H__
#define __BSPATCH_USER_H__

#include <stdint.h>
#include "cpu.h"

//差分换用用户接口，用于JL差分打包工具打包后固件做差分还原

//错误码
#define BSPATCH_RET_NONE                                             0

#define BSPATCH_RET_USER_BASE                                      (BSPATCH_RET_NONE + 200)
#define BSPATCH_RET_USER_NO_INIT                                   (BSPATCH_RET_USER_BASE + 1) //未初始化
#define BSPATCH_RET_USER_READ_HEAD_ERR                             (BSPATCH_RET_USER_BASE + 2) //读取差分包头失败
#define BSPATCH_RET_USER_CHECK_HEAD_ERR                            (BSPATCH_RET_USER_BASE + 3) //差分包头校验失败
#define BSPATCH_RET_USER_INIT_COMF_ERR                             (BSPATCH_RET_USER_BASE + 4) //初始化解压缩失败
#define BSPATCH_RET_USER_DIFF_SRC_ERR                              (BSPATCH_RET_USER_BASE + 5) //差分包校验错误
#define BSPATCH_RET_USER_DEINIT_COMF_ERR                           (BSPATCH_RET_USER_BASE + 6) //注销解压缩失败
#define BSPATCH_RET_USER_INIT_BSPATCH_ERR                          (BSPATCH_RET_USER_BASE + 7) //注销解差分还原失败
#define BSPATCH_RET_USER_OLD_NOT_MATCH                             (BSPATCH_RET_USER_BASE + 8) //旧固件不匹配
#define BSPATCH_RET_USER_INVAL_PARAM                               (BSPATCH_RET_USER_BASE + 9) //无效参数
#define BSPATCH_RET_USER_REINIT                                    (BSPATCH_RET_USER_BASE + 10) //重复初始化
#define BSPATCH_RET_USER_ALLOC_FAIL                                (BSPATCH_RET_USER_BASE + 11) //内存申请失败
#define BSPATCH_RET_USER_GET_DIFF_INFO_ERR                         (BSPATCH_RET_USER_BASE + 13) //获取差分包信息失败


/* 差分包的关键信息 */
struct bdiff_info {
    u32 u32BlockCount;  // 分块个数
    u32 u32BlockSize;   // 块大小
    u32 u32OldCrc;      // 旧版本固件数据校验码
    u32 u32OldLength;   // 旧版本数据长度
    u32 u32NewCrc;      // 新版本固件数据校验码
    u32 u32NewLength;   // 新版本数据长度
};

//差分流程句柄，用户获取并保留
struct bsuser_handle {
    struct bdiff_info info;
    void *priv; //可以保存用户的私有数据
};

/* 用户层差分还原文件操作集合 */
struct bspatch_user_ops {

    /**
    * @brief 读取差分包源数据回调函数，用户实现
    *
    * @param[in] handle 差分还原句柄
    * @param[in] buff   底层读取数据缓存
    * @param[in] offest 读取数据偏移量
    * @param[in] len    读取的长度
    * @retval           读取到数据长度
    */
    u32(*diff_src_read)(struct bsuser_handle *handle, u8 *buff, u32 off, u32 len);

    /**
    * @brief 获取旧固件回调函数，由用户申请提供读取buff，用户实现
    *
    * @param[in] handle 差分还原句柄
    * @param[out] buff  二级指针，应用申请获取旧固件缓存并传递给底层
    * @param[in] offest 读取数据偏移量
    * @param[in] len    读取的长度
    * @retval           读取到数据长度
    */
    u32(*old_src_request)(struct bsuser_handle *handle, u8 **buff, u32 off, u32 len);

    /**
    * @brief 与old_src_request配套旧固件读取完毕释放回调函数，用户实现
    *
    * @param[in] handle 差分还原句柄
    * @param[in] buff   返回在old_src_request中提供的buff基地址，底层用完告知应用释放
    * @retval           0代表成功，其他代表失败
    */
    int (*old_src_release)(struct bsuser_handle *handle, u8 *buff);
};

/**
* @brief 差分还原，初始化函数
*
* @param[in] handle     二级指针，初始化成功返回本次差分还原句柄，失败返回NULL
* @param[in] user_ops   用户层差分还原文件操作集合
* @param[in] priv       保存用户的私有数据，保存在handle->priv中
* @retval               成功返回0，其他则失败
*/
int bspatch_user_init(struct bsuser_handle **handle, const struct bspatch_user_ops *user_ops, void *priv);

/**
* @brief 差分还原，注销接口，注销本次差分还原流程的资源
*
* @param[in] handle     初始化时获取到的差分还原句柄
* @retval               成功返回0，其他则失败
*/
int bspatch_user_deinit(struct bsuser_handle *handle);

/**
* @brief 差分还原出新固件，新固件读取接口，任意读取
*
* @param[in] handle     初始化时获取到的差分还原句柄
* @param[in] buff       应用读取缓存
* @param[in] offest     读取数据偏移量
* @param[in] len        读取的长度
* @retval               成功返回读取长度，其他则失败
*/
int bspatch_user_new_read(struct bsuser_handle *handle, u8 *buff, u32 off, u32 length);

/**
* @brief 差分还原出新固件，新固件读取接口，任意读取，但读取缓存是底层提供，应用层不需要提供缓存
*
* @param[in] handle     初始化时获取到的差分还原句柄
* @param[out] buff      二级指针，底层新固件缓存，底层传递buff基地址给应用
* @param[in] offest     读取数据偏移量
* @param[in] len        读取的长度
* @retval               成功返回读取长度，其他则失败
*/
int bspatch_user_request_newblock(struct bsuser_handle *handle, u8 **buff, u32 off, u32 lenght);

/**
* @brief 与bspatch_user_request_newblock配套，用完了底层提供的新固件缓存后，释放掉
*
* @param[in] handle 差分还原句柄
* @param[in] buff   返回在bspatch_user_request_newblock中提供的新固件buff基地址，应用使用完及时释放
* @retval           0代表成功，其他代表失败
*/
int bspatch_user_release_newblock(struct bsuser_handle *handle, u8 *buff);

/**
* @brief 校验差分包的正确性，可选使用该函数
*
* @param[in] handle 差分还原句柄
* @retval           0代表成功，其他差分包校验失败
*/
int bspatch_user_diff_package_check(struct bsuser_handle *handle);

/**
* @brief 校验旧固件是否与差分包匹配，可选使用该函数
*
* @param[in] handle 差分还原句柄
* @retval           0表示匹配，其他代表不匹配
*/
int bspatch_user_old_match(struct bsuser_handle *handle);

/**
* @brief 差分的crc校验算法，与打包工具crc算法一致
*
* @param[in] ptr 计算crc数据
* @param[in] len 数据长度
* @param[in] init 初始crc值
* @retval        0代表成功，其他差分包校验失败
*/
u32 bspatch_user_calcual_crc(void *ptr, u32 len, u32 init);

#endif




