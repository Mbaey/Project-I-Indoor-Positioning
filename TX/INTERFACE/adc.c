#include "adc.h"
#include "delay.h"		
#include "oled.h"
#include "stdio.h"

float adcx0,adcx1,adcx2,adcx3,adcx4,adcx5,adcx6,adcx7,adcx8;
char adcx0_buff[20],adcx1_buff[20],adcx2_buff[20],adcx3_buff[20],adcx4_buff[20],adcx5_buff[20],adcx6_buff[20],adcx7_buff[20],adcx8_buff[20];

														   
void ADC3_Init(void)
{    
  GPIO_InitTypeDef  			GPIO_InitStructure;
	ADC_CommonInitTypeDef 	ADC_CommonInitStructure;
	ADC_InitTypeDef       	ADC_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//ʹ��GPIOFʱ��
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE); //ʹ��ADC3ʱ��

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//ģ������
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;//����������
  GPIO_Init(GPIOF, &GPIO_InitStructure);//��ʼ��  
	
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
		delay_us(500);
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





