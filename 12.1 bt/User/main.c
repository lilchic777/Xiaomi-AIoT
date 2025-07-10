/*************************************************************************************************************
功能:     通过连接蓝牙控制蓝牙子板。点灯亮起
*************************************************************************************************************/

#include "gd32f4xx.h"
#include "stdio.h"
#include "string.h"
#include "uart.h"
#include "c3.h"
#include "i2c.h"
#include "delay.h"
#include "led.h"
// #include "i2c_user.h"

uint8_t c3_result;
uint8_t c3_resu;
char recv;

int ble_init_state = -1;
int run_ble_step = 1;

char recv_buf[32];

extern ble_set_para ble_para;

int main(void)
{
	LED_Init();
			LED_BLINK();
	delay(2000);
	LED_BLINK();
	nvic_priority_group_set(NVIC_PRIGROUP_PRE4_SUB0);

	timer3_init();
	uart_init(USART0);

	i2c0_gpio_config();
	i2c0_config();

	i2c1_gpio_config();
	i2c1_config();

	c3_result = c3_init();


	while (c3_result == 0)
	{
		c3_result = c3_init();
		delay(500);
	}

	c3_resu = c3_ble_init();


	while (1)
	{
		Uart_read(recv_buf, sizeof(recv_buf), 300);
		recv = recv_buf[16];
		if (recv)
		{
			if (recv < 0x66)
			{
				LED_ON();
			}
			else if (recv >= 0x66)
			{
				LED_OFF();
			}
		}
		LED_BLINK();
		delay(700);
	}
}
