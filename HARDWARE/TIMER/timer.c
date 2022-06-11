#include "timer.h"
#include "led.h"
#include "lcd.h"
#include "text.h"	
//////////////////////////////////////////////////////////////////////////////////	 
//STM32F103ZE���İ�
//��ʱ�� ��������	   
							  
//////////////////////////////////////////////////////////////////////////////////   	 

//ͨ�ö�ʱ��3�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
void TIM3_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���


	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx					 
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
//��ʱ��3�жϷ������
void TIM3_IRQHandler(void)   //TIM3�ж�
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
		{	
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx�����жϱ�־ 
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












