/*************************************************************************************************************
功能:     通过蓝牙控制窗帘开关
          通过Wifi控制窗帘开关
					通过按键控制窗帘开关
					通过关照传感器控制窗帘开关
版本:     2023-5-17 V1.0
修改记录: 无
作者:     ZZZ
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


void user_init( void );

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
		
		
	while(1)
	{		
		S1();
		if (output == 1)
		{
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,4,output);
			output = 0;
			PCA9685_rgb_led_control(e1_rgb_led_addr.periph,e1_rgb_led_addr.addr,1);
			delay(3000);
			PCA9685_rgb_led_control(e1_rgb_led_addr.periph,e1_rgb_led_addr.addr,0);
			
		}
		if (output == 2)
		{
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,4,output);
			output = 0;
			PCA9685_rgb_led_control(e1_rgb_led_addr.periph,e1_rgb_led_addr.addr,1);
			delay(3000);
			PCA9685_rgb_led_control(e1_rgb_led_addr.periph,e1_rgb_led_addr.addr,0);
		}
		if (output == 3)
		{
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,4,output);
			output = 0;
			PCA9685_rgb_led_control(e1_rgb_led_addr.periph,e1_rgb_led_addr.addr,1);
			delay(3000);
			PCA9685_rgb_led_control(e1_rgb_led_addr.periph,e1_rgb_led_addr.addr,0);
		}
		if (output == 4)
		{
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,4,output);
			output = 0;
			PCA9685_rgb_led_control(e1_rgb_led_addr.periph,e1_rgb_led_addr.addr,1);
			delay(3000);
			PCA9685_rgb_led_control(e1_rgb_led_addr.periph,e1_rgb_led_addr.addr,0);
		}
		if (output == 5)
		{
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,4,output);
			output = 0;
			PCA9685_rgb_led_control(e1_rgb_led_addr.periph,e1_rgb_led_addr.addr,1);
			delay(3000);
			PCA9685_rgb_led_control(e1_rgb_led_addr.periph,e1_rgb_led_addr.addr,0);
		}
		if (output == 6)
		{
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,4,output);
			output = 0;
			PCA9685_rgb_led_control(e1_rgb_led_addr.periph,e1_rgb_led_addr.addr,1);
			delay(3000);
			PCA9685_rgb_led_control(e1_rgb_led_addr.periph,e1_rgb_led_addr.addr,0);
		}
		if (output == 7)
		{
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,4,output);
			output = 0;
			PCA9685_rgb_led_control(e1_rgb_led_addr.periph,e1_rgb_led_addr.addr,1);
			delay(3000);
			PCA9685_rgb_led_control(e1_rgb_led_addr.periph,e1_rgb_led_addr.addr,0);
		}
		if (output == 8)
		{
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,4,output);
			output = 0;
			PCA9685_rgb_led_control(e1_rgb_led_addr.periph,e1_rgb_led_addr.addr,1);
			delay(3000);
			PCA9685_rgb_led_control(e1_rgb_led_addr.periph,e1_rgb_led_addr.addr,0);
		}
		E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,4,0);
		pressed = 0;
		delay(1000);	    		
	}
	  
}


	


