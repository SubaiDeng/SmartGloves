/***************************************************************************************
 *	FileName					:	main.c
 *	CopyRight					:	Zoisite
 *	ModuleName					:	main
 *
 *	CPU							:	stm32f107vc
 *	RTOS						:
 *
 *	Create Date					:	2016/5/10
 *	Author/Corportation			:	Zoisite
 *
 *	Abstract Description		:	main operation
 *
 *--------------------------------Revision History--------------------------------------
 *	No	version		Date			Revised By			Item			Description
 *		
 *
 ***************************************************************************************/
 
/**************************************************************
*	Include File Section
**************************************************************/
#include "stm32f10x.h"
#include "MPU6050.h"
#include "led.h"
#include "bsp_usart.h"

/**************************************************************
*        Global Value Define Section
**************************************************************/
u32 TimeDelay;//计时变量

/**************************************************************
*        Prototype Declare Section
**************************************************************/
void DelayMs(uint32_t nTime);

/**************************************************************
*	Function Define Section
**************************************************************/
int main(void)
{
	SysTick_Config(SystemCoreClock/1000);  //1ms中断一次

	
	USART1_Config();//串口初始化
	while(1)
	{
		printf("SmartGlove Test\n");
		DelayMs(1500);
	}
}

/**
  * @说明     延时函数
  * @参数     nTime: 延时时间
  * @返回值   None
  */
void DelayMs(uint32_t nTime)
{
    TimeDelay = nTime;
    while(TimeDelay != 0);
}


