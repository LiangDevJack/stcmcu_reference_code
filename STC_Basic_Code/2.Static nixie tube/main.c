
/*#include<STC15F2K60S2.H>
void Delayms(int ms);
void main (void)
{
	P2=0XA0;P0=0X00;P2=0X80;P0=0XFF;
	P2=0XC0;P0=0X01;P2=0XFF;P0=0XFF;
	
	while(1)
	{
		P0=0XC0;
		Delayms(1000);
		P0=0XF9;
		Delayms(1000);
		P0=0XB0;
		Delayms(1000);	
		P0=0X99;
		Delayms(1000);
		P0=0X92;
		Delayms(1000);
		P0=0X82;
		Delayms(1000);
		P0=0XF8;
		Delayms(1000);
		P0=0X80;
		Delayms(1000);
		P0=0X90;
		Delayms(1000);
		P0=0XBF;
		Delayms(1000);
		P0=0XFF;
		Delayms(1000);
	}
}
void Delayms(int ms)
{
	int i,j;
	for(i=0;i<ms;i++)
		for(j=845;j>0;j--);

}
*/

#include<STC15F2K60S2.H>
void Delayms(int ms);
void Key_Scan(void);
unsigned char tap[]={0XC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XF8,0X80,0X90,\
0X88,0X80,0xC6,0XC0,0X86,0X8E};
unsigned char num;
unsigned char SMG_Flag;
void main (void)
{
	P2=0XA0;P0=0X00;P2=0X80;P0=0XFF;
	P2=0XC0;P0=0X01;P2=0XFF;P0=0XFF;
	while(1)
	{
		Key_Scan();
		if(SMG_Flag==1)
			{
				P0=tap[num];
				Delayms(1000);
				num++;
				if(num==16)num=0;//±‹√‚¬“¬Î
			}
	}
}
void Key_Scan(void)
{
	if(P33==0)
	{
		Delayms(5);
		if(P33==0)
		{
			SMG_Flag=1;
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

