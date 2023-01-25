
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
	
	TMOD = 0x16;     //��ʱ��1�÷�ʽ1����ʱ����ʱ��0�÷�ʽ2������
	
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
 
#define uchar unsigned char   //�����޷����ַ�����uchar
#define uint unsigned int     //�����޷�����������uint
 
uchar code tab[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xbf,0xff,0x8e};//����0~9����-�������ء�����F��
uchar yi,er,san,si,wu,liu,qi,ba;   //�����ַ��ͱ���yi,er,san,si,wu,liu,qi,ba�������������ʾ���Ʊ���
 
uint fan,fan_send,zheng,zheng_send,trie,pinlv,time;
bit flag=0;
 
void delayms(int ms);          //��ʱ����
void allinit();                //��ʼ������
void display1(uchar yi,uchar er);   //��һ����������ܺ���
void display2(uchar san,uchar si);  //�������Ķ�����ܺ���
void display3(uchar wu,uchar liu);  //���塢��������ܺ���
void display4(uchar qi,uchar ba);   //���ߡ��˶�����ܺ���
void Timer0Init(void);		//5΢��@12.000MHz
void Timer1Init(void);		//1����@12.000MHz
void Frequency();         //Ƶ�ʲ�����ʾ����
 
void main()//������
{
	allinit();                  //��ʼ������
	Timer0Init();
	Timer1Init();
	yi=1;er=2;san=3;si=4;wu=5;liu=6;qi=7;ba=8;//�������������ʾ1~8�����������������ʾ���������Ƿ�����
	while(1)
	{
		Frequency();              //Ƶ�ʲ�����ʾ����
		display1(yi,er);          //��һ����������ܺ���
		display2(san,si);         //�������Ķ�����ܺ���
		display3(wu,liu);         //���塢��������ܺ���
		display4(qi,ba);          //���ߡ��˶�����ܺ���
	}
}
void Frequency()           //Ƶ�ʲ�����ʾ����
{
	yi=12;er=11;san=11;
	if(pinlv>=10000){si=pinlv/10000;wu=pinlv%10000/1000;liu=pinlv%1000/100;qi=pinlv%100/10;ba=pinlv%10;}
	else if(pinlv>=1000){si=11;wu=pinlv/1000;liu=pinlv%1000/100;qi=pinlv%100/10;ba=pinlv%10;}
	else if(pinlv>=100){si=11;wu=11;liu=pinlv/100;qi=pinlv%100/10;ba=pinlv%10;}
	else if(pinlv>=10){si=11;wu=11;liu=11;qi=pinlv/10;ba=pinlv%10;}
}
void Timer0Init(void)		//5΢��@12.000MHz
{
	AUXR |= 0x80;		//��ʱ��ʱ��1Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TL0 = 0xC4;		//���ö�ʱ��ֵ
	TH0 = 0xFF;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
//	TR0 = 1;		//��ʱ��0��ʼ��ʱ
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
void Timer1Init(void)		//1����@12.000MHz
{
	AUXR |= 0x40;		//��ʱ��ʱ��1Tģʽ
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	TL1 = 0x20;		//���ö�ʱ��ֵ
	TH1 = 0xD1;		//���ö�ʱ��ֵ
	TF1 = 0;		//���TF1��־
	TR1 = 1;		//��ʱ��1��ʼ��ʱ
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
void delayms(int ms)//��ʱ����
{
	uint i,j;
	for(i=ms;i>0;i--)
		for(j=845;j>0;j--);
}
void allinit()//��ʼ������
{
	P2=0XA0;P0=0X00;      //�رշ������̵���
	P2=0X80;P0=0XFF;      //�ر�����LED��
	
	P2=0XC0;P0=0XFF;      //ѡ����������ܶ�ѡ
	P2=0XFF;P0=0XFF;      //�ر����������
}
void display1(uchar yi,uchar er)//��һ����������ܺ���
{
	P2=0XC0;P0=0X01;               //ѡ�е�һ�������λѡ
	P2=0XFF;P0=tab[yi];            //�õ�һ���������ʾyiָ���ֵ
	delayms(1);                    //��ʱ1ms
	
	P2=0XC0;P0=0X02;               //ѡ�еڶ��������λѡ
	P2=0XFF;P0=tab[er];            //�õ�һ���������ʾerָ���ֵ
	delayms(1);	                   //��ʱ1ms
}
void display2(uchar san,uchar si)//�������Ķ�����ܺ���
{
	P2=0XC0;P0=0X04;               //ѡ�е�s���������λѡ
	P2=0XFF;P0=tab[san];           //�õ�һ���������ʾsanָ���ֵ
	delayms(1);                    //��ʱ1ms
	
	P2=0XC0;P0=0X08;               //ѡ�е��ĸ������λѡ
	P2=0XFF;P0=tab[si];            //�õ�һ���������ʾsiָ���ֵ
	delayms(1);	                   //��ʱ1ms
}
void display3(uchar wu,uchar liu)//���塢��������ܺ���
{
	P2=0XC0;P0=0X10;               //ѡ�е���������λѡ
	P2=0XFF;P0=tab[wu];            //�õ�һ���������ʾwuָ���ֵ
	delayms(1);                    //��ʱ1ms
	
	P2=0XC0;P0=0X20;               //ѡ�е����������λѡ
	P2=0XFF;P0=tab[liu];           //�õ�һ���������ʾliuָ���ֵ
	delayms(1);	                   //��ʱ1ms
}
void display4(uchar qi,uchar ba)//���ߡ��˶�����ܺ���
{
	P2=0XC0;P0=0X40;               //ѡ�е��߸������λѡ
	P2=0XFF;P0=tab[qi];            //�õ�һ���������ʾqiָ���ֵ
	delayms(1);                    //��ʱ1ms
	
	P2=0XC0;P0=0X80;               //ѡ�еڰ˸������λѡ
	P2=0XFF;P0=tab[ba];            //�õ�һ���������ʾbaָ���ֵ
	delayms(1);                    //��ʱ1ms          

}
*/

