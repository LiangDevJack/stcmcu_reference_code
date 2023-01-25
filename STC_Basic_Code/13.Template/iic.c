/*
  程序说明: IIC总线驱动程序
  软件环境: Keil uVision 4.10 
  硬件环境: CT107单片机综合实训平台 8051，12MHz
  日    期: 2011-8-9
*/

#include "reg52.h"
#include "intrins.h"

#define DELAY_TIME 50

#define SlaveAddrW 0xA0
#define SlaveAddrR 0xA1

//总线引脚定义
sbit SDA = P2^1;  /* 数据线 */
sbit SCL = P2^0;  /* 时钟线 */

void IIC_Delay(unsigned char i)
{
    do{_nop_();}
    while(i--);        
}

//总线启动条件
void IIC_Start(void)
{
    SDA = 1;
    SCL = 1;
    IIC_Delay(DELAY_TIME);
    SDA = 0;
    IIC_Delay(DELAY_TIME);
    SCL = 0;	
}

//总线停止条件
void IIC_Stop(void)
{
    SDA = 0;
    SCL = 1;
    IIC_Delay(DELAY_TIME);
    SDA = 1;
    IIC_Delay(DELAY_TIME);
}

//发送应答
void IIC_SendAck(bit ackbit)
{
    SCL = 0;
    SDA = ackbit;  					// 0：应答，1：非应答
    IIC_Delay(DELAY_TIME);
    SCL = 1;
    IIC_Delay(DELAY_TIME);
    SCL = 0; 
    SDA = 1;
    IIC_Delay(DELAY_TIME);
}

//等待应答
bit IIC_WaitAck(void)
{
    bit ackbit;
	
    SCL  = 1;
    IIC_Delay(DELAY_TIME);
    ackbit = SDA;
    SCL = 0;
    IIC_Delay(DELAY_TIME);
    return ackbit;
}

//通过I2C总线发送数据
void IIC_SendByte(unsigned char byt)
{
    unsigned char i;

    for(i=0; i<8; i++)
    {
        SCL  = 0;
        IIC_Delay(DELAY_TIME);
        if(byt & 0x80) SDA  = 1;
        else SDA  = 0;
        IIC_Delay(DELAY_TIME);
        SCL = 1;
        byt <<= 1;
        IIC_Delay(DELAY_TIME);
    }
    SCL  = 0;  
}

//从I2C总线上接收数据
unsigned char IIC_RecByte(void)
{
    unsigned char i, da;
    for(i=0; i<8; i++)
    {   
    	SCL = 1;
			IIC_Delay(DELAY_TIME);
			da <<= 1;
			if(SDA) da |= 1;
			SCL = 0;
			IIC_Delay(DELAY_TIME);
    }
    return da;    
}


unsigned char AD_read(unsigned char dat)
{
    unsigned char AD;
    IIC_Start();
    IIC_SendByte(0X90);
    IIC_WaitAck();
    IIC_SendByte(dat);
    IIC_WaitAck();
    IIC_Stop();

    IIC_Start();
    IIC_SendByte(0X91);
    IIC_WaitAck();
    AD = IIC_RecByte();
    IIC_SendAck(1);
    IIC_Stop();

    return AD;
}


/*
void AD_write(unsigned char dat)
{
    IIC_Start();
    IIC_SendByte(0x90);
    IIC_WaitAck();
    IIC_SendByte(0x40);
    IIC_WaitAck();
    IIC_SendByte(dat);
    IIC_WaitAck();
    IIC_Stop();
}



unsigned char AT24C02_read(unsigned char add)
{
    unsigned char da;

    IIC_Start();
    IIC_SendByte(0XA0);
    IIC_WaitAck();
    IIC_SendByte(add);
    IIC_WaitAck();
    IIC_Stop();

    IIC_Start();
    IIC_SendByte(0XA1);
    IIC_WaitAck();
    da = IIC_RecByte();
    IIC_SendAck(1);
    IIC_Stop();

    return da;
}

void AT24C02_write(unsigned char add,unsigned char dat)
{
    IIC_Start();
    IIC_SendByte(0xA0);
    IIC_WaitAck();
    IIC_SendByte(add);
    IIC_WaitAck();
    IIC_SendByte(dat);
    IIC_WaitAck();
    IIC_Stop();
}
*/

// //总线引脚定义
// sbit SDA = P2^1;  /* 数据线 */
// sbit SCL = P2^0;  /* 时钟线 */

// void Delay10us()		//@11.0592MHz
// {
// 	unsigned char i;

// 	_nop_();
// 	i = 25;
// 	while (--i);
// }

// void IIC_Start()
// {
//     SDA = 1;
//     SCL = 1;
//     Delay10us();
//     SDA = 0;
//     Delay10us();
// }

// void IIC_Stop()
// {
//     SDA = 0;
//     SCL = 1;
//     Delay10us();
//     SDA = 1;
//     Delay10us();
// }

// void IIC_SendByte(unsigned char dat)
// {
//     unsigned char i;

//     for(i=0;i<8;i++)
//     {
//         SCL = 0 ;
//         Delay10us();
//         if(dat & 0x80)SDA=1;
//         else SDA =0;
//         Delay10us();
//         SCL = 1;
//         dat <<= 1;
//         Delay10us();
//     }
//     SCL = 0 ;
// }


// bit IIC_WaitAck(void)
// {
//     bit ackbit;

//     SCL = 1 ;
//     Delay10us();
//     ackbit = SDA ;
//     SCL = 0 ; 
//     Delay10us();

//     return ackbit;
// }

// unsigned char IIC_RecByte(void)
// {
//     unsigned char dat;
//     unsigned char i;

//     for(i=0;i<8;i++)
//     {
//         SCL = 1 ;
//         Delay10us();
//         dat<<=1;
//         if(SDA) dat |= 0x01;
//         SCL = 0 ;
//         Delay10us();
//     }
//     return dat;
// }


// void IIC_SendAck(bit ackbit)
// {
//     SDA = ackbit;
//     Delay10us();
//     SCL = 1 ;
//     Delay10us();
//     SCL = 0 ;
//     SDA = 1 ;
//     Delay10us();
// }