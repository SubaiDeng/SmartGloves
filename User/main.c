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
#include "delay.h"
#include "key.h"

/**************************************************************
*        Global Value Define Section
**************************************************************/

/**************************************************************
*        Prototype Declare Section
**************************************************************/
/**
 * @brief  		打包鼠标数据给串口
 * @param  		char *data:存储待发送数据
 * @retval 		void
 */
void PackDatasForBlueTooth(char *data);

/**************************************************************
*	Function Define Section
**************************************************************/
int main(void)
{
	SysTick_Config(SystemCoreClock/1000);  //1ms中断一次
	LED_Init();
	USART1_Config();//串口初始化
	KEY_Init();
	
	while(1)
	{
		ScanKey();
		
		//DelayMs(1500);
	}
}

/**
 * @brief  		打包鼠标数据给串口
 * @param  		char *data:存储待发送数据
 * @retval 		void
 */
void PackDatasForBlueTooth(char *data)
{
	*data++ = 'a';
	*data++ = 'a';
	*data++ = XShift;
	*data++ = YShift;
	*data++ = leftKey;
	*data   = rightKey;
}

