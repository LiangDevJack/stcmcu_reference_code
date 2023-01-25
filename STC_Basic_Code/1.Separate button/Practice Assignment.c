//实践一
/*#include<STC15F2K60S2.H>

void Delayms (int ms);
void S4 (void);
void S5 (void);
void S6 (void);
void S7 (void);
void main(void)
{
	P2=0XA0;P0=0X00;P2=0X80;P0=0XFF;

	while(1)
	{
		S4();
		S5();
		S6();
		S7();
	}
}
void S4 (void)
{
	if(P33==0)
	{
		Delayms(5);
		if(P33==0)
		{
			P0=0X00;
		}
		while(!P33);
		Delayms(100);
	}
}
void S5 (void)
{
		if(P32==0)
	{
		Delayms(5);
		if(P32==0)
		{
			P0=0XFF;
		}
		while(!P32);
		Delayms(100);
	}
}
void S6 (void)
{
		if(P31==0)
	{
		Delayms(5);
		if(P31==0)
		{
			P0=0X55;
		}
		while(!P31);
		Delayms(100);
	}
}
void S7 (void)
{
		if(P30==0)
	{
		Delayms(5);
		if(P30==0)
		{
			P0=0XAA;
		}
		while(!P30);
		Delayms(100);
	}
}

void Delayms (int ms)
{
	int i,j;
	for(i=0;i<ms;i++)
		for(j=845;j>0;j--);
}
*/
//实践二
/*#include<STC15F2K60S2.H>

void Delayms (int ms);
void main (main)
{
	P2=0XA0;P0=0X00;
	P2=0XC0;P0=0XFF;
	P2=0XFF;P0=0XFF;
	while(1)
	{
		P0=0XC0;//0
		Delayms(1000);
		P0=0XF9;//1
		Delayms(1000);
		P0=0X88;//A
		Delayms(1000);
		P0=0X83;//b
		Delayms(1000);
		P0=0XA7;//c
		Delayms(1000);
		P0=0XA1;//d
		Delayms(1000);
		P0=0X86;//E
		Delayms(1000);
		P0=0X8E;//F
		Delayms(1000);
		P0=0XC7;//L
		Delayms(1000);
	}
}
void Delayms (int ms)
{
	int i,j;
	for(i=0;i<ms;i++)
		for(j=845;j>0;j--);
}
*/
//实践三
/*#include<STC15F2K60S2.H>
unsigned char tap[]={0XC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XF8,0X80,0X90};
unsigned int num=9;
void Delayms (int ms);
void main(void)
{
	P2=0XA0;P0=0X00;
	P2=0XC0;P0=0XFF;
	P2=0XFF;P0=0XFF;
	while(1)
	{
				
		P0=tap[num];
		Delayms(1000);
		num--;
		while(!num);
		//if(num==0)break;
	}
	while(!num);
	P2=0XC0;P0=0X00;
	P0=0X80;P0=0XFE;
//	for(num=9;num<0;num--)//不懂
//	{
//		P0=tap[num];
//		Delayms(1000);
//	}
	
	
}

void Delayms (int ms)
{
	int i,j;
	for(i=0;i<ms;i++)
		for(j=845;j>0;j--);
}
*/
//实践四
/*#include<STC15F2K60S2.H>
unsigned char tap[]={0XC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XF8,0X80,0X90,0X88,0X80,0XC6,0XC0,0X86,0X8E};
#define uchar unsigned char 
uchar num;
void key_scanf16(void);
void Delayms (int ms);
void main (void)
{
	P2=0XA0;P0=0X00;
	P2=0XC0;P0=0XFF;
	P2=0XFF;P0=0XFF;
	while(1)
	{
		P0=tap[num];
		key_scanf16();
	}
}
void key_scanf16(void)
{
	uchar temp;
	P44=0;P42=1;P3=0X7F;//0111 1111
	temp=P3;
	temp=temp&0X0F;
	if(temp!=0X0F)
	{	
		Delayms(5);
		temp=P3;
		temp=temp&0X0F;
		if(temp!=0X0F)
		{
			temp=P3;
			switch(temp)
			{
				case 0X7E:num=0;break;
				case 0X7D:num=1;break;
				case 0X7B:num=2;break;
				case 0X77:num=3;break;
			}
			while(temp!=0X0F)
			{
				temp=P3;
				temp=temp&0X0F;
			}
		}
	}

	P44=1;P42=0;P3=0XBF;//1011 1111
	temp=P3;
	temp=temp&0X0F;
	if(temp!=0X0F)
	{	
		Delayms(5);
		temp=P3;
		temp=temp&0X0F;
		if(temp!=0X0F)
		{
			temp=P3;
			switch(temp)
			{
				case 0XBE:num=4;break;
				case 0XBD:num=5;break;
				case 0XBB:num=6;break;
				case 0XB7:num=7;break;
			}
			while(temp!=0X0F)
			{
				temp=P3;
				temp=temp&0X0F;
			}
		}
	}
	
	P44=1;P42=1;P3=0XDF;//1101 1111
	temp=P3;
	temp=temp&0X0F;
	if(temp!=0X0F)
	{	
		Delayms(5);
		temp=P3;
		temp=temp&0X0F;
		if(temp!=0X0F)
		{
			temp=P3;
			switch(temp)
			{
				case 0XDE:num=8;break;
				case 0XDD:num=9;break;
				case 0XDB:num=10;break;
				case 0XD7:num=11;break;
			}
			while(temp!=0X0F)
			{
				temp=P3;
				temp=temp&0X0F;
			}
		}
	}
	
	P44=1;P42=1;P3=0XEF;//0111 1111
	temp=P3;
	temp=temp&0X0F;
	if(temp!=0X0F)
	{	
		Delayms(5);
		temp=P3;
		temp=temp&0X0F;
		if(temp!=0X0F)
		{
			temp=P3;
			switch(temp)
			{
				case 0XEE:num=12;break;
				case 0XED:num=13;break;
				case 0XEB:num=14;break;
				case 0XE7:num=15;break;
			}
			while(temp!=0X0F)
			{
				temp=P3;
				temp=temp&0X0F;
			}
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

/*#include<STC15F2K60S2.H>
unsigned char tap[]={0XC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XF8,0X80,0X90};
unsigned char num=99;
unsigned int i;
unsigned int one,two;
void display1(one,two);
void Delayms (int ms);
void main(void)
{
	P2=0XA0;P0=0X00;P2=0X80;P0=0XFF;
		while(1)
		{
			i++;
			if(i==500)
			{
				i=0;
				num--;
			}	
			
			one=num/10;
			two=num%10;
			display1(one,two);
	
		}
		
//		one=num/10;
//		two=num%10;
//		for(num;num<0;num--)
//		{
//			display1(one,two);
//			
//			Delayms(1000);
//		}
//		while(1);
	
}

void display1(one,two)
{
	P2=0XC0;
	P0=0X01;
	P2=0XFF;
	P0=tap[one];
	Delayms(1);
	
	P2=0XC0;
	P0=0X02;
	P2=0XFF;
	P0=tap[two];
	Delayms(1);
}
void Delayms (int ms)
{
	int i,j;
	for(i=0;i<ms;i++)
		for(j=845;j>0;j--);
}

*/








