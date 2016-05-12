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
char leftKey;	//判断左键是否被按下，1为按下，0为否
char rightKey;	//判断右键是否被按下，1为按下，0为否

/**************************************************************
*	Function Define Section
**************************************************************/
/**
 * @brief  初始化鼠标按键
 * @retval None
 */
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Pin = LEFT_KEY | RIGHT_KEY;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	//按键上拉输入
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

/**
 * @brief  扫描鼠标左右按键是否按下,此时鼠标按下时,与vcc导通
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
