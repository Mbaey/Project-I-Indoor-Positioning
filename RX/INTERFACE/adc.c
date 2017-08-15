#include "adc.h"
#include "delay.h"		
#include "oled.h"
#include "stdio.h"
#include "timer.h"

#define ADC_DATAS 100
#define _45Hz			93
#define _55Hz			75
#define _65Hz			64

struct ADC_PEAK
{
	u16	 	val;
	u16		num;
};
extern int a;
int Height_A[100]={0},Height_B[100]={0},Height_C[100]={0};
int HeightA_avg=0,HeightB_avg=0,HeightC_avg=0;

float adcx0,adcx1,adcx2,adcx3,adcx4,adcx5,adcx6,adcx7,adcx8;
char adcx0_buff[20],adcx1_buff[20],adcx2_buff[20],adcx3_buff[20],adcx4_buff[20],adcx5_buff[20],adcx6_buff[20],adcx7_buff[20],adcx8_buff[20];
int flag,i;
int A,B,C;
														   
void ADC3_Init(void)
{    
  GPIO_InitTypeDef  			GPIO_InitStructure;
	ADC_CommonInitTypeDef 	ADC_CommonInitStructure;
	ADC_InitTypeDef       	ADC_InitStructure;
	
//  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//ʹ��GPIOFʱ��
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE); //ʹ��ADC3ʱ��

//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//ģ������
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;//����������
//  GPIO_Init(GPIOF, &GPIO_InitStructure);//��ʼ��  
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//ģ������
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;//����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��  
 
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3,ENABLE);	  //ADC3��λ
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3,DISABLE);	//��λ����	 
 
	
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;//����ģʽ
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//���������׶�֮����ӳ�5��ʱ��
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //DMAʧ��
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;//Ԥ��Ƶ4��Ƶ��ADCCLK=PCLK2/4=84/4=21Mhz,ADCʱ����ò�Ҫ����36Mhz 
  ADC_CommonInit(&ADC_CommonInitStructure);//��ʼ��
	
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//12λģʽ
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;//��ɨ��ģʽ	
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//�ر�����ת��
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//��ֹ������⣬ʹ���������
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//�Ҷ���	
  ADC_InitStructure.ADC_NbrOfConversion = 1;//1��ת���ڹ��������� Ҳ����ֻת����������1 
  ADC_Init(ADC3, &ADC_InitStructure);//ADC��ʼ��
	
 
	ADC_Cmd(ADC3, ENABLE);//����ADת����	

}				  
//���ADCֵ
//ch: @ref ADC_channels 
//ͨ��ֵ 0~16ȡֵ��ΧΪ��ADC_Channel_0~ADC_Channel_16
//����ֵ:ת�����
u16 Get_Adc(u8 ch)   
{
	  	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC3, ch, 1, ADC_SampleTime_480Cycles);	//ADC3,ADCͨ��,480������,��߲���ʱ�������߾�ȷ��			    
  
	ADC_SoftwareStartConv(ADC3);		//ʹ��ָ����ADC3�����ת����������	
	 
	while(!ADC_GetFlagStatus(ADC3, ADC_FLAG_EOC ));//�ȴ�ת������

	return ADC_GetConversionValue(ADC3);	//�������һ��ADC3�������ת�����
}
//��ȡͨ��ch��ת��ֵ��ȡtimes��,Ȼ��ƽ�� 
//ch:ͨ�����
//times:��ȡ����
//����ֵ:ͨ��ch��times��ת�����ƽ��ֵ
u16 Get_Adc_Average(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ch);
//		delay_us(1);
	}
	return temp_val/times;
} 
	 

void Read_ADC_Datas(void)
{
	adcx0=Get_Adc_Average(ADC_Channel_0,20);
	adcx0=adcx0*(3.3/4096);

	adcx1=Get_Adc_Average(ADC_Channel_1,20);
	adcx1=adcx1*(3.3/4096);
	
	adcx2=Get_Adc_Average(ADC_Channel_2,20);
	adcx2=adcx2*(3.3/4096);

	adcx3=Get_Adc_Average(ADC_Channel_3,20);
	adcx3=adcx3*(3.3/4096);

	adcx4=Get_Adc_Average(ADC_Channel_4,20);
	adcx4=adcx4*(3.3/4096);

	adcx5=Get_Adc_Average(ADC_Channel_5,20);
	adcx5=adcx5*(3.3/4096);

	adcx6=Get_Adc_Average(ADC_Channel_6,20);
	adcx6=adcx6*(3.3/4096);

	adcx7=Get_Adc_Average(ADC_Channel_7,20);
	adcx7=adcx7*(3.3/4096);

	adcx8=Get_Adc_Average(ADC_Channel_14,20);
	adcx8=adcx8*(3.3/4096);
}

void ADC_Datas_Display(void)
{
	sprintf(adcx0_buff,"%.3fV",adcx0);
	OLED_ShowString(0,0,adcx0_buff);
	
	sprintf(adcx1_buff,"%.3fV",adcx1);
	OLED_ShowString(64,0,adcx1_buff);
	
	sprintf(adcx2_buff,"%.3fV",adcx2);
	OLED_ShowString(0,2,adcx2_buff);

	sprintf(adcx3_buff,"%.3fV",adcx3);
	OLED_ShowString(64,2,adcx3_buff);
	
	sprintf(adcx4_buff,"%.3fV",adcx4);
	OLED_ShowString(0,4,adcx4_buff);
	
	sprintf(adcx5_buff,"%.3fV",adcx5);
	OLED_ShowString(64,4,adcx5_buff);

	sprintf(adcx6_buff,"%.3fV",adcx6);
	OLED_ShowString(0,6,adcx6_buff);

	sprintf(adcx7_buff,"%.3fV",adcx7);
	OLED_ShowString(64,6,adcx7_buff);

//	sprintf(adcx8_buff,"%.3fV",adcx8);
//	OLED_ShowString(64,6,adcx8_buff);
}


void Get_Freq_Datas(void)
{
	int flag=1;
	int ADC_VAL_Cnt;
	A=0,B=0,C=0;
	struct ADC_PEAK ADC_MAX,ADC_MIN;
	float differ_A,differ_B,differ_C;

	int ADC_VAL[ADC_DATAS];
	TIM3_Timer_Init(4200-1,60000-1);
	flag=1;
	a=0;
	while(flag==1)
	{if(a==1)
		break ;
		for (ADC_VAL_Cnt=0;ADC_VAL_Cnt<ADC_DATAS-1;ADC_VAL_Cnt++)
		{
			ADC_VAL[ADC_VAL_Cnt]=Get_Adc_Average(ADC_Channel_0,10);
		}
		differ_A=100*(abs(ADC_VAL[0]-ADC_VAL[_45Hz])+abs(ADC_VAL[1]-ADC_VAL[_45Hz+1])+abs(ADC_VAL[2]-ADC_VAL[_45Hz+2]));
		differ_B=100*(abs(ADC_VAL[0]-ADC_VAL[_65Hz])+abs(ADC_VAL[1]-ADC_VAL[_65Hz+1])+abs(ADC_VAL[2]-ADC_VAL[_65Hz+2]));
		differ_C=100*(abs(ADC_VAL[0]-ADC_VAL[_55Hz])+abs(ADC_VAL[1]-ADC_VAL[_55Hz+1])+abs(ADC_VAL[2]-ADC_VAL[_55Hz+2]));
		differ_A=differ_A/3;
		differ_B=differ_B/3;
		differ_C=differ_C/3;
		
		//�ж�Ϊ45Hz
		if (differ_A<differ_B && differ_A<differ_C)
		{
			ADC_MAX.val=ADC_VAL[0],ADC_MAX.num=0;
			ADC_MIN.val=ADC_VAL[0],ADC_MIN.num=0;
			for(ADC_VAL_Cnt=0;ADC_VAL_Cnt<_45Hz-1;ADC_VAL_Cnt++)
			{
				if (ADC_VAL[ADC_VAL_Cnt]>ADC_MAX.val)
				{
					ADC_MAX.val=ADC_VAL[ADC_VAL_Cnt];
					ADC_MAX.num=ADC_VAL_Cnt;
				}
				if (ADC_VAL[ADC_VAL_Cnt]<ADC_MIN.val)
				{
					ADC_MIN.val=ADC_VAL[ADC_VAL_Cnt];
					ADC_MIN.num=ADC_VAL_Cnt;
				}
			}
			Height_A[A]=ADC_MAX.val-ADC_MIN.val;
			A++;
			printf("45Hz, ADC_MAX=%d, ADC_MIN=%d, Height=%d\r\n",ADC_MAX.val,ADC_MIN.val,ADC_MAX.val-ADC_MIN.val);
		}
		//�ж�Ϊ65Hz
		else if (differ_B<differ_A && differ_B<differ_C)
		{
			for(ADC_VAL_Cnt=0;ADC_VAL_Cnt<_65Hz-1;ADC_VAL_Cnt++)
			{
				if (ADC_VAL[ADC_VAL_Cnt]>ADC_MAX.val)
				{
					ADC_MAX.val=ADC_VAL[ADC_VAL_Cnt];
					ADC_MAX.num=ADC_VAL_Cnt;
				}
				if (ADC_VAL[ADC_VAL_Cnt]<ADC_MIN.val)
				{
					ADC_MIN.val=ADC_VAL[ADC_VAL_Cnt];
					ADC_MIN.num=ADC_VAL_Cnt;
				}
			}
			Height_B[B]=ADC_MAX.val-ADC_MIN.val;
			B++;
			printf("65Hz, ADC_MAX=%d, ADC_MIN=%d, Height=%d\r\n",ADC_MAX.val,ADC_MIN.val,ADC_MAX.val-ADC_MIN.val);
		}
		//�ж�Ϊ55Hz
		else if (differ_C<differ_A && differ_C<differ_B)
		{
			for(ADC_VAL_Cnt=0;ADC_VAL_Cnt<_55Hz-1;ADC_VAL_Cnt++)
			{
				if (ADC_VAL[ADC_VAL_Cnt]>ADC_MAX.val)
				{
					ADC_MAX.val=ADC_VAL[ADC_VAL_Cnt];
					ADC_MAX.num=ADC_VAL_Cnt;
				}
				if (ADC_VAL[ADC_VAL_Cnt]<ADC_MIN.val)
				{
					ADC_MIN.val=ADC_VAL[ADC_VAL_Cnt];
					ADC_MIN.num=ADC_VAL_Cnt;
				}
			}
			Height_C[C]=ADC_MAX.val-ADC_MIN.val;
			C++;
			printf("55Hz, ADC_MAX=%d, ADC_MIN=%d, Height=%d\r\n",ADC_MAX.val,ADC_MIN.val,ADC_MAX.val-ADC_MIN.val);
		}
		printf("%d %d %d\r\n",A,B,C);
	}
}
void Get_Heights(void)
{
	int i=0;
	for (i=0;i<(A-1);i++)
	{
		HeightA_avg+=Height_A[i];
	}
	HeightA_avg=HeightA_avg/(A-1);
	printf("%d\r\n",HeightA_avg);
	for (i=0;i<(B-1);i++)
	{
		HeightB_avg+=Height_B[i];
	}
	HeightB_avg=HeightB_avg/(B-1);
	printf("%d\r\n",HeightB_avg);
	for (i=0;i<(C-1);i++)
	{
		HeightC_avg+=Height_C[i];
	}
	HeightC_avg=HeightC_avg/(C-1);
	printf("%d\r\n",HeightC_avg);
	A=0,B=0,C=0;
}


void BorD(void)
{
	if (HeightA_avg>HeightB_avg || HeightC_avg>HeightB_avg)
	{
		OLED_Clear();
		OLED_ShowString(0,0,"B(UP)");
	}
	else if (HeightB_avg>HeightC_avg || HeightA_avg>HeightC_avg)
	{
		OLED_Clear();
		OLED_ShowString(0,0,"D(DOWN)");
	}
}

void CorE(void)
{
	if (HeightA_avg>HeightC_avg || HeightA_avg>HeightB_avg)
	{
		OLED_Clear();
		OLED_ShowString(0,0,"C(RIGHT)");
	}
	else 
	{
		OLED_Clear();
		OLED_ShowString(0,0,"E(LEFT)");
	}
}

//A 45Hz   B 65Hz   C 55Hz


