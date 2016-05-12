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

/**
 * @brief  		初始化操作
 * @param  		void
 * @retval 		void
 */
void InitConfig(void);

/**************************************************************
*	Function Define Section
**************************************************************/
int main(void)
{
	char data[6];
	int i;
	InitConfig();
	
	
	while(1)
	{
		
		ScanKey();
		GetShiftValues();
		PackDatasForBlueTooth(data);
		for(i = 0; i < 6; ++i)
		{
			putchar(data[i]);
		}
		printf("c%s\n", MPU_Data);
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
	*data++ = 0x52;
	*data++ = XShift;
	*data++ = YShift;
	*data++ = leftKey;
	*data   = rightKey;
	leftKey = rightKey = 0;//之前忘记清零了
}

/**
 * @brief  		初始化操作
 * @param  		void
 * @retval 		void
 */
void InitConfig(void)
{
	SysTick_Config(SystemCoreClock / 1000);  //1ms中断一次
	
	LED_Init();
	KEY_Init();
	
	USART1_Config();//串口1初始化,用于接收六轴数据
	USART2_Config();//串口2初始化,用于发送数据
	USART1_DMA_Config();//串口1用于DMA传输六轴模块数据		
	USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);
}
