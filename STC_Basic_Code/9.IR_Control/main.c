/*#include<STC15F2K60S2.H>

typedef unsigned int uint;   		
typedef unsigned char uchar;
sbit IRIN = P3^2;       //�������ݴ����

uchar IrValue[6];
uint Time;
uchar yi,er,san;

uchar code tap[]={0XC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XF8,0X80,0X90,0X88,0X00,0XC6,0X40,0X86,0X8E,0XFF};

void delay(uint i)
{
	while (i--);
}
void Delayms (int ms)
{
	int i,j;
	for(i=0;i<ms;i++)
		for(j=845;j>0;j--);
}
void Display1(yi,er,san)//�����
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
	
	P2=0XC0;
	P0=0X04;
	P2=0XE0;
	P0=tap[san];
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

void IrInit()
{
	IT0=1;		 //�½��ش���
	EX0=1;		 //���ж�0����
	EA=1;		 //�����ж�
	IRIN=1;		 //��ʼ���˿�
}
void ReadIr() interrupt 0
{
	uchar j,k;
	uint err;
	Time = 0;
	delay(700);
	if(IRIN==0)
	{
		err=1000;	//1000*10us=10ms,����˵�����ܵ�������ź�
		while((IRIN==0)&&(err>0))//�ȴ�ǰ��9ms�ĵ͵�ƽ��ȥ
		{
			delay(1);//10us
			err--;
		}
		if(IRIN==1)//�����ȷ�ȵ�9ms�͵�ƽ
		{
			err=500;	 
			while((IRIN==1)&&(err>0))//�ȴ�4.5ms����ʼ�ߵ�ƽ��ȥ
			{
				delay(1);
				err--;
			}
			for(k=0;k<4;k++)//����4������
			{
				for(j=0;j<8;j++)//����һ������
				{
					err=60;
					while((IRIN==0)&&(err>0))//�ȴ��ź�ǰ���560us�͵�ƽ��ȥ
					{
						delay(1);
						err--;
					}
					err = 500;
					while((IRIN==1)&&(err>0))//����ߵ�ƽ��ʱ�䳤��
					{
						delay(10);	//0.1ms
						Time++;
						err--;
						if(Time>30)
						{
							return;
						}	
					}
					IrValue[k]>>=1;//k��ʾ�ڼ�������
					if(Time>=8)//����ߵ�ƽ���ִ���565us����ô��1
					{
						IrValue[k]|=0x80;
					}
					Time=0;	//�������¸�ֵ
				}
			}
		}
		if(IrValue[2]!=~IrValue[3])//�÷����ж�������ȷ
		{
			return;
		}
	}	
}
void main()
{
	IrInit();
	Allinit();
	while(1)
	{
		yi=IrValue[2]/16;er=IrValue[2]%16;san=16;
		Display1(yi,er,san);
	}  
}
*/










