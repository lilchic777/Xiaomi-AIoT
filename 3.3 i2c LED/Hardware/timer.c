#include "timer.h"
#include "gd32f4xx.h"
#include "gd32f4xx_timer.h"
#include "gd32f4xx_gpio.h"
#include "gd32f4xx_rcu.h"

//timer_oc_parameter_struct Timer_OCInitStructure;
//定时器输出参数
//timer_parameter_struct Timer_InitStructure;
//定时器计数参数

void delay_ms(uint32_t ms) {
    uint32_t i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 8000; j++) {
            __NOP();
					//	没有操作等同于阻塞等待
        }
    }
}

void Timer1_Init(){
	rcu_periph_clock_enable(RCU_GPIOA);
	gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_0);
	gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_1);
	gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_2);
	gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_0);
	gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_1);
	gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_2);
	gpio_af_set(GPIOA, GPIO_AF_1, GPIO_PIN_0);
	gpio_af_set(GPIOA, GPIO_AF_1, GPIO_PIN_1);
	gpio_af_set(GPIOA, GPIO_AF_1, GPIO_PIN_2);
	
}

void Timer1_Config(){
	timer_parameter_struct Timer1_InitStructure;
	rcu_periph_clock_enable(RCU_TIMER0);
	//外设时钟使能
	timer_deinit(TIMER1);
	Timer1_InitStructure.prescaler	 = 4199;
	//预分频系数
	Timer1_InitStructure.period 	 	 = 20;
	Timer1_InitStructure.alignedmode = TIMER_COUNTER_EDGE;
	Timer1_InitStructure.counterdirection = TIMER_COUNTER_UP;
	Timer1_InitStructure.clockdivision = TIMER_CKDIV_DIV1;
	Timer1_InitStructure.repetitioncounter = 0;
	timer_init(TIMER1,&Timer1_InitStructure);
	nvic_irq_enable(TIMER1_IRQn,1,1);
	timer_interrupt_enable(TIMER1, TIMER_INT_UP);
	timer_enable(TIMER1);
	//使能TIMER1
}


