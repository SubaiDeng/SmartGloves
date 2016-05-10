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
#include "bsp_DMA.h"

/**************************************************************
*        Global Value Define Section
**************************************************************/
u32 TimeDelay;//��ʱ����


u8 MPU_Data [33] = {0};

/**************************************************************
*        Prototype Declare Section
**************************************************************/
void DelayMs(uint32_t nTime);

/**************************************************************
*	Function Define Section
**************************************************************/
int main(void)
{
	SysTick_Config(SystemCoreClock/1000);  //1ms�ж�һ��
	
	//����1����DMA��������ģ������
	USART1_Config();
	USART1_DMA_Config();		
	USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);
	
	//����2���ڷ�������
	USART2_Config();//���ڳ�ʼ��
	
	while(1)
	{
		printf("%s\n",MPU_Data);
		DelayMs(1500);
	}
}

/**
  * @˵��     ��ʱ����
  * @����     nTime: ��ʱʱ��
  * @����ֵ   None
  */
void DelayMs(uint32_t nTime)
{
    TimeDelay = nTime;
    while(TimeDelay != 0);
}

