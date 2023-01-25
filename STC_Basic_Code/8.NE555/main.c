
#include "reg52.h"
#include "absacc.h"
 
unsigned char code SMG_DM_NoDot[18]=
		{0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,
		 0x88,0x80,0xc6,0xc0,0x86,0x8e,0xbf,0x7f};
 
unsigned int count_f = 0;
unsigned char count_t = 0;
unsigned int dat_f = 0;
 
void DelaySMG(unsigned int t)
{
	while(t--);
}
 
void DisplaySMG_Bit(unsigned char pos, unsigned char value)
{
	XBYTE[0xE000] = 0xFF;
	XBYTE[0xC000] = 0x01 << pos;
	XBYTE[0xE000] = value;
}
 
void DisplaySMG_F()
{
	DisplaySMG_Bit(0, SMG_DM_NoDot[15]);
	DelaySMG(500);
	
	if(dat_f > 9999)
		DisplaySMG_Bit(3, SMG_DM_NoDot[dat_f / 10000]);
	DelaySMG(500);
	if(dat_f > 999)
		DisplaySMG_Bit(4, SMG_DM_NoDot[(dat_f / 1000) % 10]);
	DelaySMG(500);
	if(dat_f > 99)
		DisplaySMG_Bit(5, SMG_DM_NoDot[(dat_f / 100) % 10]);
	DelaySMG(500);
	if(dat_f > 9)
		DisplaySMG_Bit(6, SMG_DM_NoDot[(dat_f / 10) % 10]);
	DelaySMG(500);
	DisplaySMG_Bit(7, SMG_DM_NoDot[dat_f % 10]);
	DelaySMG(500);
}
 
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
 
void main()
{
	Init_Timer();
	XBYTE[0x8000] = 0xff;
        XBYTE[0xA000] = 0x00;	
	while(1)
	{
		DisplaySMG_F();
	}
}

/*
#include<stc15f2k60s2.h>
 
#define uchar unsigned char   //定义无符号字符类型uchar
#define uint unsigned int     //定义无符号整型类型uint
 
uchar code tab[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xbf,0xff,0x8e};//数字0~9，“-”，“关”，“F”
uchar yi,er,san,si,wu,liu,qi,ba;   //定义字符型变量yi,er,san,si,wu,liu,qi,ba，当作数码管显示控制变量
 
uint fan,fan_send,zheng,zheng_send,trie,pinlv,time;
bit flag=0;
 
void delayms(int ms);          //延时函数
void allinit();                //初始化函数
void display1(uchar yi,uchar er);   //第一、二段数码管函数
void display2(uchar san,uchar si);  //第三、四段数码管函数
void display3(uchar wu,uchar liu);  //第五、六段数码管函数
void display4(uchar qi,uchar ba);   //第七、八段数码管函数
void Timer0Init(void);		//5微秒@12.000MHz
void Timer1Init(void);		//1毫秒@12.000MHz
void Frequency();         //频率测量显示函数
 
void main()//主函数
{
	allinit();                  //初始化函数
	Timer0Init();
	Timer1Init();
	yi=1;er=2;san=3;si=4;wu=5;liu=6;qi=7;ba=8;//让数码管依次显示1~8，用来检验数码管显示函数程序是否有误
	while(1)
	{
		Frequency();              //频率测量显示函数
		display1(yi,er);          //第一、二段数码管函数
		display2(san,si);         //第三、四段数码管函数
		display3(wu,liu);         //第五、六段数码管函数
		display4(qi,ba);          //第七、八段数码管函数
	}
}
void Frequency()           //频率测量显示函数
{
	yi=12;er=11;san=11;
	if(pinlv>=10000){si=pinlv/10000;wu=pinlv%10000/1000;liu=pinlv%1000/100;qi=pinlv%100/10;ba=pinlv%10;}
	else if(pinlv>=1000){si=11;wu=pinlv/1000;liu=pinlv%1000/100;qi=pinlv%100/10;ba=pinlv%10;}
	else if(pinlv>=100){si=11;wu=11;liu=pinlv/100;qi=pinlv%100/10;ba=pinlv%10;}
	else if(pinlv>=10){si=11;wu=11;liu=11;qi=pinlv/10;ba=pinlv%10;}
}
void Timer0Init(void)		//5微秒@12.000MHz
{
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0xC4;		//设置定时初值
	TH0 = 0xFF;		//设置定时初值
	TF0 = 0;		//清除TF0标志
//	TR0 = 1;		//定时器0开始计时
}
void time0() interrupt 1
{
	if(P34==0)
	{
		fan++;
		if(flag==0)
		{
			flag=1;
			zheng_send=zheng;
			zheng=0;
		}
	}
	else if(P34==1)
	{
		zheng++;
		if(flag==1)
		{
			flag=0;
			fan_send=fan;
			fan=0;
		}
	}
}
void Timer1Init(void)		//1毫秒@12.000MHz
{
	AUXR |= 0x40;		//定时器时钟1T模式
	TMOD &= 0x0F;		//设置定时器模式
	TL1 = 0x20;		//设置定时初值
	TH1 = 0xD1;		//设置定时初值
	TF1 = 0;		//清除TF1标志
	TR1 = 1;		//定时器1开始计时
	EA=1;ET1=1;
}
void time1() interrupt 3
{
	trie++;
	if(trie==969)
	{
		TR0 = 1;ET0=1;
	}
	else if(trie==999)
	{
		TR0 = 0;ET0=0;
		trie=0;
		time=(zheng_send+fan_send)*5;
		pinlv=1000000/time;
	}
}
void delayms(int ms)//延时函数
{
	uint i,j;
	for(i=ms;i>0;i--)
		for(j=845;j>0;j--);
}
void allinit()//初始化函数
{
	P2=0XA0;P0=0X00;      //关闭蜂鸣器继电器
	P2=0X80;P0=0XFF;      //关闭所有LED灯
	
	P2=0XC0;P0=0XFF;      //选中所有数码管段选
	P2=0XFF;P0=0XFF;      //关闭所有数码管
}
void display1(uchar yi,uchar er)//第一、二段数码管函数
{
	P2=0XC0;P0=0X01;               //选中第一个数码管位选
	P2=0XFF;P0=tab[yi];            //让第一个数码管显示yi指向的值
	delayms(1);                    //延时1ms
	
	P2=0XC0;P0=0X02;               //选中第二个数码管位选
	P2=0XFF;P0=tab[er];            //让第一个数码管显示er指向的值
	delayms(1);	                   //延时1ms
}
void display2(uchar san,uchar si)//第三、四段数码管函数
{
	P2=0XC0;P0=0X04;               //选中第s三个数码管位选
	P2=0XFF;P0=tab[san];           //让第一个数码管显示san指向的值
	delayms(1);                    //延时1ms
	
	P2=0XC0;P0=0X08;               //选中第四个数码管位选
	P2=0XFF;P0=tab[si];            //让第一个数码管显示si指向的值
	delayms(1);	                   //延时1ms
}
void display3(uchar wu,uchar liu)//第五、六段数码管函数
{
	P2=0XC0;P0=0X10;               //选中第五个数码管位选
	P2=0XFF;P0=tab[wu];            //让第一个数码管显示wu指向的值
	delayms(1);                    //延时1ms
	
	P2=0XC0;P0=0X20;               //选中第六个数码管位选
	P2=0XFF;P0=tab[liu];           //让第一个数码管显示liu指向的值
	delayms(1);	                   //延时1ms
}
void display4(uchar qi,uchar ba)//第七、八段数码管函数
{
	P2=0XC0;P0=0X40;               //选中第七个数码管位选
	P2=0XFF;P0=tab[qi];            //让第一个数码管显示qi指向的值
	delayms(1);                    //延时1ms
	
	P2=0XC0;P0=0X80;               //选中第八个数码管位选
	P2=0XFF;P0=tab[ba];            //让第一个数码管显示ba指向的值
	delayms(1);                    //延时1ms          

}
*/

