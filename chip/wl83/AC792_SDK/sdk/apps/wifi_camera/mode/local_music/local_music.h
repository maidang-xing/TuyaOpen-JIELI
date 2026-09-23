#ifndef _APP_LOCAL_MUSIC_H_
#define _APP_LOCAL_MUSIC_H_

#include "music/music_player.h"

enum {
    MUSIC_TASK_START_BY_NORMAL,
    MUSIC_TASK_START_BY_BREAKPOINT,
    MUSIC_TASK_START_BY_SCLUST,
    MUSIC_TASK_START_BY_NUMBER,
    MUSIC_TASK_START_BY_PATH,
};

//*----------------------------------------------------------------------------*/
/**@brief    music 模式切换前参数设置
   @param    type:播放方式,暂时支持：
  				  MUSIC_TASK_START_BY_NORMAL：首次播放按照正常断点播放
				  MUSIC_TASK_START_BY_SCLUST：首次播放按照簇号播放
			 val:播放参数
   @note	 首次播放执行参考music_player_play_start接口
*/
/*----------------------------------------------------------------------------*/
void local_music_task_set_parm(u8 type, int val);

#endif

