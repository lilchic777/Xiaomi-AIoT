/*************************************************************************************************************
功能:     按下sw1按键，E1上将开启三色灯不停变化颜色，按下sw2按钮,E1上将灭灯。
版本:     2023-5-17 V1.0
修改记录: 无
作者:     ZZZ
*************************************************************************************************************/
#include "gd32f4xx.h"
#include "led.h"
#include "i2c.h"
#include "delay.h"
#include "e1.h"
#include "s1.h"



void UserInit( void );


void UserInit( void ){
	i2c0_gpio_config();
	i2c0_config();
	
	i2c1_gpio_config();
	i2c1_config();

	S1_I2C_ADDR_Init();
	E1_I2C_3LED_ADDR_Init();

}

int main( void ){

	UserInit();
	while(1){
		S1();
		delay(1000);
		if (output == 1){
			for(int i=0;i<6;i++){
				PCA9685_rgb_led_control(e1_rgb_led_addr.periph,e1_rgb_led_addr.addr,i);
				delay(2000);
				if(i>=5)
					break;
			}	
			output = 0;
		}
		else if(output == 2){
			PCA9685_rgb_led_control(e1_rgb_led_addr.periph,e1_rgb_led_addr.addr,0);
			output = 0;
		}


	}
	
}








