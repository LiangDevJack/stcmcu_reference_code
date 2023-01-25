#ifndef __IIC_H
#define __IIC_H

void IIC_Start(void); 
void IIC_Stop(void);  
bit IIC_WaitAck(void);  
void IIC_SendAck(bit ackbit); 
void IIC_SendByte(unsigned char byt); 
unsigned char IIC_RecByte(void); 

unsigned char AD_read(unsigned char dat);
void AD_write(unsigned char dat);

void AT24C02_write(unsigned char add,unsigned char dat);
unsigned char AT24C02_read(unsigned char add);

#endif