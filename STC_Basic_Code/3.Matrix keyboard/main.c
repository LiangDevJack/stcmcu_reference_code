//矩阵按键 第一列
/*
#include<STC15F2K60S2.H>

void Delayms(int ms);
void Key_Scan(void);

void main(void)
{
	P2=0XA0;P0=0X00;P2=0X80;P0=0XFF;
	
	while(1)
	{
		Key_Scan();
	}
}
void Key_Scan(void)
{
	P44=0;   
	
	if(P30==0)
	{
		Delayms(5);
		if(P30==0)
		{
			P00=0;
		}
		while(!P30);
	}
	else if(P31==0)
	{
		Delayms(5);
		if(P31==0)
		{
			P01=0;
		}
		while(!P31);
	}
		else if(P32==0)
		{
			Delayms(5);
			if(P32==0)
			{
			P02=0;
			}
			while(!P32);
		}
		else if(P33==0)
		{
			Delayms(5);
			if(P33==0)
			{
				P03=0;
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
//矩阵键盘，第一列和第二列
/*#include<STC15F2K60S2.H>
void Delayms(int ms);
void Key_Scan(void);

void main (void)
{
	P2=0XA0;P0=0X00;P2=0X80;P0=0XFF;
	while(1)
	{
		Key_Scan();
	}
}
void Key_Scan(void)
{
	P44=0;P42=1;//第一列
	if((P44==0)&&(P30==0))
	{
		Delayms(5);
		if(P30==0)
		{
			P00=0;
		}
		while(!P30);
	}
	else if((P31==0)&&(P44==0))
	{
		Delayms(5);
		if(P31==0)
		{
			P01=0;
		}
		while(!P31);
	}
	else if((P32==0)&&(P44==0))
	{
		Delayms(5);
		if(P32==0)
		{
			P02=0;
		}
		while(!P32);
	}
	else if((P33==0)&&(P44==0))
		Delayms(5);
	  if(P33==0)
		{
			P03=0;
		}
		while(!P33);
		
	P44=1;P42=0;//第二列
	if((P30==0)&&(P42==0))
	{
		Delayms(5);
		if(P30==0)
		{
			P04=0;
		}
		while(!P30);
	}
	else if((P31==0)&&(P42==0))
	{	
		Delayms(5);
		if(P31==0)
		{
			P05=0;
		}
		while(!P31);
	}
	else if((P32==0)&&(P42==0))
	{
		Delayms(5);
		if(P32==0)
		{
			P06=0;
		}
		while(!P32);
	}
	else if((P33==0)&&(P42==0))
	{
		Delayms(5);
		if(P33==0)
		{
			P07=0;
		}
		while(!P33);
	}
	
	P44=1;P42=1;P35=1;//第三列
	if((P30==0)&&(P35==0))
	{
		Delayms(5);
		if(P30==0)
		{
			
		}
		while(!P30);
	}
	else if((P31==0)&&(P35==0))
	{	
		Delayms(5);
		if(P31==0)
		{
			
		}
		while(!P31);
	}
	else if((P32==0)&&(P35==0))
	{
		Delayms(5);
		if(P32==0)
		{
			
		}
		while(!P32);
	}
	else if((P33==0)&&(P35==0))
	{
		Delayms(5);
		if(P33==0)
		{
			
		}
		while(!P33);
	}
	
	P44=1;P42=1;P35=1;P34=1;//第四列
	if((P30==0)&&(P34==0))
	{
		Delayms(5);
		if(P30==0)
		{
			
		}
		while(!P30);
	}
	else if((P31==0)&&(P34==0))
	{	
		Delayms(5);
		if(P31==0)
		{
			
		}
		while(!P31);
	}
	else if((P32==0)&&(P34==0))
	{
		Delayms(5);
		if(P32==0)
		{
		
		}
		while(!P32);
	}
	else if((P33==0)&&(P34==0))
	{
		Delayms(5);
		if(P33==0)
		{
			
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
//unsigned char tap[]={0XC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XF8,0X80,0X90,0X90,0XBF,0XFF};

//void Delayms(int ms);
//void Key_Scan(void);

//void main (void)
//{
//	P2=0XA0;P0=0X00;P2=0X80;P0=0XFF;
//	P2=0XC0;P0=0X02;P2=0XFF;P0=0XFF;
//	
//	while(1)
//	{
//		Key_Scan();
//	}
//}

//void Key_Scan(void)
//	{
//		unsigned char temp;
//		P44=0;P42=1;P3=0X7F;//0111 1111
//		temp=P3;					  //0111 1110
//		temp=temp&0X0F;//
//		if(temp!=0X0F)
//		{
//			Delayms(5);
//			temp=P3;
//			temp=temp&0X0F;
//			if(temp!=0X0F)
//			{
//				temp=P3;
//				switch(temp)
//				{
//					case 0X7E:P0=tap[1];break;//0111 1110
//					case 0X7D:P0=tap[2];break;//0111 1101
//					case 0X7B:P0=tap[3];break;//0111 1011
//					case 0X77:P0=tap[4];break;//0111 0111
//				}
//				while(temp!=0X0F)
//				{
//					temp=P3;
//					temp=temp&0X0F;
//				}							
//			}
//		}
//		P44=1;P42=0;P3=0XBF;//1011 1111
//		temp=P3;					 
//		temp=temp&0X0F;//
//		if(temp!=0X0F)
//		{
//			Delayms(5);
//			temp=P3;
//			temp=temp&0X0F;
//			if(temp!=0X0F)
//			{
//				temp=P3;
//				switch(temp)
//				{
//					case 0XBE:P0=tap[5];break;//0111 1110
//					case 0XBD:P0=tap[6];break;//0111 1101
//					case 0XBB:P0=tap[7];break;//0111 1011
//					case 0XB7:P0=tap[8];break;//0111 0111
//				}
//				while(temp!=0X0F)
//				{
//					temp=P3;
//					temp=temp&0X0F;
//				}							
//			}
//		}
//		P44=1;P42=1;P3=0XDF;//1101 1111
//		temp=P3;					
//		temp=temp&0X0F;
//		if(temp!=0X0F)
//		{
//			Delayms(5);
//			temp=P3;
//			temp=temp&0X0F;
//			if(temp!=0X0F)
//			{
//				temp=P3;
//				switch(temp)
//				{
//					case 0XDE:P0=tap[9];break;
//					case 0XDD:P0=tap[10];break;
//					case 0XDB:P0=tap[11];break;
//					case 0XD7:P0=tap[12];break;
//				}
//				while(temp!=0X0F)
//				{
//					temp=P3;
//					temp=temp&0X0F;
//				}							
//			}
//		}
//		P44=1;P42=1;P3=0XEF;
//		temp=P3;					  
//		temp=temp&0X0F;//
//		if(temp!=0X0F)
//		{
//			Delayms(5);
//			temp=P3;
//			temp=temp&0X0F;
//			if(temp!=0X0F)
//			{
//				temp=P3;
//				switch(temp)
//				{
//					case 0XEE:P0=tap[13];break;//0111 1110
//					case 0XED:P0=tap[14];break;//0111 1101
//					case 0XEB:P0=tap[15];break;//0111 1011
//					case 0XE7:P0=tap[16];break;//0111 0111
//				}
//				while(temp!=0X0F)
//				{
//					temp=P3;
//					temp=temp&0X0F;
//				}							
//			}
//		}
//	}
//	void Delayms(int ms)
//		{
//			int i,j;	
//		  for(i=0;i<ms;i++)
//			for(j=845;j>0;j--);
//		}
	

#include<STC15F2K60S2.H>
unsigned char tap[]={0XC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XF8,0X80,0X90,0X90,0XBF,0XFF};
unsigned char num;
void Delayms(int ms);
void Key_Scan(void);

void main (void)
{
	P2=0XA0;P0=0X00;P2=0X80;P0=0XFF;
	P2=0XC0;P0=0X02;P2=0XFF;P0=0XFF;
	
	while(1)
	{
		Key_Scan();
		P0=tap[num%10];
	}
}

void Key_Scan(void)
	{
		unsigned char temp;
		P44=0;P42=1;P3=0X7F;//0111 1111
		temp=P3;					  //0111 1110
		temp=temp&0X0F;//
		if(temp!=0X0F)
		{
			Delayms(5);
			temp=P3;
			temp=temp&0X0F;
			if(temp!=0X0F)
			{
				temp=P3;
				switch(temp)
				{
					case 0X7E:num=1;break;//0111 1110
					case 0X7D:num=2;break;//0111 1101
					case 0X7B:num=3;break;//0111 1011
					case 0X77:num=4;break;//0111 0111
				}
				while(temp!=0X0F)
				{
					temp=P3;
					temp=temp&0X0F;
				}							
			}
		}
		P44=1;P42=0;P3=0XBF;//1011 1111
		temp=P3;					 
		temp=temp&0X0F;//
		if(temp!=0X0F)
		{
			Delayms(5);
			temp=P3;
			temp=temp&0X0F;
			if(temp!=0X0F)
			{
				temp=P3;
				switch(temp)
				{
					case 0XBE:num=5;break;//0111 1110
					case 0XBD:num=6;break;//0111 1101
					case 0XBB:num=7;break;//0111 1011
					case 0XB7:num=8;break;//0111 0111
				}
				while(temp!=0X0F)
				{
					temp=P3;
					temp=temp&0X0F;
				}							
			}
		}
		P44=1;P42=1;P3=0XDF;//1101 1111
		temp=P3;					
		temp=temp&0X0F;
		if(temp!=0X0F)
		{
			Delayms(5);
			temp=P3;
			temp=temp&0X0F;
			if(temp!=0X0F)
			{
				temp=P3;
				switch(temp)
				{
					case 0XDE:num=9;break;
					case 0XDD:num=10;break;
					case 0XDB:num=11;break;
					case 0XD7:num=12;break;
				}
				while(temp!=0X0F)
				{
					temp=P3;
					temp=temp&0X0F;
				}							
			}
		}
		P44=1;P42=1;P3=0XEF;
		temp=P3;					  
		temp=temp&0X0F;//
		if(temp!=0X0F)
		{
			Delayms(5);
			temp=P3;
			temp=temp&0X0F;
			if(temp!=0X0F)
			{
				temp=P3;
				switch(temp)
				{
					case 0XEE:num=13;break;//0111 1110
					case 0XED:num=14;break;//0111 1101
					case 0XEB:num=15;break;//0111 1011
					case 0XE7:num=16;break;//0111 0111
				}
				while(temp!=0X0F)
				{
					temp=P3;
					temp=temp&0X0F;
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
		
/*
#include <STC15F2K60S2.H>
unsigned char tap[]={0XC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XF8,0X80,0X90,0XBF,0XFF};
unsigned char Key_Value=0;
unsigned char num;
unsigned char yi,er,san,si,wu,liu,qi,ba;
void Delayms(int ms);
void Scanf_Keys(void);
void Allinit (void)；
void main (void)
{
	Allinit();
	while(1)
	{
	
	}
}
void Allinit (void)
{
	P2=0XA0;
	P0=0X00;//关闭蜂鸣器
	
	P2=0XC0;
	P0=0XFF;
	P2=0XFF;
	P0=0XFF;//关闭数码管
	
	P2=0X80;
	P0=0XFF;//关闭LED灯
}
void Display1(yi,er)//数码管
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
void Display2(san,er)
{
	P2=0XC0;
	P0=0X04;//0000 0100
	P2=0XFF;
	P0=tap[san];
	Delayms(1);
	
	P2=0XC0;
	P0=0X08;
	P2=0XFF;
	P0=tap[si];
	Delayms(1);
}
void Scanf_Keys(void)//独立按键
{
	if(P30==0)//S7按键
	{
		Delayms(5);
		if(P30==0)
		{
		
		}
		while(!P30);
	}
	if(P31==0)//S6按键
	{
		Delayms(5);
		if(P31==0)
		{
		
		}
		while(!P31);
	}
	if(P32==0)//S5按键
	{
		Delayms(5);
		if(P32==0)
		{
		
		}
		while(!P32);
	}
	if(P30==3)//S4按键
	{
		Delayms(5);
		if(P33==0)
		{
		
		}
		while(!P33);
	}
}
void KeyScan(void)
{
	unsigned char temp;
	P44=0;P42=1;P3=0X7F;//0111 1111
	temp=P3;
	temp=temp & 0X0F;//0000 1111 & 0111 1110 = 0000 1110
	if(temp!=0X0F)
	{
		Delayms(5);
		temp=P3;
		temp=temp & 0X0F;
		if(temp!=0X0F)
		{
			temp=P3;
			switch(temp)
			{
				case 0X7E:num=1;break;//0111 1110
				case 0X7D:num=2;break;//0111 1101
				case 0X7B:num=3:break;//0111 1011
				case 0X77:num=4:break;//0111 0111
			}
			while(temp=!0X0F)
			{
				temp=P3;
				temp=temp & 0X0F;//0111 1111 & 0111 1110 = 0111 1110
			}
		}
	}
	
	P44=1;P42=0;P3=0XBF;//1011 1111
	temp=P3;
	temp=temp & 0X0F;
	if(temp!=0X0F)
	{
		Delayms(5);
		temp=P3;
		temp=temp & 0X0F;
		if(temp!=0X0F)
		{
			temp=P3;
			switch(temp)
			{
				case 0XBE:num=1;break;//0111 1110
				case 0XBD:num=2;break;//0111 1101
				case 0XBB:num=3;break;//0111 1011
				case 0XB7:num=4;break;//0111 0111
			}
			while(temp=!0X0F)
			{
				temp=P3;
				temp=temp & 0X0F;//0111 1111 & 0111 1110 = 0111 1110
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


















































