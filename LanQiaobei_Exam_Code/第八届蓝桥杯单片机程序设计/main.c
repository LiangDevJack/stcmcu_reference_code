#include<STC15F2K60S2.H>
#include<INTRINS.H>

sbit SCK=P1^7;//U19		SCLK
sbit SDA=P2^3;//数据线I/O
sbit RST=P1^3;//CE
sbit DQ=P1^4;
unsigned char tap[]={0XC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XF8,0X80,0X90,0XBF,0XFF,0XC6};
unsigned char yi,er,san,si,wu,liu,qi,ba;
char Init_Time[]={50,59,23,16,10,2,19};
char shijian[7];
char alarm[]={0,0,0,16,10,2,19};
unsigned char wendu;
unsigned char LED;
unsigned char shift0;
unsigned char shift1;
unsigned char tt;
unsigned char TT;
unsigned char s4;
unsigned char Key_Add=0;
unsigned char Key_Minus=0;
unsigned char model=0;

void Scan_Key(void);
void Init_Timer0(void);
void Select_Model(void);
void Select_Shift0(void);
void Select_Shift1(void);
void DS18B20_Init(void);
void DS18B20_WriteByte(unsigned char dat);
unsigned char Temperature_Get(void);
void DS1302_Init(void);
void DS1302_Get(void);
void Write_DS1302(unsigned char address,unsigned char dat);
unsigned char Read_DS1302(unsigned char address);
void Write_Byte(unsigned char temp);
void display1(yi,er);
void display2(san,si);
void display3(wu,liu);
void display4(qi,ba);
void Allinit(void);
void Delay500us();
void Delay80us();	
void Delayms(int ms);

void main(void)
{
	Allinit();
	Init_Timer0();
	DS1302_Init();
	DS18B20_Init();
	DS18B20_WriteByte(0XCC);	
	DS18B20_WriteByte(0X44);
	yi=11;er=11;san=11;si=11;wu=11;liu=11;qi=11;ba=11;
	IT0=0;//外部中断
	EX0=1;
	EA=1;//总开关
	PX0=1;
	while(1)
	{
		DS1302_Get();
		wendu=Temperature_Get();
		Scan_Key();
		
		display1(yi,er);
		display2(san,si);
		display3(wu,liu);
		display4(qi,ba);

	}	
}
void Select_Model(void)
{
	switch(model)
	{
		case 0://时钟模式
		{
			Select_Shift0();
			
		if(LED==1)
		{
			P2=0X80;
			P0=0XFE;
			tt++;
			TT++;
			if(tt==5)
			{
				P0=0XFF;
				tt=0;
			}
		}
			
			break;
		}
		case 1://闹铃模式
		{
			Select_Shift1();
			
			break;
		}
	}
}
void Select_Shift0(void)//时钟切换调整
{
	switch(shift0)
	{
		case 0://正常
			{
				yi=shijian[2]/10;er=shijian[2]%10;san=10;
				si=shijian[1]/10;wu=shijian[1]%10;liu=10;
				qi=shijian[0]/10;ba=shijian[0]%10;
				
				break;
			}
		case 1://秒
			{
				yi=shijian[2]/10;er=shijian[2]%10;san=10;
				si=shijian[1]/10;wu=shijian[1]%10;liu=10;
				qi=11;ba=11;//解决7，8闪烁问题
				tt++;
				if(tt==20)
				{
					if(Key_Add==1)
					{
						Init_Time[0]=0;
						
						Key_Add=0;
					}
					else if(Key_Minus==1)
					{
						Init_Time[0]=0;
					
						Key_Minus=0;
					}
						DS1302_Init();
						DS1302_Get();
					qi=shijian[0]/10;ba=shijian[0]%10;
					tt=0;
				}
	
				break;
			}	
		case 2://分
			{
				yi=shijian[2]/10;er=shijian[2]%10;san=10;
				si=11;wu=11;liu=10;//解决4，5闪烁问题
				qi=shijian[0]/10;ba=shijian[0]%10;
				tt++;
				if(tt==20)
				{
					if(Key_Add==1)
					{
						Init_Time[1]++;
						if(Init_Time[1]==60)
						{
							Init_Time[1]=0;
						}
						
						Key_Add=0;
					}
					else if(Key_Minus==1)
					{
						Init_Time[1]--;
						if(Init_Time[1]<0)
						{
							Init_Time[1]=59;
						}

						Key_Minus=0;
					}
						DS1302_Init();
						DS1302_Get();
					si=shijian[1]/10;wu=shijian[1]%10;
					tt=0;
				}
				
				break;
			}	
			case 3://时
			{
				yi=11;er=11;san=10;
				si=shijian[1]/10;wu=shijian[1]%10;liu=10;
				qi=shijian[0]/10;ba=shijian[0]%10;
				tt++;
				if(tt==20)
				{
					if(Key_Add==1)
					{
						Init_Time[2]++;
						if(Init_Time[2]==24)
						{
							Init_Time[2]=0;
						}
						Key_Add=0;
					}
					else if(Key_Minus==1)
					{
						Init_Time[2]--;
						if(Init_Time[2]<0)
						{
							Init_Time[2]=23;
						}
						Key_Minus=0;
					}
						DS1302_Init();
						DS1302_Get();
					yi=shijian[2]/10;er=shijian[2]%10;					
					tt=0;
				}
				
				break;
			}
		case 4:
			{
				yi=11;er=11;san=11;si=11;wu=11;
				liu=wendu/10;qi=wendu%10;ba=12;
				break;
			}		
		
	}	
}
void Select_Shift1(void)//闹钟切换调整
{
	switch(shift1)
	{
		case 0://正常
			{
				yi=alarm[0]/10;er=alarm[0]%10;san=10;
				si=alarm[1]/10;wu=alarm[1]%10;liu=10;
				qi=alarm[2]/10;ba=alarm[2]%10;
				
				break;
			}
		case 1://秒
			{
				yi=alarm[0]/10;er=alarm[0]%10;san=10;
				si=alarm[1]/10;wu=alarm[1]%10;liu=10;
				qi=11;ba=11;
				
				tt++;
				if(tt==20)
				{
					if(Key_Add==1)
					{
						alarm[2]++;
						Key_Add=0;
						if(alarm[2]==60)
						{
							alarm[2]=0;
						}
					}
					else if(Key_Minus==1)
					{
						alarm[2]--;
						Key_Minus=0;
						if(alarm[2]==-1)
						{
							alarm[2]=59;
						}
					}
					qi=alarm[2]/10;ba=alarm[2]%10;
					tt=0;
				}
				break;
			}	
		case 2://分
			{
				yi=alarm[0]/10;er=alarm[0]%10;san=10;
				si=11;wu=11;liu=10;
				qi=alarm[2]/10;ba=alarm[2]%10;
				tt++;
				if(tt==20)
				{
					if(Key_Add==1)
					{
						alarm[1]++;
						Key_Add=0;
						if(alarm[1]==60)
						{
							alarm[1]=0;
						}
					}
					else if(Key_Minus==1)
					{
						alarm[1]--;
						Key_Minus=0;
						if(alarm[1]==-1)
						{
							alarm[1]=59;
						}
					}
					si=alarm[1]/10;wu=alarm[1]%10;
					tt=0;
				}
				break;
			}	
		case 3://时
			{
				yi=11;er=11;san=10;
				si=alarm[1]/10;wu=alarm[1]%10;
				qi=alarm[2]/10;ba=alarm[2]%10;
				tt++;
				if(tt==20)
				{
					if(Key_Add==1)
					{
						alarm[0]++;
						Key_Add=0;
						if(alarm[0]==24)
						{
							alarm[0]=0;
						}
					}
					else if(Key_Minus==1)
					{
						alarm[0]--;
						Key_Minus=0;
						if(alarm[0]==-1)
						{
							alarm[0]=23;
						}
					}
					yi=alarm[0]/10;er=alarm[0]%10;
					tt=0;
				}
				
				break;
			}			
	}	
}

//=======================闹钟模块========================
void Alarm_Display()
{
	if((shijian[0]==alarm[2])&&(shijian[1]==alarm[1])&&(shijian[2]==alarm[0]))
	{
		LED=1;
	}
		
}


//======================定时器中断=======================
void Init_Timer0(void)
{
	TMOD=0X01;//16位定时、计数模式
	TH0=(65535-50000)/256;//0XD8
	TL0=(65535-50000)/256;//0XEF
	
	ET0=1;
	EA=1;//总开关
	TR0=1;//启动定时器
	PT0=0;
}
void Service_Temperature() interrupt 0
{
		if(TT==100)
		{
			LED=0;
			TT=0;
		}
}
void ServiceTimer0() interrupt 1
{
	TH0=(65535-50000)/256;//0XD8
	TL0=(65535-50000)/256;//0XEF
	
	Select_Model();
	Alarm_Display();
		
}

//===================DS1302时钟芯片======================

void Write_DS1302(unsigned char address,unsigned char dat)
{
	RST=0;
	_nop_();
	SCK=0;
	_nop_();
	RST=1;
	Write_Byte(address);
	Write_Byte(((dat/10)<<4)|(dat%10));
}
void Write_Byte(unsigned char temp)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		SCK=0;//上升沿传输数据
		SDA=temp&0X01;
		temp>>=1;
		SCK=1;
	}
}
unsigned char Read_DS1302(unsigned char address)
{
	unsigned char i,temp,dat1,dat2;
	RST=0;
	_nop_();
	SCK=0;
	_nop_();
	RST=1;
	Write_Byte(address);
	for(i=0;i<8;i++)
	{
		SCK=0;
		temp>>=1;
		if(SDA)temp|=0X80;
		SCK=1;
	}
	SDA=0;
	dat1=temp/16;
	dat2=temp%16;
	temp=dat1*10+dat2;
	
	return temp;
}
void DS1302_Init(void)
{
	unsigned char i,add;
	add=0X80;//写秒
	Write_DS1302(0X8E,0X00);
	for(i=0;i<7;i++)
	{
		Write_DS1302(add,Init_Time[i]);
		add=add+2;
	}
	Write_DS1302(0X8E,0X80);
}
void DS1302_Get(void)
{
	unsigned char i,add;
	add=0X81;//读秒
	Write_DS1302(0X8E,0X00);//WP=0
	for(i=0;i<7;i++)
	{
		shijian[i]=Read_DS1302(add);
		add=add+2;//秒分时寄存器地址都相差2
	}
	Write_DS1302(0X8E,0X80);//禁止写操作
}





//=======================================================


//===================DS18B20温度传感器===================
void DS18B20_Init(void)
{
	DQ=0;
	Delay500us();
	DQ=1;
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
		dat>>=1;
	}
}
unsigned char DS18B20_ReadByte(void)
{
	unsigned char i;
	unsigned char dat;
	for(i=0;i<8;i++)
	{
		DQ=0;
		dat>>=1;
		DQ=1;
		if(DQ==1)
		{
			dat=dat|0X80;
		}
		Delay80us();
	}
	return dat;//把计算结果返回给调用者
}
unsigned char Temperature_Get(void)
{
	unsigned char low,high;
	unsigned char temp;
	DS18B20_Init();
	DS18B20_WriteByte(0XCC);	
	DS18B20_WriteByte(0X44);
	Delay500us();

	DS18B20_Init();
	DS18B20_WriteByte(0XCC);
	DS18B20_WriteByte(0XBE);

	low=DS18B20_ReadByte();
	high=DS18B20_ReadByte();
	temp=high<<4;
	temp=temp|(low>>4);
	
	return temp;
}


//=======================================================
void Scan_Key(void)
{
	if(P30==0)//s7按键：时钟设置
	{
		Delayms(5);
		if(P30==0)
		{
			model=0;
			shift0++;
			if(shift0==4)
			{
				shift0=0;
			}
		}
	while(!P30);
	}
	else if(P31==0)//s6按键：闹钟设置
	{
		Delayms(5);
		if(P31==0)
		{
			model=1;
			shift1++;
			if(shift1==4)
			{
				shift1=0;
			}
		}
	while(!P31);
	}
	else if(P32==0)//s5按键：加
	{
		Delayms(5);
		if(P32==0)
		{
			Key_Add=1;
		}
	while(!P32);
	}
	else if(P33==0)//s4按键：减
	{
		Delayms(5);
		if(P33==0)
		{
			s4=1;
			Key_Minus=1;
			if(shift0==0)shift0=4;
		}
	}
	if((P33==1)&&(s4==1))
		{
			s4=0;
			shift0=0;
		}
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
void Delayms(int ms)
{
	int i,j;
	for(i=0;i<ms;i++)
		for(j=845;j>0;j--);
}




