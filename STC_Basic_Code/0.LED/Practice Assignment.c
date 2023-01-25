//实践一
/*#include<STC15F2K60S2.H>


void Delayms (int ms);
void main (void)
{
	P2=0XA0;P0=0X00;P2=0X80;P0=0XFF;
	while(1)
	{
		P0=0XFE;
		Delayms(200);
		P0=0XFF;
		Delayms(200);
	}
}
void Delayms (int ms)
{
	int i,j;
	for(i=0;i<ms;i++)
		for(j=845;j>0;j--);
}*/
//实践二
/*#include<STC15F2K60S2.H>
unsigned char LED;
void Delayms (int ms);
void main (void)
{
	P2=0XA0;P0=0X00;P2=0X80;P0=0XFF;
	while(1)
	{
		for(LED=0;LED<8;LED++)
		{
			P0=~(0X01<<LED);
			Delayms(500);
			P0=~(0X00<<LED);
			Delayms(500);
			Delayms(1000);
		}
	}
}
void Delayms (int ms)
{
	int i,j;
	for(i=0;i<ms;i++)
		for(j=845;j>0;j--);
}*/
//实践三
#include<STC15F2K60S2.H>
unsigned char LED1,LED2,LED3;
void Delayms (int ms);
void main (void)
{
	P2=0XA0;P0=0X00;P2=0X80;P0=0XFF;
	while(1)
	{
		for(LED1=0;LED1<8;LED1++)
		{
			P0=~(0X01<<LED1);
			Delayms(200);
		}	
		for(LED2=0;LED2<8;LED2++)
		{
			P0=~(0X80>>LED2);//变量放后面
			Delayms(200);
		}
		for(LED3=0;LED3<5;LED3++)
		{
			P0=0XFF;
			Delayms(300);
			P0=0X00;
			Delayms(300);
		}
	}

}	
void Delayms (int ms)
{
	int i,j;
	for(i=0;i<ms;i++)
		for(j=845;j>0;j--);
}

//实践四
/*#include<STC15F2K60S2.H>
unsigned char LED;
void Delayms (int ms);
void main (void)
{
	P2=0XA0;P0=0X00;P2=0X80;P0=0XFF;
	while(1)
	{
		for(LED=0;LED<8;LED++)
		{
			P0=0XFE<<LED;
			Delayms(300);
		}	
	}
}
void Delayms (int ms)
{
	int i,j;
	for(i=0;i<ms;i++)
		for(j=845;j>0;j--);
}
*/
//实践五
/*#include<STC15F2K60S2.H>
unsigned char LED0,LED1,LED2,LED3,LED4,LED5,LED6;
void Delayms (int ms);
void main (void)
{
	P2=0XA0;P0=0X00;P2=0X80;P0=0XFF;
	
	
	for(LED0=0;LED0<3;LED0++)
	{
			P0=0X55;//0101 0101
			Delayms(300);
			P0=0XAA;//1010 1010
			Delayms(300);
	}
	for(LED4=0;LED4<3;LED4++)
	{
			for(LED1=0;LED1<8;LED1++)
			{
				P0=~(0X01<<LED1);
				Delayms(200);
			}	
			for(LED2=0;LED2<8;LED2++)
			{
				P0=~(0X80>>LED2);//变量放后面
				Delayms(200);
			}
	}
//	for(LED3=0;LED3<4;LED3++)
//	{
//		P0=0XE7;
//		Delayms(200);
//		P0=0XDB;
//		Delayms(200);
//		P0=0XBD;
//		Delayms(200);
//		P0=0X7E;
//		Delayms(200);
//	}
		for(LED3=0;LED3<4;LED3++)//不懂
		{
		
			P0=~((0X08>>LED3)|(0X10<<LED3));
			
			//P0=~(0X10<<LED3);
			//0000 1000
			
		
			Delayms(300);
		}
//	for(LED3=0;LED3<4;LED3++)
//	{
//		for(LED5=0;LED5<1;LED5++)
//		{
//			P0=~(0X10<<LED3);
//		}
//		for(LED6=0;LED6<1;LED6++)
//		{
//			P0=~(0X08>>LED3);
//		}
//		Delayms(300);
//	}
		P0=0XFF;
	while(1);
}
void Delayms (int ms)
{
	int i,j;
	for(i=0;i<ms;i++)
		for(j=845;j>0;j--);
}
*/













