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
char leftKey;	//�ж�����Ƿ񱻰��£�1Ϊ���£�0Ϊ��
char rightKey;	//�ж��Ҽ��Ƿ񱻰��£�1Ϊ���£�0Ϊ��

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
 * @brief  ɨ��������Ұ����Ƿ���,��ʱ��갴��ʱ,��vcc��ͨ
 * @retval None
 */
void ScanKey(void)
{
	if(IS_LEFT_KEY_DOWN == SET)
	{
		DelayMs(5);
		leftKey = ((IS_LEFT_KEY_DOWN == SET) ? 1 : 0);
	}
	
	if(IS_RIGHT_KEY_DOWN == SET)
	{
		DelayMs(5);
		rightKey = ((IS_RIGHT_KEY_DOWN == SET) ? 1 : 0);
	}
}
