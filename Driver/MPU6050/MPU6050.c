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
 *	Abstract Description		:	a series of operations for MPU6050
 *
 *--------------------------------Revision History--------------------------------------
 *	No	version		Date			Revised By			Item			Description
 *		1			2016/5/10		maple								create this file
 *
 ***************************************************************************************/
 
/**************************************************************
*	Include File Section
**************************************************************/
#include "MPU6050.h"

/**************************************************************
*	Debug switch Section
**************************************************************/

/**************************************************************
*        Global Value Define Section
**************************************************************/
extern u8 MPU_Data [33];
float Axis[3];
float Angle[3];
float Angular[3];
float FinalBaseAxis[3];
char XShift;//X轴位移
char YShift;//Y轴位移

/**************************************************************
*	Function Define Section
**************************************************************/
/**
 * @brief  得出三个方向轴的加速度
 * @param  
 * @retval None
 */
void Axis_DataTransfrom(void)
{
	int i, j;
	for(i = 0 ; i < 3; i++)
	{			
		if(MPU_Data[i * 11 + 1] == 0x51)
		{
			for(j = 0; j < 3; ++j)
				Axis[j] = ((short)(MPU_Data[3 + 2 * j + i * 11] << 8 | MPU_Data[2 + j * 2 + i * 11])) / 32768.0 * 16;
				
			return;
				
//			Axis[0] = ((short)(MPU_Data[3 + i * 11] << 8 | MPU_Data[2 + i * 11])) / 32768.0 * 16;		//X轴加速度	 
//			Axis[1] = ((short)(MPU_Data[5 + i * 11] << 8 | MPU_Data[4 + i * 11])) / 32768.0 * 16;    	//Y轴加速度
//			Axis[2] = ((short)(MPU_Data[7 + i * 11] << 8 | MPU_Data[6 + i * 11])) / 32768.0 * 16;    	//Z轴加速度		
		}
	}
}

/**
 * @brief  得出三个方向轴的角速度
 * @param  
 * @retval None
 */
void Angular_DataTransFrom(void)
{
	int i, j;
	for(i = 0 ; i < 3; i++)
	{			
		if(MPU_Data[i * 11 + 1] == 0x52)
		{
			for(j = 0; j < 3; ++j)
				Angular[j] = ((short)(MPU_Data[3 + 2 * j + i * 11] << 8 | MPU_Data[2 + j * 2 + i * 11])) / 32768.0 * 2000;
					
		return;
					
//			Angular[0] = ((short)(MPU_Data[3 + i * 11] << 8 | MPU_Data[2 + i * 11])) / 32768.0 * 2000;		//X轴角速度	 
//			Angular[1] = ((short)(MPU_Data[5 + i * 11] << 8 | MPU_Data[4 + i * 11])) / 32768.0 * 2000;		//Y轴角速度
//			Angular[2] = ((short)(MPU_Data[7 + i * 11] << 8 | MPU_Data[6 + i * 11])) / 32768.0 * 2000;		//Z轴角速度		
		}
	}
}

/**
 * @brief  获得三个方向轴的角度
 * @param  
 * @retval None
 */
void Angle_DataTransfrom(void)
{
	int i, j;
	for(i = 0; i < 3; i++)
	{
		if(MPU_Data[i * 11 + 1] == 0x53)
		{
			for(j = 0; j < 3; ++j)
				Angle[j] = ((short)(MPU_Data[3 + 2 * j + i * 11] << 8 | MPU_Data[2 + j * 2 + i * 11])) / 32768.0 * 180;
					
			return;
//			Angle[0] = ((short)(MPU_Data[3 + i * 11] << 8) | MPU_Data[2 + i * 11]) / 32768.0 * 180;	//X轴角度
//			Angle[1] = ((short)(MPU_Data[5 + i * 11] << 8) | MPU_Data[4 + i * 11]) / 32768.0 * 180;	//Y轴角度
//			Angle[2] = ((short)(MPU_Data[7 + i * 11] << 8) | MPU_Data[6 + i * 11]) / 32768.0 * 180;	//Z轴角度
		}
	}
}

/**
 * @brief  处理获得的加速度，去除基准值
 * @param  
 * @retval None
 */
void Axis_GetFinalData(void)
{
	/*分别获得角速度和加速度基准值*/
	Axis_DataTransfrom();
	Angle_DataTransfrom();
	Angular_DataTransFrom();
	
	/*处理加速度的基准值*/
	DealWithRotation();
}

/**
 * @brief  		按照X、Y或Z轴旋转后得到旋转矩阵
 * @param  		matrix：旋转矩阵，存储旋转后的数据
 * 				angleIndegree：角度，以熟知的度数方式表示，需要转换为π / n
 *				axis：	表示绕着哪个轴转
 */
#define MATRIX( row, col ) matrix[ row * 3 + col ]
static void Rotate(float matrix[], float angleInDegree, float x, float y, float z)
{
	float alpha = angleInDegree / 180.0 * PI;	//将角度转换为π / n的格式
	float Sin = sin(alpha);						
	float Cos = cos(alpha);						
	float translateValue = 1.0 - Cos;			//矩阵系数值

	MATRIX(0, 0) = translateValue * x * x + Cos;
	MATRIX(0, 1) = translateValue * x * y + Sin * z;
	MATRIX(0, 2) = translateValue * x * z - Sin * y;
	MATRIX(1, 0) = translateValue * x * y - Sin * z;
	MATRIX(1, 1) = translateValue * y * y + Cos;
	MATRIX(1, 2) = translateValue * y * z + Sin * x;
	MATRIX(2, 0) = translateValue * x * z + Sin * y;
	MATRIX(2, 1) = translateValue * y * z - Sin * x;
	MATRIX(2, 2) = translateValue * z * z + Cos;
}

/**
 * @brief  		按照矩阵乘法进行矩阵右乘获得各个轴旋转后的位置
 * @param  		matrix：旋转矩阵，存储旋转后的数据
 *				coord：坐标矩阵，初始时的位置坐标
 */
static void GetAcceleration(float matrix[9], float originCoord[3], float finalCoord[3])
{
	int i, j;
	for(i = 0; i < 3; ++i)
	{
		finalCoord[i] = 0.0;
		for(j = 0; j < 3; ++j)//矩阵右乘
		{
			finalCoord[i] += originCoord[j] * MATRIX(j, i);
		}
	}
}

/**
 * @brief  		处理旋转后加速度的消除平衡问题
 * @param  		void
 */
void DealWithRotation(void)
{
	float matrix[9] = {0.0};
	float originCoord[3];
	int i, j;
	
	for(i = 0; i < 3; ++i)
	{
		for(j = 0; j < 3; ++j)
			originCoord[j] = 0.0;
		
		originCoord[i] = 1.0;
		
		Rotate(matrix, Angle[0], 1.0, 0.0, 0.0);
		GetAcceleration(matrix, originCoord, FinalBaseAxis);	//依次将获得的矩阵中的值进行右乘
		Rotate(matrix, Angle[1], 0.0, 1.0, 0.0);
		GetAcceleration(matrix, FinalBaseAxis, originCoord);	//交换的原因是方便存储和修改，因为每一次可以将获得的作为下一次的参数
		Rotate(matrix, Angle[2], 0.0, 0.0, 1.0);
		GetAcceleration(matrix, originCoord, FinalBaseAxis);
		
		Axis[i] -= FinalBaseAxis[2];	//减去Z轴的(其为其重力方向的加速度)
	}
}

/**
 * @brief  		通过角速度来得出位移
 * @param  		void
 */
void GetShiftValues(void)
{
	Angular_DataTransFrom();//获取角速度
	
	/*获取Y轴位移*/
	if(fabs(Angular[0]) < FILTER)//过滤角速度过大的值
	{
		YShift = (char)( Angular[0]/ PROPOTION );//获取Y轴偏移
	}
	else
	{
		YShift = 0;
	}
	
	/*获取X轴位移*/
	if(fabs(Axis[2]) < FILTER)//过滤角速度过大的值
	{
		XShift = (char)(- (Angular[2] / PROPOTION));//获取X轴偏移
	}
	else
	{
		YShift = 0;
	}
}

