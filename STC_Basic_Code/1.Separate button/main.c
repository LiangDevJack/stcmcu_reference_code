//��������LED��
/*#include<STC15F2K60S2.H>

void main(void)
{
	P2=0XA0;P0=0X00;P2=0X80;P0=0XFF;
	
	while(1)
	{
	if(P30==0)P00=0;
	if(P31==0)P0=0X01;
	}
}
*/	
//����һ����ˮ��
/*#include<STC15F2K60S2.H>

unsigned char LED;
void Delayms(int ms);

void main(void)
{
	P2=0XA0;P0=0X00;P2=0X80;P0=0XFF;
	if(P30==0)
	{
		for(LED=0;LED<8;LED++)
		{
			P0=~(0X01<<LED);
			Delayms(1000);
		}
	}
}
void Delayms(int ms)
{
	int i,j;
	for(i=0;i<ms;i++)
		for(j=845;j>0;j--);
}
*/
//����������ˮ��ѭ��
/*#include<STC15F2K60S2.H>

unsigned char LED;
unsigned char LED_RUN;
void Delayms(int ms);

void main(void)
{
	P2=0XA0;P0=0X00;P2=0X80;P0=0XFF;
	while(1)
	{
		if(P30==0)LED_RUN=1;
		if(LED_RUN==1)
		{
			for(LED=0;LED<8;LED++)
			{
				P0=~(0X01<<LED);
				Delayms(1000);
			}
		}
	}
}
void Delayms(int ms)
{
	int i,j;
	for(i=0;i<ms;i++)
		for(j=845;j>0;j--);
}
*/

//����������ˮ��
/*#include<STC15F2K60S2.H>

unsigned char LED=0;
void Delayms(int ms);

void main(void)
{
	P2=0XA0;P0=0X00;P2=0X80;P0=0XFF;
	
	while(1)
	{
		if(P30==0)LED++;
		P0=~(0X01<<LED);
		Delayms(100);
	}
}
void Delayms(int ms)
{
	int i,j;
	for(i=0;i<ms;i++)
		for(j=845;j>0;j--);
}
*/
//������������ˮ��
/*#include<STC15F2K60S2.H>

unsigned char LED=0;
void Delayms(int ms);

void main(void)
{
	P2=0XA0;P0=0X00;P2=0X80;P0=0XFF;
	
	while(1)//����Ϊ���㳣����ѭ��
	{
		if(P30==0)
		{
			Delayms(5);//����������
			if(P30==0)
			{
				P0=~(0X01<<LED);
				LED++;
				if(LED==8)LED=0;//ѭ��
			}
			while(!P30);//P30!=0Ϊ��ֹͣ��
			Delayms(100);
	  }
	}
}

void Delayms(int ms)
{
	int i,j;
	for(i=0;i<ms;i++)
		for(j=845;j>0;j--);
}
*/
/*#include<STC15F2K60S2.H>

unsigned char LED=0;
void Delayms(int ms);

void main(void)
{
	P2=0XA0;P0=0X00;P2=0X80;P0=0XFF;
	
	while(1)
	{
		if(P30==0)LED++;
		P0=~0X01<<LED;
		//Delayms(100);
	}
}
void Delayms(int ms)
{
	int i,j;
	for(i=0;i<ms;i++)
		for(j=845;j>0;j--);
}*/
	
//������������ˮ��
/*#include<STC15F2K60S2.H>

unsigned char LED=0;
void Delayms(int ms);

void main(void)
{
	P2=0XA0;P0=0X00;P2=0X80;P0=0XFF;
	
	while(1)
	{
		if(P30==0)
		{
			Delayms(5);//����������
			if(P30==0)
			{
				P0=~(0X01<<LED);
				LED++;
				if(LED==8)LED=0;
			}
			while(!P30);//������
			Delayms(100);//����
	  }
	}
}
void Delayms(int ms)
{
	int i,j;
	for(i=0;i<ms;i++)
		for(j=845;j>0;j--);
}
*/	

//��������LED�ƣ�̧�ּ��
/*#include<STC15F2K60S2.H>

unsigned char LED=0;
unsigned char LED_Flag=0;
void Delayms(int ms);

void main(void)
{
	P2=0XA0;P0=0X00;P2=0X80;P0=0XFF;
	
	while(1)
	{
		if(P30==0)
		{
			Delayms(5);//����������
			if(P30==0)
			{
				LED_Flag=1;
			}
			while(!P30);//ֹͣ
		}
			if(LED_Flag==1)
			{
				LED_Flag=0;
				P0=~(0X01<<LED);
				LED++;
				if(LED==8)LED=0;
			}
	}
			
}
void Delayms(int ms)
{
	int i,j;
	for(i=0;i<ms;i++)
		for(j=845;j>0;j--);
}
*/
//����������ˮ�ƣ��Ӻ���
/*#include<STC15F2K60S2.H>

unsigned char LED=0;
unsigned char LED_Flag=0;
void Delayms(int ms);
void Key_Scan(void);

void main(void)
{
	P2=0XA0;P0=0X00;P2=0X80;P0=0XFF;
	
	while(1)
	{
			Key_Scan();
			if(LED_Flag==1)
			{
				LED_Flag=0;
				P0=~(0X01<<LED);
				LED++;
				if(LED==8)LED=0;
			}
	}
}
void Key_Scan(void)
{	
    if(P30==0)//����S7
		{
			Delayms(5);//����������
			if(P30==0)
			{
				LED_Flag=1;
			}
			while(!P30);
		}
		if(P31==0)//����S6
		{
			Delayms(5);//����������
			if(P31==0)
			{
				LED_Flag=1;
			}
			while(!P31);
		}
		if(P32==0)//����S5
		{
			Delayms(5);//����������
			if(P32==0)
			{
				LED_Flag=1;
			}
			while(!P32);
		}
		if(P33==0)//����S4
		{
			Delayms(5);//����������
			if(P33==0)
			{
				LED_Flag=1;
			}
			while(!P33);
		}
}
void Delayms(int ms)
{
	int i,j;
	for(i=0;i<ms;i++)
		for(j=845;j>0;j--);
}
*/

//����������ˮ�ƣ��ĸ�����
/*#include<STC15F2K60S2.H>

unsigned char LED=0;
unsigned char LED_Flag=0;
unsigned char LED_RUN=0;
void Delayms(int ms);
void Key_Scan(void);

void main(void)
{
	P2=0XA0;P0=0X00;P2=0X80;P0=0XFF;
	
	while(1)
	{
			Key_Scan();
			if(LED_Flag==1)
			{
				LED_Flag=0;
				P0=~(0X01<<LED);
				LED++;
				if(LED==8)LED=0;
				Delayms(1000);
			}
			
			if(LED_RUN==1)
			{
				P0=~(0X01<<LED);
				LED++;
				if(LED==8)LED=0;
				Delayms(1000);
			}			
	}
}
void Key_Scan(void)
{	
    if(P30==0)//����S7
		{
			Delayms(5);//����������
			if(P30==0)
			{
				LED_Flag=1;
			}
			while(!P30);
		}
		if(P31==0)//����S6
		{
			Delayms(5);//����������
			if(P31==0)
			{
				LED_RUN=1;
			}
			while(!P31);
		}
		if(P32==0)//����S5
		{
			Delayms(5);//����������
			if(P32==0)
			{
				P00=0;
			}
			while(!P32);
		}
		if(P33==0)//����S4
		{
			Delayms(5);//����������
			if(P33==0)
			{
			P00=1;
			}
			while(!P33);
		}
}
void Delayms(int ms)
{
	int i,j;
	for(i=0;i<ms;i++)
		for(j=845;j>0;j--);
}
*/

//#include<STC15F2K60S2.H>

//unsigned char LED=0;
//unsigned char LED_Flag=0;
//void Delayms(int ms);
//void Key_Scan(void);

//void main(void)
//{
//	P2=0XA0;P0=0X00;P2=0X80;P0=0XFF;
//	
//	while(1)
//	{
//			Key_Scan();
//			if(LED_Flag==1)
//			{
//				LED_Flag=0;
//				P0=0XFE<<LED;
//				LED++;
//				if(LED==8)LED=0;
//			}
//	}
//}
//void Key_Scan(void)
//{	
//    if(P30==0)//����S7
//		{
//			Delayms(5);//����������
//			if(P30==0)
//			{
//				LED_Flag=1;
//			}
//			while(!P30);
//		}
//		if(P31==0)//����S6
//		{
//			Delayms(5);//����������
//			if(P31==0)
//			{
//				LED_Flag=1;
//			}
//			while(!P31);
//		}
//		if(P32==0)//����S5
//		{
//			Delayms(5);//����������
//			if(P32==0)
//			{
//				LED_Flag=1;
//			}
//			while(!P32);
//		}
//		if(P33==0)//����S4
//		{
//			Delayms(5);//����������
//			if(P33==0)
//			{
//				LED_Flag=1;
//			}
//			while(!P33);
//		}
//}
//void Delayms(int ms)
//{
//	int i,j;
//	for(i=0;i<ms;i++)
//		for(j=845;j>0;j--);
//}

#include<STC15F2K60S2.H>
unsigned char s7flag=0,s6flag=0;
void delayms(unsigned int ms);
void keyscan(void);
unsigned char LED=0;
void main(void)
{

	P2=0XA0;P0=0X00;P2=0X80;P0=0XFF;
	for(LED=0;LED<8;LED++)
		{
			P0=~(0X01<<LED);//0000 0001 ~ 1111 1110 //0000 0010 ~ 1111 1101
			delayms(1000);
		}
	while(1)
	{
//	  keyscan();
		
		for(LED=0;LED<8;LED++);
		  {
			  P0=~(0X01<<LED);
				
				delayms(500);
			}
//		if(s7flag==1)
//		{
//			s7flag=0;
//      
//			for(LED=0;LED<8;LED++);
//		  {
//			  P0=~(0X01<<LED);
//				delayms(500);
//			}
//		}
//		if(s6flag==1)
//		{
//		  s6flag=0;
//			
//			for(LED=0;LED<8;LED++);
//			{
//			  P0=~(0X80>>LED);
//				delayms(500);
//			}
//		}
	}
}
void keyscan(void)
{
  if(P30==0)
	{
		delayms(10);
		if(P30==0)
		{
		  s7flag=1;
		}
		while(!P30);
	}
	if(P31==0)
	{
	  delayms(10);
		if(P31==0)
		{
			s6flag=1;
		}
		while(!P31);
	}
}
void delayms(unsigned int ms)
{
  int i,j;
	for(i=0;i<ms;i++)
	for(j=845;j>0;j--);
}


