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
#define IS_LEFT_KEY_DOWN GPIO_ReadInputDataBit(GPIOC, LEFT_KEY)		//�ж�����Ƿ񱻰���
#define IS_RIGHT_KEY_DOWN GPIO_ReadInputDataBit(GPIOC, RIGHT_KEY)	//�ж��Ҽ��Ƿ񱻰���

/**************************************************************
*        Struct Define Section
**************************************************************/

/**************************************************************
*        Global Value Declare Section
**************************************************************/
extern u8 leftKey;	//�ж�����Ƿ񱻰��£�1Ϊ���£�0Ϊ��
extern u8 rightKey;	//�ж��Ҽ��Ƿ񱻰��£�1Ϊ���£�0Ϊ��
/**************************************************************
*        Prototype Declare Section
**************************************************************/
/**
 * @brief  ��ʼ����갴��
 * @retval None
 */
void KEY_Init(void);

/**
 * @brief  ɨ��������Ұ����Ƿ���
 * @retval None
 */
void ScanKey(void);

#endif
