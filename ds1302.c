/*-----------------------------------------------
  ���ƣ�DS1302ʱ��ģ����������
------------------------------------------------*/
#include "ds1302.h"
#include<reg52.h>
#include<intrins.h>

sbit SCK=P2^3;		
sbit SDA=P2^2;		
sbit RST=P2^4;

//��λ��
#define RST_CLR	RST=0//��ƽ�õ�
#define RST_SET	RST=1//��ƽ�ø�

//˫������
#define IO_CLR	SDA=0//��ƽ�õ�
#define IO_SET	SDA=1//��ƽ�ø�
#define IO_R	SDA  //��ƽ��ȡ

//ʱ���ź�
#define SCK_CLR	SCK=0//ʱ���ź�
#define SCK_SET	SCK=1//��ƽ�ø�

unsigned char cur_time_buf[8] = {20,20,8,5,0,0,0,3};	//��ʼ������ʱ������,���ϲ㴫���õĸ�ʽ�ַ���
																			

																			
/*------------------------------------------------
           ��DS1302д��һ�ֽ�����
------------------------------------------------*/
void Ds1302_Write_Byte(unsigned char addr, unsigned char d)
{

	unsigned char i;
	RST_SET;	
	
	//д��Ŀ���ַ��addr
	addr = addr & 0xFE;     //���λ����
	for (i = 0; i < 8; i ++) 
	    { 
		if (addr & 0x01) 
		    {
			IO_SET;
			}
		else 
		    {
			IO_CLR;
			}
		SCK_SET;
		SCK_CLR;
		addr = addr >> 1;
		}
	
	//д�����ݣ�d
	for (i = 0; i < 8; i ++) 
	   {
		if (d & 0x01) 
		    {
			IO_SET;
			}
		else 
		    {
			IO_CLR;
			}
		SCK_SET;
		SCK_CLR;
		d = d >> 1;
		}
	RST_CLR;					//ֹͣDS1302����
}
/*------------------------------------------------
           ��DS1302����һ�ֽ�����
------------------------------------------------*/

unsigned char Ds1302_Read_Byte(unsigned char addr) 
{

	unsigned char i;
	unsigned char temp;
	RST_SET;	

	//д��Ŀ���ַ��addr
	addr = addr | 0x01;//���λ�ø�
	for (i = 0; i < 8; i ++) 
	    {
	     
		if (addr & 0x01) 
		   {
			IO_SET;
			}
		else 
		    {
			IO_CLR;
			}
		SCK_SET;
		SCK_CLR;
		addr = addr >> 1;
		}
	
	//������ݣ�temp
	for (i = 0; i < 8; i ++) 
	    {
		temp = temp >> 1;
		if (IO_R) 
		   {
			temp |= 0x80;
			}
		else 
		   {
			temp &= 0x7F;
			}
		SCK_SET;
		SCK_CLR;
		}
	
	RST_CLR;	//ֹͣDS1302����
	return temp;
}

/*------------------------------------------------
            ��DS1302д��ʱ������
------------------------------------------------*/
void Ds1302_Write_Time(void) 
{
  unsigned char time_buf[8];
	unsigned char i,tmp;
	for(i=0;i<8;i++)
	{                  //BCD����
		tmp=cur_time_buf[i]/10;
		time_buf[i]=cur_time_buf[i]%10;
		time_buf[i]=time_buf[i]+tmp*16;
	}

	Ds1302_Write_Byte(ds1302_control_add,0x00);				//�ر�д���� 
	Ds1302_Write_Byte(ds1302_sec_add,0x80);						//��ͣ 
	//Ds1302_Write_Byte(ds1302_charger_add,0xa9);			//������ 
	Ds1302_Write_Byte(ds1302_year_add,time_buf[1]);		//�� 
	Ds1302_Write_Byte(ds1302_month_add,time_buf[2]);	//�� 
	Ds1302_Write_Byte(ds1302_date_add,time_buf[3]);		//�� 
	Ds1302_Write_Byte(ds1302_day_add,time_buf[7]);		//�� 
	Ds1302_Write_Byte(ds1302_hr_add,time_buf[4]);			//ʱ 
	Ds1302_Write_Byte(ds1302_min_add,time_buf[5]);		//��
	Ds1302_Write_Byte(ds1302_sec_add,time_buf[6]);		//��
	Ds1302_Write_Byte(ds1302_day_add,time_buf[7]);		//�� 
	Ds1302_Write_Byte(ds1302_control_add,0x80);				//��д���� 
}

/*------------------------------------------------
           ��DS1302����ʱ������
------------------------------------------------*/
void Ds1302_Read_Time(void)  
{ 
	unsigned char i,tmp;
	unsigned char time_buf[8];  //��������ʱ�����ܣ�ģ���ڲ�ʹ�õĸ�ʽ�ַ���
	time_buf[1]=Ds1302_Read_Byte(ds1302_year_add);		//�� 
	time_buf[2]=Ds1302_Read_Byte(ds1302_month_add);		//�� 
	time_buf[3]=Ds1302_Read_Byte(ds1302_date_add);		//�� 
	time_buf[4]=Ds1302_Read_Byte(ds1302_hr_add);		//ʱ 
	time_buf[5]=Ds1302_Read_Byte(ds1302_min_add);		//�� 
	time_buf[6]=(Ds1302_Read_Byte(ds1302_sec_add))&0x7F;//�� 
	time_buf[7]=Ds1302_Read_Byte(ds1302_day_add);		//�� 


	for(i=0;i<8;i++)
	{           //BCD����
		tmp=time_buf[i]/16;
		cur_time_buf[i]=time_buf[i]%16;
		cur_time_buf[i]=cur_time_buf[i]+tmp*10;
	}
}

/*------------------------------------------------
                DS1302��ʼ��
------------------------------------------------*/
void Ds1302_Init(void)
{
	RST_CLR;			//RST���õ�
	SCK_CLR;			//SCK���õ�
	Ds1302_Write_Byte(ds1302_sec_add,0x00);				 
}
