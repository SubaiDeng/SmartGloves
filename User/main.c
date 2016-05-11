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
<<<<<<< HEAD
#include "delay.h"
#include "key.h"
=======
>>>>>>> refs/remotes/origin/master
#include "bsp_DMA.h"

/**************************************************************
*        Global Value Define Section
**************************************************************/


u8 MPU_Data [33] = {0};

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
	SysTick_Config(SystemCoreClock / 1000);  //1ms中断一次
	LED_Init();
	USART1_Config();//串口1初始化
	USART2_Config();//串口2初始化,用于发送数据
	USART1_DMA_Config();//串口1用于DMA传输六轴模块数据		
	USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);
	KEY_Init();
	
	
	while(1)
	{
		ScanKey();
		printf("%s\n",MPU_Data);
		DelayMs(1500);
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

