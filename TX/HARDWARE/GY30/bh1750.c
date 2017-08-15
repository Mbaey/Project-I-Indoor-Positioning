#include "BH1750.h"
#include "myiic.h"
#include "delay.h"

float result_lx=0;

u8 BUF[2]={0};
u16 result=0;

//��ʼ��
void Init_BH1750(void)
{
	IIC_Init();
}

void Cmd_Write_BH1750(u8 cmd)
{
    IIC_Start();                  //��ʼ�ź�
    IIC_Send_Byte(BH1750_Addr+0);   //�����豸��ַ+д�ź�
	while(IIC_Wait_Ack());
    IIC_Send_Byte(cmd);    //�ڲ��Ĵ�����ַ
	while(IIC_Wait_Ack());
    //BH1750_SendByte(REG_data);       //�ڲ��Ĵ������ݣ�
    IIC_Stop();                   //����ֹͣ�ź�
	delay_ms(5);
}
void Start_BH1750(void)
{
	Cmd_Write_BH1750(BH1750_ON);	 //power on
	Cmd_Write_BH1750(BH1750_RSET);	//clear
	Cmd_Write_BH1750(LMODE_ONE);  //һ��H�ֱ���ģʽ������120ms��֮���Զ��ϵ�ģʽ  
}
void Read_BH1750(void)
{   	
    IIC_Start();                          //��ʼ�ź�
    IIC_Send_Byte(BH1750_Addr+1);         //�����豸��ַ+���ź�
	while(IIC_Wait_Ack());
	BUF[0]=IIC_Read_Byte(1);  //����ACK
	BUF[1]=IIC_Read_Byte(0);  //����NACK

    IIC_Stop();                          //ֹͣ�ź�
    delay_ms(5);
}
void Convert_BH1750(void)
{
	
	result=BUF[0];
	result=(result<<8)+BUF[1];  //�ϳ����ݣ�����������
	
	result_lx=(float)result/1.2;
}

void BH1750(void)
{
	Start_BH1750();
	delay_ms(30);
	Read_BH1750();
	Convert_BH1750();
}
