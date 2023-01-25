//EEPROM�洢����ģ��ת��
#include<STC15F2K60S2.H>
unsigned char tap[]={0XC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XF8,0X80,0X90,0XBF,0XFF};
unsigned char yi,er,san,si,wu,liu,qi,ba;
unsigned char count;
unsigned char tt;
unsigned char s6;
unsigned char LED=0;
unsigned char start=0;
unsigned int time=100;
unsigned char luminance=10;
unsigned char model=0;
unsigned char LED_Model=0;
sbit SDA=P2^1;
sbit SCL=P2^0;
void InitTimer0();
void Select_Model(void);
void Scan_Keys();
void LED_Indicator();
void Allinit(void);
void Display1(yi,er);
void Display2(san,si);
void Display3(wu,liu);
void Display4(qi,ba);
void Delayms(int ms);
void Delay6us();
void main (void)
{
	Allinit();
	InitTimer0();
	yi=11;er=11;san=11;si=11;wu=11;liu=11;qi=11;ba=11;
	while(1)
	{
		Scan_Keys();
		Select_Model();
		Display1(yi,er);
		Display2(san,si);
		Display3(wu,liu);
		Display4(qi,ba);
	}
}

//=========================�������ʾ========================
void Select_Model(void)
{
	if(s6==1)
	{
		switch(model)
		{
			case 0:
			{
				yi=0;er=LED_Model;san=0;si=11;wu=11;liu=time/100;
				qi=time%100/10;ba=time%10;
				
				break;
			}
			case 1:
			{
				tt++;
				yi=11;er=11;san=11;si=11;wu=11;
				qi=time%100/10;ba=time%10;
				if(tt==100)
				{
					yi=0;er=LED_Model;san=0;si=11;wu=11;liu=time/100;
					qi=time%100/10;ba=time%10;
					tt=0;
				}

				break;		
			}
			case 2:
			{
				tt++;
				yi=0;er=LED_Model;san=0;si=11;wu=11;liu=11;
				qi=11;ba=11;
				if(tt==100)
				{
					liu=time/100;
					qi=time%100/10;ba=time%10;
					tt=0;
				}
			
				break;	
			}
		}
	}
}
//=========================LEDָʾ��=========================
void InitTimer0()
{
	TMOD=0X01;
	TH0=(65535-1000)/256;
	TL0=(65535-1000)%256;
	
	EA=1;
	ET0=1;
	
}

void Service_Timer0() interrupt 1
{
	TH0=(65535-1000)/256;
	TL0=(65535-1000)%256;
	
	
	LED_Indicator();
	
}
void LED_Indicator()
{
	count++;
	switch(LED_Model)
	{
		case 0:
		P2=0X80;
		if(count<=10)
		{
			P0=~(0X01<<LED);
		}
		else if(count<=luminance)
		{
			P0=0XFF;
		}
		else 
		{
			LED++;
			P0=~(0X01<<LED);
			count=0;
			if(LED==8)
			{
				LED_Model=1;
				LED=0;
			}	
		}
		break;
		
		case 1:
			P2=0X80;
		if(count<=time)
		{
			P0=~(0X80>>LED);
		}
		else if(count<=10)
		{
			P0=0XFF;
		}
		else 
		{
			LED++;
			P0=~(0X80>>LED);			
			count=0;
			if(LED==8)
			{
				LED_Model=2;
				LED=0;
			}
		}
		break;
		
		case 2:
			P2=0X80;
		if(count<=time)
		{
			P0=~((0X80>>LED)|(0X01<<LED));
		}
		else if(count<=10)
		{
			P0=0XFF;
		}
		else 
		{
			LED++;
			P0=~((0X80>>LED)|(0X01<<LED));
			count=0;
			if(LED==4)
			{
				LED_Model=3;
				LED=0;
			}
		}
		break;
		
		case 3:
			P2=0X80;
		if(count<=time)
		{
			P0=~((0X08>>LED)|(0X10<<LED));
		}
		else if(count<=10)
		{
			P0=0XFF;
		}
		else 
		{
			LED++;
			P0=~((0X08>>LED)|(0X10<<LED));
			count=0;
			if(LED==4)
			{
				LED_Model=0;
				LED=0;
			}
		}
		break;
	}
}
//========================��������===========================
void Scan_Keys()//S7����
{
	if(P30==0)
	{
		Delayms(5);
		if(P30==0)
		{
			TR0=!TR0;
		}
		while(!P30);
	}
	else if(P31==0)//S6���� ���ð���
	{
		Delayms(5);
		if(P31==0)
		{
			s6=1;
			model++;
			if(model==3)
			{
				model=0;
			}
		}
		while(!P31);
	}
	else if(P32==0)//S5����
	{
		Delayms(5);
		if(P32==0)
		{
			luminance=luminance+10;
			time=time+50;
			if(time==300)
			{
				time=100;
			}
		}
		while(!P32);
	}
	else if(P33==0)//S4����
	{
		Delayms(5);
		if(P33==0)
		{
			time=time-50;
			if(time==50)
			{
				time=250;
			}
		}
		while(!P33);
	}
}

//=====================PCF8591ģ��ת��=======================
void IIC_Start()
{
	SDA=1;
	SCL=1;
	Delay6us();
	SDA=0;
	Delay6us();
	SCL=0;
}
void IIC_Stop()
{
	SDA=0;
	SCL=1;
	Delay6us();
	SDA=1;
}
void IIC_SendByte(unsigned char dat)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		if(dat&0X80)SDA=1;
		else SDA=0;
		Delay6us();
		SCL=1;
		dat<<=1;
		Delay6us();
		SCL=0;
	}
}
bit IIC_WaitAck()
{
	SDA=1;
	Delay6us();
	SCL=1;
	Delay6us();
	if(SDA)
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
void IIC_SendAck(bit ackbit)
{
    SCL = 0;
    SDA = ackbit;  					// 0��Ӧ��1����Ӧ��
    Delay6us();
    SCL = 1;
    Delay6us();
    SCL = 0; 
    SDA = 1;
    Delay6us();
}
unsigned char IIC_RecByte()
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
unsigned char AD_Read(unsigned char add)
{
	unsigned char temp;
	IIC_Start();
	IIC_SendByte(0X90);
	IIC_WaitAck();
	IIC_SendByte(add);
	IIC_WaitAck();
	IIC_Stop();
	
	IIC_Start();
	IIC_SendByte(0X91);
	IIC_WaitAck();
	temp=IIC_RecByte();
	IIC_Stop();
	
	temp=temp*0.039;
	return temp;
}
//=====================AT24C02�洢оƬ=======================
void Write_24C02(unsigned char addr, unsigned char dat)
{
	IIC_Start();		//IIC������ʼ�ź�					
	IIC_SendByte(0xa0); 	//24C02��д�豸��ַ
	IIC_WaitAck();		//�ȴ��ӻ�Ӧ��	
	IIC_SendByte(addr); 	//�ڴ��ֽ��ֽ�
	IIC_WaitAck(); 		//�ȴ��ӻ�Ӧ��	
	IIC_SendByte(dat); 	//д��Ŀ������
	IIC_WaitAck();		//�ȴ��ӻ�Ӧ��	
	IIC_Stop();
}
unsigned char Read_24C02(unsigned char addr)
{
	unsigned char tmp;
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
	tmp = IIC_RecByte();	//��ȡĿ������
	IIC_SendAck(0); 		//������Ӧ���ź�		
	IIC_Stop();		//IIC����ֹͣ�ź�			
	return tmp;
}
//===========================================================
void Allinit(void)
{
	P2=0XA0;
	P0=0X00;
	
	P2=0XC0;
	P0=0XFF;
	P2=0XFF;
	P0=0XFF;
	
	P2=0X80;
	P0=0XFF;
}
void Display1(yi,er)
{
	P2=0XC0;
	P0=0X01;
	P2=0XFF;
	P0=tap[yi];
	Delayms(1);
	
	P2=0XC0;
	P0=0X02;
	P2=0XFF;
	P0=tap[er];
	Delayms(1);
}
void Display2(san,si)
{
	P2=0XC0;
	P0=0X04;
	P2=0XFF;
	P0=tap[san];
	Delayms(1);
	
	P2=0XC0;
	P0=0X08;
	P2=0XFF;
	P0=tap[si];
	Delayms(1);
}
void Display3(wu,liu)
{
	P2=0XC0;
	P0=0X10;
	P2=0XFF;
	P0=tap[wu];
	Delayms(1);
	
	P2=0XC0;
	P0=0X20;
	P2=0XFF;
	P0=tap[liu];
	Delayms(1);
}
void Display4(qi,ba)
{
	P2=0XC0;
	P0=0X40;
	P2=0XFF;
	P0=tap[qi];
	Delayms(1);
	
	P2=0XC0;
	P0=0X80;
	P2=0XFF;
	P0=tap[ba];
	Delayms(1);
}
void Delayms(int ms)
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



