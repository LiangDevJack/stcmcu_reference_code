//��ʱ��
/*#include<STC15F2K60S2.H>

unsigned char tt;

void main (void)
{
	P2=0XA0;P0=0X00;P2=0X80;P0=0XFF;
		
	
	AUXR=0X80;
	TMOD=0XF0;
	TH0=0X28;
	TL0=0X00;
	TF0=0;
	TR0=1;
	
	EA=1;ET0=1;
	while(1)
	{
	
	}
}

void time0(void) interrupt 1		//�ж�һ
{
	tt++;
	if(tt==100)
	{
	  tt=0;
		P00=~P00;
	}
}
*/
//һ��������ʱ
//#include<STC15F2K60S2.H>
//unsigned char tap[]={0XC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XF8,0X80,0X90,0X90,0XBF,0XFF};
//unsigned char tt;
//unsigned char num=0;
//void Timer1Init(void);
//void main (void)
//{
//	P2=0XA0;P0=0X00;P2=0X80;P0=0XFF;
//	P2=0XC0;P0=0X01;P2=0XFF;P0=0XFF;
//	Timer1Init();
//	EA=1;
//	ET1=1;
//	while(1);
//}
//void Timer1Init(void)		//5����@11.0592MHz
//{
//	AUXR |= 0x40;		//��ʱ��ʱ��1Tģʽ
//	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
//	TL1 = 0x00;		//���ö�ʱ��ֵ
//	TH1 = 0x28;		//���ö�ʱ��ֵ
//	TF1 = 0;		//���TF1��־
//	TR1 = 1;		//��ʱ��1��ʼ��ʱ
//}
//void time0(void) interrupt 3		
//{
//	TL1 = 0x00;		//���ö�ʱ��ֵ
//	TH1 = 0x28;		//���ö�ʱ��ֵ
//	
//	tt++;
//	if(tt==200)
//	{
//	  tt=0;
//		P0=tap[num];
//		num++;
//		if(num==9)
//		{
//			num=0;
//		}
//	}
//}

/*#include<STC15F2K60S2.H>

unsigned char LED=0;
unsigned char LED_RUN=0;
void Delayms (int ms);

void main (void)
{
	P2=0XA0;P0=0X00;P2=0X80;P0=0XFF;
	
	IT0=0;//�ⲿ�ж�
	EX0=1;
	EA=1;//�ܿ���
	while(1)
	{
	
		if(LED_RUN==1)
		{
			P0=~(0X01<<LED);//0000 0001 0000 0010
			LED++;
			if(LED==8)LED=0;
			Delayms(1000);
		} 
	}
}
//	void Key_Scan (void)
//	{
//		if(P32==0)
//		{
//			Delayms(5);
//			if(P32==0)
//		{	
//			if(LED_RUN=0)LED_RUN=1;
//			else LED_RUN=0;
//		}
//		while(!P32);
//		}
//	}
void Delayms (int ms)
{
	int i,j;
	for(i=0;i<ms;i++)
		for(j=845;j>0;j--);
}
void exint0() interrupt 0//�ж����ݣ�����Ҫ���
{
	if(P33==1)//S5����
	{
		if(LED_RUN==0)LED_RUN=1;
		else LED_RUN=0;
	}

}
*/
//��ʱ��ʵ�������
/*#include<STC15F2K60S2.H>
unsigned char code SMG_NoDot[18]={0XC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XF8,0X80,0X90,0X88,0X80,0XC6,0XC0,0X86,0X8E,0XBF,0X7F};
void Delayms (int ms);
sbit S4=P3^3;
sbit S5=P3^2;
unsigned char t_m=0;
unsigned char t_s=0;
unsigned char t_005s=0;
void SelectHC573(unsigned char channel)
{
	switch(channel)
	{
		case 4:P2=(P2&0X1F)|0X80;break;
		case 5:P2=(P2&0X1F)|0XA0;break;
		case 6:P2=(P2&0X1F)|0XC0;break;
		case 7:P2=(P2&0X1F)|0XE0;break;
	}	
}
void DisplaySMG_Bit(unsigned char value,unsigned char pos)
{
	SelectHC573(6);
	P0=0X01<<pos;
	SelectHC573(7);
	P0=value;
}
void DisplayTime()
{
	DisplaySMG_Bit(SMG_NoDot[t_005s%10],7);
	Delayms(1);
	DisplaySMG_Bit(SMG_NoDot[t_005s/10],6);
	Delayms(1);
	DisplaySMG_Bit(SMG_NoDot[16],5);
	Delayms(1);
	
	DisplaySMG_Bit(SMG_NoDot[t_s%10],4);
	Delayms(1);
	DisplaySMG_Bit(SMG_NoDot[t_s/10],3);
	Delayms(1);
	DisplaySMG_Bit(SMG_NoDot[16],2);
	Delayms(1);
	
	DisplaySMG_Bit(SMG_NoDot[t_m%10],1);
	Delayms(1);
	DisplaySMG_Bit(SMG_NoDot[t_m/10],0);
	Delayms(1);
}
void InitTimer0()
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
	
	t_005s++;
	if(t_005s==20)
	{
		t_s++;
		t_005s=0;
		if(t_s==60)
		{
			t_m++;
			t_s=0;
		}
		if(t_m==99)
		{
			t_m=0;
		}
	}
	
}
void ScanKeys()
{
	if(S4==0)//�����������ͣ
	{
		Delayms(5);
		if(S4==0)
		{
			TR0=~TR0;
			while(S4==0)
			{
				DisplayTime();
			}
		}
	}
	
	if(S5==0)//�������
	{
		Delayms(5);
		if(S5==0)
		{
			t_s=0;
			t_005s=0;
			t_m=0;
			while(S5==0)
			{
				DisplayTime();
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
void main ()
{
	InitTimer0();
	while(1)
	{
		DisplayTime();
		ScanKeys();
	}
}
*/
/*#include<STC15F2K60S2.H>

unsigned char tap[]={0XC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XF8,0X80,0X90,0X88,0X80,0XC6,0XC0,0X86,0X8E};
unsigned char LED=0;
unsigned char LED_RUN=0;
unsigned char yi;
unsigned char num;
void Display(yi);
void Delayms (int ms);

void main (void)
{
	P2=0XA0;P0=0X00;P2=0X80;P0=0XFF;
	
	EA=1;//�ܿ���
	EX0=1;
	IT0=1;//�ⲿ�ж��½��ش���
	while(1)
	{
		yi=num;
		if(LED_RUN==1)
		{
			num++;
			Delayms(1000);
			if(num==16)
			{
				num=0;
			}
		}
		Display(yi);
	}
}

void Display(yi)
{
	P2=0XC0;
	P0=0X01;
	P2=0XFF;
	P0=tap[yi];
	Delayms(1);
}
void Delayms (int ms)
{
	int i,j;
	for(i=0;i<ms;i++)
		for(j=845;j>0;j--);
}
void exint0() interrupt 0//�ж����ݣ�����Ҫ���
{
	if(P33==1)//S5����
	{
		if(LED_RUN==0)LED_RUN=1;
		else LED_RUN=0;
	}
}
*/
















