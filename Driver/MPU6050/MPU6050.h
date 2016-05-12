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
extern u8 MPU_Data [33];	//存储MPU6050数据

extern float Axis[3];		//三个轴的加速度
extern float Angle[3];		//三个轴的角度
extern float Angular[3];	//三个轴的角速度
extern char  XShift;		//X轴位移
extern char  YShift;		//Y轴位移

/**************************************************************
*        Prototype Declare Section
**************************************************************/

/**
 * @brief  获得三个方向轴的角度
 * @param  
 * @retval None
 */
void Angle_DataTransfrom(void);

/**
 * @brief  得出三个方向轴的角速度
 * @param  
 * @retval None
 */
void Angular_DataTransFrom(void);

/**
 * @brief  得出三个方向轴的加速度
 * @param  
 * @retval None
 */
void Axis_DataTransfrom(void);

/**
 * @brief  处理获得的加速度，去除基准值
 * @param  
 * @retval None
 */
void Axis_GetFinalData(void);

/**
 * @brief  		处理旋转后加速度的消除平衡问题
 * @param  		void
 */
void DealWithRotation(void);

/**
 * @brief  		通过角速度来得出位移
 * @param  		void
 */
void GetShiftValues(void);
/**************************************************************
*        End-Multi-Include-Prevent Section
**************************************************************/
#endif


