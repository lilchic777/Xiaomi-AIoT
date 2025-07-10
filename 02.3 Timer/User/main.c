/*************************************************************************************************************
功能:     程序死循环开始立即闪烁一次后LED保持熄灭，程序正常E1板子每1.5秒闪烁一次
*************************************************************************************************************/

#include "gd32f4xx.h"
#include "led.h"
#include "watchdogtimer.h"
#include "timer.h"
#include "delay.h"

uint16_t delay_count = 0; // 延时变量
uint16_t time_count = 0;  // 1s定时变量

uint8_t flag = 0;

uint8_t tim_flag = 0;
// 定时器1
uint8_t wdgt_flag = 0;
// 看门狗定时器

void UserInit(void);
void setTimerType(uint8_t mode);
// void watchDog_Init(void);

void setTimerType(uint8_t mode)
{
	if (mode == 1)
	{
		tim_flag = 1;
		wdgt_flag = 0;
	}
	else if (mode == 2)
	{
		wdgt_flag = 1;
		tim_flag = 0;
		// watchDog_Init();
	}
	else
	{
		tim_flag = 0;
		wdgt_flag = 0;
	}
}

//void watchDog_Init(void)
//{
//	rcu_periph_clock_enable(RCU_WWDGT);
//	wwdgt_config(1270, 800, WWDGT_CFG_PSC_DIV4);
//	wwdgt_enable();
//}

void UserInit(void)
{
	nvic_priority_group_set(NVIC_PRIGROUP_PRE4_SUB0);
	Timer1_Init();
	Timer1_Config();
	LED_Init();
	setTimerType(1);
}

int main(void)
{

	UserInit();

//	if (RESET != rcu_flag_get(RCU_FLAG_WWDGTRST))
//	{
//		LED_BLINK();
//		delay(250);
//		rcu_all_reset_flag_clear();

//		while (1)
//			;
//	}

	while (tim_flag)
	{
		if (flag == 1)
		{
			flag = 0;
			LED_BLINK();
			// delay(100);
		}
	}

//	while (wdgt_flag)
//	{
//		if (flag == 1)
//		{
//			flag = 0;
//			LED_BLINK();
//			delay(1500);
//			wwdgt_counter_update(1270);
//		}
//	}
}

void TIMER1_IRQHandler(void)
{
	if (timer_interrupt_flag_get(TIMER1, TIMER_INT_FLAG_UP))
	{
		timer_interrupt_flag_clear(TIMER1, TIMER_INT_FLAG_UP);

		if (delay_count > 0)
			delay_count--;

		if (time_count++ >= 1500)
		{
			time_count = 0;
			flag = 1;
		}
	}
}
