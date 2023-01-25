//实践二
/*#include<STC15F2K60S2.H>
void Timer0Init(void);
void Delayms(int ms);
void Key_Scan(void);
unsigned char num0;
unsigned char num1;
unsigned char k;
unsigned char tap0[]={0XC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XF8,0X80,0X90,\
0X88,0X80,0XC6,0XC0,0X86,0X8E,0XFF};
unsigned char tap1[]={0XC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XF8,0X80,0X90,\
0X88,0X83,0XA7,0XA1,0X86,0X8E,0XFF};

unsigned char tt=0;
void main (void)
{
	P2=0XA0;P0=0X00;
	Timer0Init();
	while(1)
	{
		Key_Scan();	
	}
}

void Display0(void)
{
	P2=0XC0;
	P0=0X80;
	P2=0XFF;
	P0=tap0[num0];
}
void Display1(void)
{
	P2=0XC0;
	P0=0X80;
	P2=0XFF;
	P0=tap1[num1];
}

void Key_Scan(void)
{
	if(P33==0)
	{
		Delayms(5);
		if(P33==0)
		{
			k=0;
			num0=0;
			while(P33==0)
			{
				Display0();
			}
		}
	}
	else	if(P32==0)
	{
		Delayms(5);
		if(P32==0)
		{
			k=1;
			num1=0;
			while(P33==0)
			{
				Display1();
			}
		}
	}
	else	if(P31==0)
	{
		Delayms(5);
		if(P31==0)
		{
			k=2;
			num1=0;
			while(P33==0)
			{
				Display1();
			}
		}
	}
}

void Timer0Init(void)		
{
	TMOD=0X01;
	TH0=(65535-50000)/256;
	TL0=(65535-50000)%256;
	
	ET0=1;
	EA=1;
	TR0=1;
}
void ServiceTimer0() interrupt 1
{
	TH0=(65535-50000)/256;
	TL0=(65535-50000)%256;
	
	tt++;
	if(tt==10)
	{
		if(k==1)
			{
				tt++;
				if(tt==20)
				{
					
					Display1();
					num1++;
					tt=0;
					if(num1==17)
					{
						num1=0;
					}
				}
			}
			else if(k==0)
			{
				
				Display0();
				num0++;
				tt=0;
				if(num0==17)
				{
					num0=0;
				}
			}
			
			else if(k==2)
			{
				tt++;
				if(tt==40)
				{
					
					Display1();
					num1++;
					tt=0;
					if(num1==17)
					{
						num1=0;
					}
				}
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
//实践三
/*#include<STC15F2K60S2.H>
unsigned char tap[]={0XC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XF8,0X80,0X90};
void ScanfKeys(void);
void Display(void);
void Timer0Init(void);
void Delayms(int ms);
unsigned char num;
unsigned char tt;
unsigned char k;
void main (void)
{
	Timer0Init();
	while(1)
	{
		ScanfKeys();
	}

}

void Timer0Init(void)
{
	TMOD=0X01;
	TH0=(65535-50000)/256;
	TL0=(65535-50000)%256;
	
	ET0=1;
	EA=1;
	TR0=1;
}	
void ServiceTimer0() interrupt 1
{
	TH0=(65535-50000)/256;
	TL0=(65535-50000)%256;
	
	tt++;
	if(tt==20)
	{
		tt=0;
		
		if(k==0)
		{
			Display();
			num++;
			if(num==10)
			{
				num=0;
			}
		
		}
	else if(k==1)
			{
				Display();
				num--;
				if(num==0)
				{
					num=9;
				}
			}	
	}
}
void ScanfKeys(void)
{
	if(P33==0)
	{
		Delayms(5);
		if(P33==0)
		{
			num=0;
			k=0;
		}
	}
	else if(P32==0)
	{
		Delayms(5);
		if(P32==0)
		{
			num=9;
			k=1;
		}
	}

}
void Display(void)
{
	P2=0XC0;
	P0=0X80;
	P2=0XFF;
	P0=tap[num];
	Delayms(1);
}
void Delayms(int ms)
{
	int i,j;
	for(i=0;i<ms;i++)
		for(j=845;j>0;j--);
}
*/



























































