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

/**************************************************************
*        Global Value Define Section
**************************************************************/
u32 TimeDelay;//��ʱ����

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
	
	while(1)
	{
		
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
