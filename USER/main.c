#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 		 	 
#include "lcd.h"  
#include "key.h"      
#include "malloc.h"
#include "sdio_sdcard.h"  
#include "w25qxx.h"    
#include "ff.h"  
#include "exfuns.h"   
#include "text.h"  
#include "pyinput.h"
#include "touch.h"	
#include "string.h"    	
#include "usmart.h"     
#include "timer.h"
 
/************************************************
 ALIENTEK战舰STM32开发板实验46
 T9拼音输入法 实验 
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/
 
//数字表
const u8* kbd_tbl1[49]={
	"日","一","二","三","四","五","六",
	" " ," " ," " ," "  ," " ," " ,"01" ,
	"02" ,"03" ,"04" ,"05" ,"06" ,"07" ,"08" ,
	"09" ,"10","11","12","13","14","15",
	"16","17","18","19","20","21","22",
	"23","24","25","26","27","28","29",
	"30","31" ," " ," " ," " ," " ," " ,
											};
const u8* kbd_tbl2[49]={
	"日","一","二","三","四","五","六",
	" " ," " ,"01" ,"02" ,"03" ,"04" ,"05" ,
	"06" ,"07" ,"08" ,"09" ,"10","11","12",
	"13","14","15","16","17","18","19",
	"20","21","22","23","24","25","26",
	"27","28"," "," "," " ," " ," " ,
	" " ," " ," " ," " ," " ," " ," ",
											};

											const u8* kbd_tbl3[49]={
	"日","一","二","三","四","五","六",
	" " ," " ,"01" ,"02" ,"03" ,"04" ,"05" ,
	"06" ,"07" ,"08" ,"09" ,"10","11","12",
	"13","14","15","16","17","18","19",
	"20","21","22","23","24","25","26",
	"27","28","29","30","31" ," " ," " ,
	" " ," " ," " ," " ," " ," " ," ",
											};
											
											const u8* kbd_tbl4[49]={
	"日","一","二","三","四","五","六",
	" " ," " ," "  ," " ," " ,"01" ,
	"02" ,"03" ,"04" ,"05" ,"06" ,"07" ,"08" ,
	"09" ,"10","11","12","13","14","15",
	"16","17","18","19","20","21","22",
	"23","24","25","26","27","28","29",
	"30"," " ," " ," " ," " ," " ," " ," ",
											};
	const u8* kbd_tbl5[49]={
	"日","一","二","三","四","五","六",
	"01" ,
	"02" ,"03" ,"04" ,"05" ,"06" ,"07" ,"08" ,
	"09" ,"10","11","12","13","14","15",
	"16","17","18","19","20","21","22",
	"23","24","25","26","27","28","29",
	"30","31" ," " ," " ," " ," " ," " ," "," " ," " ," "  ," " ," " ,
											};

const u8* kbd_tbl6[49]={
												"日","一","二","三","四","五","六",
										    " " ," " ," " ,"01" ,"02" ,"03" ,"04" ,
												 "05" ,"06" ,"07" ,"08" ,"09","10","11",
												"12","13","14","15","16","17","18",
												"19","20","21","22","23","24","25",
												"26","27","28","29","30"," " ," " ,
												" " ," " ," " ," " ," " ," " ," " ,
											};

											const u8* kbd_tbl7[49]={
	"日","一","二","三","四","五","六",
	" " ," " ," "  ," " ," " ,"01" ,
	"02" ,"03" ,"04" ,"05" ,"06" ,"07" ,"08" ,
	"09" ,"10","11","12","13","14","15",
	"16","17","18","19","20","21","22",
	"23","24","25","26","27","28","29",
	"30","31" ," " ," " ," " ," " ," " ," ",
											};
											const u8* kbd_tbl8[49]={
	"日","一","二","三","四","五","六",
	" " ,"01" ,
	"02" ,"03" ,"04" ,"05" ,"06" ,"07" ,"08" ,
	"09" ,"10","11","12","13","14","15",
	"16","17","18","19","20","21","22",
	"23","24","25","26","27","28","29",
	"30","31" ," " ," " ," " ," " ," " ," "," " ," "  ," " ," " ,
											};
											const u8* kbd_tbl9[49]={
	"日","一","二","三","四","五","六",
	" " ," "  ," " ," " ,"01" ,
	"02" ,"03" ,"04" ,"05" ,"06" ,"07" ,"08" ,
	"09" ,"10","11","12","13","14","15",
	"16","17","18","19","20","21","22",
	"23","24","25","26","27","28","29",
	"30"," " ," " ," " ," " ," " ," " ," "," " ,
											};	
											const u8* kbd_tbl10[49]={
	"日","一","二","三","四","五","六",
	" "," " ," " ," "  ," " ," " ,"01" ,
	"02" ,"03" ,"04" ,"05" ,"06" ,"07" ,"08" ,
	"09" ,"10","11","12","13","14","15",
	"16","17","18","19","20","21","22",
	"23","24","25","26","27","28","29",
	"30","31" ," " ," " ," " ," " ," " ,
											};
											const u8* kbd_tbl11[49]={
	"日","一","二","三","四","五","六",
	" " ," " ,"01" ,
	"02" ,"03" ,"04" ,"05" ,"06" ,"07" ,"08" ,
	"09" ,"10","11","12","13","14","15",
	"16","17","18","19","20","21","22",
	"23","24","25","26","27","28","29",
	"30"," " ," " ," " ," " ," " ," " ," "," " ," " ," "  ,
											};
											const u8* kbd_tbl12[49]={
	"日","一","二","三","四","五","六",
	" " ," " ," "  ," " ,"01" ,
	"02" ,"03" ,"04" ,"05" ,"06" ,"07" ,"08" ,
	"09" ,"10","11","12","13","14","15",
	"16","17","18","19","20","21","22",
	"23","24","25","26","27","28","29",
	"30","31" ," " ," " ," " ," " ," " ," "," " ,
											};
//字符表
const u8* kbs_tbl[9]={"DEL","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz",};

u16 kbdxsize;	//虚拟键盘按键宽度
u16 kbdysize;	//虚拟键盘按键高度

extern int ri;
extern int yue;
extern int nian;
extern int flag;
extern int shi;
extern int fen;
extern int miao;

int nshi = 0;
int nfen = 0;


u8* date[3] = {"2022","6","3",};

u8* ri1[32] = {"01" ,"02" ,"03" ,"04" ,
							 "05" ,"06" ,"07" ,"08" ,"09","10","11",
							"12","13","14","15","16","17","18",
							"19","20","21","22","23","24","25",
							"26","27","28","29","30","31"};

u8* yue1[13] = {"01" ,"02" ,"03" ,"04" ,
							 "05" ,"06" ,"07" ,"08" ,"09","10","11",
							"12",};
u8* fen1[60] = {"00","01" ,"02" ,"03" ,"04" ,
							 "05" ,"06" ,"07" ,"08" ,"09","10","11",
							"12","13","14","15","16","17","18",
							"19","20","21","22","23","24","25",
							"26","27","28","29","30","31",
"32","33","34","35","36","37","38","39","40","41",
"42","43","44","45","46","47","48","49","50",
	"51",
"52","53","54","55","56","57","58","59",
};

u8* miao1[60] = {"00","01" ,"02" ,"03" ,"04" ,
							 "05" ,"06" ,"07" ,"08" ,"09","10","11",
							"12","13","14","15","16","17","18",
							"19","20","21","22","23","24","25",
							"26","27","28","29","30","31"
"32","33","34","35","36","37","38","39","40","41",
"42","43","44","45","46","47","48","49","50",
	"51",
"52","53","54","55","56","57","58","59",
};

u8* shi1[24] = {"00","01" ,"02" ,"03" ,"04" ,
							 "05" ,"06" ,"07" ,"08" ,"09","10","11",
							"12","13","14","15","16","17","18",
							"19","20","21","22","23",};

//加载键盘界面
//x,y:界面起始坐标
//void py_load_ui(u16 x,u16 y)
//{
//	u16 i;
//	POINT_COLOR=RED;
//	LCD_DrawRectangle(x,y,x+kbdxsize*3,y+kbdysize*3);						   
//	LCD_DrawRectangle(x+kbdxsize,y,x+kbdxsize*2,y+kbdysize*3);						   
//	LCD_DrawRectangle(x,y+kbdysize,x+kbdxsize*3,y+kbdysize*2);
//	POINT_COLOR=BLUE;
//	for(i=0;i<9;i++)
//	{
//		Show_Str_Mid(x+(i%3)*kbdxsize,y+4+kbdysize*(i/3),(u8*)kbd_tbl[i],16,kbdxsize);		
//		Show_Str_Mid(x+(i%3)*kbdxsize,y+kbdysize/2+kbdysize*(i/3),(u8*)kbs_tbl[i],16,kbdxsize);		
//	}  		 					   
//}


void py_load_ui(u16 x,u16 y)
{
	u16 i;
	POINT_COLOR=RED;
	LCD_DrawRectangle(x,y,x+kbdxsize*7,y+kbdysize*7);	//画一个大的矩形
	
	LCD_DrawRectangle(x+kbdxsize,y,x+kbdxsize*2,y+kbdysize*7);	//画一些小矩形
	LCD_DrawRectangle(x+kbdxsize*3,y,x+kbdxsize*4,y+kbdysize*7);	
	LCD_DrawRectangle(x+kbdxsize*5,y,x+kbdxsize*6,y+kbdysize*7);	

	LCD_DrawRectangle(x,y+kbdysize,x+kbdxsize*7,y+kbdysize*2);
	LCD_DrawRectangle(x,y+kbdysize*3,x+kbdxsize*7,y+kbdysize*4);
	LCD_DrawRectangle(x,y+kbdysize*5,x+kbdxsize*7,y+kbdysize*6);
	
//	LCD_DrawRectangle(x+kbdxsize,y,x+kbdxsize*2,y+kbdysize*3);						   
//	LCD_DrawRectangle(x,y+kbdysize,x+kbdxsize*3,y+kbdysize*2);
	POINT_COLOR=BLUE;
//	for(i=0;i<9;i++)
//	{
//		Show_Str_Mid(x+(i%3)*kbdxsize,y+4+kbdysize*(i/3),(u8*)kbd_tbl[i],16,kbdxsize);		
//		Show_Str_Mid(x+(i%3)*kbdxsize,y+kbdysize/2+kbdysize*(i/3),(u8*)kbs_tbl[i],16,kbdxsize);		
//	} 

	
	for(i=0;i<49;i++)
	{	
		if(yue == 6)
		{
					if((u8*)kbd_tbl6[i] == ri1[ri - 1])
					{
						POINT_COLOR=RED;
						Show_Str_Mid(x+(i%7)*kbdxsize,y+4+kbdysize*(i/7),(u8*)kbd_tbl6[i],16,kbdxsize);	
//						LCD_Draw_Circle(x+12+(i%7)*kbdxsize,y+4+7+kbdysize*(i/7),10);

					}
					else
					{
//						POINT_COLOR=WHITE;
//						LCD_Draw_Circle(x+12+(i%7)*kbdxsize,y+4+7+kbdysize*(i/7),10);
						POINT_COLOR=BLUE;
						Show_Str_Mid(x+(i%7)*kbdxsize,y+4+kbdysize*(i/7),(u8*)kbd_tbl6[i],16,kbdxsize);	
					}
		}
		if(yue == 1)
		{
					if((u8*)kbd_tbl1[i] == ri1[ri - 1])
					{
						POINT_COLOR=RED;
						Show_Str_Mid(x+(i%7)*kbdxsize,y+4+kbdysize*(i/7),(u8*)kbd_tbl1[i],16,kbdxsize);	


					}
					else
					{
						POINT_COLOR=BLUE;
						Show_Str_Mid(x+(i%7)*kbdxsize,y+4+kbdysize*(i/7),(u8*)kbd_tbl1[i],16,kbdxsize);	
					}
		}
				if(yue == 2)
		{
					if((u8*)kbd_tbl2[i] == ri1[ri - 1])
					{
						POINT_COLOR=RED;
						Show_Str_Mid(x+(i%7)*kbdxsize,y+4+kbdysize*(i/7),(u8*)kbd_tbl2[i],16,kbdxsize);	


					}
					else
					{
						POINT_COLOR=BLUE;
						Show_Str_Mid(x+(i%7)*kbdxsize,y+4+kbdysize*(i/7),(u8*)kbd_tbl2[i],16,kbdxsize);	
					}
		}
				if(yue == 3)
		{
					if((u8*)kbd_tbl3[i] == ri1[ri - 1])
					{
						POINT_COLOR=RED;
						Show_Str_Mid(x+(i%7)*kbdxsize,y+4+kbdysize*(i/7),(u8*)kbd_tbl3[i],16,kbdxsize);	


					}
					else
					{
						POINT_COLOR=BLUE;
						Show_Str_Mid(x+(i%7)*kbdxsize,y+4+kbdysize*(i/7),(u8*)kbd_tbl3[i],16,kbdxsize);	
					}
		}
				if(yue == 4)
		{
					if((u8*)kbd_tbl4[i] == ri1[ri - 1])
					{
						POINT_COLOR=RED;
						Show_Str_Mid(x+(i%7)*kbdxsize,y+4+kbdysize*(i/7),(u8*)kbd_tbl4[i],16,kbdxsize);	


					}
					else
					{
						POINT_COLOR=BLUE;
						Show_Str_Mid(x+(i%7)*kbdxsize,y+4+kbdysize*(i/7),(u8*)kbd_tbl4[i],16,kbdxsize);	
					}
		}
				if(yue == 5)
		{
					if((u8*)kbd_tbl5[i] == ri1[ri - 1])
					{
						POINT_COLOR=RED;
						Show_Str_Mid(x+(i%7)*kbdxsize,y+4+kbdysize*(i/7),(u8*)kbd_tbl5[i],16,kbdxsize);	


					}
					else
					{
						POINT_COLOR=BLUE;
						Show_Str_Mid(x+(i%7)*kbdxsize,y+4+kbdysize*(i/7),(u8*)kbd_tbl5[i],16,kbdxsize);	
					}
		}
				if(yue == 7)
		{
					if((u8*)kbd_tbl7[i] == ri1[ri - 1])
					{
						POINT_COLOR=RED;
						Show_Str_Mid(x+(i%7)*kbdxsize,y+4+kbdysize*(i/7),(u8*)kbd_tbl7[i],16,kbdxsize);	


					}
					else
					{
						POINT_COLOR=BLUE;
						Show_Str_Mid(x+(i%7)*kbdxsize,y+4+kbdysize*(i/7),(u8*)kbd_tbl7[i],16,kbdxsize);	
					}
		}
				if(yue == 8)
		{
					if((u8*)kbd_tbl8[i] == ri1[ri - 1])
					{
						POINT_COLOR=RED;
						Show_Str_Mid(x+(i%7)*kbdxsize,y+4+kbdysize*(i/7),(u8*)kbd_tbl8[i],16,kbdxsize);	


					}
					else
					{
						POINT_COLOR=BLUE;
						Show_Str_Mid(x+(i%7)*kbdxsize,y+4+kbdysize*(i/7),(u8*)kbd_tbl8[i],16,kbdxsize);	
					}
		}
				if(yue == 9)
		{
					if((u8*)kbd_tbl9[i] == ri1[ri - 1])
					{
						POINT_COLOR=RED;
						Show_Str_Mid(x+(i%7)*kbdxsize,y+4+kbdysize*(i/7),(u8*)kbd_tbl9[i],16,kbdxsize);	


					}
					else
					{
						POINT_COLOR=BLUE;
						Show_Str_Mid(x+(i%7)*kbdxsize,y+4+kbdysize*(i/7),(u8*)kbd_tbl9[i],16,kbdxsize);	
					}
		}
				if(yue == 10)
		{
					if((u8*)kbd_tbl10[i] == ri1[ri - 1])
					{
						POINT_COLOR=RED;
						Show_Str_Mid(x+(i%7)*kbdxsize,y+4+kbdysize*(i/7),(u8*)kbd_tbl10[i],16,kbdxsize);	


					}
					else
					{
						POINT_COLOR=BLUE;
						Show_Str_Mid(x+(i%7)*kbdxsize,y+4+kbdysize*(i/7),(u8*)kbd_tbl10[i],16,kbdxsize);	
					}
		}
						if(yue == 11)
		{
					if((u8*)kbd_tbl11[i] == ri1[ri - 1])
					{
						POINT_COLOR=RED;
						Show_Str_Mid(x+(i%7)*kbdxsize,y+4+kbdysize*(i/7),(u8*)kbd_tbl11[i],16,kbdxsize);	


					}
					else
					{
						POINT_COLOR=BLUE;
						Show_Str_Mid(x+(i%7)*kbdxsize,y+4+kbdysize*(i/7),(u8*)kbd_tbl11[i],16,kbdxsize);	
					}
		}
						if(yue == 12)
		{
					if((u8*)kbd_tbl12[i] == ri1[ri - 1])
					{
						POINT_COLOR=RED;
						Show_Str_Mid(x+(i%7)*kbdxsize,y+4+kbdysize*(i/7),(u8*)kbd_tbl12[i],16,kbdxsize);	


					}
					else
					{
						POINT_COLOR=BLUE;
						Show_Str_Mid(x+(i%7)*kbdxsize,y+4+kbdysize*(i/7),(u8*)kbd_tbl12[i],16,kbdxsize);	
					}
		}
		
		
	} 

 	
}
//按键状态设置
//x,y:键盘坐标
//key:键值（0~8）
//sta:状态，0，松开；1，按下；
//void py_key_staset(u16 x,u16 y,u8 keyx,u8 sta)
//{		  
//	u16 i=keyx/3,j=keyx%3;
//	if(keyx>8)return;
//	if(sta)LCD_Fill(x+j*kbdxsize+1,y+i*kbdysize+1,x+j*kbdxsize+kbdxsize-1,y+i*kbdysize+kbdysize-1,GREEN);
//	else LCD_Fill(x+j*kbdxsize+1,y+i*kbdysize+1,x+j*kbdxsize+kbdxsize-1,y+i*kbdysize+kbdysize-1,WHITE); 
//	Show_Str_Mid(x+j*kbdxsize,y+4+kbdysize*i,(u8*)kbd_tbl[keyx],16,kbdxsize);		
//	Show_Str_Mid(x+j*kbdxsize,y+kbdysize/2+kbdysize*i,(u8*)kbs_tbl[keyx],16,kbdxsize);		 
//}
//得到触摸屏的输入
//x,y:键盘坐标
//返回值：按键键值（1~9有效；0,无效）
//u8 py_get_keynum(u16 x,u16 y)
//{
//	u16 i,j;
//	static u8 key_x=0;//0,没有任何按键按下；1~9，1~9号按键按下
//	u8 key=0;
//	tp_dev.scan(0); 		 
//	if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
//	{	
//		for(i=0;i<3;i++)
//		{
//			for(j=0;j<3;j++)
//			{
//			 	if(tp_dev.x[0]<(x+j*kbdxsize+kbdxsize)&&tp_dev.x[0]>(x+j*kbdxsize)&&tp_dev.y[0]<(y+i*kbdysize+kbdysize)&&tp_dev.y[0]>(y+i*kbdysize))
//				{	
//					key=i*3+j+1;	 
//					break;	 		   
//				}
//			}
//			if(key)
//			{	   
//				if(key_x==key)key=0;
//				else 
//				{
//					py_key_staset(x,y,key_x-1,0);
//					key_x=key;
//					py_key_staset(x,y,key_x-1,1);
//				}
//				break;
//			}
//		}  
//	}else if(key_x) 
//	{
//		py_key_staset(x,y,key_x-1,0);
//		key_x=0;
//	} 
//	return key; 
//}
u8 py_get_keynum(u16 x,u16 y)
{

	u8 key=0;
	tp_dev.scan(0); 		 
	if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
	{	

		if(tp_dev.x[0]<(30)&&tp_dev.x[0]>(100)&&tp_dev.y[0]<(50)&&tp_dev.y[0]>(33))
		{	
			key=1;	
				
		}

	}
	return key; 
}
							   
//显示结果.
//index:0,表示没有一个匹配的结果.清空之前的显示
//   其他,索引号	
void py_show_result(u8 index)
{
 	LCD_ShowNum(30+144,125,index,1,16); 		//显示当前的索引
	LCD_Fill(30+40,125,30+40+48,130+16,WHITE);	//清除之前的显示
 	LCD_Fill(30+40,145,lcddev.width,145+48,WHITE);//清除之前的显示    
	if(index)
	{
 		Show_Str(30+40,125,200,16,t9.pymb[index-1]->py,16,0); 	//显示拼音
		Show_Str(30+40,145,lcddev.width-70,48,t9.pymb[index-1]->pymb,16,0);//显示对应的汉字
		printf("\r\n拼音:%s\r\n",t9.pymb[index-1]->py);	//串口输出拼音
		printf("结果:%s\r\n",t9.pymb[index-1]->pymb);	//串口输出结果
	}
}	


 int main(void)
 {	 
 	u8 i=0;	    	  	    
	u8 result_num;
	u8 cur_index;
	u8 key;
	u8 inputstr[7];		//最大输入6个字符+结束符
	u8 inputlen;		//输入长度	 
	 
	TIM3_Int_Init(4999,7199);//10Khz的计数频率，计数到5000为500ms  
	delay_init();	    	 //延时函数初始化	  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
	usmart_dev.init(72);		//初始化USMART
 	LED_Init();		  			//初始化与LED连接的硬件接口
	KEY_Init();					//初始化按键
	LCD_Init();			   		//初始化LCD     
	W25QXX_Init();				//初始化W25Q128
	tp_dev.init();				//初始化触摸屏
 	my_mem_init(SRAMIN);		//初始化内部内存池
	exfuns_init();				//为fatfs相关变量申请内存  
 	f_mount(fs[0],"0:",1); 		//挂载SD卡 
 	f_mount(fs[1],"1:",1); 		//挂载FLASH.
 	POINT_COLOR=RED;       
 	while(font_init()) 			//检查字库
	{	    
		LCD_ShowString(30,50,200,16,16,"Font Error!");
		delay_ms(200);				  
		LCD_Fill(30,50,240,66,WHITE);//清除显示	     
	}
 RESTART:
 	POINT_COLOR=RED;       
	Show_Str(30,5,200,16,"湖南工程学院",16,0);
	Show_Str(30,25,200,16,"电信1803沈嘉龙",16,0);	
	
	Show_Str(30,45,200,16,"当前时间：",16,0);	


	
	Show_Str(30,65,200,16,"当前日期：",16,0);	
	
	Show_Str(100,65,200,16,date[0],16,0);
	Show_Str(135,65,200,16,"年",16,0);
	Show_Str(150,65,200,16,yue1[yue-1],16,0);
	Show_Str(165,65,200,16,"月",16,0);
	
		POINT_COLOR=RED; 
	Show_Str(180,65,200,16,ri1[ri-1 ],16,0);	


	
// 	Show_Str(30,65,200,16,"  KEY2:校准  KEY0:清除",16,0);	 
// 	Show_Str(30,85,200,16,"KEY_UP:上翻  KEY1:下翻",16,0);	 
//	Show_Str(30,105,200,16,"输入:        匹配:  ",16,0);
// 	Show_Str(30,125,200,16,"拼音:        当前:  ",16,0);
// 	Show_Str(30,145,210,32,"结果:",16,0);
	
	if(lcddev.id==0X5310){kbdxsize=86;kbdysize=43;}//根据LCD分辨率设置按键大小
	else if(lcddev.id==0X5510||lcddev.id==0X1963){kbdxsize=140;kbdysize=70;}
	else {kbdxsize=25;kbdysize=25;}
	
	if(lcddev.id==0X5310){kbdxsize=40;kbdysize=20;}//根据LCD分辨率设置按键大小
	else if(lcddev.id==0X5510||lcddev.id==0X1963){kbdxsize=140;kbdysize=70;}
	else {kbdxsize=25;kbdysize=25;}
	
//	py_load_ui(30,195);
	py_load_ui(30,100);
	memset(inputstr,0,7);	//全部清零
	inputlen=0;				//输入长度为0
	result_num=0;			//总匹配数清零
	cur_index=0;			
	while(1)
	{
		i++;
		delay_ms(10);
		

		
		if(flag == 1)
		{
			
					//				闹钟
				if(shi == nshi && fen == nfen)
				{
					LED0=0;
				}
				else
				{
					LED0=1;
				}
			
				py_load_ui(30,100);
				POINT_COLOR=RED; 
				Show_Str(180,65,200,16,ri1[ri-1 ],16,0);	
				tp_dev.scan(0); 		 
				if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
				{	
					
//					日期
					if(tp_dev.x[0]<(200)&&tp_dev.x[0]>(100)&&tp_dev.y[0]<(80)&&tp_dev.y[0]>(65))
					{	
						flag = 2;
						LCD_Clear(WHITE);//清屏  			
					}
					
//					时间
					if(tp_dev.x[0]<(200)&&tp_dev.x[0]>(100)&&tp_dev.y[0]<(60)&&tp_dev.y[0]>(45))
					{	
						flag = 3;
						LCD_Clear(WHITE);//清屏  			
					}
					
//					if(tp_dev.x[0]<(130)&&tp_dev.x[0]>(100)&&tp_dev.y[0]<(80)&&tp_dev.y[0]>(65))
//					{	
//						flag = 3;
//						LCD_Clear(WHITE);//清屏  			
//					}
						
				}  
		}
		
		if(flag == 2)
		{
			POINT_COLOR=RED; 
			Show_Str(30,5,200,16,"日期设置页面",16,0);
			Show_Str(150,5,200,16,"返回",16,0);								
			Show_Str(30,30,200,16,"当前日期：",16,0);	
			Show_Str(100,30,200,16,date[0],16,0);
			Show_Str(135,30,200,16,"年",16,0);
			Show_Str(150,30,200,16,yue1[yue-1],16,0);
			Show_Str(165,30,200,16,"月",16,0);
			Show_Str(180,30,200,16,ri1[ri-1 ],16,0);	
			Show_Str(30,60,200,16,"日加1",16,0);
			Show_Str(80,60,200,16,"日减1",16,0);
			Show_Str(30,90,200,16,"月加1",16,0);
			Show_Str(80,90,200,16,"月减1",16,0);
//			LCD_DrawRectangle(30,60,70,75);	
//			LCD_DrawRectangle(80,60,120,75);	
			
				tp_dev.scan(0); 	
				if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
				{	
//返回主页面
					if(tp_dev.x[0]<(170)&&tp_dev.x[0]>(150)&&tp_dev.y[0]<(20)&&tp_dev.y[0]>(5))
					{	
						
						LCD_Clear(WHITE);//清屏  
						 	POINT_COLOR=RED;       
							Show_Str(30,5,200,16,"湖南工程学院",16,0);
							Show_Str(30,25,200,16,"电信1803沈嘉龙",16,0);	
							
							Show_Str(30,45,200,16,"当前时间：",16,0);	


							
							Show_Str(30,65,200,16,"当前日期：",16,0);	
							
							Show_Str(100,65,200,16,date[0],16,0);
							Show_Str(135,65,200,16,"年",16,0);
							Show_Str(150,65,200,16,yue1[yue-1],16,0);
							Show_Str(165,65,200,16,"月",16,0);
							
								POINT_COLOR=RED; 
							Show_Str(180,65,200,16,ri1[ri-1 ],16,0);	
						flag = 1;
							
					}

//					日加1
					if(tp_dev.x[0]<(70)&&tp_dev.x[0]>(30)&&tp_dev.y[0]<(75)&&tp_dev.y[0]>(60))
					{
						delay_ms(100);
						if(yue == 1 || yue == 3 || yue == 5 || yue==7 || yue == 8 || yue == 10 || yue == 12)
						{
							if(ri < 31)
							{
								ri = ri + 1;
							}
							else
							{
								ri = 1;
							}
						}

						
						if(yue == 2)
						{
							if(ri < 28)
							{
								ri = ri + 1;
							}
							else
							{
								ri = 1;
							}
					 }
						
					if(yue == 4 || yue == 6 || yue == 9 || yue == 11) 
						{
							if(ri < 30)
							{
								ri = ri + 1;
							}
							else
							{
								ri = 1;
							}
					  }
							
					}
//					日减1
					if(tp_dev.x[0]<(110)&&tp_dev.x[0]>(80)&&tp_dev.y[0]<(75)&&tp_dev.y[0]>(60))
					{
									delay_ms(100);
									if(yue == 1 || yue == 3 || yue == 5 || yue==7 || yue == 8 || yue == 10 || yue == 12)
									{
										if(ri > 1)
										{
											ri = ri - 1;
										}
										else
										{
											ri = 31;
										}
									}

									
									if(yue == 2)
									{
										if(ri > 1)
										{
											ri = ri - 1;
										}
										else
										{
											ri = 28;
										}
								 }
									
								if(yue == 4 || yue == 6 || yue == 9 || yue == 11) 
									{
										if(ri > 1)
										{
											ri = ri - 1;
										}
										else
										{
											ri = 30;
										}
									}
					}
//					月加1
					if(tp_dev.x[0]<(70)&&tp_dev.x[0]>(30)&&tp_dev.y[0]<(105)&&tp_dev.y[0]>(90))
					{
						delay_ms(100);
						if(yue > 11)
						{
							yue = 1;
						}
						else
						{
							yue = yue + 1;
						}
					}
//					月减1
					if(tp_dev.x[0]<(110)&&tp_dev.x[0]>(80)&&tp_dev.y[0]<(105)&&tp_dev.y[0]>(90))
					{		
						delay_ms(100);
						if(yue < 2)
						{
							yue = 12;
						}
						else
						{
							yue = yue - 1;
						}
					}
				}
		}
		
		if(flag == 3)
		{
			POINT_COLOR=RED; 
			Show_Str(30,5,200,16,"时间设置页面",16,0);
			Show_Str(150,5,200,16,"返回",16,0);								
			Show_Str(30,30,200,16,"当前时间：",16,0);	
			Show_Str(100,30,200,16,shi1[shi],16,0);
			Show_Str(120,30,200,16,"时",16,0);
			Show_Str(140,30,200,16,fen1[fen],16,0);
			Show_Str(160,30,200,16,"分",16,0);
//			Show_Str(180,30,200,16,miao1[0],16,0);	
			Show_Str(30,60,200,16,"分加1",16,0);
			Show_Str(80,60,200,16,"分减1",16,0);
			Show_Str(30,90,200,16,"时加1",16,0);
			Show_Str(80,90,200,16,"时减1",16,0);
			
			Show_Str(30,120,200,16,"闹钟时间：",16,0);	
			Show_Str(100,120,200,16,shi1[nshi],16,0);
			Show_Str(120,120,200,16,"时",16,0);
			Show_Str(140,120,200,16,fen1[nfen],16,0);
			Show_Str(160,120,200,16,"分",16,0);
			
			Show_Str(30,160,200,16,"分加1",16,0);
			Show_Str(80,160,200,16,"分减1",16,0);
			Show_Str(30,190,200,16,"时加1",16,0);
			Show_Str(80,190,200,16,"时减1",16,0);
			
			tp_dev.scan(0); 	
				if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
				{	
//返回主页面
					if(tp_dev.x[0]<(170)&&tp_dev.x[0]>(150)&&tp_dev.y[0]<(20)&&tp_dev.y[0]>(5))
					{	
						
						LCD_Clear(WHITE);//清屏  
						 	POINT_COLOR=RED;       
							Show_Str(30,5,200,16,"湖南工程学院",16,0);
							Show_Str(30,25,200,16,"电信1803沈嘉龙",16,0);	
							
							Show_Str(30,45,200,16,"当前时间：",16,0);	


							
							Show_Str(30,65,200,16,"当前日期：",16,0);	
							
							Show_Str(100,65,200,16,date[0],16,0);
							Show_Str(135,65,200,16,"年",16,0);
							Show_Str(150,65,200,16,yue1[yue-1],16,0);
							Show_Str(165,65,200,16,"月",16,0);
							
								POINT_COLOR=RED; 
							Show_Str(180,65,200,16,ri1[ri-1 ],16,0);	
						flag = 1;
							
					}
					
					
					
					
					
					//				分加1
					if(tp_dev.x[0]<(70)&&tp_dev.x[0]>(30)&&tp_dev.y[0]<(75)&&tp_dev.y[0]>(60))
					{
						delay_ms(100);
						if(fen < 59)
						{
							fen = fen + 1;
						}
						else
						{
							fen = 0;
						}							
					}
//					分减1
					if(tp_dev.x[0]<(110)&&tp_dev.x[0]>(80)&&tp_dev.y[0]<(75)&&tp_dev.y[0]>(60))
					{
									delay_ms(100);
						if(fen > 0)
						{
							fen = fen - 1;
						}
						else
						{
							fen = 59;
						}	
					
					}
//					时加1
					if(tp_dev.x[0]<(70)&&tp_dev.x[0]>(30)&&tp_dev.y[0]<(105)&&tp_dev.y[0]>(90))
					{
						delay_ms(100);
						if(shi < 23)
						{
							shi = shi + 1;
						}
						else
						{
							shi = 0;
						}	

					}
//					时减1
					if(tp_dev.x[0]<(110)&&tp_dev.x[0]>(80)&&tp_dev.y[0]<(105)&&tp_dev.y[0]>(90))
					{		
						if(shi > 0)
						{
							shi = shi - 1;
						}
						else
						{
							shi = 23;
						}	
					}
					
					
					
					
					
		
					
					//				分加1
					if(tp_dev.x[0]<(70)&&tp_dev.x[0]>(30)&&tp_dev.y[0]<(175)&&tp_dev.y[0]>(160))
					{
						delay_ms(100);
						if(nfen < 59)
						{
							nfen = nfen + 1;
						}
						else
						{
							nfen = 0;
						}							
					}
//					分减1
					if(tp_dev.x[0]<(110)&&tp_dev.x[0]>(80)&&tp_dev.y[0]<(175)&&tp_dev.y[0]>(160))
					{
									delay_ms(100);
						if(nfen > 0)
						{
							nfen = nfen - 1;
						}
						else
						{
							nfen = 59;
						}	
					
					}
//					时加1
					if(tp_dev.x[0]<(70)&&tp_dev.x[0]>(30)&&tp_dev.y[0]<(205)&&tp_dev.y[0]>(190))
					{
						delay_ms(100);
						if(nshi < 23)
						{
							nshi = nshi + 1;
						}
						else
						{
							nshi = 0;
						}	

					}
//					时减1
					if(tp_dev.x[0]<(110)&&tp_dev.x[0]>(80)&&tp_dev.y[0]<(205)&&tp_dev.y[0]>(190))
					{		
						if(nshi > 0)
						{
							nshi = nshi - 1;
							
						}
						else
						{
							nshi = 23;
						}	
					}
					
					
				}


		}
		
		
       										    			    
	} 

}


