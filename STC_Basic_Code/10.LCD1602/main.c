#include<STC15F2K60S2.H>
#include<INTRINS.H>

#define LCD1602_DB P0
sbit LCD1602_RS=P2^0;  //RS,数据/命令选择端(H/L)
sbit LCD1602_RW=P2^1;  //R/W，读/写选择端(H/L)
sbit LCD1602_E=P1^2;  // E,使能信号


//读状态
void read_state(void)
{
	unsigned char sta;			//状态读取存储变量
	LCD1602_DB=0xff;	
	LCD1602_RS=0;
	LCD1602_RW=1;
	LCD1602_E=1;
	do
	{
		LCD1602_E=1;
		sta=LCD1602_DB;	//把状态字读取到sta变量中，可通过最高位判断液晶是否处于忙态，1时为忙 
		LCD1602_E=0;	//释放总线，防止影响其他模块
	}while(sta&0x80);	//判断最高位，直到允许读写时跳出循环
}

//写指令
void write_cmd(unsigned char cmd)
{
	read_state();
	LCD1602_RS=0; 	//RS=0->指令
	LCD1602_RW=0;	//R/W=0->写
	LCD1602_DB=cmd;	//写入指令
	LCD1602_E=1;	
	LCD1602_E=0;			
}
 
 //写数据
void write_data(unsigned char date)
{
	read_state();
	LCD1602_RS=1;   //RS=1->数据
	LCD1602_RW=0;	//R/W=0->写
	LCD1602_DB=date;	//写入数据
	LCD1602_E=1;
	LCD1602_E=0;
}
//LCD初始化设置
void lcd_init()
{		
	LCD1602_E=0;		 //使能关(操作前关使能使用时打开)
	write_cmd(0x3c);     //设置16*2显示，5*7点阵，8位数据口
	write_cmd(0x0c);     //设置开显示，不显示光标
	write_cmd(0x06);     //设置写一个字符后地址指针自动加1
	write_cmd(0x01);     //显示清0，数据指针清0
}

//x为列，范围0~39
//y为行,0——第1行,1——第2行
//将坐标转换为对应的RAM地址，实际指针地址为0x80+RAM映射地址，0x80为指令固定位
void LCD1602_SetRAM(unsigned char x,unsigned char y)
{
    unsigned char addr;
    if(y == 0)
        addr = 0x80 + x;
    else
        addr = 0xc0 + x;
    write_cmd(addr);
}

//对应位置显示字符串
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
	LCD1602_Show(0,0,"Hello everyone!");	//第一行显示Hello everyone!
	//向CGRAM中存入字符：write_cmd(0X40+num);num为8的倍数(0~56)
	//然后用write_data(data);循环写入8个字节，即一个字符对应的8行
	//如果要将CGRAM中自己存入的字符显示到屏幕上
	//可先write_cmd(addr);addr为DDRAM的地址
	//然后write_data(num);num=1~8,即CGRAM中的8个字符
	//注意首先要保证CGRAM中已经存入字符
 	while(1)
	{	
		write_cmd(0x18);	//显示器字符左移
		Delayms(2000);
	}					 
}








