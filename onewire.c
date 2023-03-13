/*
  ����˵��: ��������������
  �������: Keil uVision 4.10 
  Ӳ������: CT107��Ƭ���ۺ�ʵѵƽ̨
  ��    ��: 2011-8-9
*/

#include "onewire.h"

//��������ʱ����
void Delay_OneWire(unsigned int t)
{
  while(t--);
}

//DS18B20оƬ��ʼ��
bit Init_DS18B20(void)
{
	bit initflag = 0;
	DQ = 1;
	Delay_OneWire(12);
	DQ = 0;
	Delay_OneWire(80); 		//��������480us����
	DQ = 1;									//Ȼ���ͷ�����
	Delay_OneWire(10); 			//�ȴ�15��60us
	initflag = DQ;    			//��ȡDS18B20�ĸ�λӦ���ź�
	Delay_OneWire(5);			//�ȴ�60��240us���ͷ�����
  
	return initflag;				//Ӧ���ź�Ϊ�͵�ƽ����ʾ��λ�ɹ�
}

//ͨ����������DS18B20дһ���ֽ�
void Write_DS18B20(unsigned char dat)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		DQ = 0;								//�Ƚ���������10~15us
		DQ = dat&0x01;				//������д������
		Delay_OneWire(5);		//ά��20��45us
		DQ = 1;								//�ͷ�����
		dat >>= 1;						//������һ������λ
	}
	Delay_OneWire(5);
}

//��DS18B20��ȡһ���ֽ�
unsigned char Read_DS18B20(void)
{
	unsigned char i;
	unsigned char dat;
  
	for(i=0;i<8;i++)
	{
		DQ = 0;								//�Ƚ���������10��15us
		dat >>= 1;						//����λ����
		DQ = 1;								//�ͷ�����
		if(DQ)								//��ȡ�����ϵ�����
		{
			dat |= 0x80;
		}	    
		Delay_OneWire(5);		//�ӳ�45us���ң��ٶ���һ������λ
	}
	return dat;
}