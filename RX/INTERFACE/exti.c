//#include "exti.h"
//#include "stm32f4xx.h"
//#include "delay.h"
//#include "pwm.h"
//#include "ServoControl.h"

//u32 t,dir,angle;

//void EXTI_PulseCnt_Init(void)
//{
//	NVIC_InitTypeDef   NVIC_InitStructure;
//	EXTI_InitTypeDef   EXTI_InitStructure;
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);				//ʹ��SYSCFGʱ��
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource1);	//����GPIO���ж��ߵ�ӳ���ϵ
//	//�ṹ������
//	EXTI_InitStructure.EXTI_Line=EXTI_Line1;											//�ж���1
//	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;							//����Ϊ�ж�ģʽ
//	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising;					//�����жϴ�����ʽ
//	EXTI_InitStructure.EXTI_LineCmd=ENABLE;												//ʹ���ж���
//	EXTI_Init(&EXTI_InitStructure);																//��ʼ���ⲿ�ж�
//	//�жϷ�������
//	NVIC_InitStructure.NVIC_IRQChannel=EXTI1_IRQn;								//ʹ���ⲿ�ж�2
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x03;		//������ռ���ȼ�
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x00;						//������Ӧ���ȼ�
//	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;									//ʹ���ⲿ�ж�ͨ��
//	NVIC_Init(&NVIC_InitStructure);																//��ʼ���жϷ���
//}

//void EXTI1_IRQHandler(void)
//{
//	t++;
//	if (t>=AngleControl(360))
//	{
//		TIM_Cmd(TIM4,DISABLE);
//		delay_ms(100);
//		t=0;
//		TIM_Cmd(TIM4,ENABLE);
//		if (dir==1)
//			dir=0;
//		else if (dir==0)
//			dir=1;
//		DirControl(dir);
//	}
//	EXTI_ClearITPendingBit(EXTI_Line1);
//}
//	

