/*************************************************************************************************************
功能:     当把盖子拿开时，超声波开始进行检测，触碰到物体后，进行反馈，在数码管上显示距离
*************************************************************************************************************/

#include "gd32f4xx.h"
#include "stdio.h"
#include "string.h"
#include "e1.h"
#include "s6.h"
#include "i2c.h"
#include "delay.h"
#include "led.h"

int main(void)
{
	LED_Init();

	i2c0_gpio_config();
	i2c0_config();

	i2c1_gpio_config();
	i2c1_config();

	E1_I2C_ADDR_Init();
	S6_US_ADDR_Init();

	while (1)
	{
		S6_US_Get(s6_uso_addr.periph, s6_uso_addr.addr);
		delay(500);
		E1_HT16K33_display_data(e1_nixie_tube_addr.periph, e1_nixie_tube_addr.addr, 1, usoData / 1000 % 10);
		E1_HT16K33_display_data(e1_nixie_tube_addr.periph, e1_nixie_tube_addr.addr, 2, usoData / 100 % 10);
		E1_HT16K33_display_data(e1_nixie_tube_addr.periph, e1_nixie_tube_addr.addr, 3, usoData / 10 % 10);
		E1_HT16K33_display_data(e1_nixie_tube_addr.periph, e1_nixie_tube_addr.addr, 4, usoData % 10);
		delay(500);
	}
}
