/*
  ����˵��: IIC������������
  �������: Keil uVision 4.10 
  Ӳ������: CT107��Ƭ���ۺ�ʵѵƽ̨ 8051��12MHz
  ��    ��: 2011-8-9
*/

#include "reg52.h"
#include "intrins.h"

#define DELAY_TIME 50

#define SlaveAddrW 0xA0
#define SlaveAddrR 0xA1

//�������Ŷ���
sbit SDA = P2^1;  /* ������ */
sbit SCL = P2^0;  /* ʱ���� */

void IIC_Delay(unsigned char i)
{
    do{_nop_();}
    while(i--);        
}

//������������
void IIC_Start(void)
{
    SDA = 1;
    SCL = 1;
    IIC_Delay(DELAY_TIME);
    SDA = 0;
    IIC_Delay(DELAY_TIME);
    SCL = 0;	
}

//����ֹͣ����
void IIC_Stop(void)
{
    SDA = 0;
    SCL = 1;
    IIC_Delay(DELAY_TIME);
    SDA = 1;
    IIC_Delay(DELAY_TIME);
}

//����Ӧ��
void IIC_SendAck(bit ackbit)
{
    SCL = 0;
    SDA = ackbit;  					// 0��Ӧ��1����Ӧ��
    IIC_Delay(DELAY_TIME);
    SCL = 1;
    IIC_Delay(DELAY_TIME);
    SCL = 0; 
    SDA = 1;
    IIC_Delay(DELAY_TIME);
}

//�ȴ�Ӧ��
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

//ͨ��I2C���߷�������
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

//��I2C�����Ͻ�������
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

// //�������Ŷ���
// sbit SDA = P2^1;  /* ������ */
// sbit SCL = P2^0;  /* ʱ���� */

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