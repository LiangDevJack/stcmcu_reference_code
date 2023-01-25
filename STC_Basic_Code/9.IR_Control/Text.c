#include<STC15F2K60S2.H>

typedef unsigned int u16;   		
typedef unsigned char u8;
typedef unsigned long u32;
sbit IR_INPUT = P1^1;
u8 code LedChar[] = {
    0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8,
    0x80, 0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E
};
u8 LedBuff[] = {
 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};

u8 T0RH = 0, T0RL = 0;

bit irflag = 0;
u8 ircode[4];

void InitInfrared()//初始化T1相关参数，等着一会计时用！
{
  IR_INPUT = 1;//确保红外引脚被释放
	AUXR &= 0xBF;//定时器时钟12T模式
	TMOD &= 0x0F;
	TMOD |= 0x10;
	TR1 = 0;
	ET1 = 0;
}
u16 GetHighTime()
{
  TH1 = 0;
	TL1 = 0;
	TR1 = 1;
	while(IR_INPUT)
	{
   if(TH1 >= 0x46)//高电平持续时间大于18ms  ...0x4650...
		{
    break;
		}
	}
 TR1 = 0;

 return (TH1*256 + TL1);
}

u16 GetLowTime()
{
  TH1 = 0;
 TL1 = 0;
 TR1 = 1;
 while(!IR_INPUT)
 {
   if(TH1 >= 0X46)//低电平持续时间大于18ms  ...0x4650...
  {
    break;
  }
 }
 TR1 = 0;

 return (TH1*256 + TL1);
}
void IRScan()//对应的内部晶振11.0592M
{
  u8 i, j;
	u8 byt;
	u16 time;

 time = GetLowTime();     //引导码的低电平 9ms - 9000
 if((time<8500) || (time>9500))
 {
  return;  
 }

 time = GetHighTime();
 if((time<4000) || (time>5000))//引导码的高电平 4.5ms - 4500
 {
   return; 
 }

 for(i=0; i<4; i++)
 {
  for(j=0; j<8; j++)
  {
    time = GetLowTime();
   if((time<340) || (time>780))
   {
     return;
   }

   time = GetHighTime();
   if((time>340) && (time<780))
   {
     byt >>= 1;
   }
   else if((time>1460) && (time<1900))
   {
    byt >>= 1;
    byt |= 0x80;
   }
   else
   {
     return;
   }
  }
  ircode[i] = byt;
 }
 irflag = 1;
}

//void IRScan()////对应的内部晶振12M
//{
//  u8 i, j;
// u8 byt;
// u16 time;

// time = GetLowTime();
// if((time <7833) || (time > 8755))    
// {
//  return; 
// }

// time = GetHighTime();
// if((time<3686) || (time > 4608))
// {
//  return;
// }
// for(i=0; i<4; i++)
// {
//  for(j=0; j<8; j++)
//  {
//   time = GetLowTime();
//   if((time<313) ||(time >718))
//   {
//    return;
//   }
//   time = GetHighTime();
//   if((time>313) && (time <718))
//   {
//    byt >>= 1; 
//   }
//   else if((time>1345) && (time<1751))
//   {
//    byt >>= 1;
//    byt |= 0x80;
//   }
//   else
//   {
//    return;
//   }
//  }
//  ircode[i] = byt;
// }
// irflag = 1;
//}
void CloseFucker()
{
  P2 = (P2 & 0x1F) | 0xA0;
 P0 = P0 & 0xAF;
 P2 = P2&0x1F;
}


void ConfigTimer0(u16 ms)
{
    u32 tmp; 
    
    tmp = 11059200 / 12;    
    tmp = (tmp * ms) / 1000;  
    tmp = 65536 - tmp;          
    T0RH = (u8)(tmp>>8);  
    T0RL = (u8)tmp;
    TMOD &= 0xF0;   
    TMOD |= 0x01;   
    TH0 = T0RH;     
    TL0 = T0RL;
    ET0 = 1;       
    TR0 = 1;       
}
void LedScan()
{
  static u8 index=0;

 P2 = (P2 & 0x1F) | 0xE0;
 P0 = 0xFF;
 P2 = (P2 & 0x1F);

 P2 = (P2 & 0x1F) | 0xC0;
 P0 = 0x80>>index;
 P2 = (P2 & 0x1F);
 P2 = (P2 & 0x1F) | 0xE0;
 P0 = LedBuff[index];
 P2 = (P2 & 0x1F);
 
 index++;
 index &= 0x07;
}

void InterruptTimer0() interrupt 1
{
    TH0 = T0RH; 
    TL0 = T0RL;

 LedScan();
}
void main()
{ 
 EA = 1;
 CloseFucker();
 ConfigTimer0(1);
 InitInfrared();

 while(1)
 {
  if(!IR_INPUT)
  {
   IRScan();
  }
  if(irflag)
  {
    irflag = 0;
   LedBuff[5] = LedChar[ircode[0] >> 4];//用户码
   LedBuff[4] = LedChar[ircode[0]&0x0F];
   LedBuff[1] = LedChar[ircode[2] >> 4];//键码
   LedBuff[0] = LedChar[ircode[2]&0x0F];
  }
 }
}
