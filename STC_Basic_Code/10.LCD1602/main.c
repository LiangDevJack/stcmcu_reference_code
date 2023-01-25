#include<STC15F2K60S2.H>
#include<INTRINS.H>

#define LCD1602_DB P0
sbit LCD1602_RS=P2^0;  //RS,����/����ѡ���(H/L)
sbit LCD1602_RW=P2^1;  //R/W����/дѡ���(H/L)
sbit LCD1602_E=P1^2;  // E,ʹ���ź�


//��״̬
void read_state(void)
{
	unsigned char sta;			//״̬��ȡ�洢����
	LCD1602_DB=0xff;	
	LCD1602_RS=0;
	LCD1602_RW=1;
	LCD1602_E=1;
	do
	{
		LCD1602_E=1;
		sta=LCD1602_DB;	//��״̬�ֶ�ȡ��sta�����У���ͨ�����λ�ж�Һ���Ƿ���æ̬��1ʱΪæ 
		LCD1602_E=0;	//�ͷ����ߣ���ֹӰ������ģ��
	}while(sta&0x80);	//�ж����λ��ֱ�������дʱ����ѭ��
}

//дָ��
void write_cmd(unsigned char cmd)
{
	read_state();
	LCD1602_RS=0; 	//RS=0->ָ��
	LCD1602_RW=0;	//R/W=0->д
	LCD1602_DB=cmd;	//д��ָ��
	LCD1602_E=1;	
	LCD1602_E=0;			
}
 
 //д����
void write_data(unsigned char date)
{
	read_state();
	LCD1602_RS=1;   //RS=1->����
	LCD1602_RW=0;	//R/W=0->д
	LCD1602_DB=date;	//д������
	LCD1602_E=1;
	LCD1602_E=0;
}
//LCD��ʼ������
void lcd_init()
{		
	LCD1602_E=0;		 //ʹ�ܹ�(����ǰ��ʹ��ʹ��ʱ��)
	write_cmd(0x3c);     //����16*2��ʾ��5*7����8λ���ݿ�
	write_cmd(0x0c);     //���ÿ���ʾ������ʾ���
	write_cmd(0x06);     //����дһ���ַ����ַָ���Զ���1
	write_cmd(0x01);     //��ʾ��0������ָ����0
}

//xΪ�У���Χ0~39
//yΪ��,0������1��,1������2��
//������ת��Ϊ��Ӧ��RAM��ַ��ʵ��ָ���ַΪ0x80+RAMӳ���ַ��0x80Ϊָ��̶�λ
void LCD1602_SetRAM(unsigned char x,unsigned char y)
{
    unsigned char addr;
    if(y == 0)
        addr = 0x80 + x;
    else
        addr = 0xc0 + x;
    write_cmd(addr);
}

//��Ӧλ����ʾ�ַ���
void LCD1602_Show(unsigned char x,unsigned y,unsigned char *str)
{
    LCD1602_SetRAM(x,y);
    while(*str != '\0')
    {
        write_data(*str++);
    }
}
void Delayms (int ms)
{
	int i,j;
	for(i=0;i<ms;i++)
		for(j=845;j>0;j--);
}
void main()
{
	lcd_init();
	LCD1602_Show(0,0,"Hello everyone!");	//��һ����ʾHello everyone!
	//��CGRAM�д����ַ���write_cmd(0X40+num);numΪ8�ı���(0~56)
	//Ȼ����write_data(data);ѭ��д��8���ֽڣ���һ���ַ���Ӧ��8��
	//���Ҫ��CGRAM���Լ�������ַ���ʾ����Ļ��
	//����write_cmd(addr);addrΪDDRAM�ĵ�ַ
	//Ȼ��write_data(num);num=1~8,��CGRAM�е�8���ַ�
	//ע������Ҫ��֤CGRAM���Ѿ������ַ�
 	while(1)
	{	
		write_cmd(0x18);	//��ʾ���ַ�����
		Delayms(2000);
	}					 
}








