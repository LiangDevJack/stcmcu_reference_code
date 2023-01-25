//LED灯
/*#include<STC15F2K60S2.H>

unsigned int i;

void main(void)
{
	P2=0XA0;P0=0X80;
	P2=0X9F;P0=0XFF;//P25=0;P26=0;P27=1;或者：P2=0X80
	
	while(1)
	{
		P00=0;
		for(i=0;i<65535;i++);
		P00=1;
		for(i=0;i<65535;i++);
	}
}
*/
//继电器打开关闭&蜂鸣器打开
/*#include<STC15F2K60S2.H>
unsigned int i;

void main(void)
{
	P25=1;P26=0;P27=1;
	
	while(1)
	{
		P04=0;
		for(i=0;i<65535;i++);
		P04=1;
		for(i=0;i<65535;i++);
	}
}
*/
//数码管正计时
/*#include<STC15F2K60S2.H>

void Delayms(int ms);
void main (void)
{
	P2=0XA0;P0=0X00;P2=0X80;P0=0XFF;

	
	while(1)
	{
		P2=0XC0;//打开数码管位选573锁存器 Y6C=0
		P0=0X01;//选中第一个数码管    		C0M1=1
		P2=0XE0;//打开数码管段选573锁存器 Y7C=0
		P0=0XF9;//数码管显示1 
		Delayms(1);
		
		P2=0XC0;
		P0=0X02;
		P2=0XE0;
		P0=0XA4;
		Delayms(1);
		
		P2=0XC0;
		P0=0X04;
		P2=0XE0;
		P0=0XB0;
		Delayms(1);
	}
}
void Delayms(int ms)
{
	int i,j;
	for(i=0;i<ms;i++)
		for(j=845;j>0;j--);
}

*/
//99倒计时&LED灯、蜂鸣器指示
#include<STC15F2K60S2.H>

unsigned char tap[]={0XC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XF8,0X80,0X90};

char num=99;
unsigned int i;

unsigned char yi,er;
void Delayms(int ms);
void Indicator_NUM (void);
void display(unsigned char yi,unsigned char er);
void main (void)
{
		P2=0XA0;P0=0X00;P2=0X80;P0=0XFF;
		while(1)
		{
			i++;
			if(i==500)
			{
				i=0;
				num--;
				if(num<0)
				{
					num=99;
				}
			}	
			
			yi=num/10;
			er=num%10;
			display(yi,er);
			Indicator_NUM();
		}
}

void display(unsigned char yi,unsigned char er)
{
	  P2=0XC0;//打开数码管位选573锁存器 Y6C=0
		P0=0X01;//选中第一个数码管    		C0M1=1
		P2=0XE0;//打开数码管段选573锁存器 Y7C=0
		P0=tap[yi];
		Delayms(1);
		
		P2=0XC0;
		P0=0X02;
		P2=0XE0;
		P0=tap[er];
		Delayms(1);
}
void Indicator_NUM (void)
{
	if(num<70)
	{
		P2=0X80;
		P0=0XFE;
		if(num<30)
		{
			P2=0XA0;
			P0=0XFF;
			if(num==0)
			{
				P0=0X00;
			}
		}
	}
	else
	{
		P2=0X80;
		P0=0XFF;
	}
}
void Delayms(int ms)
{
	int i,j;
	for(i=0;i<ms;i++)
		for(j=845;j>0;j--);
}
//99倒计时过后出现乱码的情况

//全部动态数码管
/*#include<STC15F2K60S2.H>

unsigned char tap[]={0XC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XF8,0X80,0X90};
unsigned char yi,er,san,si,wu,liu,qi,ba;

void Delayms(int ms);
void display(yi,er,san,si,wu,liu,qi,ba);

void main (void)
{
		P2=0XA0;P0=0X00;P2=0X80;P0=0XFF;
		while(1)
		{
			
			yi=1;er=2;san=3;si=4;wu=5;liu=6;qi=7;	ba=8;
			display(yi,er,san,si,wu,liu,qi,ba);
		
		}
}

void display(yi,er,san,si,wu,liu,qi,ba)
{
	  P2=0XC0;//打开数码管位选573锁存器 Y6C=0
		P0=0X01;//选中第一个数码管    		C0M1=1
		P2=0XE0;//打开数码管段选573锁存器 Y7C=0
		P0=tap[yi];
		Delayms(1);
		
		P2=0XC0;
		P0=0X02;
		P2=0XE0;
		P0=tap[er];
		Delayms(1);
	
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
		
		P2=0XC0;
		P0=0X40;
		P2=0XE0;
		P0=tap[qi];
		Delayms(1);
		
		P2=0XC0;
		P0=0X80;
		P2=0XE0;
		P0=tap[ba];
		Delayms(1);
}

void Delayms(int ms)
{
	int i,j;
	for(i=0;i<ms;i++)
		for(j=845;j>0;j--);
}
*/
//按键控制倒计时、正计时
/*#include<STC15F2K60S2.H>

unsigned char tap[]={0XC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XF8,0X80,0X90};

unsigned char num;
unsigned int i;
bit s7,s6;
void keyscan(void);
unsigned char yi,er;
void Delayms(int ms);
void display(yi,er);
void main (void)
{
		P2=0XA0;P0=0X00;P2=0X80;P0=0XFF;
		yi=0;er=0;
		while(1)
		{
			i++;
			if(i==500)
			{
				i=0;
				if(s7==1)num--;
				else num++;	
			}	
			keyscan();
			yi=num/10;
			er=num%10;
			display(yi,er);
		
		}
}

void display(yi,er)
{
	  P2=0XC0;//打开数码管位选573锁存器 Y6C=0
		P0=0X01;//选中第一个数码管    		C0M1=1
		P2=0XE0;//打开数码管段选573锁存器 Y7C=0
		P0=tap[yi];
		Delayms(1);
		
		P2=0XC0;
		P0=0X02;
		P2=0XE0;
		P0=tap[er];
		Delayms(1);
}
void keyscan(void)//独立键盘
{
	if(P30==0)
	{
		Delayms(5);
		if(P30==0)
		{
			s7=1;s6=0;
			num=99;
		}
		while(!P30);//等待手的松开,抬手检测
	}
	else if(P31==0)
	{
		Delayms(5);
		if(P31==0)
		{
			s6=1;s7=0;
			num=0;
		}
		while(!P31);//等待手的松开,抬手检测
	}
}
void Delayms(int ms)
{
	int i,j;
	for(i=0;i<ms;i++)
		for(j=845;j>0;j--);
}
*/



