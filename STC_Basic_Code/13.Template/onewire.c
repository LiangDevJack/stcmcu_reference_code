/*
  ����˵��: ��������������
  �������: Keil uVision 4.10 
  Ӳ������: CT107��Ƭ���ۺ�ʵѵƽ̨(�ⲿ����12MHz) STC89C52RC��Ƭ��
  ��    ��: 2011-8-9
*/
#include "reg52.h"
#include <intrins.h>

sbit DQ = P1^4;  //�����߽ӿ�

////��������ʱ����
//void Delay_OneWire(unsigned int t)  //STC89C52RC
//{
//	while(t--);
//}

////ͨ����������DS18B20дһ���ֽ�
//void Write_DS18B20(unsigned char dat)
//{
//	unsigned char i;
//	for(i=0;i<8;i++)
//	{
//		DQ = 0;
//		DQ = dat&0x01;
//		Delay_OneWire(50);
//		DQ = 1;
//		dat >>= 1;
//	}
//	Delay_OneWire(50);
//}

////��DS18B20��ȡһ���ֽ�
//unsigned char Read_DS18B20(void)
//{
//	unsigned char i;
//	unsigned char dat;
//  
//	for(i=0;i<8;i++)
//	{
//		DQ = 0;
//		dat >>= 1;
//		DQ = 1;
//		if(DQ)
//		{
//			dat |= 0x80;
//		}	    
//		Delay_OneWire(50);
//	}
//	return dat;
//}

////DS18B20�豸��ʼ��
//bit init_ds18b20(void)
//{
//  	bit initflag = 0;
//  	
//  	DQ = 1;
//  	Delay_OneWire(120);
//  	DQ = 0;
//  	Delay_OneWire(800);
//  	DQ = 1;
//  	Delay_OneWire(100); 
//    initflag = DQ;     
//  	Delay_OneWire(50);
//  
//  	return initflag;
//}

/*

void Delay1us(unsigned int us)		//@11.0592MHz
{
	unsigned int i=0;
	for(i=0;i<us;i++)
	{
		_nop_();	_nop_();	_nop_();		
	}
}


//��������ʱ����
void Delay_OneWire(unsigned int t)  //STC89C52RC
{
	while(t--);
}

//ͨ����������DS18B20дһ���ֽ�
void Write_DS18B20(unsigned char dat)
{
	unsigned char j=0,k=20;		// k=20  Լ20����  1100  1100   0100 0100  
	unsigned char i;
	for(i=0;i<8;i++)
	{
		DQ = 1;
		Delay1us(5);
		DQ = 0;
		Delay1us(5);
		DQ = dat&0x01;
		Delay1us(40);
		DQ = 1;
		dat >>= 1;
	}
	Delay1us(80);
}

//��DS18B20��ȡһ���ֽ�
unsigned char Read_DS18B20(void)
{
	unsigned char j=0,k=20;		// k=20  Լ20����
	unsigned char i;
	unsigned char dat;
  
	for(i=0;i<8;i++)
	{
		DQ = 1;
		Delay1us(5);
		DQ = 0;
		Delay1us(5);
		dat >>= 1;
		DQ = 1;
		Delay1us(5);
		if(DQ)
		{
			dat |= 0x80;
		}	    
		Delay1us(30);
	}
	return dat;
}

//DS18B20�豸��ʼ��
bit init_ds18b20(void)
{
  	bit initflag = 1;
  	
  	DQ = 1;
  	Delay1us(120);
  	DQ = 0;
  	Delay1us(600);
  	DQ = 1;
  	Delay1us(50);
    initflag = DQ;     
  	Delay1us(120);
  
  	return initflag;
}
*/
void Delay1us(unsigned int us)		//@11.0592MHz
{
	unsigned int i=0;
	for(i=0;i<us;i++)
	{
		_nop_();	_nop_();	_nop_();		
	}
}

unsigned char Read_DS18B20(void)
{
	unsigned char dat;
	unsigned char i=0;
	for(i=0;i<8;i++)
	{
		DQ = 1;
		Delay1us(5);
		DQ = 0; 
		Delay1us(5);
		dat >>=1; 
		DQ = 1;
		Delay1us(5);
		if(DQ==1)
		{
			dat |= 0x80;  //0000 0000 | 1000 0000 = 1000 0000   
		}
		Delay1us(30);
	}
	return dat;
}


void Write_DS18B20(unsigned char dat)
{
	unsigned char i=0;
	for(i=0;i<8;i++)
	{
		DQ = 1;
		Delay1us(5);
		DQ = 0; 
		Delay1us(5);
		DQ = (dat & 0x01); // 1100 1100 & 0000 0001 = 0000 0000 
		Delay1us(40);
		dat >>=1; 
	}
	DQ = 1 ;
	Delay1us(80);
}

bit init_ds18b20(void)
{
	bit init_flag = 1;
	
	DQ =1 ;
	Delay1us(120);
	DQ =0 ;
	Delay1us(700);
	DQ =1 ;
	Delay1us(80);
	init_flag = DQ ;
	Delay1us(120);
	
	return init_flag;
}


unsigned long Temp_get(void)
{
	unsigned char low,high;
	unsigned int Temp;
	
	init_ds18b20();
	Write_DS18B20(0XCC);
	Write_DS18B20(0X44);
	Delay1us(200);
	
	init_ds18b20();
	Write_DS18B20(0XCC);
	Write_DS18B20(0XBE);
	
	low=Read_DS18B20();
	high=Read_DS18B20();
	
//	temp = high<<4 ;  //  ssss xxxx   = xxxx 0000 
//	temp |= (low>>4); 	// xxxx 0000  | XXXX XXXX >>4 = 0000 XXXX
	
	Temp=high&0X0F;  // SSSS  XXXX  
	Temp <<= 8;			//	Temp =Temp << 8;
	Temp |= low; 			// Temp =Temp | low;
	
	return Temp;
	
}



