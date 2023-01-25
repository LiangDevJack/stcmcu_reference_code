/*#include<STC15F2K60S2.H>

typedef unsigned int uint;   		
typedef unsigned char uchar;
sbit IRIN = P3^2;       //红外数据传输端

uchar IrValue[6];
uint Time;
uchar yi,er,san;

uchar code tap[]={0XC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XF8,0X80,0X90,0X88,0X00,0XC6,0X40,0X86,0X8E,0XFF};

void delay(uint i)
{
	while (i--);
}
void Delayms (int ms)
{
	int i,j;
	for(i=0;i<ms;i++)
		for(j=845;j>0;j--);
}
void Display1(yi,er,san)//数码管
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
	
	P2=0XC0;
	P0=0X04;
	P2=0XE0;
	P0=tap[san];
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

void IrInit()
{
	IT0=1;		 //下降沿触发
	EX0=1;		 //打开中断0允许
	EA=1;		 //打开总中断
	IRIN=1;		 //初始化端口
}
void ReadIr() interrupt 0
{
	uchar j,k;
	uint err;
	Time = 0;
	delay(700);
	if(IRIN==0)
	{
		err=1000;	//1000*10us=10ms,超过说明接受到错误的信号
		while((IRIN==0)&&(err>0))//等待前面9ms的低电平过去
		{
			delay(1);//10us
			err--;
		}
		if(IRIN==1)//如果正确等到9ms低电平
		{
			err=500;	 
			while((IRIN==1)&&(err>0))//等待4.5ms的起始高电平过去
			{
				delay(1);
				err--;
			}
			for(k=0;k<4;k++)//共有4组数据
			{
				for(j=0;j<8;j++)//接受一组数据
				{
					err=60;
					while((IRIN==0)&&(err>0))//等待信号前面的560us低电平过去
					{
						delay(1);
						err--;
					}
					err = 500;
					while((IRIN==1)&&(err>0))//计算高电平的时间长度
					{
						delay(10);	//0.1ms
						Time++;
						err--;
						if(Time>30)
						{
							return;
						}	
					}
					IrValue[k]>>=1;//k表示第几组数据
					if(Time>=8)//如果高电平出现大于565us，那么是1
					{
						IrValue[k]|=0x80;
					}
					Time=0;	//用完重新赋值
				}
			}
		}
		if(IrValue[2]!=~IrValue[3])//用反码判断数据正确
		{
			return;
		}
	}	
}
void main()
{
	IrInit();
	Allinit();
	while(1)
	{
		yi=IrValue[2]/16;er=IrValue[2]%16;san=16;
		Display1(yi,er,san);
	}  
}
*/










