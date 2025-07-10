#include "delay.h"
#include "e1.h"
#include "u1.h"
#include "timer.h"

int main()
{
	/* LED初始化 */
	e1_led_info = e1_led_init();

	u1_led_init();
	// u1_led_on();

	u1_timer0_init();
	Timer1_Init();
	Timer1_Config();

	while (1)
	{
		/* 循环递增i的值 */
		for (unsigned char i = 0; i < 100; i++)
		{
			/* 将红色LED亮度设置为i%，绿色LED亮度设置为0%，蓝色LED亮度设置为0% */
			e1_led_rgb_set(e1_led_info, i, 0, 0);
			/* 延时10ms */
			delay(10);
		}
		/* 循环递减i的值 */
		for (unsigned char i = 100; i > 0; i--)
		{
			/* 将红色LED亮度设置为i%，绿色LED亮度设置为0%，蓝色LED亮度设置为0% */
			e1_led_rgb_set(e1_led_info, i, 0, 0);
			/* 延时10ms */
			delay(10);
		}
	}
}



