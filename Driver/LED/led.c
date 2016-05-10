/**************************************************************
*	Include File Section
**************************************************************/
#include "led.h"

/**************************************************************
*	Function Define Section
**************************************************************/
//��ʼ��led
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	GPIO_InitStructure.GPIO_Pin = LED;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
}

//����led��ledStatusΪ1ʱ������Ϊ0ʱ�ر�
void LED_Control(uint16_t led, u8 ledStatus)
{
	if(ledStatus == 0)
	{
		GPIO_SetBits(GPIOE, led);
	}
	else
	{
		GPIO_ResetBits(GPIOE, led);
	}
}
