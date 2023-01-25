#include<STC15F2K60S2.H>
#include<INTRINS.H>
sbit DQ=P1^4;
sbit SDA=P2^1;
sbit SCL=P2^0;
void Delayms(int ms);
void Allinit(void);
unsigned char tap[]={0XC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XF8,0X80,0X90,0XBF,0XFF,0XC6,0X8C};
unsigned char yi,er,san,si,wu,liu,qi,ba;
unsigned char wendu;
unsigned char model=0;
unsigned char shift=0;

unsigned char T_max,T_min;
void Display1(yi,er);
void Display2(san,si);
void Display3(wu,liu);
void Display4(qi,ba);
void DS18B20_WriteByte(unsigned char dat);
void Init_DS18B20(void);
void Scanf_Key(void);
void Select_Model();
void Select_Shift(unsigned char shift);
void Model_0(void);
unsigned char DAC_Output(unsigned char V_out);
unsigned char V_out;
void LED_Indicator ();
void DAC_Output_If();
void Delay6us();
void Delay80us();
void Delay500us();
unsigned char Read_Temperature(void);
void main(void)
{
	Allinit();
	yi=11;er=11;san=11;si=11;wu=11;liu=11;qi=11;ba=11;
	Init_DS18B20();
	DS18B20_WriteByte(0XCC);
	DS18B20_WriteByte(0X44);
	T_min=20;T_max=30;
	IT0=0;//外部中断
	EX0=1;
	EA=1;//总开关
	while(1)
	{
		
		
		
		wendu=Read_Temperature();
		DAC_Output_If();
		Scanf_Key();
		
		LED_Indicator ();
		Select_Model();
		
		Select_Shift(shift);
		Display1(yi,er);
		Display2(san,si);
		Display3(wu,liu);
		Display4(qi,ba);
		DAC_Output(V_out);
	}
}
void Model_0(void)//数据界面
{
	yi=12;er=11;san=11;si=11;wu=11;liu=11;
	qi=wendu/10;ba=wendu%10;
	if(model==1)
	{
		si=T_max/10;wu=T_max%10;
		qi=T_min/10;ba=T_min%10;
	}
}
void Model_1(void)//参数界面
{
	yi=13;er=11;san=11;si=T_max/10;wu=T_max%10;liu=11;
	qi=T_min/10;ba=T_min%10;
	
}
void Select_Model()
{
	
	if(model==0)
	{
		Model_0();
	
	}
	else 
	{
		Model_1();
	}
//	switch(model)
//	{
//		case 0:Model_0();break;
//		case 1:Model_1();break;
//	}
//	switch(shift)
//	{
//		case 0:si=T_max/10,wu=T_max%10;break;
//		case 1:wu=T_min/10,wu=T_min%10;break;
//	}
}
void Select_Shift(unsigned char shift)
{
	if(shift==1)
	{
		qi=T_min/10;
		ba=T_min%10;
	}
	else if(shift==0)
	{
		si=T_max/10;
		wu=T_max%10;
		if(model==0)//避免model_0模式出现四五数码管留存现象
		{
			si=11;
			wu=11;
		}
	}
}


//==============温度传感器===============
void Init_DS18B20(void)
{
	DQ=0;//拉低
	Delay500us();
	DQ=1;//拉高
	Delay500us();
}
void DS18B20_WriteByte(unsigned char dat)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		DQ=0;
		DQ=dat&0X01;
		Delay80us();
		DQ=1;
		dat>>=1;//从低位开始传输
	}
}
unsigned char DS18B20_ReadByte(void)
{
	unsigned char i;
	unsigned char dat;
	
	for(i=0;i<8;i++)
	{
		DQ=0;
		dat >>=1;
		DQ=1;
		if(DQ==1)
		{
			dat=dat|0X80;
		}
		Delay80us();
	}
	return dat;
}
unsigned char Read_Temperature(void)
{
	unsigned char low,hign;
	unsigned char temp;
	Init_DS18B20();
	DS18B20_WriteByte(0XCC);
	DS18B20_WriteByte(0X44);
	Delay500us();
	
	Init_DS18B20();
	DS18B20_WriteByte(0XCC);
	DS18B20_WriteByte(0XBE);
	
	low=DS18B20_ReadByte();
	hign=DS18B20_ReadByte();

	temp=hign<<4;
	temp=temp|(low>>4);
	return temp;
}
//======================================
void LED_Indicator () 
{
		P2=0X80;
		P0=0XFF;
	if(T_max>T_min)
	{
		P00=0;
		if(wendu<=T_max)
		{
			P01=0;
			P00=1;
			if(wendu<T_min)
			{
				P02=0;
				P01=1;
			}
		}
	}	
	else
		{
			P03=0;
			P00=1;
			model=1;
		}	
}
void Scanf_Key(void)
{
	
	if(P33==0)//S4按键 界面转换
	{	
		Delayms(5);
		if(P33==0)
		{
			model=~model;
		}
		while(!P33);
	}
	else if(P32==0)//S5按键 参数界面切换选择上下限温度
	{	
		Delayms(5);
		if(P32==0)
		{
			shift=~shift;
		}
		while(!P32);
	}
	else if(P31==0)//S6按键 加
	{	
		Delayms(5);
		if(P31==0)
		{
			if(shift==0)    //分割写，避免最高和最低温度一起改变
			{
				T_max++;
				if(T_max==100)
				{
					T_max=30;
				}
			} 
			else //if(shift==0)不能加，影响下面程序的执行，qi,ba数码管示数不动，并列关系条件才行
			{
				T_min++;
				if(T_min==100)
				{
					T_min=20;
				}
			}
		
			
		}  
			while(!P31);
	}
	else if(P30==0)//S7按键 减
	{	
		Delayms(5);
		if(P30==0)
		{
			if(shift==0)    //分割写，避免最高和最低温度一起改变
			{
				T_max--;
				if(T_max==0)
				{
					T_max=30;
				}
			}
			else //而且写法顺序前后保持一致
			{
				T_min--;
				if(T_min==0)
				{
					T_min=20;
				}
			}
		}
		while(!P30);
	}
}	
void DAC_Output_If()
{
	V_out=0XCB;//4V
	if(wendu<=T_max)
	{
		V_out=0X96;//3V
		if(wendu<T_min)
		{
			V_out=0X64;//2V
		}
	}
}
//==============D/A转换===============
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
void IIC_Send_Byte(unsigned char dat)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		if(dat&0X80)SDA=1;
		else SDA=0;
		Delay6us();
		SCL=1;
		dat<<=1;
		Delay6us();
		SCL=0;
	}
}
bit IIC_Wait_Ack(void)
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
unsigned char DAC_Output(unsigned char V_out)
{
	IIC_Start();
	IIC_Send_Byte(0X90);
	IIC_Wait_Ack();
	IIC_Send_Byte(0X40);
	IIC_Wait_Ack();
	IIC_Send_Byte(V_out);
	IIC_Wait_Ack();
	IIC_Stop();
	return(1);
}
//====================================


void Display1(yi,er)
{
	P2=0XC0;
	P0=0X01;
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
void Delay6us()		//@11.0592MHz
{
	unsigned char i;

	i = 14;
	while (--i);
}

void Delay80us()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	i = 1;
	j = 217;
	do
	{
		while (--j);
	} while (--i);
}
void Delay500us()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 6;
	j = 93;
	do
	{
		while (--j);
	} while (--i);
}
void Delayms(int ms)
{
	int i,j;
	for(i=0;i<ms;i++)
		for(j=845;j>0;j--);
}




