#include "stm32f10x.h"
#include "bps_usart.h"

u32 TimeDelay;//��ʱ����

void delay(int k );
int main(void)
{
	//���ڳ�ʼ��
	USART1_Config();
	while(1)
	{
			printf("SmartGlove Test\n");
			delay(1500);
	}	
}


void delay(int k )
{
	while(k--)
	{
		int t = 12000;
		while(t--);
	}
}
