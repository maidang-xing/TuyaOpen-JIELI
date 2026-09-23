
/**
  环境变量
    src:当前操作的控件
    find函数：查找当前页面的控件 参数：控件名称 xxx.xxx
    show函数：消息提醒  参数：text 提示文本
    
  控件属性
    name:控件的名称：xxx.xxx 只读
  disabled：是否禁止控件
  min：控件最小值：计数器型控件有效
  max：控件最大值：计数器型控件有效
  val：控件值
  options：下拉选择类控件有效,数组类型，子属性 ：value、label、disable、hide
  groupEnable:分组右上角的状态
  isUndo: 判断是否在执行撤销操作(只在src中可读)
  undoVal: 记录修改前的值，在src.isUndo为true时，可以修改groupEnable/val 为这个值
*/
/*
// 强关联项的直接写正反向操作即可正常撤销，如：if(a.val==1)b.val=1;if(a.val==0)b.val=0
// 弱关联项撤销例子： MSBC例子，在修改dest.val之前把旧val记录在dest.undoVal上,
if (src.name == '经典蓝牙.MSBC') {
  const dest = find('$板级配置.编码配置.MSBC')
  let undoVal = []
  if (dest.undoVal && Array.isArray(dest.undoVal)) undoVal = dest.undoVal

  if (src.isUndo) {//撤销操作
    dest.val = undoVal.pop()
  } else {
    undoVal.push(dest.val)
    dest.undoVal = undoVal

    //非撤销操作再判断脚本操作
    if (src.val == 1) {
      dest.val = 1;
    }
  }

}
//开关例子： 电源配置,时钟&电源.电源模式 受 时钟&电源.powerDown控制
if(src.name == '时钟&电源.powerDown'){
  const dest =  find('时钟&电源.电源模式');	
  if(!dest){
    return
  }
  dest.disabled=src.val;
	
}
// 下拉选择例子： 涓流电流 约束恒流电流
else if(src.name == '充电配置.涓流电流'){
  const dest =  find('充电配置.恒流电流');
    if(!dest){
    return
  }
  if(src.val==='30mA'){
    //选项禁止选择
    dest.options[1].disabled = true;
    //选项不显示
    dest.options[2].hide = false;
    // 修改值
    if(dest.val == '40mA' || dest.val =='30mA'){
      dest.val = '50mA'
    }
  }else {
    dest.options[1].disabled = false;
    dest.options[2].hide = true; 
  }	
}

//计数器例子
else if(src.name == '充电配置.开机充电'){
  const dest =  find('充电配置.入舱滤波时间(ms)');
	
  if(!dest){
    return
  }
  if(src.val){
    dest.min = 0;
    dest.max = 600;
  }else{
    dest.min = 10;
    dest.max = 65535;
  }	
  // 纠正值
  if(dest.val > dest.max){
    dest.val = dest.max;
  }else if(dest.val < dest.min){
    dest.val = dest.min;
  }
	
}

// 分组使能
else if(src.name =='充电配置'){
  const dest = find('智能仓');
  dest.groupEnable = !src.groupEnable;
}

// 消息提示

else if(src.name =='充电配置.入舱滤波时间(ms)'){
  if(src.val > 20){
    src.val = 20
    show('最大值不能超过20')
  }
}

else if (src.name == '内置触摸按键配置') {
  if (src.groupEnable == true) {
    const dest = find('内置触摸按键配置.键值') 
    if (dest) {
      dest.val = 'KEY_SLIDER'
    }
  }
	
}
*/

if (src.name == '第0段.Detect Mode') {
  const dest = find('第0段.Rms Time')
  if (dest) {
    if (src.val == 'PEAK') {
      dest.disabled = true;
    } else {
      dest.disabled = false;
    }
  }
}
if (src.name == '第0段.Effect Mode') {
  const dest = find('第0段.Max Enhance or Decay Gain')
  const dest2 = find('第0段.Ratio')
  if (dest) {
    if (src.val == 'ENHANCE') {
      dest.src.__config__.tip = "范围（0~30）dB"
      dest.min = 0;
      dest.max = 30;
      dest.val = 30;
    } else {
      dest.src.__config__.tip = "范围（-30~0）dB"
      dest.min = -30;
      dest.max = 0;
      dest.val = -30;
    }
  }
  if (dest2) {
    if (src.val == 'ENHANCE') {
      dest2.src.__config__.tip = "范围0.1~1"
      dest2.min = 0.1;
      dest2.max = 1;
      dest2.val = 1;
    } else {
      dest2.src.__config__.tip = "范围1~30"
      dest2.min = 1;
      dest2.max = 30;
      dest2.val = 30;
    }
  }
}
if (src.name == '第0段.Threshold') {
  const dest = find('第0段.Noisegate Threshold', true)
  if (dest) {
    if (src.val <= dest.val) {
      src.val = dest.val;
      show('Noisegae Threshold 应当比Threshold 小')
    }
  }
}
if (src.name == '第0段.Noisegate Threshold') {
  const dest = find('第0段.Threshold')
  if (dest) {
    if (src.val >= dest.val) {
      src.val = dest.val;
      show('Noisegae Threshold 应当比Threshold 小')
    }
  }
}

////////////////////////////////
if (src.name == '第1段.Detect Mode') {
  const dest = find('第1段.Rms Time')
  if (dest) {
    if (src.val == 'PEAK') {
      dest.disabled = true;
    } else {
      dest.disabled = false;
    }
  }
}
if (src.name == '第1段.Effect Mode') {
  const dest = find('第1段.Max Enhance or Decay Gain')
  const dest2 = find('第1段.Ratio')
  if (dest) {
    if (src.val == 'ENHANCE') {
      dest.src.__config__.tip = "范围（0~30）dB"
      dest.min = 0;
      dest.max = 30;
      dest.val = 30;
    } else {
      dest.src.__config__.tip = "范围（-30~0）dB"
      dest.min = -30;
      dest.max = 0;
      dest.val = -30;
    }
  }
  if (dest2) {
    if (src.val == 'ENHANCE') {
      dest2.src.__config__.tip = "范围0.1~1"
      dest2.min = 0.1;
      dest2.max = 1;
      dest2.val = 1;
    } else {
      dest2.src.__config__.tip = "范围1~30"
      dest2.min = 1;
      dest2.max = 30;
      dest2.val = 30;
    }
  }
}
if (src.name == '第1段.Threshold') {
  const dest = find('第1段.Noisegate Threshold', true)
  if (dest) {
    if (src.val <= dest.val) {
      src.val = dest.val;
      show('Noisegae Threshold 应当比Threshold 小')
    }
  }
}
if (src.name == '第1段.Noisegate Threshold') {
  const dest = find('第1段.Threshold')
  if (dest) {
    if (src.val >= dest.val) {
      src.val = dest.val;
      show('Noisegae Threshold 应当比Threshold 小')
    }
  }
}

////////////////////////////////
if (src.name == '第2段.Detect Mode') {
  const dest = find('第2段.Rms Time')
  if (dest) {
    if (src.val == 'PEAK') {
      dest.disabled = true;
    } else {
      dest.disabled = false;
    }
  }
}
if (src.name == '第2段.Effect Mode') {
  const dest = find('第2段.Max Enhance or Decay Gain')
  const dest2 = find('第2段.Ratio')
  if (dest) {
    if (src.val == 'ENHANCE') {
      dest.src.__config__.tip = "范围（0~30）dB"
      dest.min = 0;
      dest.max = 30;
      dest.val = 30;
    } else {
      dest.src.__config__.tip = "范围（-30~0）dB"
      dest.min = -30;
      dest.max = 0;
      dest.val = -30;
    }
  }
  if (dest2) {
    if (src.val == 'ENHANCE') {
      dest2.src.__config__.tip = "范围0.1~1"
      dest2.min = 0.1;
      dest2.max = 1;
      dest2.val = 1;
    } else {
      dest2.src.__config__.tip = "范围1~30"
      dest2.min = 1;
      dest2.max = 30;
      dest2.val = 30;
    }
  }
}
if (src.name == '第2段.Threshold') {
  const dest = find('第2段.Noisegate Threshold', true)
  if (dest) {
    if (src.val <= dest.val) {
      src.val = dest.val;
      show('Noisegae Threshold 应当比Threshold 小')
    }
  }
}
if (src.name == '第2段.Noisegate Threshold') {
  const dest = find('第2段.Threshold')
  if (dest) {
    if (src.val >= dest.val) {
      src.val = dest.val;
      show('Noisegae Threshold 应当比Threshold 小')
    }
  }
}

////////////////////////////////
if (src.name == '第3段.Detect mode') {
  const dest = find('第3段.Rms Time')
  if (dest) {
    if (src.val == 'PEAK') {
      dest.disabled = true;
    } else {
      dest.disabled = false;
    }
  }
}
if (src.name == '第3段.Effect Mode') {
  const dest = find('第3段.Max Enhance or Decay Gain')
  const dest2 = find('第3段.Ratio')
  if (dest) {
    if (src.val == 'ENHANCE') {
      dest.src.__config__.tip = "范围（0~30）dB"
      dest.min = 0;
      dest.max = 30;
      dest.val = 30;
    } else {
      dest.src.__config__.tip = "范围（-30~0）dB"
      dest.min = -30;
      dest.max = 0;
      dest.val = -30;
    }
  }
  if (dest2) {
    if (src.val == 'ENHANCE') {
      dest2.src.__config__.tip = "范围0.1~1"
      dest2.min = 0.1;
      dest2.max = 1;
      dest2.val = 1;
    } else {
      dest2.src.__config__.tip = "范围1~30"
      dest2.min = 1;
      dest2.max = 30;
      dest2.val = 30;
    }
  }
}
if (src.name == '第3段.Threshold') {
  const dest = find('第3段.Noisegate Threshold', true)
  if (dest) {
    if (src.val <= dest.val) {
      src.val = dest.val;
      show('Noisegae Threshold 应当比Threshold 小')
    }
  }
}
if (src.name == '第3段.Noisegate Threshold') {
  const dest = find('第3段.Threshold')
  if (dest) {
    if (src.val >= dest.val) {
      src.val = dest.val;
      show('Noisegae Threshold 应当比Threshold 小')
    }
  }
}

/////////////////////////////
//段与段之间算法类型的约束,跟随第0段
if (src.name == '第3段.Detect Mode') {
  const dest = find('第0段.Detect Mode')
  /* if (dest) { */
    // if (src.val != dest.val) {
      // src.val = dest.val;
      // show('算法类型跟随第0段')
    // }
  /* } */
  const dest_t = find('第3段.Rms Time')
  if (dest_t) {
    if (src.val == 'PEAK') {
      dest_t.disabled = true;
    } else {
      dest_t.disabled = false;
    }
  }
}
if (src.name == '第2段.Detect Mode') {
  const dest = find('第0段.Detect Mode')
  /* if (dest) { */
    // if (src.val != dest.val) {
      // src.val = dest.val;
      // show('算法类型跟随第0段')
    // }
  /* } */
  const dest_t = find('第2段.Rms Time')
  if (dest_t) {
    if (src.val == 'PEAK') {
      dest_t.disabled = true;
    } else {
      dest_t.disabled = false;
    }
  }
}
if (src.name == '第1段.Detect Mode') {
  const dest = find('第0段.Detect Mode')
  /* if (dest) { */
    // if (src.val != dest.val) {
      // src.val = dest.val;
      // show('算法类型跟随第0段')
    // }
  /* } */
  const dest_t = find('第1段.Rms Time')
  if (dest_t) {
    if (src.val == 'PEAK') {
      dest_t.disabled = true;
    } else {
      dest_t.disabled = false;
    }
  }
}

if (src.name == '第0段.Detect Mode') {
  const dest1 = find('第1段.Detect Mode')
  const dest2 = find('第2段.Detect Mode')
  const dest3 = find('第3段.Detect Mode')
/*   if (dest1) { */
    // if (dest1.val != src.val) {
      // dest1.val = src.val;
    // }
  // }
  // if (dest2) {
    // if (dest2.val != src.val) {
      // dest2.val = src.val;
    // }
  // }
  // if (dest3) {
    // if (dest3.val != src.val) {
      // dest3.val = src.val;
    // }
  /* } */
  const dest11 = find('第1段.Rms Time')
  const dest22 = find('第2段.Rms Time')
  const dest33 = find('第3段.Rms Time')
  if (dest11) {
    if (dest1.val == 'PEAK') {
      dest11.disabled = true;
    } else {
      dest11.disabled = false;
    }
  }
  if (dest22) {
    if (dest2.val == 'PEAK') {
      dest22.disabled = true;
    } else {
      dest22.disabled = false;
    }
  }
  if (dest33) {
    if (dest3.val == 'PEAK') {
      dest33.disabled = true;
    } else {
      dest33.disabled = false;
    }
  }
}

//显示隐藏脚本 status: 0 :显示 1：仅隐藏（不影响导出） 2:隐藏且不导出
if (src.name == 'Dynamic EQ.nSection') {
  let dest0 = find('第0段')
  let dest1 = find('第1段')
  let dest2 = find('第2段')
  let dest3 = find('第3段')

  if (src.val == 1) {
    if (dest0) {
      dest0.status = 0;
    }
    if (dest1) {
      dest1.status = 1;
    }
    if (dest2) {
      dest2.status = 1;
    }
    if (dest3) {
      dest3.status = 1;
    }
  }
  if (src.val == 2) {
    if (dest0) {
      dest0.status = 0;
    }
    if (dest1) {
      dest1.status = 0;
    }
    if (dest2) {
      dest2.status = 1;
    }
    if (dest3) {
      dest3.status = 1;
    }
  }
  if (src.val == 3) {
    if (dest0) {
      dest0.status = 0;
    }
    if (dest1) {
      dest1.status = 0;
    }
    if (dest2) {
      dest2.status = 0;
    }
    if (dest3) {
      dest3.status = 1;
    }
  }
  if (src.val == 4) {
    if (dest0) {
      dest0.status = 0;
    }
    if (dest1) {
      dest1.status = 0;
    }
    if (dest2) {
      dest2.status = 0;
    }
    if (dest3) {
      dest3.status = 0;
    }
  }

}
if (src.name == 'Dynamic EQ Ext Detector.nSection') {
  let dest0 = find('第0段')
  let dest1 = find('第1段')
  let dest2 = find('第2段')
  let dest3 = find('第3段')
  if (src.val == 1) {
    if (dest0) {
      dest0.status = 0;
    }
    if (dest1) {
      dest1.status = 1;
    }
    if (dest2) {
      dest2.status = 1;
    }
    if (dest3) {
      dest3.status = 1;
    }
  }
  if (src.val == 2) {
    if (dest0) {
      dest0.status = 0;
    }
    if (dest1) {
      dest1.status = 0;
    }
    if (dest2) {
      dest2.status = 1;
    }
    if (dest3) {
      dest3.status = 1;
    }
  }
  if (src.val == 3) {
    if (dest0) {
      dest0.status = 0;
    }
    if (dest1) {
      dest1.status = 0;
    }
    if (dest2) {
      dest2.status = 0;
    }
    if (dest3) {
      dest3.status = 1;
    }
  }
  if (src.val == 4) {
    if (dest0) {
      dest0.status = 0;
    }
    if (dest1) {
      dest1.status = 0;
    }
    if (dest2) {
      dest2.status = 0;
    }
    if (dest3) {
      dest3.status = 0;
    }
  }

}


//显示隐藏脚本 status: 0 :显示 1：仅隐藏（不影响导出） 2:隐藏且不导出
if (src.name == 'Spectrum Advance.nSection') {
	
  const maxSection = src.max
  const curSection = src.val
  
  for(let i = 0;i<maxSection;i++){
	  const dest = find("第"+i+"段")
      dest.status = i<curSection?0:1 
  }
}

var pattern = /^第[0-9]{1,2}段.Algorithm Type$/
if (pattern.test(src.name)) {
   // console.error('errr',src)
       const destName = src.name.replace('Algorithm Type','Rms Time')
       const dest = find(destName)
       if (dest){
           if (src.val == 'PEAK') {
               dest.disabled = true;
           } else {
               dest.disabled = false;
           }
       }
}
if (src.name == 'AEC回采配置.回采类型') {
  let dest0 = find('AEC回采配置.硬回采MIC选择')
  if (src.val == '软回采') {
	if (dest0) {
      dest0.status = 1;
    }  
  }
  if (src.val == '硬回采') {
    if (dest0) {
      dest0.status = 0;
    }
  }
}

console.error(src)
/////////////////////////////

if (src.name == 'Energy Detect.Mute Energy') {
  const dest = find('Energy Detect.Unmute Energy')
  if (dest) {
    if (src.val >= dest.val) {
      src.val = dest.val;
      show('Mute Energy 应当比Unmute Energy 小')
    }
  }
}
if (src.name == 'Energy Detect.Unmute Energy') {
  const dest = find('Energy Detect.Mute Energy')
  if (dest) {
    if (src.val <= dest.val) {
      src.val = dest.val;
      show('Mute Energy 应当比Unmute Energy 小')
    }
  }
}
if (src.name == 'Energy Detect.Mute Time(ms)') {
  const dest = find('Energy Detect.Count Cycle(ms)')
  if (dest) {
    if (src.val <= dest.val) {
      src.val = dest.val;
      show('Mute Time(ms) 应当比Count Cycle(ms) 大')
    }
  }
}
if (src.name == 'Energy Detect.Count Cycle(ms)') {
  const dest = find('Energy Detect.Mute Time(ms)')
  if (dest) {
    if (src.val >= dest.val) {
      src.val = dest.val;
      show('Mute Time(ms) 应当比Count Cycle(ms) 大')
    }
  }
}
if (src.name == 'CrossOver 3Band.低中分频点') {
  const dest = find('CrossOver 3Band.中高分频点')
  if (dest) {
    if (src.val >= dest.val) {
      src.val = dest.val;
      show('中高分频点应当比低中分频点大')
    }
  }
}
if (src.name == 'CrossOver 3Band.中高分频点') {
  const dest = find('CrossOver 3Band.低中分频点')
  if (dest) {
    if (src.val <= dest.val) {
      src.val = dest.val;
      show('中高分频点应当比低中分频点大')
    }
  }
}


if (src.name == 'Bass Treble.低音.Cur Gain') {
  const dest1 = find('Bass Treble.低音.Min Gain')
  const dest2 = find('Bass Treble.低音.Max Gain')
  if (dest1 && dest2) {
    src.min = dest1.val;
    src.max = dest2.val;
    if (src.val >= src.max) {
      src.val = src.max;
    }
    if (src.val <= src.min) {
      src.val = src.min;
    }
  }
}
if (src.name == 'Bass Treble.中音.Cur Gain') {
  const dest1 = find('Bass Treble.中音.Min Gain')
  const dest2 = find('Bass Treble.中音.Max Gain')
  if (dest1 && dest2) {
    src.min = dest1.val;
    src.max = dest2.val;
    if (src.val >= src.max) {
      src.val = src.max;
    }
    if (src.val <= src.min) {
      src.val = src.min;
    }
  }
}

if (src.name == 'Bass Treble.高音.Cur Gain') {
  const dest1 = find('Bass Treble.高音.Min Gain')
  const dest2 = find('Bass Treble.高音.Max Gain')
  if (dest1 && dest2) {
    src.min = dest1.val;
    src.max = dest2.val;
    if (src.val >= src.max) {
      src.val = src.max;
    }
    if (src.val <= src.min) {
      src.val = src.min;
    }
  }
}

if (src.name === '流程图.使能控制') {
   const moudle = src.moudle // 流程模块名称
   if(moudle=='pipeline-mic_effect'){
	 const dest = find('$功能配置.混响配置.混响使能')
	 dest.val = src.enable?0x01:0x00
   }
}

if (src.name === '混响配置.混响使能') {
   const dest = find('$麦克风音效') // 流程图模块   
   console.error('errr',dest)
   dest.enable = src.val 
   console.error('set enable',dest)
}

if ((src.name == '经典蓝牙.LHDC_V3/V4') || (src.name == '经典蓝牙.LHDC_V5')) {	
	if (src.val == 1) {
		show("未授权情况下仅支持播放10分钟", true);
	}
}

if (src.name == '调试串口.使能调试串口') {
	const dest = find('DEBUG相关配置.打印开关');
	if (!dest) {
		return;
		}
		
	if (src.val == 1 && dest.val == 0) {
		show('使能调试串口请确保打印开关已打开');
	}
}

if (src.name == 'FW编辑、在线调音.通信方式') {
	const dest = find('FW编辑、在线调音.USB后台模式使能');
	if (!dest) {
		return;
		}
		
	if (src.val == 'USB' && dest.val == 0) {
		show('启动在线调试请确保USB后台模式使能已打开');
	}
}

if (src.name == 'SD0配置.SD0固定组IO') {
  const dest = find('SD0配置.SD0_PORTS');
  if(!dest){
	return;
  }
  if(src.val == 'A') {
	dest.val = 'A';
  } else if(src.val == 'B') {
	dest.val = 'B';
  }else if(src.val == 'C') {
	dest.val = 'C';
  }else if(src.val == 'D') {
	dest.val = 'D';
  }
}
if (src.name == 'SD1配置.SD1固定组IO') {
  const dest = find('SD1配置.SD1_PORTS');
  if(!dest){
	return;
  }
  if(src.val == 'A') {
	dest.val = 'A';
  } else if(src.val == 'B') {
	dest.val = 'B';
  }
}

// 流程图分组切换
if (/^流程图\.分组切换\..+$/.test(src.name)) {
  const moudle = src.moudle // 流程模块名称
  let dest = find('$音频配置.DAC配置.声道配置');
  const group = src.name.replace('流程图.分组切换.','');
  if(group == '单声道' || group == '单声道pro') {
    //show('DAC声道配置切换到单声道')
    dest.val = '左声道';
    dest.options[0].disabled = false;
    dest.options[1].disabled = false;
    dest.options[2].disabled = false;
    dest = find('$音频配置.DAC配置.输出模式');
    if (dest) {
      dest.options[1].disabled = false;
      dest.options[2].disabled = false;
    }
  } else if(group == '立体声' || group == '立体声pro') {
    //show('DAC声道配置切换到双声道')
    dest.val = '双声道';
    dest.options[0].disabled = false;
    dest.options[1].disabled = false;
    dest.options[2].disabled = false;
    dest = find('$音频配置.DAC配置.输出模式');
    if (dest) {
      dest.options[1].disabled = false;
      dest.options[2].disabled = false;
    }
  }
  
}

//蓝牙HFP限制
if (src.name == '蓝牙协议.HFP') {
  const src1 = find('经典蓝牙.MSBC')
  const dest1 = find('$音频配置.编码配置.MSBC')
  const dest2 = find('$音频配置.编码配置.CVSD')
  if (src.val) {
    dest2.val = 1;
    if (src1.val == 1) {
      dest1.val = 1;
    }
  }
}

if (src.name == '经典蓝牙.MSBC') {
  const dest = find('$音频配置.编码配置.MSBC')
  let undoVal = []
  if (dest.undoVal && Array.isArray(dest.undoVal)) undoVal = dest.undoVal

  if (src.isUndo) {//撤销操作
    dest.val = undoVal.pop()
  } else {
    undoVal.push(dest.val)
    dest.undoVal = undoVal

    //非撤销操作再判断脚本操作
    if (src.val == 1) {
      dest.val = 1;
    }
  }

}

if (src.name == '编码配置.MSBC') {
  const dest1 = find('$蓝牙配置.蓝牙协议.HFP')
  const dest2 = find('$蓝牙配置.经典蓝牙.MSBC')
  if (!src.val && dest1.val && dest2.val) {
    src.val = 1;
    show('因蓝牙HFP配置不可关闭MSBC编码');
  }
}

if (src.name == '编码配置.CVSD') {
  const dest1 = find('$蓝牙配置.蓝牙协议.HFP')
  if (!src.val && dest1.val) {
    src.val = 1;
    show('因蓝牙HFP配置不可关闭CVSD编码');
  }
}

//蓝牙发射器使能同步
if (src.name == '经典蓝牙.蓝牙发射器使能') {
  const dest = find('蓝牙协议.HFP_AG')
  if (src.val) {
    dest.val = 1;
    show('已同步开启HFP_AG');
  } else {
    dest.val = 0;
    show('已同步关闭HFP_AG');
  }
}

if (src.name == '蓝牙协议.HFP_AG') {
  const dest = find('经典蓝牙.蓝牙发射器使能')
  if (src.val) {
    dest.val = 1;
    show('已同步打开蓝牙发射器');
  } else {
    dest.val = 0;
    show('已同步关闭蓝牙发射器');
  }
}

if (src.name == 'DAC配置.VCM电容') {
  const dest1 = find('DAC配置.音频供电档位')
  if (src.val == '不带电容') {
    dest1.options[4].disabled = true;
  } else {
    dest1.options[4].disabled = false;
  }
}

//----------------------------ADC供电选择逻辑控制------------------------------------------
if (src.name == 'MIC 0 配置.供电端口' || src.name == 'MIC 1 配置.供电端口') {
  const group = src.name.substring(0, 8)
  const dest_bias = find(group + '.MIC BIAS上拉电阻挡位');
  const dest_io = find(group + '.IO供电选择');
  // console.warn('group', group)
  dest_bias.disabled = true;
  dest_io.disabled = true;
  if (src.val == '其他（IO供电或外部供电）') {
    dest_io.disabled = false;
  } else if (src.val != 'MIC_LD0（PA0）') {
    dest_bias.disabled = false;
  }

}
//----------------------------音量配置逻辑控制------------------------------------------

if (src.name == '音量配置.最大音量等级') {
  const dest = find('音量配置.当前音量值')
  let p = find("音量配置");
  if (src.val != dest.max) {
      if (dest.val > src.val) {
          dest.val = src.val;
          p.children[6].val = dest.val;
      }
      dest.max = src.val;
      p.children[6].max = dest.max;
  }
}
if(src.name == '音量配置.当前音量值'){
    const dest = find("音量配置");
    const child5 = dest.children[5];
    const child6 = dest.children[6];
    child6.val = child5.val;

}
if(src.name == '音量配置.'){
    const dest = find("音量配置");
    const child5 = dest.children[5];
    const child6 = dest.children[6];
    child5.val = child6.val;
}




if(src.name == '音量配置.音量表类型'){
	const dest = find('音量表')
	const max_lvl = find('音量配置.最大音量等级')
	const max_vol = find('音量配置.最大音量(dB)')
	const min_vol = find('音量配置.最小音量(dB)')
	// 子控件数组
	let temp = min_vol.val
	if(src.val == '自定义'){
		dest.insert(0, max_lvl.val)

		dest.children[0].val = min_vol.val
		//dest.children[0].src.__config__.label = "音量等级1"
		for(let i = 1; i < (dest.size - 1); i++){
			dest.children[i].val = temp + (max_vol.val - min_vol.val) / max_lvl.val
			temp = dest.children[i].val
			//dest.children[i].src.__config__.label = "音量等级" + (i+1)
		}
		dest.children[dest.size - 1].val = max_vol.val
		//dest.children[dest.size - 1].src.__config__.label = "音量等级" + (dest.size - 1 +1)
	} else {
    if(dest.size > 0){
		  dest.remove(0, dest.size)
    }
	}
}

if(src.name == 'TWS.MAC地址'){
  if(src.val == "使用公共地址"){
    let p = find("TWS.单台连手机也能进行配对")
    p.val = 0;
    p.disabled = 1;
    p = find("TWS.两边同时按配对键进入配对")
    p.disabled = 0;
    p = find("TWS.自动主从切换")
    p.val = 0;
    p.disabled = 0;
    p = find("TWS.主从电量平衡")
    p.val = 0;
    p.disabled = 0;
  }else{
    let q = find("TWS.两边同时按配对键进入配对")
    q.val = 0;
    q.disabled = 1;
    q = find("TWS.单台连手机也能进行配对")
    q.val = 1;
    q.disabled = 0;
    q = find("TWS.自动主从切换")
    q.val = 0;
    q.disabled = 1;
    q = find("TWS.主从电量平衡")
    q.val = 0;
    q.disabled = 1;
    q = find("TWS.配对方式")
    q.val = '按键配对'
    q = find("TWS.同步关机")
    q.val = 1
  }
}

if(src.name == 'TWS.配对方式'){
  let p = find("TWS.MAC地址")
  if(p.val == "不使用公共地址" && src.val == "自动配对"){
    src.val = "按键配对"
    show("不使用公共地址只能选择按键配对", true)
  }
}

if(src.name == '音量配置.最大音量等级' ||src.name == '音量配置.最大音量(dB)'||src.name == '音量配置.最小音量(dB)' ){
  const vtype = find ('音量配置.音量表类型')
	const dest = find('音量表')
	const max_lvl = find('音量配置.最大音量等级')
	const max_vol = find('音量配置.最大音量(dB)')
	const min_vol = find('音量配置.最小音量(dB)')
	// 子控件数组
	let temp = min_vol.val
	if(vtype.val == '自定义'){
    if(dest.size > 0){
      dest.remove(0, dest.size)
    }
		dest.insert(0, max_lvl.val)
		dest.children[0].val = min_vol.val
		// dest.children[0].src.__config__.label = "音量等级1"
		for(let i = 1; i < (dest.size - 1); i++){
			dest.children[i].val = temp + (max_vol.val - min_vol.val) / max_lvl.val
			temp = dest.children[i].val
			// dest.children[i].src.__config__.label = "音量等级" + (i + 1)
		}
		dest.children[dest.size - 1].val = max_vol.val
		// dest.children[dest.size - 1].src.__config__.label = "音量等级" + (dest.size - 1 + 1)
	} else {
    //console.log('destSize',dest.size,dest)
    if(dest.size > 0){
		  dest.remove(0, dest.size)
    }
	}
}

//record mix 录音配置
if(src.name === '录音配置.混合录音使能'){
  const dest = find('$功能配置.录音配置.混合录音使能')
  if(dest.val) {
    show('使能录音已默认使能音频配置里的MP3和ADPCM编码开关', true)
    const mp3_enc_switch = find('$音频配置.编码配置.MP3')
    mp3_enc_switch.val = 1
    const adpcm_enc_switch = find('$音频配置.编码配置.ADPCM')
    adpcm_enc_switch.val = 1
    const mediaFlow = find('$媒体')
    mediaFlow.changeGroup('立体声-REC')
    const EscoFlow = find('$蓝牙通话')
    EscoFlow.changeGroup('立体声-REC')
    const MicEffectFlow = find('$麦克风音效')
    MicEffectFlow.changeGroup('立体声-REC')
    const RecordFlow = find('$录音')
    RecordFlow.changeGroup('立体声-REC')
    show('媒体、通话、混响、录音数据流均切为 立体声-REC')
  }
}

if(src.name === '流程图.分组切换.立体声-REC') {
  show('默认使能混合录音功能')
  const dest = find('$功能配置.录音配置.混合录音使能')
  dest.val = 1
  show('使能录音已默认使能音频配置里的MP3和ADPCM编码开关', true)
  const mp3_enc_switch = find('$音频配置.编码配置.MP3')
  mp3_enc_switch.val = 1
  const adpcm_enc_switch = find('$音频配置.编码配置.ADPCM')
  adpcm_enc_switch.val = 1
}

if (src.name == '第3段.High Threshold'||src.name == '第3段.Low Threshold'||src.name == '第3段.Gain') {
    const low = find('第3段.Low Threshold', true);  
    const high = find('第3段.High Threshold', true);  
    const gain = find('第3段.Gain');  
    if (high && low){
        low.max = high.val - 0.1;
        if (low.val >= low.max){
            low.val = low.max;
        }
    }

    if (gain && high && low){
        gain.max = high.val - low.val;  
        if(gain.val > gain.max){
            gain.val = gain.max;
        }
    }
} 
if (src.name == '第2段.High Threshold'||src.name == '第2段.Low Threshold'||src.name == '第2段.Gain') { 
    const low = find('第2段.Low Threshold', true);  
    const high = find('第2段.High Threshold', true);  
    const gain = find('第2段.Gain');  
    if (high && low){
        low.max = high.val - 0.1;
        if (low.val >= low.max){
            low.val = low.max;
        }
    }
    if (gain && high && low){
        gain.max = high.val - low.val;  
        if(gain.val > gain.max){
            gain.val = gain.max;
        }
    }
} 
if (src.name == '第1段.High Threshold'||src.name == '第1段.Low Threshold'||src.name == '第1段.Gain') { 
    const low = find('第1段.Low Threshold', true);  
    const high = find('第1段.High Threshold', true);  
    const gain = find('第1段.Gain');  
    if (high && low){
        low.max = high.val - 0.1;
        if (low.val >= low.max){
            low.val = low.max;
        }
    }
    if (gain && high && low){
        gain.max = high.val - low.val;  
        if(gain.val > gain.max){
            gain.val = gain.max;
        }
    } 
} 
if (src.name == '第0段.High Threshold'||src.name == '第0段.Low Threshold'||src.name == '第0段.Gain') {
        const low = find('第0段.Low Threshold', true);  
        const high = find('第0段.High Threshold', true);  
        const gain = find('第0段.Gain');  
        if (high && low){
            low.max = high.val - 0.1;
            if (low.val >= low.max){
                low.val = low.max;
            }
        }
        if (gain && high && low){
            gain.max = high.val - low.val;  
            if(gain.val > gain.max){
                gain.val = gain.max;
            }
        }
    
}
//显示隐藏脚本 status: 0 :显示 1：仅隐藏（不影响导出） 2:隐藏且不导出
if ((src.name == 'Dynamic EQ Pro.nSection') || (src.name == 'Dynamic EQ Pro Ext Detector.nSection') || (src.name == 'Frequency Compressor.nSection')) {
  let dest0 = find('第0段');
  let dest1 = find('第1段');
  let dest2 = find('第2段');
  let dest3 = find('第3段');
  if (src.val == 1) {
    if (dest0) {

      dest0.status = 0;
    }
    if (dest1) {
      dest1.status = 1;
    }
    if (dest2) {
      dest2.status = 1;
    }
    if (dest3) {
      dest3.status = 1;
    }
  }
  if (src.val == 2) {
    if (dest0) {
      dest0.status = 0;
    }
    if (dest1) {
      dest1.status = 0;
    }
    if (dest2) {
      dest2.status = 1;
    }
    if (dest3) {
      dest3.status = 1;
    }
  }
  if (src.val == 3) {
    if (dest0) {
      dest0.status = 0;
    }
    if (dest1) {
      dest1.status = 0;
    }
    if (dest2) {
      dest2.status = 0;
    }
    if (dest3) {
      dest3.status = 1;
    }
  }
  if (src.val == 4) {
    if (dest0) {
      dest0.status = 0;
    }
    if (dest1) {
      dest1.status = 0;
    }
    if (dest2) {
      dest2.status = 0;
    }
    if (dest3) {
      dest3.status = 0;
    }
  }
}


if (src.name == '高级配置.Type') {
  const dest = find('StereoMtapsEcho.Repeat Time')
  if (dest) {
    if (src.val == 'FIR') {
      dest.disabled = false;
    } else {
      dest.disabled = true;
    }
  }
}

if (src.name === '流程图.位宽切换') {
  const moudle = src.moudle // 流程模块名称
  const bitWidth =  src.bitWidth
  if(moudle=='pipeline-Media') {
    const dest = find('$USB Audio')
    if(!dest) {
      show('找不到USB Audio')
      return
    }
    dest.bitWidth = bitWidth
    show('USB Audio位宽切换为' + bitWidth + 'bit')
  } else if(moudle=='pipeline-PCAudio') {
    const dest = find('$媒体')
    if(!dest) {
      show('找不到媒体')
      return
    }
    dest.bitWidth = bitWidth
    show('媒体位宽切换为' + bitWidth + 'bit')
  }
}

//----------------------编码器节点配置控制---------------------------
if(src.name == '编码器参数配置.编码格式'){
	let dest0 = find('编码器参数配置.位宽')
	let dest1 = find('编码器参数配置.码率')
    let dest2 = find('编码器参数配置.声道')
	let dest3 = find('编码器参数配置.采样率')
	dest0.disabled = false;
	dest1.disabled = false;
	dest2.disabled = false;
	dest3.disabled = false;
	
	if (src.val == 'PCM') {
		if (dest0) {
			dest0.disabled = false;
			dest0.options[1].label = "定点24位";
			dest0.options[2].label = "定点32位";
			dest0.options[3].label = "浮点32位";
		}
		if (dest1) {
			dest1.status = 1;
		}	
	} else if (src.val == 'AMR'){
		if(dest0){
			dest0.val = "定点16位";
			dest0.disabled = true;
		}
		if(dest2){
			dest2.val = "单声道";
			dest2.disabled = true;
		}
	} else {
		if (dest1) {
			dest1.status = 0;
		}			
		
	}
}


if (src.name == 'CrossOver.多带数') {
  let dest0 = find('Low-Band')
  let dest1 = find('Mid-Band')
  let dest2 = find('High-Band')
  let dest3 = find('Full-Band')

  let dest_mid_freq = find('CrossOver.高分频点')
  let dest_low_freq = find('CrossOver.低分频点');

  if (src.val == 2) {
    if (dest0) {
      dest0.status = 0;
    }
    if (dest1) {
      dest1.status = 1;
    }
    if (dest2) {
      dest2.status = 0;
    }
    if (dest3) {
      dest3.status = 0;
    }
    if (dest_mid_freq){
        dest_mid_freq.status = 1;
    }
    if (dest_low_freq){
        dest_low_freq.max = 20000;
    }
  }
  if (src.val == 3) {
    if (dest0) {
      dest0.status = 0;
    }
    if (dest1) {
      dest1.status = 0;
    }
    if (dest2) {
      dest2.status = 0;
    }
    if (dest3) {
      dest3.status = 0;
    }

    if (dest_mid_freq){
        dest_mid_freq.status = 0;
        if (dest_low_freq){
            dest_low_freq.max = dest_mid_freq.val;
            if (dest_low_freq.val >= dest_mid_freq.val){
                dest_low_freq.val = dest_mid_freq.val ;
            }
        }
    }

  }
}

if (src.name == 'CrossOver.低分频点') {
    const dest = find('CrossOver.高分频点');
    const band = find('CrossOver.多带数');
    if (band.val  == 3){
        if (dest) {
            dest.min = src.val;
            if (src.val > dest.val) {
                src.val = dest.val;
                // show('高分频点应当比低分频点大');
            }
        }
    }
}
if (src.name == 'CrossOver.高分频点') {
    const dest = find('CrossOver.低分频点');
    const band = find('CrossOver.多带数');
    if (band.val  == 3){
        if (dest) {
            dest.max = src.val;
            if (src.val < dest.val) {
                src.val = dest.val;
                // show('高分频点应当比低分频点大');
            }
        }
    }
}

//单独录音模式
if(src.name === '录音配置.录音回播使能') {
  if(src.val) {
    show('使能录音回播功能请自行使能单独录音模式！！')
  }
}
if(src.name === 'APP模式配置.录音模式') {
  let dest1 = find("$音频配置.解码相关配置.通用解码格式.MP3")
  let dest2 = find("$音频配置.编码配置.MP3")
  let dest3 = find("$音频配置.编码配置.MP3格式选择")
  let dest4 = find("$音频配置.编码配置.ADPCM")
  if(src.val == 1) {
    show('录音模式打开时将自动使能:<br/>(1)使能MP3格式的编码和解码;<br/>(2)MP3编码格式选择MP2;<br/>(3)使能ADPCM编码;', true)
    dest1.val = 1;
    dest2.val = 1;
    dest3.val = 'MP2';
    dest4.val = 1;
  } else {
    show('录音模式关闭时将以下配置恢复默认:<br/>(1)关闭MP3格式的编码;<br/>(2)关闭ADPCM编码<br/>(3)如若有MP3格式或者ADPCM的编码需求，请自行打开;', true)
    dest2.val = 0;
    dest4.val = 0;
  }
}

//reverb
if ((src.name == 'Reverb.Buffer Param.EarlyReflection Bufsize Factor') 
        || (src.name == 'Reverb.LateReflection Param.LateReflection Pre Delay') ) {
    const srct = find('Reverb.Buffer Param.EarlyReflection Bufsize Factor')
    const dest = find('Reverb.LateReflection Param.LateReflection Pre Delay')
    if (dest && srct) { 
        dest.max = srct.val
        if (dest.val > srct.val) {
             dest.val= srct.val
        }
    } 
}


//-------------------------Pingpon Echo Delay ---------------------------
if (src.name == 'Pingpong Echo.Delay') {
    const dest = find('Pingpong Echo.Max Delay');
    if (dest) {
        src.max = dest.val;
        if (src.val > dest.val) {
            src.val = dest.val;
        }
    }
}
if (src.name == 'Pingpong Echo.Pre Delay') {
    const dest = find('Pingpong Echo.Max Delay');
    if (dest) {
        src.max = dest.val;
        if (src.val > dest.val) {
            src.val = dest.val;
        }
    }
}
if (src.name == 'Pingpong Echo.Max Delay') {
    const dest = find('Pingpong Echo.Delay');
    const dest2 = find('Pingpong Echo.Pre Delay');
    if (dest) {
        if (src.val < dest.val) {
            dest.val = src.val;
            dest.max = src.val;
        }
    }
    if (dest2) {
        if (src.val < dest2.val) {
            dest2.val = src.val;
            dest2.max = src.val;
        }
    }
}

/*
///-------------------------LE_AUDIO-------------------------
*/
if (src.name == '公共配置.le_audio 应用选择' && (src.val.find(v=>v==='LE_AUDIO_AURACAST_SINK_EN'))){
	
	let a = find("$BIS配置.BIS功能配置.广播角色")

	let b = find("$BIS配置.BIS功能配置.本地同步播放")
	

	if (src.val.find(v=>v==='LE_AUDIO_AURACAST_SOURCE_EN')){
		a.val = '不固定';
		show('开启AURACAST，请关闭BIS发送与接收使能，CIS主机与从机使能，注意查看广播是否固定角色')
	}else if (a.val != '接收端'){
		a.val = '接收端';
		b.val = 0;
		show('开启AURACAST，请关闭BIS发送与接收使能，CIS主机与从机使能。当前只开接收使能，自动固定为接收端角色')
	}
	
}

if (src.name == '公共配置.le_audio 应用选择' && (src.val.find(v=>v==='LE_AUDIO_AURACAST_SOURCE_EN'))){
	
	let a = find("$BIS配置.BIS功能配置.广播角色")

	let b = find("$BIS配置.BIS功能配置.本地同步播放")
	

	if (src.val.find(v=>v==='LE_AUDIO_AURACAST_SINK_EN')){
		a.val = '不固定';
		show('开启AURACAST，请关闭BIS发送与接收使能，CIS主机与从机使能，注意查看广播是否固定角色')
	}else if (a.val != '发送端'){
		a.val = '发送端';
		b.val = 1;
		show('开启AURACAST，请关闭BIS发送与接收使能，CIS主机与从机使能。当前只开发送使能，自动固定为发送端角色')
	}
	
}

/*
//----------------------LINEIN模式配置提示---------------------------
if (src.name == 'APP模式配置.LINEIN模式') {
  const dest = find('APP模式配置.LINEIN模式')  // linein模式功能打开后要使能对应的LINEIN检测配置,否则切换模式的时候可能出现死机
  if (dest.val) {
    show('LINEIN模式功能已打开, 需要在板级配置中使能对应的LINEIN检测配置和LINEIN配置!',true)
  } 
}
*/
