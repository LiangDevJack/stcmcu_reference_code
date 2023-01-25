#include<STC15F2K60S2.H>
#include<INTRINS.H>
#define uchar unsigned char;
#define uint unsigned int;

sbit SCK=P1^7;//U19
sbit SDA=P2^3;//数据线
sbit RST=P1^3;

uchar tap[]={0XC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XF8,0X80,0X90,0XBF,0XFF};
uchar yi,er,san,si,wu,liu,qi,ba;
bit S4,S5,S6,S7;
uchar tt;

uchar Init_Time[]={50,59,23,16,10,2,19};
uchar shijian[7];//赋予七个内容
void Write_Byte(unsigned char temp);
void Write_DS1302(unsigned char address,unsigned char dat);
void Display1(yi,er);
void Display2(san,si);
void Display3(wu,liu);
void Display4(qi,ba);
void DS1302_Init(void);
void DS1302_Get(void);
void Allinit(void);

unsigned char Read_DS1302(unsigned char address);

void Delayms(int ms);	
void main (void) 
{
	Allinit();
	DS1302_Init();
	yi=0;er=8;san=10;si=5;wu=9;liu=10;qi=5;ba=0;
	while(1)
	{
		DS1302_Get();
		yi=shijian[2]/10;er=shijian[2]%10;san=10;
		si=shijian[1]/10;wu=shijian[1]%10;liu=10;
		qi=11;ba=11;
		tt++;
		if(tt==100)
		{
			tt=0;
			qi=shijian[0]/10;
			ba=shijian[0]%10;
			Delayms(5);
		}
		Display1(yi,er);
		Display2(san,si);
		Display3(wu,liu);
		Display4(qi,ba);
	}
}
	
void Write_Byte(unsigned char temp)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		SCK=0;
		SDA=temp&0X01;
		temp>>=1;
		SCK=1;
	}
}
void Write_DS1302(unsigned char address,unsigned char dat)
{
	
	RST=0;
	_nop_();
	SCK=0;
	_nop_();
	RST=1;
	Write_Byte(address);
	Write_Byte(((dat/10)<<4)|(dat%10));//向左移四位；变为高四位
}
unsigned char Read_DS1302(unsigned char address)
{
	unsigned char i,temp,dat1,dat2;
	RST=0;
	_nop_();
	SCK=0;
	_nop_();
	RST=1;
	Write_Byte(address);
	
	for(i=0;i<8;i++)
	{
		SCK=0;
		temp>>=1;
		if(SDA)temp|=0X80;
		SCK=1;
	}
	SDA=0;//没有上拉电阻，利于稳定需要置零
	dat1=temp/16;//高四位的值
	dat2=temp%16;
	temp=dat1*10+dat2;
	
	return temp;
}

void DS1302_Init(void)
{
	unsigned char i,add;
	add=0X80;
	Write_DS1302(0X8E,0X00);
	for(i=0;i<7;i++)//七个地址
		{
			Write_DS1302(add,Init_Time[i]);
			add=add+2;
		}
		Write_DS1302(0X8E,0X80);
}
 
void DS1302_Get(void)
{
	unsigned char i,add;
	add=0X81;
	Write_DS1302(0X8E,0X00);
	for(i=0;i<7;i++)
		{
			shijian[i]=Read_DS1302(add);
			add=add+2;
		}
	Write_DS1302(0X8E,0X80);
}

void Display1(yi,er)//数码管
{
	P2=0XC0;
	P0=0X01;//0000 0001
	P2=0XE0;
	P0=tap[yi];
	Delayms(1);
	
	P2=0XC0;
	P0=0X02;
	P2=0XE0;
	P0=tap[er];
	Delayms(1);
}
void Display2(san,si)
{
	P2=0XC0;
	P0=0X04;
	P2=0XE0;
	P0=tap[san];
	Delayms(1);
	
	P2=0XC0;
	P0=0X08;
	P2=0XE0;
	P0=tap[si];
	Delayms(1);
}
void Display3(wu,liu)
{
	P2=0XC0;
	P0=0X10;
	P2=0XE0;
	P0=tap[wu];
	Delayms(1);
	
	P2=0XC0;
	P0=0X20;
	P2=0XE0;
	P0=tap[liu];
	Delayms(1);
}
void Display4(qi,ba)
{
	P2=0XC0;
	P0=0X40;//0100 0000
	P2=0XE0;
	P0=tap[qi];
	Delayms(1);
	
	P2=0XC0;
	P0=0X80;
	P2=0XE0;
	P0=tap[ba];
	Delayms(1);
}
void Allinit(void)
{
	P2=0XA0;//打开控制蜂鸣器的573
	P0=0X00;//关闭蜂鸣器继电器
	
	P2=0XC0;//打开控制数码管的位选573
	P0=0XFF;//选中所有的数码管
	P2=0XE0;//打开控制数码管段选573
	P0=0XFF;//关闭所有数码管
	
	P2=0X80;//打开控制LED灯的573
	P0=0XFF;//关闭所有LED灯
}

void Delayms (int ms)
{
	int i,j;
	for(i=0;i<ms;i++)
		for(j=845;j>0;j--);
}







































