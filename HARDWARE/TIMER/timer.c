#include "timer.h"
#include "led.h"
#include "lcd.h"
#include "text.h"	
//////////////////////////////////////////////////////////////////////////////////	 
//STM32F103ZE核心板
//定时器 驱动代码	   
							  
//////////////////////////////////////////////////////////////////////////////////   	 

//通用定时器3中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!
void TIM3_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能
	
	//定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器


	TIM_Cmd(TIM3, ENABLE);  //使能TIMx					 
}

int miao = 50;
int fen = 59;
int shi = 23;
int ri = 1;
int yue = 5;
int nian1 = 20;
int nian2 = 22;
int nian;
int n = 0;
extern int flag;
//定时器3中断服务程序
void TIM3_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
		{	
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx更新中断标志 
			if(flag == 1)
			{
				LED1=!LED1;
				n++;
				if(n == 2)
				{
					miao++;
					n = 0;
					if(miao == 60)
					{
						fen ++;
						miao = 0;
						if(fen == 60)
						{
							fen = 0;
							shi++;
							if(shi == 24)
							{
								shi = 0;
								ri++;
							}
						}
					}
				}
				
				nian = nian1 * 100 + nian2;
				POINT_COLOR=RED;  
				LCD_ShowNum(160,45,miao,2,16);
				Show_Str(150,45,200,16,":",16,0);				
				LCD_ShowNum(130,45,fen,2,16);	
				Show_Str(120,45,200,16,":",16,0);
				LCD_ShowNum(100,45,shi,2,16);
				
				
					
//				LCD_ShowNum(100,65,nian1,2,16);
//				LCD_ShowNum(115,65,nian2,2,16);
//				Show_Str(130,65,200,16,"-",16,0);
//				LCD_ShowNum(135,65,yue,2,16);
//				Show_Str(150,65,200,16,"-",16,0);
//				LCD_ShowNum(155,65,ri,2,16);
				

			}
		}
}












