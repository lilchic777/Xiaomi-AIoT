#include "gd32f4xx.h"
#include "gd32f4xx_rcu.h"
#include "gd32f4xx_gpio.h"
#include "led.h"

// void LED_Init( void ){
// 	rcu_periph_clock_enable(RCU_GPIOF);
// 	gpio_mode_set(GPIOF, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, GPIO_PIN_4);
// 	gpio_output_options_set(GPIOF, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_4);
// 	gpio_bit_reset(GPIOF, GPIO_PIN_4);

// }

// void LED_ON( void ){
// 	gpio_bit_set(GPIOF, GPIO_PIN_4);
// }

// void LED_OFF( void ){
// 	gpio_bit_reset(GPIOF, GPIO_PIN_4);
// }

// void LED_BLINK( void ){
// 	gpio_bit_toggle(GPIOF, GPIO_PIN_4);
// }

void LED_Init( void ){
	rcu_periph_clock_enable(RCU_GPIOD);
	gpio_mode_set(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, GPIO_PIN_15);
	gpio_output_options_set(GPIOD, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_15);
	gpio_bit_set(GPIOD, GPIO_PIN_15);	// 注意此处与U1不同，U1默认PF4，reset为关闭

}

void LED_ON( void ){
	gpio_bit_reset(GPIOD, GPIO_PIN_15);
}

void LED_OFF( void ){
	gpio_bit_set(GPIOD, GPIO_PIN_15);
}

void LED_BLINK( void ){
	gpio_bit_toggle(GPIOD, GPIO_PIN_15);
}



