//实践一
/*#include<STC15F2K60S2.H>
unsigned char TAP[]={0XC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XF8,0X80,0X90,0XBF};
unsigned char yi,er,san,si,wu,liu,qi,ba;
void display (yi,er,san,si,wu,liu,qi,ba);
void Delayms(int ms);
void main(void)
{
	P2=0XA0;P0=0XFF;
	while(1)
	{
		yi=2;er=3;san=10;si=5;liu=9;qi=5;ba=0;
		
		display(yi,er,san,si,wu,liu,qi,ba);
	}	
	

}
void display (yi,er,san,si,wu,liu,qi,ba)
{
	P2=0XC0;
	P0=0X01;
	P2=0XFF;
	P0=TAP[yi];
	Delayms(1000);
	P2=0XC0;
	P0=0X02;
	P2=0XFF;
	P0=TAP[er];
	Delayms(1000);
	P2=0XC0;
	P0=0X04;
	P2=0XFF;
	P0=TAP[san];
	Delayms(1000);
	P2=0XC0;
	P0=0X08;
	P2=0XFF;
	P0=TAP[si];
	Delayms(1000);
	P2=0XC0;
	P0=0X10;
	P2=0XFF;
	P0=TAP[wu];
	Delayms(1000);
	P2=0XC0;
	P0=0X20;
	P2=0XFF;
	P0=TAP[liu];
	Delayms(1000);
	P2=0XC0;
	P0=0X40;
	P2=0XFF;
	P0=TAP[qi];
	Delayms(1000);
	P2=0XC0;
	P0=0X80;
	P2=0XFF;
	P0=TAP[ba];
	Delayms(1000);
}


void Delayms(int ms)
{
	int i,j;
	for(i=0;i<ms;i++)
		for(j=845;j>0;j--);

}
*/

/*#include<STC15F2K60S2.H>
unsigned char TAP[]={0XC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XF8,0X80,0X90,0XBF};
unsigned char yi,er,san;
unsigned int num=999;
unsigned int k=0;
unsigned char y=1;
void jiou (void);
void s4 (void);
void display (yi,er,san);
void Key_Scan (void);
void Delayms(int ms);
void main(void)
{
	P2=0XA0;P0=0XFF;
	yi=10;er=10;san=10;
	IT0=0;
	EX0=1;
	EA=1;
	while(1)
	{
		k++;
		if(k==500)//动态数码管间隔时间很小
		{
			k=0;
			if(y==1)num--;
			else num++;
			
		}
		yi=num/100;er=num%100/10;san=num%10;
		display(yi,er,san);
		
		jiou ();
	  Key_Scan ();
		//Delayms(1000);会导致动态数码管间隔时间很大
	
	}	
}
void jiou (void)
{
	P2=0X80;P0=0XFF;
	if(num%2)P0=0XFF;
	else P0=0XFE;
}

void Key_Scan (void)
{
	if(P33==0)
	{
		y=0;
		Delayms(5);
		if(P33==0)
	{	
		num=0;
	}
	while(!P32);
	}
}
void exint0() interrupt 0
{
	if(y==0)y=1;
		else y=0;
}
void display (yi,er,san)
{
	P2=0XC0;
	P0=0X01;
	P2=0XFF;
	P0=TAP[yi];
	Delayms(1);
	P2=0XC0;
	P0=0X02;
	P2=0XFF;
	P0=TAP[er];
	Delayms(1);
	P2=0XC0;
	P0=0X04;
	P2=0XFF;
	P0=TAP[san];
	Delayms(1);
	

}
	

void Delayms(int ms)
{
	int i,j;
	for(i=0;i<ms;i++)
		for(j=845;j>0;j--);

}
*/










