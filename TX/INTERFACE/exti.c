#include "exti.h"
#include "stm32f4xx.h"
#include "delay.h"
#include "pwm.h"
#include "oled.h"
#include "key.h"


u32 t,dir,angle;

void EXTI_KEY_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);				//ʹ��SYSCFGʱ��
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource9);	//����GPIO���ж��ߵ�ӳ���ϵ
	//�ṹ������
	EXTI_InitStructure.EXTI_Line=EXTI_Line9;											//�ж���1
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;							//����Ϊ�ж�ģʽ
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising_Falling;	//�����жϴ�����ʽ
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;												//ʹ���ж���
	EXTI_Init(&EXTI_InitStructure);																//��ʼ���ⲿ�ж�
	//�жϷ�������
	NVIC_InitStructure.NVIC_IRQChannel=EXTI9_5_IRQn;								//ʹ���ⲿ�ж�2
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x03;		//������ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x00;						//������Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;									//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);																//��ʼ���жϷ���
}

void EXTI9_5_IRQHandler(void)
{
	delay_ms(20);
	if (PGout(9)==0)
	{
		OLED_Clear();
		OLED_ShowString(0,0,"Select:");
		delay_ms(200);
		while(PGout(9)!=0&&PGout(11)!=0&&PGout(13)!=0);
		Mode_Switch();
	}
	EXTI_ClearITPendingBit(EXTI_Line9);
}
	

