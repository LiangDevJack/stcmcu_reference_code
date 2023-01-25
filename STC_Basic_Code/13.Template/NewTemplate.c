#include<stc15.h>
#include <intrins.h>

unsigned char LED_Bit=0XFF;
unsigned char Actuator_Bit=0X00;

#define LEDx_ON(n) //打开第几个数码管
{
    LED_Bit&=_crol_(0XFE,n-1);//1111 1111 & 1111 1110 = 1111 1110
    P0=LED_Bit;
    P2|=0X80;//打开LED锁存器 1??? ????
    P2&=0X9F;// 100? ????
    P2&=0X1F;// 000? ????
}
#define LEDx_OFF(n)//关闭第几个数码管
{
    LED_Bit|=_crol_(0X01,n-1);
    P0=LED_Bit;
    P2|=0X80;
    P2&=0X9F;
    P2&=0X1F;
}
#define Buzzer_ON
{
    Actuator_Bit|=0X40;//0100 0000
    P0=Actuator_Bit;//0100 0000
    P2|=0XA0;//1010 0000 | P2 = 1?1? ????
    P2&=0XBF;//1011 1111 & P2 = 101? ????
    P2&=0X1F;//0001 1111
}
#define Buzzer_OFF
{
    Actuator_Bit|=0XBF;
    P0=Actuator_Bit;//1011 111
    P2|=0XA0;
    P2&=0XBF;
    P2&=0X1F;
}
#define Relay_ON
{
    Actuator_Bit|=0x10;
    P0=Actuator_Bit;
    P2|=0XA0;
    P2&=0XBF;
    P2&=0X1F;
}
#define Relay_OFF 	
{
    Actuator_Bit&=0XEF;
    P0=Actuator_Bit;
    P2|=0XA0;
    P2&=0XBF; 
    P2&=0X1F;
}

unsigned char LED_Bit = 0XFF;
unsigned char SEG_Show = 1;
unsigned char Digcom = 0;
unsigned char DigBuf[8]={21,21,21,21,21,21,21,21};
unsigned char tap[]={0XC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XF8,0X80,0X90,\
													0X40,0X79,0X24,0X30,0X19,0X12,0X02,0X78,0X00,0X10,\
													0XBF,0XFF,0X8C,0XC6};
unsigned char Temp_Value,AD_Value;

void All_Init();
void Timer0Init(void);
void Delay_MS(unsigned int ms);
void main(void)
{
    All_Init();
    Timer0Init();
    EA=1;ET0=1;
    Buzzer_ON;Delay_MS(500); Buzzer_OFF;Delay_MS(500);
    Buzzer_ON;Delay_MS(500); Buzzer_OFF;Delay_MS(500);
    Buzzer_ON;Delay_MS(500); Buzzer_OFF;Delay_MS(500);

    DigBuf[0]=2;DigBuf[1]=1;DigBuf[2]=20;DigBuf[3]=1;
    DigBuf[4]=2;DigBuf[5]=20;DigBuf[6]=1;DigBuf[7]=2;
    Delay_MS(1000);

    while(1)
    {

    }
}
void All_Init()
{
    P0=0X00;
    P2|=0XA0;//1010 0000 | P2 = 1?1? ????
    P2&=0XBF;//1011 1111 & P2 = 101? ????
    P2&=0X1F;//0001 1111 & P2 = 000? ????
    //综上：P2先为101后清零000
    P0=0XFF;
    P2|=0X80;//1000 0000 | P2 = 1??? ????
    P2&=0X9F;//1001 1111 & P2 = 100? ????
    P2&=0X1F;//0001 1111 & P2 = 000? ????
    //综上：先关闭LED灯，后初始化P2
    P0=0XFF;
    P2|=0XC0;//1100 0000 | P2 = 11?? ????
    P2&=0XDF;//1101 1111 & P2 = 110? ????
    P2&=0X1F;//0001 1111 & P2 = 000? ????
    //综上：打开所有数码管位选，后初始化P2
    P0=0XFF;
    P2|=0XE0;//1110 0000 | P2 = 111? ????
    P2&=0XFF;//1111 1111 | P2 = 111? ????
    P2&=0X1F;//0001 1111 | P2 = 000? ????
    //综上：先关闭所有数码管段选，后初始化P2
    //这样写可以保证其他五位不受变化，只改变P25,P26,P27
    //同时可以保证每次操作完，都能初始化为零
    //对程序整体有优化作用
    //&运算：必须都为1结果才为1，       所以1为不确定，0为确定
    //|运算：只要有一个为1结果就为1，   所以1为确定，0为不确定
}
void Delay_MS(unsigned int ms)
{
    unsigned int i,j;
    for(i=0;i<ms;i++)
        for(j=845;j>0;j--);
}
void Timer0() interrupt 1
{
    P0=0XFF;
    P2|=0XC0;//1100 0000 | P2 = 11?? ????
    P2&=0XDF;//1101 1111 & P2 = 110? ????
    P2&=0X1F;//0001 1111 & P2 = 000? ????
    //综上：打开所有数码管位选，后初始化P2
    P0=0XFF;
    P2|=0XE0;//1110 0000 | P2 = 111? ????
    P2&=0XFF;//1111 1111 | P2 = 111? ????
    P2&=0X1F;//0001 1111 | P2 = 000? ????
    //综上：先关闭所有数码管段选，后初始化P2

    P0=(0X01 << Digcom);//选中第一个数码管
    P2|=0XC0;//打开位选573
    P2&=0XDF;//1101 1111 | P2 = 110? ????
    P2&=0X1F;//000? ????

    P0=tap[DigBuf[Digcom]];//输入数码管要显示的码值
    P2|=0XE0;
    P2&=0XFF;
    P2&=0X1F;
}
void Timer0Init(void)		//1毫秒@11.0592MHz
{
	AUXR |= 0x80;		//定时器时钟1T模式   XXXX XXXX | 1000 0000  = 1XXX XXXX
	TMOD &= 0xF0;		//设置定时器模式		 XXXX XXXX & 1111 0000  = XXXX 0000	
	TL0 = 0xCD;		//设置定时初始值			
	TH0 = 0xD4;		//设置定时初始值			// 11.0592MHZ  11059200
 	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
}
void SEG_Display()
{
    if(SEG_Show=1)
    {
        DigBuf[0]=
        
    }
}
