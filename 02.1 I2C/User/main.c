/*************************************************************************************************************
功能:     按下sw1按键，E1上将亮灯，按下sw2按钮,E1上将灭灯
*************************************************************************************************************/
#include "gd32f4xx.h"
#include "gd32f450z_eval.h"
#include "led.h"
#include "i2c.h"
#include "uart.h"
#include "s1.h"
#include "e1.h"
#include "delay.h"
#include <string.h>

void UserInit( void );


void UserInit( void ){

	LED_Init();
	i2c0_gpio_config();
	i2c0_config();
	
	i2c1_gpio_config();
	i2c1_config();
	
	S1_I2C_ADDR_Init();
	E1_I2C_3LED_ADDR_Init();
}

int main( void ){
	//systick_config();
	UserInit();
	
		
	while(1){
		S1();
		delay(1000);
		if(output == 1){
			LED_ON();
			PCA9685_rgb_led_control(e1_rgb_led_addr.periph,e1_rgb_led_addr.addr,1);
			delay(1000);
			output = 0;
		}
		else if(output == 2){
			LED_OFF();
			PCA9685_rgb_led_control(e1_rgb_led_addr.periph,e1_rgb_led_addr.addr,0);
			delay(1000);
			output = 0;
		}
	}
		
}
