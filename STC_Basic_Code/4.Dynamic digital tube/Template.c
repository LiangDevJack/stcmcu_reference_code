/*#include<STC15F2K60S2.H>
#include<INTRINS.H>

#define uchar unsigned char
#define uint unsigned char
uchar tap[]={0XC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XF8,0X80,0X90,0XBF,0XFF};
uchar yi,er,san,si,wu,liu,qi,ba;
bit s4,s5;s6,s7;
void Display1(yi,er);
void Display2(san,si);
void Display3(wu,liu);
void Display4(qi,ba);


void keyscan(void);
void Allinit (void);
void Delayms(int ms);
uchar num;
void main(void)
{
	Allinit();
	yi=1;er=2;san=3;si=4;wu=5;liu=6;qi=7;ba=8;
	while(1)
	{
		//keyscan16();
		keyscan();
		Display1(yi,er);
		yi=num;
		if(s7==1)
		{
			yi=11;er=11;san=11;si=11;wu=11;liu=11;qi=2;ba=5;
			Display1(yi,er);
			Display2(san,si);
			Display3(wu,liu);
			Display4(qi,ba);
		}
	}
}
void keyscan16(void)//矩阵按键
{
	uchar temp;
	
	P44=0;P42=1;P3=0X7F;//0111 1111
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
				case 0X7E:num=0;break;//0111 1110
				case 0X7D:num=1;break;//0111 1101
				case 0X7B:num=2;break;
				case 0X77:num=3;break;
			}
			while(temp!=0X0F)
			{
				temp=P3;
				temp=temp&0X0F;
			}
		}
	}
	
	P44=1;P42=0;P3=0XBF;
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
				case 0XBE:num=4;break;
				case 0XBD:num=5;break;
				case 0XBB:num=6;break;
				case 0XB7:num=7;break;
			}
			while(temp!=0X0F)
			{
				temp=P3;
				temp=temp&0X0F;
			}
		}
	}
		
	P44=1;P42=1;P3=0XDF;
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
				case 0XDE:num=8;break;
				case 0XDD:num=9;break;
				case 0XDB:num=10;break;
				case 0XD7:num=11;break;
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
				case 0XEE:num=12;break;
				case 0XED:num=13;break;
				case 0XEB:num=14;break;
				case 0XE7:num=15;break;
			}
			while(temp!=0X0F)
			{
				temp=P3;
				temp=temp&0X0F;
			}
		}
	}
}
void keyscan(void)//独立键盘
{
	if(P30==0)
	{
		Delayms(5);
		if(P30==0)
		{
			s7=1;yi=1;
		}
		while(!P30);//等待手的松开,抬手检测
	}
	else if(P31==0)
	{
		Delayms(5);
		if(P31==0)
		{
			s6=1;er=2;
		}
		while(!P31);//等待手的松开,抬手检测
	}
	else if(P32==0)
	{
		Delayms(5);
		if(P32==0)
		{
			s5=1;san=3;
		}
		while(!P32);//等待手的松开,抬手检测
	}
	else	if(P33==0)
	{
		Delayms(5);
		if(P33==0)
		{
			s4=1;si=4;
		}
		while(!P33);//等待手的松开,抬手检测
	}
}






void Display1(yi,er)//数码管
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
	P2=0XA0;//打开控制蜂鸣器的573
	P0=0X00;//关闭蜂鸣器继电器
	
	P2=0XC0;//打开控制数码管的位选573
	P0=0XFF;//选中所有的数码管
	P2=0XE0;//打开控制数码管段选573
	P0=0XFF;//关闭所有数码管
	
	P2=0X80;//打开控制LED灯的573
	P0=0XFF;//关闭所有LED灯
}



void Delayms (int ms)
{
	int i,j;
	for(i=0;i<ms;i++)
		for(j=845;j>0;j--);
}
/*void Delayms (int ms)
{
	uchar i,j,k;
	for(k=0;k<ms;k++)
		{
			_nop_();
			_nop_();
			_nop_();
			i=11;
			j=190;
			do
			{
				while(--j);
			} 
				while(--i);
		}
}*/







