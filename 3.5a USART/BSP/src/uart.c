#include <string.h>
#include "uart.h"
#include "delay.h"
#include "gd32f4xx_usart.h"
#include "gd32f4xx_rcu.h"
#include "gd32f4xx_gpio.h"

/*********************************************************************************************
 *函数名:    uart_init
 *功能:      初始化相应串口
 *入口参数:  usart_periph   USART0/USART1/USART2
 *出口参数： 无
 *返回值：   无
 **********************************************************************************************/
void uart_init(uint32_t usart_periph)
{
	if (usart_periph == USART0)
	{
		nvic_irq_enable(USART0_IRQn, 0, 0);
		rcu_periph_clock_enable(RCU_GPIOB);								  /* enable GPIO clock */
		rcu_periph_clock_enable(RCU_USART0);							  /* enable USART clock */
		gpio_af_set(GPIOB, GPIO_AF_7, GPIO_PIN_6);						  /* connect port to USARTx_Tx */
		gpio_af_set(GPIOB, GPIO_AF_7, GPIO_PIN_7);						  /* connect port to USARTx_Rx */
		gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_6); /* configure USART Tx as alternate function push-pull */
		gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_6);
		gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_7); /* configure USART Rx as alternate function push-pull */
		// gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_7);
		/* USART configure */
		usart_deinit(USART0);
		usart_baudrate_set(USART0, 115200U);
		usart_receive_config(USART0, USART_RECEIVE_ENABLE);
		usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);
		usart_enable(USART0);
		usart_interrupt_enable(USART0, USART_INT_RBNE);
	}
	else if (usart_periph == USART1)
	{
		nvic_irq_enable(USART1_IRQn, 5, 0);
		rcu_periph_clock_enable(RCU_GPIOD);								  /* enable GPIO clock */
		rcu_periph_clock_enable(RCU_USART1);							  /* enable USART clock */
		gpio_af_set(GPIOD, GPIO_AF_7, GPIO_PIN_5);						  /* connect port to USARTx_Tx */
		gpio_af_set(GPIOD, GPIO_AF_7, GPIO_PIN_6);						  /* connect port to USARTx_Rx */
		gpio_mode_set(GPIOD, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_5); /* configure USART Tx as alternate function push-pull */
		gpio_output_options_set(GPIOD, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_5);
		gpio_mode_set(GPIOD, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_6); /* configure USART Rx as alternate function push-pull */
		// gpio_mode_set(GPIOD, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO_PIN_9);  // 正确配置
		// gpio_output_options_set(GPIOD, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_6);
		/* USART configure */
		usart_deinit(USART1);
		usart_baudrate_set(USART1, 115200U);
		usart_receive_config(USART1, USART_RECEIVE_ENABLE);
		usart_transmit_config(USART1, USART_TRANSMIT_ENABLE);
		usart_enable(USART1);
		usart_interrupt_enable(USART1, USART_INT_RBNE);
	}
	else if (usart_periph == USART2)
	{
		nvic_irq_enable(USART2_IRQn, 5, 0);
		rcu_periph_clock_enable(RCU_GPIOD);								  /* enable GPIO clock */
		rcu_periph_clock_enable(RCU_USART2);							  /* enable USART clock */
		gpio_af_set(GPIOD, GPIO_AF_7, GPIO_PIN_8);						  /* connect port to USARTx_Tx */
		gpio_af_set(GPIOD, GPIO_AF_7, GPIO_PIN_9);						  /* connect port to USARTx_Rx */
		gpio_mode_set(GPIOD, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_8); /* configure USART Tx as alternate function push-pull */
		gpio_output_options_set(GPIOD, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_8);
		gpio_mode_set(GPIOD, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_9); /* configure USART Rx as alternate function push-pull */
		// gpio_mode_set(GPIOD, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO_PIN_9);  // 正确配置
		// gpio_output_options_set(GPIOD, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);
		/* USART configure */
		usart_deinit(USART2);
		usart_baudrate_set(USART2, 115200U);
		usart_receive_config(USART2, USART_RECEIVE_ENABLE);
		usart_transmit_config(USART2, USART_TRANSMIT_ENABLE);
		usart_enable(USART2);
		usart_interrupt_enable(USART2, USART_INT_RBNE);
	}
}

/********************************************************************************************************
//发送数据
*********************************************************************************************************/
uint16_t uart_send_bytes(uint32_t usart_periph, uint8_t *data, uint16_t len)
{
	uint8_t i;
	for (i = 0; i < len; i++)
	{
		while (usart_flag_get(usart_periph, USART_FLAG_TC) == RESET)
			;
		// usart_flag_clear(usart_periph, USART_FLAG_TC); // 清除TC标志
		usart_data_transmit(usart_periph, data[i]);
	}
	while (usart_flag_get(usart_periph, USART_FLAG_TC) == RESET)
		;
	return len;
}
