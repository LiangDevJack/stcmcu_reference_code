/*流水灯点亮程序*/
/*#include<STC15F2K60S2.H>

void main (void)
{
	P2=0XA0;P0=0X00;P2=0X80;P0=0XFF;//初始化程序 

	P00=0;
	while(1);	
}	*/

/*LED灯闪烁程序*/
/*#include<STC15F2K60S2.H>
	unsigned int i;
 
void main (void)
{
	P2=0XA0;P0=0X80;P2=0X80;P0=0XFF;//初始化程序
	
	while(1)
		{	P00=0;
			for(i=0;i<65535;i++);
			P01=1;
			for(i=0;i<65535;i++);
		}
} */


/*#include<STC15F2K60S2.H>
	unsigned int i;
	
void main (void)
{
	P2=0XA0;P0=0X00;P2=0X80;P0=0XFF;//初始化程序
	
	while(1)
	{
		P00=0;
		for(i=0;i<65535;i++);
		P00=1;
		P01=0;
		for(i=0;i<65535;i++);
		P02=1;
		P03=0;
		for(i=0;i<65535;i++);
		P03=1;
		P04=0;
		for(i=0;i<65535;i++);
		P04=1;
		P05=0;
		for(i=0;i<65535;i++);
		P05=1;
		P06=0;
		for(i=0;i<65535;i++);
		P06=1;
		P07=0;
		for(i=0;i<65535;i++);
		P07=1;
	}
}
*/
	
	
//简易流水灯
/*#include<STC15F2K60S2.H>
	unsigned int i;
		
void main (void)
{
	P2=0XA0;P0=0X80;P2=0X80;P0=0XFF;//初始化程序
	
	P0=0XFE;					//1111 1110
	while(1);
}*/

/*#include<STC15F2K60S2.H>
	unsigned int i;
	
void main (void)
{
	P2=0XA0;P0=0X00;P2=0X80;P0=0XFE;//初始化程序
	
	while(1)
	{ P0=0XFE;							//1111 1110
		for(i=0;i<65535;i++);
		P0=0XFD;							//1111 1101
		for(i=0;i<65535;i++);
		P0=0XFB;							//1111 1011
		for(i=0;i<65535;i++);
		P0=0XF7;							//1111 0111
		for(i=0;i<65535;i++);
		P0=0XE0;							//1110 0000
		for(i=0;i<65535;i++);
		P0=0XDF;							//1101 1111
		for(i=0;i<65535;i++);
		P0=0XBF;							//1011 1111
		for(i=0;i<65535;i++);
		P0=0X7F;							//0111 1111
		for(i=0;i<65535;i++);
		P0=0X00;							//0000 0000
		for(i=0;i<65535;i++);
	}
}
*/
/*#include<stc15f2k60s2.H>

	void Delayms (int ms);
	void main(void)
{
	P2=0XA0;P0=0X00;P2=0X80;P0=0XFF;//初始化程序
	
	while(1)
	{
		P0=0XFE;//1110 1111
		Delayms(100);
		P0=0XFD;
		Delayms(300);
		P0=0XFB;
		Delayms(500);
		P0=0XF7;
		Delayms(800);
		P0=0XEF;
		Delayms(1000);
		P0=0XDF;
		Delayms(1000);
		P0=0XBF;
		Delayms(1000);
		P0=0X7F;
		Delayms(2000);
		P0=0XFF;
		Delayms(200);
	}
}

	void Delayms(int ms)
	{
		int i,j;
		for(i=0;i<ms;i++)
			for(j=845;j>0;j--);
	}

*/
//流水灯程序（简洁）
/*#include<STC15F2K60S2.H>
	
	unsigned char LED;
	
	void Delayms(int ms);
	void main(void)
{
	P2=0XA0;P0=0X00;P2=0X80;P0=0XFF;//初始化程序
	
	while(1)
	{
		for(LED=0;LED<8;LED++)
		{
			P0=~(0X01<<LED);//0000 0001 ~ 1111 1110 //0000 0010 ~ 1111 1101
			Delayms(1000);
		}
	}
}

void Delayms(int ms)
{
	int i,j;
			for(i=0;i<ms;i++)
			for(j=845;j>0;j--);
}
*/

//sbit的应用
/*#include<STC15F2K60S2.H>
	
sbit LED1=P0^0;

void main (void)
{
	P2=0XA0;P0=0X00;P2=0X80;P0=0XFF;
	
	LED1=0;
	while(1);
}*/
/*#include<STC15F2K60S2.H>

void main(void)
{
	P2=0XA0;P0=0X00;P2=0X80;P0=0XFF;
	
	while(1)
	{
	if(P30==0)P00=0;
	if(P31==0)P0=0X01;
	}
}*/

#include "reg52.h"
#include "iic.h"
#include "intrins.h"

sfr AUXR = 0X8E;
sbit S4 = P3^3;
unsigned char code SMG_duanma[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71,0x40,0x80};
bit Key_channel = 0;
unsigned int dat,dat_channel_1,dat_channel_3;

void SelectHC573(unsigned char channel)
{
switch(channel)
{
case 4:
P2 = (P2 & 0X1F) | 0X80;
break;
case 5:
P2 = (P2 & 0X1F) | 0XA0;
break;
case 6:
P2 = (P2 & 0X1F) | 0XC0;
break;
case 7:
P2 = (P2 & 0X1F) | 0XE0;
break;
case 0:
P2 = (P2 & 0X1F) | 0X00;
break;
}
}

void InitSystem()
{
SelectHC573(4);
P0 = 0XFF;
SelectHC573(5);
P0 = 0X00;
SelectHC573(6);
P0 = 0X00;
SelectHC573(7);
P0 = 0XFF;
SelectHC573(0);
}

void DelayK(unsigned int t)
{
while(t--);
while(t--);
}

void ScanKeys()
{
if(S4 == 0)
{
DelayK(10000);
if(S4 == 0)
{
while(S4 == 0);
Key_channel = ~Key_channel;
}
}
}
void Read_AIN1()
{
IIC_Start();
IIC_SendByte(0x90);
IIC_WaitAck();
IIC_SendByte(0x01);
IIC_WaitAck();
IIC_Stop();
IIC_Start();
}






