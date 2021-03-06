/**************************************************************
*        Multi-Include-Prevent Section
**************************************************************/
#ifndef _LED_H
#define _LED_H

/**************************************************************
*        Include File Section
**************************************************************/
#include "stm32f10x.h"

/**************************************************************
*        Macro Define Section
**************************************************************/
#define LED GPIO_Pin_0
#define ON 1
#define OFF 0

/**************************************************************
*        Prototype Declare Section
**************************************************************/
void LED_Init(void);//初始化led
void LED_Control(uint16_t led, u8 ledStatus);//控制led，ledStatus为ON时点亮，为OFF时关闭

#endif
