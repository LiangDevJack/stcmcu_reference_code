/*#include<STC15F2K60S2.H>
sbit L1 = P0^0;
sbit S7 = P3^0;
unsigned char stat;
unsigned char pwm_duty;
unsigned char count;
void SelectHC573()
{
	P2=(P2 & 0X1F) | 0X80;//0001 1111 | 1000 0000
}
void Delay(unsigned int t)
{
	while(t--);
}

void InitTimer0()
{
	TMOD=0X01;
	TH0=(65535-100)/256;
	TL0=(65535-100)%256;
	
	ET0=1;
	EA=1;
}
void ServiceTimer0() interrupt 1
{
	TH0=(65535-100)/256;
	TL0=(65535-100)%256;
	
	count++;
	if(count==pwm_duty)
	{
		L1=1;
	}
	else if(count == 100)
	{
		L1=0;
		count=0;
	}
}
void ScanKeys()
{
	if(S7 == 0)
	{
		Delay(100);
		if(S7 == 0)
		{
			switch(stat)
			{
				case 0:
					L1=0;
					TR0=1;
					pwm_duty=10;
					stat=1;
				break;
				
				case 1:
					pwm_duty=50;
					stat=2;
				break;
				
				case 2:
					pwm_duty=90;
					stat=3;
				break;
				
				case 3:
					L1=1;
					TR0=0;
					stat=0;
				break;
			}	
				while(S7==0);
		}
	}
}
void main(void)
{
	InitTimer0();
	SelectHC573();
	L1=1;
	while(1)
	{
		ScanKeys();
	}
}
*/
/*
#include<STC15F2K60S2.H>
#include "absacc.h"
 
sbit S7 = P3^0;
sbit S4 = P3^3;
 
unsigned char pwm = 0;          
unsigned char pwm_duty = 0;              
unsigned char times = 0;        
unsigned char led_go = 0;       
unsigned char stat_go = 0;      
unsigned char stat = 0;         
unsigned char key_puse = 0;     
 
unsigned char code SMG_duanma[18]=
		{0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,
		 0x88,0x80,0xc6,0xc0,0x86,0x8e,0xbf,0x7f};
 
void DelaySMG(unsigned int t)
{
	while(t--);
}
 
void DisplaySMG_Bit(unsigned char pos, unsigned char value)
{
	XBYTE[0xE000] = 0xff;
	XBYTE[0xC000] = 0x01 << pos;
	XBYTE[0xE000] = value;
}
 
void Display_Info(unsigned char pos, unsigned char duty)
{
	DisplaySMG_Bit(0, SMG_duanma[pos]);
	DelaySMG(500);
 
	DelaySMG(500);
	DisplaySMG_Bit(6, SMG_duanma[duty / 10]);
	DelaySMG(500);
	DisplaySMG_Bit(7, SMG_duanma[duty % 10]);	
	DelaySMG(500);
	
	DisplaySMG_Bit(0, 0xff);
	DisplaySMG_Bit(6, 0xff);
	DisplaySMG_Bit(7, 0xff);
}
 
void Init_Timer0()
{
	TMOD = 0x01;
	TH0 = (65535 - 1000) / 256;			
	TL0 = (65535 - 1000) % 256;
	
	ET0 = 1;
	EA = 1;
	TR0 = 1;
}
 
void Service_Timer0() interrupt 1
{
	TH0 = (65535 - 1000) / 256;
	TL0 = (65535 - 1000) % 256;
	
	if(stat_go == 0)      						
      {
        XBYTE[0x8000] = 0xe7;						
        return;
      } 
	
        pwm++;                
  
      if(pwm <= pwm_duty)   
      {
				XBYTE[0x8000] = ~(0x01 << stat);
      }
      else if(pwm <= 10)
      {
        XBYTE[0x8000] = 0xff;
      }
      else
      {
        XBYTE[0x8000] = ~(0x01 << stat);
    
        pwm = 0;
        if(key_puse == 0)     
        {
          times++;
        }
      }
}
 
void LED_Control()
{
  if(times == 5)          
  {
    times = 0;
    if(led_go == 0)       
    {
      pwm_duty = pwm_duty + 1;
      if(pwm_duty == 11)
      {
				pwm_duty = 10;
        led_go = 1;
      }
    }
    else if(led_go == 1)  
    {
      pwm_duty = pwm_duty - 1;
      if(pwm_duty == 255)
      {
				pwm_duty = 0;
        led_go = 0;
        
        if(stat_go == 1)      
        {
          stat++;
          if(stat == 8)
          {
            stat = 0;
          }
        }
        else if(stat_go == 2) 
        {
          stat--;
          if(stat == 255)
          {
            stat = 7;
          }
        }
      }
    }
  }
}
 
void Scan_Keys()
{
	if(S4 == 0)
	{
		DelaySMG(100);
		if(S4 == 0)
		{
			while(S4 == 0)
			{
				key_puse = 1;
			}
			key_puse = 0;
			
      stat_go++;            
      if(stat_go == 3)
      {
        stat_go = 1;
      }
		}
	}
	
	if(S7 == 0)
	{
		DelaySMG(100);
		if(S7 == 0)
		{
			while(S7 == 0)
			{
				key_puse = 1;
				Display_Info(stat + 1, pwm_duty * 10);
			}
			key_puse = 0;
		}
	}
}
 
void Init_System()
{
	XBYTE[0xA000] = 0xff;
	XBYTE[0xA000] = 0x00;
	XBYTE[0xE000] = 0xff;
	XBYTE[0xC000] = 0xff;
	
	Init_Timer0();
}
 
main()
{
	Init_System();
	while(1)
	{
		LED_Control();
		Scan_Keys();
	}
}
*/

//按下S7灯会变亮
#include<STC15F2K60S2.H>
sbit L1 = P0^0;
sbit S7 = P3^0;
unsigned char stat;
unsigned char pwm_duty;
unsigned char count;
void SelectHC573()
{
	P2=(P2 & 0X1F) | 0X80;//0001 1111 | 1000 0000
}
void Delay(unsigned int t)
{
	while(t--);
}


void Timer0Init(void)		//100微秒@11.0592MHz
{
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0xAE;		//设置定时初值
	TH0 = 0xFB;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	
	ET0=1;
	EA=1;

}

void ServiceTimer0() interrupt 1
{
	TL0 = 0xAE;		//设置定时初值
	TH0 = 0xFB;		//设置定时初值
	
	count++;
	if(count==pwm_duty)
	{
		L1=1;
	}
	else if(count == 100)
	{
		L1=0;
		count=0;
	}
}
void ScanKeys()
{
	if(S7 == 0)
	{
		Delay(100);
		if(S7 == 0)
		{
			switch(stat)
			{
				case 0:
					L1=0;
					TR0=1;
					pwm_duty=10;
					stat=1;
				break;
				
				case 1:
					pwm_duty=50;
					stat=2;
				break;
				
				case 2:
					pwm_duty=90;
					stat=3;
				break;
				
				case 3:
					L1=1;
					TR0=0;
					stat=0;
				break;
			}	
				while(S7==0);
		}
	}
}
void main(void)
{
	Timer0Init();
	SelectHC573();
	L1=1;
	while(1)
	{
		ScanKeys();
	}
}





