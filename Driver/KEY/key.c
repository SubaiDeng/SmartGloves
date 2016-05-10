/***************************************************************************************
 *	FileName					:	key.c
 *	CopyRight					:	Zoisite
 *	ModuleName					:	key
 *
 *	CPU							:	stm32f107vc
 *	RTOS						:
 *
 *	Create Date					:	2016/5/10
 *	Author/Corportation			:	Zoisite
 *
 *	Abstract Description		:	a series of operations for key
 *
 *--------------------------------Revision History--------------------------------------
 *	No	version		Date			Revised By			Item			Description
 *		1			2016/5/10		maple				Smartglove		create this file
 *
 ***************************************************************************************/
 
/**************************************************************
*	Include File Section
**************************************************************/
#include "key.h"

/**************************************************************
*	Debug switch Section
**************************************************************/

/**************************************************************
*        Global Value Define Section
**************************************************************/
u8 leftKey;	//�ж�����Ƿ񱻰��£�1Ϊ���£�0Ϊ��
u8 rightKey;//�ж��Ҽ��Ƿ񱻰��£�1Ϊ���£�0Ϊ��

/**************************************************************
*	Function Define Section
**************************************************************/
/**
 * @brief  ��ʼ����갴��
 * @retval None
 */
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Pin = LEFT_KEY | RIGHT_KEY;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	//������������
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

/**
 * @brief  ɨ��������Ұ����Ƿ���
 * @retval None
 */
void ScanKey(void)
{
	if(IS_LEFT_KEY_DOWN)
	{
		DelayMs(5);
		leftKey = ((IS_LEFT_KEY_DOWN == RESET) ? 0 : 1);
	}
	
	if(IS_RIGHT_KEY_DOWN)
	{
		DelayMs(5);
		rightKey = ((IS_RIGHT_KEY_DOWN == RESET) ? 0 : 1);
	}
}
