#include<STC15F2K60S2.H>
#include<INTRINS.H>

#define uchar unsigned char
#define uint unsigned char
uchar tap[]={0XC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XF8,0X80,0X90,\
							0X40,0X79,0X24,0X30,0X19,0X12,0X02,0X78,0X00,0X10,0XBF,0XFF};
uchar yi,er,san,si,wu,liu,qi,ba;
void Display1(yi,er);
void Display2(san,si);
void Display3(wu,liu);
void Display4(qi,ba);
void Allinit (void);
sbit DQ=P1^4;
void Delayms(int ms);
uchar num;
uchar tt;
long wendu;
unsigned char DS18B20_ReadByte(void);
void Init_DS18b20(void);
long TemperGet(void);
void DS18b20_WriteByte(unsigned char dat);
void Delay500us();
void Delay80us();

void main (void)
{
	Allinit();
	yi=21;er=21;san=21;si=21;wu=21;liu=21;qi=21;ba=21;
	Init_DS18b20();					
	DS18b20_WriteByte(0XCC);
	DS18b20_WriteByte(0X44);
		
	while(1)
	{

			wendu=TemperGet();//211625
			yi=wendu/100000;er=wendu%100000/10000+10;
			san=wendu%10000/1000;si=wendu%1000/100;wu=wendu%100/10;liu=wendu%10;
			if(wendu<=300000)
			{
				P2=0XA0;
				P0=0X00;
				P2=0X80;
				P0=0XFE;
			
			 }
			else 
			{
				P2=0X80;
				P0=0XFF;
				P2=0XA0;
				P0=0XEF;
			}
			Display1(yi,er);
			Display2(san,si);
			Display3(wu,liu);
			Display4(qi,ba);
	}
}


void Init_DS18b20(void)//初始化
{
	DQ=0;//拉低
	Delay500us();
	DQ=1;//拉高
	Delay500us();
}
void DS18b20_WriteByte(unsigned char dat)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		DQ=0;//拉低
		DQ=dat&0X01;//1100 1100 & 0000 0001 =0000 0000
		Delay80us();
		DQ=1;
		dat >>=1;
		
	}
}
unsigned char DS18b20_ReadByte(void)
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

long TemperGet(void)
{
	unsigned char low,high;
	long temp;
	Init_DS18b20();					//初始化
	DS18b20_WriteByte(0XCC);//忽略ROM指令
	DS18b20_WriteByte(0X44);//温度转换指令
	Delay500us();
	
	Init_DS18b20();					
	DS18b20_WriteByte(0XCC);
	DS18b20_WriteByte(0XBE);//读暂存器指令
	
	low=DS18b20_ReadByte();
	high=DS18b20_ReadByte();
//	temp=high<<4;		//0000 1010 ; 1010 0000 
//	temp=temp|(low>>4);		//1010 0110 ; 0000 1010
	temp=high&0X0F;
	temp<<=8;
	temp=temp|low;
	temp=temp*625;
		
	return temp;
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
void Delayms (int ms)
{
	int i,j;
	for(i=0;i<ms;i++)
		for(j=845;j>0;j--);
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
//bit Init_DS18b20(void)
//{
//	bit DS=0;
//	DQ=0;
//	Delay500us();
//	DQ=1;
//	Delay100us();
//	DS=DQ;
//	Delay100us();
//	
//	return DS;
//}














