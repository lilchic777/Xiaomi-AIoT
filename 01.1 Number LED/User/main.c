/*************************************************************************************************************
功能:    	按下sw5按键，数显屏上将不间断显示0-50
*************************************************************************************************************/

#include "gd32f4xx.h"
#include "stdio.h"
#include "string.h"
#include "i2c.h"
#include "delay.h"
#include "led.h"

#include "s1.h"
#include "e1.h"

i2c_addr_def e1_nixie_tube_addr;
i2c_addr_def e1_rgb_led_addr;

void user_init(void);

void user_init()
{
	LED_Init();
	nvic_priority_group_set(NVIC_PRIGROUP_PRE4_SUB0);

	i2c0_gpio_config();
	i2c0_config();

	i2c1_gpio_config();
	i2c1_config();

	S1_I2C_ADDR_Init();

	E1_4NLED_ADDR_Init();
	E1_3LED_ADDR_Init();
}

int main(void)
{
	user_init();
	int num = 0;

	while (1)
	{
		S1();
		if (output == 5)
		{
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph, e1_nixie_tube_addr.addr, 3, num / 10 % 10);
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph, e1_nixie_tube_addr.addr, 4, num % 10);
			num++;
			if (num == 51)
			{
				num = 0;
				output = 0;
			}
		}
		pressed = 0;
		delay(100);
	}
}
