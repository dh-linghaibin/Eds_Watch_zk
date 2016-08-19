
#ifndef __MENU_H
#define __MENU_H

#include "Type.h"

/**********************************************函数定义***************************************************** 
* 函数名称: void MenuInit(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能: 菜单参数初始化  
* 作    者: by lhb_steven
* 日    期: 2016/3/17
************************************************************************************************************/ 
void MenuInit(void);
/**********************************************函数定义***************************************************** 
* 函数名称: void MenuModeSet(u8 cmd) 
* 输入参数: u8 cmd 
* 返回参数: void  
* 功    能: 更新相应模式进入相应功能  
* 作    者: by lhb_steven
* 日    期: 2016/3/17
************************************************************************************************************/ 
void MenuModeSet(u8 cmd);
/**********************************************函数定义***************************************************** 
* 函数名称: void MenuServiceTime(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能: 菜单时间服务函数，主要用于后拨的自动换档  
* 作    者: by lhb_steven
* 日    期: 2016/3/18
************************************************************************************************************/ 
void MenuServiceTime(void);
/**********************************************函数定义***************************************************** 
* 函数名称: u8 MenuGetMode(void) 
* 输入参数: void 
* 返回参数: u8  
* 功    能: 模式状态  
* 作    者: by lhb_steven
* 日    期: 2016/3/26
************************************************************************************************************/ 
u8 MenuGetMode(void);
/**********************************************函数定义***************************************************** 
* 函数名称: void MenuSetBeind(u8 cmd) 
* 输入参数: u8 cmd 
* 返回参数: void  
* 功    能: 设置前拨档位  
* 作    者: by lhb_steven
* 日    期: 2016/6/2
************************************************************************************************************/ 
void MenuSetBeind(u8 cmd);

#endif


