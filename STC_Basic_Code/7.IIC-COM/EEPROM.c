/*#include<STC15F2K60S2.H>
#include<INTRINS.H>

#define uchar unsigned char
#define uint unsigned char
sbit SDA=P2^1;
sbit SCL=P2^0;
uchar AD;
uchar tap[]={0XC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XF8,0X80,0X90,0XBF,0XFF};
uchar yi,er,san,si,wu,liu,qi,ba;

void Display1(yi,er);
void Display2(san,si);
void Display3(wu,liu);
void Display4(qi,ba);

void Allinit (void);
void Delayms(int ms);
uchar num;
void Delay6us ();
void IIC_Delay(unsigned char i);
unsigned char AD_Read(unsigned char add);
void AD_Write(unsigned char dat);


void main(void)
{
	Allinit();
	yi=11;er=11;san=11;si=11;wu=11;liu=11;qi=11;ba=11;
	while(1)
	{
		AD=AD_Read(0X01);
		
		yi=AD/100;er=AD%100/10;san=AD%10;
		Display1(yi,er);
		Display2(san,si);
		Display3(wu,liu);
		Display4(qi,ba);
		
	}
}
void IIC_Delay(unsigned char i)
{
    do{_nop_();}
    while(i--);        
}
void IIC_Start()//��ʼ����
{
	SDA=1;//������
	SCL=1;//ʱ����
	Delay6us();
	SDA=0;
	Delay6us();
	SCL=0;
}
void IIC_Stop()
{
	SDA=0;//�ɸߵ���
	SCL=1;
	Delay6us();
	SDA=1;
}

void IIC_SendByte(unsigned char dat)//�����и�λ����λ����
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		if(dat&0X80)SDA=1;
		else SDA=0;
		Delay6us();//�����ȶ�״̬
		SCL=1;
		dat<<=1;
		Delay6us();
		SCL=0;
	}
}
//����Ӧ��
void IIC_SendAck(bit ackbit)
{
    SCL = 0;
    SDA = ackbit;  					// 0��Ӧ��1����Ӧ��
    IIC_Delay(5);
    SCL = 1;
    IIC_Delay(5);
    SCL = 0; 
    SDA = 1;
    IIC_Delay(5);
}
bit IIC_WaitAck(void)
{
	SDA=1;
	Delay6us();
	SCL=1;
	Delay6us();
	if(SDA)//SDA=1;�źŴ���ʧ�ܣ�ֹͣ��
	{
		SCL=0;
		IIC_Stop();
		return 0;
	}
	else
	{
		SCL=0;
		return 1;
	}
}
unsigned char IIC_RecByte(void)
{
	unsigned char i;
	unsigned char dat;
	for(i=0;i<8;i++)
	{
		SCL=1;
		Delay6us();
		dat<<=1;
		if(SDA)dat|=0X01;
		
		SCL=0;
		Delay6us();
	}
	return dat;
}
void Write_24C02(unsigned char addr, unsigned char dat)
{
	IIC_Start();		//IIC������ʼ�ź�					
	IIC_SendByte(0xa0); 	//24C02��д�豸��ַ
	IIC_WaitAck();		//�ȴ��ӻ�Ӧ��	
	IIC_SendByte(addr); 	//�ڴ��ֽ��ֽ�
	IIC_WaitAck(); 		//�ȴ��ӻ�Ӧ��	
	IIC_SendByte(dat); 	//д��Ŀ������
	IIC_WaitAck();		//�ȴ��ӻ�Ӧ��	
	IIC_Stop();		//IIC����ֹͣ�ź�		
}

unsigned char Read_24C02(unsigned char addr)
{
	unsigned char temp;
	//����һ��αд����
	IIC_Start();		//IIC������ʼ�ź�					
	IIC_SendByte(0xa0); 	//24C02д�豸��ַ
	IIC_WaitAck();		//�ȴ��ӻ�Ӧ��	
	IIC_SendByte(addr); 	//�ڴ��Լ���ַ
	IIC_WaitAck(); 		//�ȴ��ӻ�Ӧ��	
	IIC_Stop();										
	//�����ֽڶ�����
	IIC_Start();		//IIC������ʼ�ź�					
	IIC_SendByte(0xa1); 	//24C02���豸��ַ
	IIC_WaitAck();		//�ȴ��ӻ�Ӧ��	
	temp = IIC_RecByte();	//��ȡĿ������
	IIC_SendAck(0); 		//������Ӧ���ź�		
	IIC_Stop();		//IIC����ֹͣ�ź�			
	return temp;
}
void Display1(yi,er)//�����
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
}
void Display2(san,si)
{
	P2=0XC0;
	P0=0X04;
	P2=0XE0;
	P0=tap[san];
	Delayms(1);
	
	P2=0XC0;
	P0=0X08;
	P2=0XE0;
	P0=tap[si];
	Delayms(1);
}
void Display3(wu,liu)
{
	P2=0XC0;
	P0=0X10;
	P2=0XE0;
	P0=tap[wu];
	Delayms(1);
	
	P2=0XC0;
	P0=0X20;
	P2=0XE0;
	P0=tap[liu];
	Delayms(1);
}
void Display4(qi,ba)
{
	P2=0XC0;
	P0=0X40;//0100 0000
	P2=0XE0;
	P0=tap[qi];
	Delayms(1);
	
	P2=0XC0;
	P0=0X80;
	P2=0XE0;
	P0=tap[ba];
	Delayms(1);
}
void Allinit(void)
{
	P2=0XA0;//�򿪿��Ʒ�������573
	P0=0X00;//�رշ������̵���
	
	P2=0XC0;//�򿪿�������ܵ�λѡ573
	P0=0XFF;//ѡ�����е������
	P2=0XE0;//�򿪿�������ܶ�ѡ573
	P0=0XFF;//�ر����������
	
	P2=0X80;//�򿪿���LED�Ƶ�573
	P0=0XFF;//�ر�����LED��
}



void Delayms (int ms)
{
	int i,j;
	for(i=0;i<ms;i++)
		for(j=845;j>0;j--);
}
void Delay6us()		//@11.0592MHz
{
	unsigned char i;

	i = 14;
	while (--i);
}
*/