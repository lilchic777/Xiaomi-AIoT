#include "gd32f4xx.h"
#include "i2c.h"
#include "irFaucet.h"
#include "e1.h"
#include "s7.h"
#include "timer.h"

void E1_S7_FAUCET( void ){
	if(irState){
		PCA9685_rgb_led_control(e1_rgb_led_addr.periph,e1_rgb_led_addr.addr,3);
		delay_ms(10000);
	}else if(!irState){
		PCA9685_rgb_led_control(e1_rgb_led_addr.periph,e1_rgb_led_addr.addr,0);
		
	}
	delay_ms(8000);
}
