#include<STC15F2K60S2.H>
#include<intrins.h>
sbit SDA=P2^1;
sbit SCL=P2^0;

unsigned char tap[]={0XC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XF8,0X80,0X90,\
0X40,0X79,0X24,0X30,0X19,0X12,0X02,0X78,0X00,0X10,0XBF,0XFF,0XC1,0X8E};
unsigned char AD;
unsigned char count_t=0;
unsigned int count_f=0;
unsigned int dat_f=0;
unsigned char yi,er,san,si,wu,liu,qi,ba;
unsigned char shift0=0;
unsigned char shift1=0;
unsigned char LED=0;
unsigned char Nixie_Tube=0;

void Select_shift0(void);
void Select_shift1(void);
void SMGON_OFF(void);
void LED_Indicator(void);
void LED_Indicator_L4(void);
void Scan_Keys(void);
unsigned char AD_Read(unsigned char add);
void AD_Write(unsigned char V_Out);
void Init_Timer();

void Allinit(void);
void display1(yi,er);
void display2(san,si);
void display3(wu,liu);
void display4(qi,ba);
void Delayms (int ms);
void Delay6us();
void main (void)
{
	Allinit();
	Init_Timer();
	while(1)
	{
		Scan_Keys();
		Select_shift0();
		Select_shift1();
		SMGON_OFF();  
		LED_Indicator();
		LED_Indicator_L4();
	}
}
//===================模式切换====================
void Select_shift0(void)
{
	switch(shift0)
	{
		case 0://电压界面
		{
			AD=AD_Read(0X03);
			yi=22;er=21;san=21;si=21;wu=21;
			liu=AD/100+10;qi=AD%100/10;ba=AD%10;
			if(LED==0)
			{
				P2=0X80;P0=0XFE;
			}
			
			break;
		}
		case 1://频率界面
		{
			yi=23;er=21;san=21;si=21;wu=21;
			if(dat_f>99)//被除数不能为零
			{
				liu=dat_f/100;
			}
			if(dat_f>9)
			{
				qi=dat_f%100/10;
			}
			ba=dat_f%10;
			if(LED==0)
			{
				P2=0X80;P0=0XFD;	
			}
			break;
		}
	}
}
void Select_shift1(void)
{
	switch(shift1)
	{
		case 1:
		{
			AD_Write(AD);
			
			break;
		}
		case 0:
		{
			AD_Write(0X64);
			
			break;
		}
	}
}

//==================LED指示功能==================
void LED_Indicator(void)
{
	
	if(LED==0)
	{
		P2=0X80;
			if(AD<150)
		 {
			P0=0XFF;
		 }
			else if((AD>=150) &&(AD<250))
		 {
			 P0=0XFB;
		 }
			 else if((AD>=250) &&(AD<350))
		{
		
			P0=0XFF;
		}
			else if(AD>=350)
		{
			 P0=0XFB;
		}
	}
	else
	{
		P0=0XFF;
	}
	
}
void LED_Indicator_L4(void)
{
	
	if(LED==0)
	{
		P2=0X80;
		if(dat_f<1000)
		 {
			P0=0XFF;
		 }
		 else if((dat_f>=1000)&&(dat_f<5000))
		 {
			P0=0XF7;
		 }
		 else if((dat_f>=5000)&&(dat_f<10000))
		 {
			P0=0XFF;
		 }
		else if(dat_f>=10000)
		 {
			P0=0XF7;
	  	}
	}
		else
	{
		P0=0XFF;
	}
	
}
//==================数码管关/开==================
void SMGON_OFF(void)
{
	if(Nixie_Tube==0)
	{
		display1(yi,er);
		display2(san,si);
		display3(wu,liu);
		display4(qi,ba);
	}
	else
	{
		yi=21;er=21;san=21;si=21;wu=21;liu=21;qi=21;ba=21;
		display4(qi,ba);
	}
}
//===================独立按键====================
void Scan_Keys(void)
{
	if(P33==0)//显示界面切换
	{
		Delayms(5);
		if(P33==0)
		{
			shift0=!shift0;
		}
		while(!P33);
	}
	else if(P32==0)//输出模式切换
	{
		Delayms(5);
		if(P32==0)
		{
			shift1=!shift1;
		}
		while(!P32);
	}
	else if(P31==0)//LED指示灯功能控制
	{
		Delayms(5);
		if(P31==0)
		{
			LED=!LED;
		}
		while(!P31);
	}
	else if(P30==0)//数码管显示功能控制
	{
		Delayms(5);
		if(P30==0)
		{
			Nixie_Tube=!Nixie_Tube;
		}
		while(!P30);
	}
}
//===================PCF8591=====================
void IIC_Start()
{
	SDA=1;
	SCL=1;
	Delay6us();
	SDA=0;
	Delay6us();
	SCL=0;
}
void IIC_Stop()
{
	SDA=0;
	SCL=1;
	Delay6us();
	SDA=1;
}
void IIC_SendByte(unsigned char dat)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		if(dat&0X80)SDA=1;
		else SDA=0;
		Delay6us();
		SCL=1;
		dat<<=1;//传输从高位开始
		Delay6us();
		SCL=0;
	}
}
bit IIC_WaitAck(void)
{
	SDA=1;
	Delay6us();
	SCL=1;
	Delay6us();
	if(SDA)
	{
		SCL=0;
		IIC_Stop();
		return 0;
	}
	else
	{
		SCL=0;
		return 1;
	}
}
unsigned char IIC_RecByte(void)
{
	unsigned char i;
	unsigned char dat;
	for(i=0;i<8;i++)
	{
		SCL=1;
		Delay6us();
		dat<<=1;
		if(SDA)dat|=0X01;
		SCL=0;
		Delay6us();
	}
	return dat;
}
unsigned char AD_Read(unsigned char add)
{
	unsigned char temp;
	IIC_Start();
	IIC_SendByte(0X90);
	IIC_WaitAck();
	IIC_SendByte(add);
	IIC_WaitAck();
	IIC_Stop();
	
	IIC_Start();
	IIC_SendByte(0X91);
	IIC_WaitAck();
	temp=IIC_RecByte();
	IIC_Stop();

	return temp;
}
void AD_Write(unsigned char V_Out)
{
	IIC_Start();
	IIC_SendByte(0X90);
	IIC_WaitAck();
	IIC_SendByte(0X40);//D/A转换指令
	IIC_WaitAck();
	IIC_SendByte(V_Out);//读模式128
	IIC_WaitAck();
	IIC_Stop();
}
//==================NE555频率====================
void Init_Timer()
{
	TH0 = 0xff;        
	TL0 = 0xff;
	
	TH1 = (65536 - 50000) / 256;        
	TL1 = (65536 - 50000) % 256;
	
	TMOD = 0x16;     //定时器1用方式1，定时；定时器0用方式2，计数
	
  ET0 = 1;
  ET1 = 1;
	EA = 1;
	
	TR0 = 1;
	TR1 = 1;
}
 
void Service_T0() interrupt 1
{
	count_f++;
}
 
void Service_T1() interrupt 3
{
  TH1 = (65536 - 50000) / 256;        
	TL1 = (65536 - 50000) % 256;
	count_t++;
	if(count_t == 20)
	{
		dat_f = count_f;
		count_f = 0;
		count_t = 0;
	}
}
//===============================================
void Allinit(void)
{
	P2=0XA0;
	P0=0X00;
	
	P2=0XC0;
	P0=0XFF;
	P2=0XFF;
	P0=0XFF;
	
	P2=0X80;
	P0=0XFF;
}
void display1(yi,er)
{
	P2=0XC0;
	P0=0X01;
	P2=0XFF;
	P0=tap[yi];
	Delayms(1);
	
	P2=0XC0;
	P0=0X02;
	P2=0XFF;
	P0=tap[er];
	Delayms(1);
}
void display2(san,si)
{
	P2=0XC0;
	P0=0X04;
	P2=0XFF;
	P0=tap[san];
	Delayms(1);
	
	P2=0XC0;
	P0=0X08;
	P2=0XFF;
	P0=tap[si];
	Delayms(1);
}
void display3(wu,liu)
{
	P2=0XC0;
	P0=0X10;
	P2=0XFF;
	P0=tap[wu];
	Delayms(1);
	
	P2=0XC0;
	P0=0X20;
	P2=0XFF;
	P0=tap[liu];
	Delayms(1);
}
void display4(qi,ba)
{
	P2=0XC0;
	P0=0X40;
	P2=0XFF;
	P0=tap[qi];
	Delayms(1);
	
	P2=0XC0;
	P0=0X80;
	P2=0XFF;
	P0=tap[ba];
	Delayms(1);
}
void Delayms (int ms)
{
	int i,j;
	for(i=0;i<ms;i++)
		for(j=845;j>0;j--);
}
void Delay6us()		//@11.0592MHz
{
	unsigned char i;

	i = 14;
	while (--i);
}





