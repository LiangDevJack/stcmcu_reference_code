
#include <stc15.h>
#include <intrins.h>
#include <Onewire.h>
#include <IIC.h>
#include <DS1302.h>

unsigned char LED_Bit=0XFF;
unsigned char Actuator_Bit=0X00;

#define LEDx_ON(n) 	{LED_Bit&=_crol_(0XFE,n-1); P0=LED_Bit; P2|=0X80;	P2&=0X9F;	P2&=0X1F;}
#define LEDx_OFF(n) {LED_Bit|=_crol_(0X01,n-1); P0=LED_Bit; P2|=0X80;	P2&=0X9F;	P2&=0X1F;}

#define Buzzer_ON 	Actuator_Bit|=0x40; P0=Actuator_Bit;P2|=0XA0;P2&=0XBF; P2&=0X1F;
#define Buzzer_OFF  Actuator_Bit&=0XBF; P0=Actuator_Bit;P2|=0XA0;P2&=0XBF; P2&=0X1F;
#define Relay_ON 		Actuator_Bit|=0x10; P0=Actuator_Bit;P2|=0XA0;P2&=0XBF; P2&=0X1F;
#define Relay_OFF 	Actuator_Bit&=0XEF; P0=Actuator_Bit;P2|=0XA0;P2&=0XBF; P2&=0X1F;

//unsigned char tab[]={0XC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XF8,0X80,0X90,0XBF,0XFF};
unsigned char code tab[]={0XC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XF8,0X80,0X90,\
													0X40,0X79,0X24,0X30,0X19,0X12,0X02,0X78,0X00,0X10,\
													0XBF,0XFF,0X8C,0XC6};
unsigned char KEY_Value=0;
unsigned char DigCom=0;
unsigned char DigBuf[8] = {21,21,21,21,21,21,21,21};

unsigned char LED=1;
unsigned int LED_tt =0;
bit LED_Ref =0;

unsigned int SEG_tt =0;
bit SEG_Ref =0;
bit SEG_Run = 0 ;


unsigned int Temp_tt =0;
bit Temp_Ref =0;
unsigned int Temper = 0 ;
unsigned char Temp_Vaue = 0 ;
unsigned long Temp_DotValue = 0 ;


unsigned int AD_VALUE=0;
unsigned int AD_tt =0;
bit AD_Ref =0;

unsigned char SEG_Show=1;

unsigned int DS_tt =0;
bit DS_Ref =0;
extern unsigned char Get_Time[7];
extern unsigned char shijian[7];

unsigned int Num = 800;

unsigned char Temper_para=25;
unsigned int AD_para=250;
unsigned char Para_Ch=0;


void Delay_MS(unsigned int MS);
void KeyScan(void);
void ALL_Init(void);
void Timer0Init(void);		//1毫秒@11.0592MHz
void SEG_Display(void);

void main(void)
{
	ALL_Init();	
	Timer0Init();
	EA=1;ET0=1;
	
	Buzzer_ON;Delay_MS(500);	Buzzer_OFF;Delay_MS(500);
	Buzzer_ON;Delay_MS(500);	Buzzer_OFF;Delay_MS(500);
	Buzzer_ON;Delay_MS(500);	Buzzer_OFF;Delay_MS(500);		
	
	
	DigBuf[0]=2;DigBuf[1]=1;DigBuf[2]=20;DigBuf[3]=1;DigBuf[4]=2;DigBuf[5]=20;DigBuf[6]=1;DigBuf[7]=2;
	Delay_MS(1000);
	
	DS_init();
	
	while(1)
	{		
		if(Temp_Ref==1)
		{
			Temp_Ref=0;;
			Temp_Vaue=Temp_get()>>4;
		}
		
		if(AD_Ref==1)
		{
			AD_Ref=0;
			AD_VALUE=AD_read(0X03);
			AD_VALUE=AD_VALUE*1.96;
		}		
		
		if(DS_Ref==1)
		{
			DS_Ref=0;
			DS_get();
		}
		
		if(SEG_Ref==1)
		{
			SEG_Ref=0;
			SEG_Display();
		}	
		
		KeyScan();
		if(KEY_Value==7)
		{
			KEY_Value=0;
			if(SEG_Show==1)SEG_Show=2;
			else if(SEG_Show==2)SEG_Show=3;
			else if(SEG_Show==3)SEG_Show=1;			
		}
		if(KEY_Value==6)
		{
			KEY_Value=0;
			if((Para_Ch==0)&&(SEG_Show==3))Para_Ch=1;
			else if((Para_Ch==1)&&(SEG_Show==3))Para_Ch=2;
			else if((Para_Ch==2)&&(SEG_Show==3))Para_Ch=0;
		}
		if(KEY_Value==5)
		{
			KEY_Value=0;
			if(Para_Ch==1)Temper_para=Temper_para+1;
			else if(Para_Ch==2)AD_para=AD_para+50;
		}			
		if(KEY_Value==4)
			{
			KEY_Value=0;
			if(Para_Ch==1)Temper_para=Temper_para-1;
			else if(Para_Ch==2)
			{
				if(AD_para>=50)
				{
					AD_para=AD_para-50;
				}
				else 
				{
					AD_para=50;
				}
			}
		}
	}
}

void Timer0(void) interrupt 1
{
	P0=0XFF;							//选中第一个数码管
	P2|=0XC0;//打开位选573   U8		//	  XXXX XXXX | 1100 0000 = 11XX XXXX
	P2&=0XDF;											//    11XX XXXX & 1101 1111 = 110X XXXX
	P2&=0X1F;
	P0=0XFF; 				//输入数码管要显示的码值
	P2|=0XE0;											//	  XXXX XXXX | 1110 0000 = 111X XXXX
	P2&=0XFF;//打开段选573   U7		//		111X XXXX & 1111 1111 = 111X XXXX
	P2&=0X1F;
	
	P0=(0X01<<DigCom);							//选中第一个数码管
	P2|=0XC0;//打开位选573   U8		//	  XXXX XXXX | 1100 0000 = 11XX XXXX
	P2&=0XDF;											//    11XX XXXX & 1101 1111 = 110X XXXX
	P2&=0X1F;
	P0=tab[DigBuf[DigCom]]; 				//输入数码管要显示的码值
	P2|=0XE0;											//	  XXXX XXXX | 1110 0000 = 111X XXXX
	P2&=0XFF;//打开段选573   U7		//		111X XXXX & 1111 1111 = 111X XXXX
	P2&=0X1F;
	if(++DigCom==8)DigCom=0;
	
	LED_tt++;
	if(LED_tt==999){LED_tt=0;LED_Ref=1;}
	
	SEG_tt++;
	if(SEG_tt==199){SEG_tt=0;SEG_Ref=1;}
	
	Temp_tt++;
	if(Temp_tt==799){Temp_tt=0;Temp_Ref=1;}
		
	AD_tt++;
	if(AD_tt==299){AD_tt=0;AD_Ref=1;}
	
	DS_tt++;
	if(DS_tt==999){DS_tt=0;DS_Ref=1;}
	
	
	
	
}



void SEG_Display(void)
{
		if(SEG_Show==1)
		{
			DigBuf[0]=Temp_Vaue/10;DigBuf[1]=Temp_Vaue%10;DigBuf[2]=21;DigBuf[3]=21;DigBuf[4]=21;
			DigBuf[5]=AD_VALUE/100+10;DigBuf[6]=AD_VALUE%100/10;DigBuf[7]=AD_VALUE%10;				
		}
		else if(SEG_Show==2)
		{
			DigBuf[0] = Get_Time[2]/10; DigBuf[1] = Get_Time[2]%10; DigBuf[2] = 20;
			DigBuf[3] = Get_Time[1]/10; DigBuf[4] = Get_Time[1]%10; DigBuf[5] = 20;
			DigBuf[6] = Get_Time[0]/10; DigBuf[7] = Get_Time[0]%10; 					
		}
		else if(SEG_Show==3)
		{
			DigBuf[0]=22;DigBuf[1]=Temper_para/10;;DigBuf[2]=Temper_para%10;DigBuf[3]=21;
			DigBuf[4]=23;DigBuf[5]=AD_para/100+10;DigBuf[6]=AD_para%100/10;DigBuf[7]=AD_para%10;							
		}
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

void KeyScan(void)
{
	if(P30==0)
	{
		Delay_MS(10);
		if(P30==0)KEY_Value=7;//P0=tab[1];
		while(!P30);
	}
	else if(P31==0)
	{
		Delay_MS(10);
		if(P31==0)KEY_Value=6;
		while(!P31);
	}	
	else if(P32==0)
	{
		Delay_MS(10);
		if(P32==0)KEY_Value=5;
		while(!P32);
	}	
	else if(P33==0)
	{
		Delay_MS(10);
		if(P33==0)KEY_Value=4;
		while(!P33);
	}	
}

void ALL_Init(void)
{
	P0=0X00;	P2|=0XA0;	P2&=0XBF; 	P2&=0X1F;
	P0=0XFF; 	P2|=0X80;	P2&=0X9F;	P2&=0X1F;
	
	P0=0XFF;	P2|=0XC0;	P2&=0XDF;	P2&=0X1F;
	P0=0xFF;	P2|=0XE0;	P2&=0XFF;	P2&=0X1F;
}

void Delay_MS(unsigned int MS)
{
	unsigned int i,j;
	for(i=0;i<MS;i++)
		for(j=845;j>0;j--);
}
