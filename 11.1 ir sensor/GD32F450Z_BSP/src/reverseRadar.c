#include "gd32f4xx.h"
#include "reverseRadar.h"
#include "i2c.h"
#include "s6.h"
#include "e1.h"

void E1_S6_Reverse( void ){
	S6_US_Get(s6_uso_addr.periph,s6_uso_addr.addr);
	if(usoData){
		E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,1,(usoData/1000)%10);
		E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,2,(usoData/100)%10);
		E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,3,(usoData/10)%10);
		E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,4,(usoData)%10);
		if(usoData <= 200){
			PCA9685_rgb_led_control(e1_rgb_led_addr.periph,e1_rgb_led_addr.addr,1);
		}else if(usoData > 200 && usoData <= 400){
			PCA9685_rgb_led_control(e1_rgb_led_addr.periph,e1_rgb_led_addr.addr,4);
		}else if(usoData > 400 && usoData <= 600){
			PCA9685_rgb_led_control(e1_rgb_led_addr.periph,e1_rgb_led_addr.addr,5);
		}else if(usoData > 600 && usoData <= 800){
			PCA9685_rgb_led_control(e1_rgb_led_addr.periph,e1_rgb_led_addr.addr,2);
		}else if(usoData > 800){
			PCA9685_rgb_led_control(e1_rgb_led_addr.periph,e1_rgb_led_addr.addr,3);
		}
	}
}

