/*#include<STC15F2K60S2.H>
#include<INTRINS.H>

#define uchar unsigned char
#define uint unsigned char
sbit SDA=P2^1;
sbit SCL=P2^0;
uchar AD;
uchar tap[]={0XC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XF8,0X80,0X90,0XBF,0XFF};
uchar yi,er,san,si,wu,liu,qi,ba;

void Display1(yi,er);
void Display2(san,si);
void Display3(wu,liu);
void Display4(qi,ba);

void Allinit (void);
void Delayms(int ms);
uchar num;
void Delay6us ();
void IIC_Delay(unsigned char i);
unsigned char AD_Read(unsigned char add);
void AD_Write(unsigned char dat);


void main(void)
{
	Allinit();
	yi=11;er=11;san=11;si=11;wu=11;liu=11;qi=11;ba=11;
	while(1)
	{
		AD=AD_Read(0X01);
		
		yi=AD/100;er=AD%100/10;san=AD%10;
		Display1(yi,er);
		Display2(san,si);
		Display3(wu,liu);
		Display4(qi,ba);
		
	}
}
void IIC_Delay(unsigned char i)
{
    do{_nop_();}
    while(i--);        
}
void IIC_Start()//开始条件
{
	SDA=1;//数据线
	SCL=1;//时针线
	Delay6us();
	SDA=0;
	Delay6us();
	SCL=0;
}
void IIC_Stop()
{
	SDA=0;//由高到低
	SCL=1;
	Delay6us();
	SDA=1;
}

void IIC_SendByte(unsigned char dat)//数据有高位往低位传输
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		if(dat&0X80)SDA=1;
		else SDA=0;
		Delay6us();//保持稳定状态
		SCL=1;
		dat<<=1;
		Delay6us();
		SCL=0;
	}
}
//发送应答
void IIC_SendAck(bit ackbit)
{
    SCL = 0;
    SDA = ackbit;  					// 0：应答，1：非应答
    IIC_Delay(5);
    SCL = 1;
    IIC_Delay(5);
    SCL = 0; 
    SDA = 1;
    IIC_Delay(5);
}
bit IIC_WaitAck(void)
{
	SDA=1;
	Delay6us();
	SCL=1;
	Delay6us();
	if(SDA)//SDA=1;信号传输失败；停止。
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
void Write_24C02(unsigned char addr, unsigned char dat)
{
	IIC_Start();		//IIC总线起始信号					
	IIC_SendByte(0xa0); 	//24C02的写设备地址
	IIC_WaitAck();		//等待从机应答	
	IIC_SendByte(addr); 	//内存字节字节
	IIC_WaitAck(); 		//等待从机应答	
	IIC_SendByte(dat); 	//写入目标数据
	IIC_WaitAck();		//等待从机应答	
	IIC_Stop();		//IIC总线停止信号		
}

unsigned char Read_24C02(unsigned char addr)
{
	unsigned char temp;
	//进行一个伪写操作
	IIC_Start();		//IIC总线起始信号					
	IIC_SendByte(0xa0); 	//24C02写设备地址
	IIC_WaitAck();		//等待从机应答	
	IIC_SendByte(addr); 	//内存自己地址
	IIC_WaitAck(); 		//等待从机应答	
	IIC_Stop();										
	//进行字节读操作
	IIC_Start();		//IIC总线起始信号					
	IIC_SendByte(0xa1); 	//24C02读设备地址
	IIC_WaitAck();		//等待从机应答	
	temp = IIC_RecByte();	//读取目标数据
	IIC_SendAck(0); 		//产生非应答信号		
	IIC_Stop();		//IIC总线停止信号			
	return temp;
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
void Delay6us()		//@11.0592MHz
{
	unsigned char i;

	i = 14;
	while (--i);
}
*/