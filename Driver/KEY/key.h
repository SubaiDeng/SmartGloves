/***************************************************************************************
 *	FileName					:	KEY.h
 *	CopyRight					:	Zoisite
 *	ModuleName					:	MPU6050
 *
 *	CPU							:	stm32f107vc
 *	RTOS						:
 *
 *	Create Date					:	2016/5/10
 *	Author/Corportation			:	Zoisite
 *
 *	Abstract Description		:	declare some prototypes, structs, include files 
 *									and define macro for KEY
 *
 *--------------------------------Revision History--------------------------------------
 *	No	version		Date			Revised By			Item			Description
 *		1			2016/5/10		maple				SmartGlove		Create this file
 *
 ***************************************************************************************/
/**************************************************************
*        Multi-Include-Prevent Section
**************************************************************/
#ifndef _KEY_H
#define _KEY_H

/**************************************************************
*        Debug switch Section
**************************************************************/

/**************************************************************
*        Include File Section
**************************************************************/
#include "stm32f10x.h"
#include "delay.h"

/**************************************************************
*        Macro Define Section
**************************************************************/
#define LEFT_KEY GPIO_Pin_2
#define RIGHT_KEY GPIO_Pin_0
#define IS_LEFT_KEY_DOWN GPIO_ReadInputDataBit(GPIOC, LEFT_KEY)		//判断左键是否被按下
#define IS_RIGHT_KEY_DOWN GPIO_ReadInputDataBit(GPIOC, RIGHT_KEY)	//判断右键是否被按下

/**************************************************************
*        Struct Define Section
**************************************************************/

/**************************************************************
*        Global Value Declare Section
**************************************************************/
extern u8 leftKey;	//判断左键是否被按下，1为按下，0为否
extern u8 rightKey;	//判断右键是否被按下，1为按下，0为否
/**************************************************************
*        Prototype Declare Section
**************************************************************/
/**
 * @brief  初始化鼠标按键
 * @retval None
 */
void KEY_Init(void);

/**
 * @brief  扫描鼠标左右按键是否按下
 * @retval None
 */
void ScanKey(void);

#endif
