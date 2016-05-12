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
char XShift;//X��λ��
char YShift;//Y��λ��

/**************************************************************
*	Function Define Section
**************************************************************/
/**
 * @brief  �ó�����������ļ��ٶ�
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
				
//			Axis[0] = ((short)(MPU_Data[3 + i * 11] << 8 | MPU_Data[2 + i * 11])) / 32768.0 * 16;		//X����ٶ�	 
//			Axis[1] = ((short)(MPU_Data[5 + i * 11] << 8 | MPU_Data[4 + i * 11])) / 32768.0 * 16;    	//Y����ٶ�
//			Axis[2] = ((short)(MPU_Data[7 + i * 11] << 8 | MPU_Data[6 + i * 11])) / 32768.0 * 16;    	//Z����ٶ�		
		}
	}
}

/**
 * @brief  �ó�����������Ľ��ٶ�
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
					
//			Angular[0] = ((short)(MPU_Data[3 + i * 11] << 8 | MPU_Data[2 + i * 11])) / 32768.0 * 2000;		//X����ٶ�	 
//			Angular[1] = ((short)(MPU_Data[5 + i * 11] << 8 | MPU_Data[4 + i * 11])) / 32768.0 * 2000;		//Y����ٶ�
//			Angular[2] = ((short)(MPU_Data[7 + i * 11] << 8 | MPU_Data[6 + i * 11])) / 32768.0 * 2000;		//Z����ٶ�		
		}
	}
}

/**
 * @brief  �������������ĽǶ�
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
//			Angle[0] = ((short)(MPU_Data[3 + i * 11] << 8) | MPU_Data[2 + i * 11]) / 32768.0 * 180;	//X��Ƕ�
//			Angle[1] = ((short)(MPU_Data[5 + i * 11] << 8) | MPU_Data[4 + i * 11]) / 32768.0 * 180;	//Y��Ƕ�
//			Angle[2] = ((short)(MPU_Data[7 + i * 11] << 8) | MPU_Data[6 + i * 11]) / 32768.0 * 180;	//Z��Ƕ�
		}
	}
}

/**
 * @brief  �����õļ��ٶȣ�ȥ����׼ֵ
 * @param  
 * @retval None
 */
void Axis_GetFinalData(void)
{
	/*�ֱ��ý��ٶȺͼ��ٶȻ�׼ֵ*/
	Axis_DataTransfrom();
	Angle_DataTransfrom();
	Angular_DataTransFrom();
	
	/*������ٶȵĻ�׼ֵ*/
	DealWithRotation();
}

/**
 * @brief  		����X��Y��Z����ת��õ���ת����
 * @param  		matrix����ת���󣬴洢��ת�������
 * 				angleIndegree���Ƕȣ�����֪�Ķ�����ʽ��ʾ����Ҫת��Ϊ�� / n
 *				axis��	��ʾ�����ĸ���ת
 */
#define MATRIX( row, col ) matrix[ row * 3 + col ]
static void Rotate(float matrix[], float angleInDegree, float x, float y, float z)
{
	float alpha = angleInDegree / 180.0 * PI;	//���Ƕ�ת��Ϊ�� / n�ĸ�ʽ
	float Sin = sin(alpha);						
	float Cos = cos(alpha);						
	float translateValue = 1.0 - Cos;			//����ϵ��ֵ

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
 * @brief  		���վ���˷����о����ҳ˻�ø�������ת���λ��
 * @param  		matrix����ת���󣬴洢��ת�������
 *				coord��������󣬳�ʼʱ��λ������
 */
static void GetAcceleration(float matrix[9], float originCoord[3], float finalCoord[3])
{
	int i, j;
	for(i = 0; i < 3; ++i)
	{
		finalCoord[i] = 0.0;
		for(j = 0; j < 3; ++j)//�����ҳ�
		{
			finalCoord[i] += originCoord[j] * MATRIX(j, i);
		}
	}
}

/**
 * @brief  		������ת����ٶȵ�����ƽ������
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
		GetAcceleration(matrix, originCoord, FinalBaseAxis);	//���ν���õľ����е�ֵ�����ҳ�
		Rotate(matrix, Angle[1], 0.0, 1.0, 0.0);
		GetAcceleration(matrix, FinalBaseAxis, originCoord);	//������ԭ���Ƿ���洢���޸ģ���Ϊÿһ�ο��Խ���õ���Ϊ��һ�εĲ���
		Rotate(matrix, Angle[2], 0.0, 0.0, 1.0);
		GetAcceleration(matrix, originCoord, FinalBaseAxis);
		
		Axis[i] -= FinalBaseAxis[2];	//��ȥZ���(��Ϊ����������ļ��ٶ�)
	}
}

/**
 * @brief  		ͨ�����ٶ����ó�λ��
 * @param  		void
 */
void GetShiftValues(void)
{
	Angular_DataTransFrom();//��ȡ���ٶ�
	
	/*��ȡY��λ��*/
	if(fabs(Angular[0]) < FILTER)//���˽��ٶȹ����ֵ
	{
		YShift = (char)( Angular[0]/ PROPOTION );//��ȡY��ƫ��
	}
	else
	{
		YShift = 0;
	}
	
	/*��ȡX��λ��*/
	if(fabs(Axis[2]) < FILTER)//���˽��ٶȹ����ֵ
	{
		XShift = (char)(- (Angular[2] / PROPOTION));//��ȡX��ƫ��
	}
	else
	{
		YShift = 0;
	}
}

