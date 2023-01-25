#include<STC15F2K60S2.H>
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

unsigned char AD_Read(unsigned char add)
{
	unsigned char temp;
	IIC_Start();//起始信号
	IIC_SendByte(0X90);//发送地址
	IIC_WaitAck();		//等待响应信号
	IIC_SendByte(add);//控制器件
	IIC_WaitAck();
	IIC_Stop();
	
	IIC_Start();
	IIC_SendByte(0X91);//读模式
	IIC_WaitAck();
	temp=IIC_RecByte();//接受通信
	IIC_Stop();
	
	//temp=temp*0.39;//范围0到100显示
	return temp;
}
void AD_Write(unsigned char dat)
{
	IIC_Start();//起始信号
	IIC_SendByte(0X90);//发送地址
	IIC_WaitAck();		//等待响应信号
	IIC_SendByte(0X40);//D/A转换
	IIC_WaitAck();
	
	IIC_SendByte(dat);//读模式128
	IIC_WaitAck();
	
	IIC_Stop();
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

/*#include<STC15F2K60S2.H>
#include<INTRINS.H>

#define uchar unsigned char
#define uint unsigned char
sbit SDA=P2^1;
sbit SCL=P2^0;
sbit DQ=P1^4;
uchar AD;
uchar num[8];
uchar wendu;
uchar tap[]={0XC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XF8,0X80,0X90,0XBF,0XFF};
uchar yi,er,san,si,wu,liu,qi,ba;

void Display1(yi,er);
void Display2(san,si);
void Display3(wu,liu);
void Display4(qi,ba);

void Allinit (void);
void Delayms(int ms);

void Delay6us ();
unsigned char DS18B20_ReadByte(void);
void Init_DS18b20(void);
unsigned char TemperGet(void);
void DS18b20_WriteByte(unsigned char dat);
void Delay500us();
void Delay80us();
void EEPROM_Read(unsigned char add);
void EEPROM_Write(unsigned char add);
void main(void)
{
	Allinit();
	Init_DS18b20();					
	DS18b20_WriteByte(0XCC);
	DS18b20_WriteByte(0X44);
	yi=11;er=11;san=11;si=11;wu=11;liu=11;qi=11;ba=11;
	while(1)
	{
		wendu=TemperGet();
		EEPROM_Write(0X00);Delayms(2);
		EEPROM_Read(0X00);Delayms(2);
		
		qi=num[7]/10;ba=num[7]%10;
		Display1(yi,er);
		Display2(san,si);
		Display3(wu,liu);
		Display4(qi,ba);
		
	}
}
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
		dat<<=1;
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
void IIC_Ack(bit ackbit)
{
	SDA=ackbit;
	Delay6us();
	SCL=1;
	Delay6us();
	SCL=0;
	Delay6us();
	SDA=1;
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

void EEPROM_Read(unsigned char add)
{
	unsigned char i;
	IIC_Start();
	IIC_SendByte(0XA0);
	IIC_WaitAck();		
	IIC_SendByte(add);
	IIC_WaitAck();
	IIC_Stop();
	
	IIC_Start();
	IIC_SendByte(0XA1);
	IIC_WaitAck();

	for(i=0;i<8;i++)
	{
		num[i]=IIC_RecByte();
		IIC_Ack(0);
	}
	IIC_Stop();
}
void EEPROM_Write(unsigned char add)
{
	unsigned char i;
	IIC_Start();
	IIC_SendByte(0XA0);
	IIC_WaitAck();		
	IIC_SendByte(add);
	IIC_WaitAck();
	for(i=0;i<8;i++)
	{
		IIC_SendByte(wendu);
		IIC_WaitAck();
	}
	IIC_Stop();
}

//温度传感器
void Init_DS18b20(void)
{
	DQ=0;
	Delay500us();
	DQ=1;
	Delay500us();
}
void DS18b20_WriteByte(unsigned char dat)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		DQ=0;
		DQ=dat&0X01;
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

unsigned char TemperGet(void)
{
	unsigned char low,high;
	unsigned char temp;
	Init_DS18b20();					
	DS18b20_WriteByte(0XCC);
	DS18b20_WriteByte(0X44);
	Delay500us();
	
	Init_DS18b20();					
	DS18b20_WriteByte(0XCC);
	DS18b20_WriteByte(0XBE);
	
	low=DS18b20_ReadByte();
	high=DS18b20_ReadByte();
	temp=high<<4;		//0000 1010 ; 1010 0000 
	temp=temp|(low>>4);		//1010 0110 ; 0000 1010
		
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

void Display1(yi,er)
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
	P2=0XA0;
	P0=0X00;
	
	P2=0XC0;
	P0=0XFF;
	P2=0XE0;
	P0=0XFF;
	
	P2=0X80;
	P0=0XFF;
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








