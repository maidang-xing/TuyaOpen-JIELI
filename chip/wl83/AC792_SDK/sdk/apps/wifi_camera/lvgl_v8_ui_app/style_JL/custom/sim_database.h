#include "app_config.h"
#ifdef CONFIG_UI_STYLE_JL_ENABLE
#ifndef __SIM_DATABASE_H_
#define __SIM_DATABASE_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "custom.h"



#define ARRAY_SIZE(array)  (sizeof(array)/sizeof(array[0]))

#define CN_PA   (('0' << 24) | ('A' << 16)  | (0xA9BE << 0))
#define CN_PB   (('0'    << 0) | ('0' << 8) | ('0' << 16) | ('0' << 24))

/*
 * ��Ƶ�ֱ���
 */
#define     VIDEO_RES_1080P         0
#define     VIDEO_RES_720P          1
#define     VIDEO_RES_VGA           2


/*
 * ������Ӧ������
 */
#define     GRA_SEN_OFF             0
#define     GRA_SEN_LO              1
#define     GRA_SEN_MD              2
#define     GRA_SEN_HI              3


/*
 * ������ʽ
 */
#define     TVM_PAL                 0
#define     TVM_NTSC                1


/*
* ���շֱ���
*/
#define     PHOTO_RES_VGA            0       /* 640*480 */
#define     PHOTO_RES_1M             1       /* 1280*720 */
#define     PHOTO_RES_2M             2       /* 1920*1080 */
#define     PHOTO_RES_3M             3       /* 2048*1552 */
#define     PHOTO_RES_4M             4       /* 2560*1552 */
#define     PHOTO_RES_5M             5       /* 2592*1968 */
#define     PHOTO_RES_6M             6       /* 3072*1968 */
#define     PHOTO_RES_7M             7       /* 2456*1968 */
#define     PHOTO_RES_8M             8       /* 3456*2448 */
#define     PHOTO_RES_9M             9       /* 3456*2592 */
#define     PHOTO_RES_10M            10      /* 3648*2736 */
#define     PHOTO_RES_11M            11      /* 4032*2736 */
#define     PHOTO_RES_12M            12      /* 4032*3024 */
#define     PHOTO_RES_16M            13      /* 5120*2880 */
#define     PHOTO_RES_24M            14      /* 6016*4090 */
#define     PHOTO_RES_32M            15      /* 7680*4352 */
#define     PHOTO_RES_64M            16      /* 10240*5760 */

/*
 * ͼƬ����
 */
#define     PHOTO_QUA_LO            0
#define     PHOTO_QUA_MD            1
#define     PHOTO_QUA_HI            2

/*
 * ͼ�����
 */
#define     PHOTO_ACU_LO            0
#define     PHOTO_ACU_MD            1
#define     PHOTO_ACU_HI            2

/*
 * ͼ���ƽ��
 */
#define     PHOTO_WBL_AUTO          0       /* �Զ� */
#define     PHOTO_WBL_SUN           1       /* �չ� */
#define     PHOTO_WBL_CLDY          2       /* ���� */
#define     PHOTO_WBL_TSL           3       /* ��˿�� */
#define     PHOTO_WBL_FLUL          4       /* ӫ��� */

/*
* ͼ��ɫ��
*/
#define     PHOTO_COLOR_NORMAL      0
#define     PHOTO_COLOR_WB          1
#define     PHOTO_COLOR_OLD         2


#if LV_USE_GUIBUILDER_SIMULATOR//���Է���ר��

struct db_cfg {
    const char *name;
    int len;
    int index;
    int value;
};

//��ȡָ���˵���
int db_select(const char *name);
//����ָ���˵���
int db_update(const char *name, uint32_t value);
//�ָ�Ĭ������--�û�������0~59
int db_reset(void);



#endif

#ifdef __cplusplus
}
#endif
#endif /* __SIM_DATABASE_H_ */


#endif
