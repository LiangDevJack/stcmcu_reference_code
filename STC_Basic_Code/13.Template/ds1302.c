/*
  程序说明: DS1302驱动程序
  软件环境: Keil uVision 4.10 
  硬件环境: CT107单片机综合实训平台 8051，12MHz
  日    期: 2011-8-9
*/

#include <reg52.h>
#include <intrins.h>


unsigned char shijian[7] = {35,59,23,26,11,5,21};
unsigned char Get_Time[7];


sbit SCK = P1^7;		
sbit SDA = P2^3;		
sbit RST = P1^3;   // DS1302复位												

// void Write_Ds1302(unsigned  char temp) 
// {
// 	unsigned char i;
// 	for (i=0;i<8;i++)     	
// 	{ 
// 		SCK=0;
// 		SDA=temp&0x01;
// 		temp>>=1; 
// 		SCK=1;
// 	}
// }   

// void Write_Ds1302_Byte( unsigned char address,unsigned char dat )     
// {
//  	RST=0;	_nop_();
//  	SCK=0;	_nop_();
//  	RST=1; 	_nop_();  
//  	Write_Ds1302(address);	
//  	Write_Ds1302(dat);		
//  	RST=0; 
// }

// unsigned char Read_Ds1302_Byte ( unsigned char address )
// {
//  	unsigned char i,temp=0x00;
//  	RST=0;	_nop_();
//  	SCK=0;	_nop_();
//  	RST=1;	_nop_();
//  	Write_Ds1302(address);
//  	for (i=0;i<8;i++) 	
//  	{		
// 		SCK=0;
// 		temp>>=1;	
//  		if(SDA)
//  		temp|=0x80;	
//  		SCK=1;
// 	} 
//  	RST=0;	_nop_();
//  	SCK=0;	_nop_();
// 	SCK=1;	_nop_();
// 	SDA=0;	_nop_();
// 	SDA=1;	_nop_();
// 	return (temp);			
// }



void Write_Ds1302_Byte(unsigned char add,unsigned dat)
{
	unsigned char i;
	unsigned char temp;

	RST = 0 ; _nop_();
	SCK = 0 ; _nop_();
	RST = 1 ; _nop_();

	temp = add ;
	for(i=0;i<8;i++)
	{
		SCK = 0 ;_nop_();
		SDA = temp & 0x01 ; 
		temp >>=1 ;
		SCK = 1 ;_nop_();
	}

	temp = dat ;
	for(i=0;i<8;i++)
	{
		SCK = 0 ;_nop_();
		SDA = temp & 0x01 ; 
		temp >>=1 ;
		SCK = 1 ;_nop_();
	}

	RST = 0 ; 
}


unsigned char  Read_Ds1302_Byte(unsigned char add)
{
	unsigned char temp,dat;
	unsigned char i;

	RST = 0 ; _nop_();
	SCK = 0 ; _nop_();
	RST = 1 ; _nop_();	
	temp = add ;
	for(i=0;i<8;i++)
	{
		SCK = 0 ;
		SDA = temp & 0x01 ; 
		temp >>=1 ;
		SCK = 1 ;
	}

	for(i=0;i<8;i++)
	{
		SCK = 0 ;
		dat >>=1;
		if(SDA==1) dat |=0x80;   // 1000 0000 
		SCK = 1; 
	}
	RST = 0 ;_nop_();
	SCK = 0 ;_nop_();
	SDA = 0 ;_nop_();

	return dat;
}



void DS_init(void)
{
	unsigned char i,add;
	add=0x80;
	Write_Ds1302_Byte(0X8E,0X00);
	for(i=0;i<7;i++)
	{
		Write_Ds1302_Byte(add,(shijian[i]/10<<4)|(shijian[i]%10));
		add = add + 2 ;
	}
	Write_Ds1302_Byte(0X8E,0X80);
}

void DS_get(void)
{
	unsigned char i,add,dat;
	add=0x81;
	for(i=0;i<7;i++)
	{
		dat = Read_Ds1302_Byte(add);
		Get_Time[i] = dat/16*10+dat%16;
		add = add + 2 ;
	}
}

