/*************************************************************************************************************
����:     ����debug ģʽ��watch1�����irOut�Թ۲�ֵ�ı仯����irOut�����λȡ1ʱ�����Ϊ1���򴥷��ɹ�
*************************************************************************************************************/

#include "gd32f4xx.h"
#include "stdio.h"
#include "string.h"
#include "s7.h"
#include "e1.h"
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
	
		S7_IR_ADDR_Init();
		E1_I2C_1_ADDR_Init();
		
		while(1)
		{
			S7_IR_Get(s7_ir_addr.periph, s7_ir_addr.addr);
			if (irState == 1)
				PCA9685_rgb_led_control(e1_rgb_led_addr.periph,e1_rgb_led_addr.addr,3);
			else
				PCA9685_rgb_led_control(e1_rgb_led_addr.periph,e1_rgb_led_addr.addr,0);
			delay(1000);
		}
	  
}


	


