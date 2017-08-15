#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h" 
	 

/*����ķ�ʽ��ͨ��ֱ�Ӳ����⺯����ʽ��ȡIO*/
#define KEY0 		GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_9 ) //PG9
#define KEY1 		GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_6) //PG11
#define KEY2 		GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_4) //PG13
#define KEY3  	GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2) //PG15


#define KEY0_PRES 	0
#define KEY1_PRES	  1
#define KEY2_PRES	  2
#define KEY3_PRES   3

void KEY_Init(void);	//IO��ʼ��
void BOMA_Init(void);
int  KEY_Scan(int);  		//����ɨ�躯��	
void Mode_Switch(void);

#endif
