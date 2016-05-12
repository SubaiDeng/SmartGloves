/***************************************************************************************
 *	FileName					:	MPU6050.c
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
 *									and define macro for MPU6050
 *
 *--------------------------------Revision History--------------------------------------
 *	No	version		Date			Revised By			Item			Description
 *		1			2016/5/10		maple2snow			SmartGlove		Create this file
 *
 ***************************************************************************************/
/**************************************************************
*        Multi-Include-Prevent Section
**************************************************************/
#ifndef _MPU6050_H
#define _MPU6050_H

/**************************************************************
*        Debug switch Section
**************************************************************/


/**************************************************************
*        Include File Section
**************************************************************/
#include "math.h"
#include "stm32f10x.h"

/**************************************************************
*        Macro Define Section
**************************************************************/
#define PI 3.1415926
#define Square(x) ((x) * (x))
#define IS_MPU_RUNNING (MPU_Data[0] == 0x55)
#define FILTER 300.0
#define PROPOTION 15.0

/**************************************************************
*        Struct Define Section
**************************************************************/

/**************************************************************
*        Global Value Declare Section
**************************************************************/
extern u8 MPU_Data [33];	//�洢MPU6050����

extern float Axis[3];		//������ļ��ٶ�
extern float Angle[3];		//������ĽǶ�
extern float Angular[3];	//������Ľ��ٶ�
extern char  XShift;		//X��λ��
extern char  YShift;		//Y��λ��

/**************************************************************
*        Prototype Declare Section
**************************************************************/

/**
 * @brief  �������������ĽǶ�
 * @param  
 * @retval None
 */
void Angle_DataTransfrom(void);

/**
 * @brief  �ó�����������Ľ��ٶ�
 * @param  
 * @retval None
 */
void Angular_DataTransFrom(void);

/**
 * @brief  �ó�����������ļ��ٶ�
 * @param  
 * @retval None
 */
void Axis_DataTransfrom(void);

/**
 * @brief  �����õļ��ٶȣ�ȥ����׼ֵ
 * @param  
 * @retval None
 */
void Axis_GetFinalData(void);

/**
 * @brief  		������ת����ٶȵ�����ƽ������
 * @param  		void
 */
void DealWithRotation(void);

/**
 * @brief  		ͨ�����ٶ����ó�λ��
 * @param  		void
 */
void GetShiftValues(void);
/**************************************************************
*        End-Multi-Include-Prevent Section
**************************************************************/
#endif


