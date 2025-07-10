/* 连接串口发送‘9’，E1亮蓝灯，发送'a'立刻熄灭E1 LED，发送‘A’E1亮白灯 */
#include <stdio.h>
#include "delay.h"
#include "e1.h"
#include "u1.h"
#include "uart.h"
#include "gd32f4xx.h"
#include "gd32f4xx_usart.h"

#define BUFFER_SIZE 64

uint8_t buffer;
uint8_t sndBuf[2] = {'H', 'i'};

// 串口数据接收缓存
// uint8_t Uart0_RecvBuffer[1];
// uint16_t Uart0_RecvLenth = 0;

// uint8_t Uart1_RecvBuffer[BUFFER_SIZE]; // 增加缓冲区容量，避免数据覆盖
// volatile uint16_t Uart1_RecvLenth = 0;

uint8_t Uart2_RecvBuffer[BUFFER_SIZE]; // 增加缓冲区容量，避免数据覆盖
volatile uint16_t Uart2_RecvLenth = 0;

void UserInit(void)
{
	u1_led_init();
	uart_init(USART2);
	__enable_irq(); // 关键中断使能

	/* E1初始化 */
	e1_tube_info = e1_tube_init();
	e1_led_info = e1_led_init();
	e1_led_rgb_set(e1_led_info, 0, 0, 0);
}

int main()
{
	char buf[10] = {0};
	char showBuf[10] = {0};

	UserInit();
	memset(Uart2_RecvBuffer, 0, 1);

	u1_led_on();
	delay(2000);
	u1_led_off();

	while (1)
	{
		// usart_flag_clear(USART2, USART_FLAG_TC); // 发送前清除TC标志，确保首次发送有效
		uart_send_bytes(USART2, sndBuf, 2);
		delay(1000);
		u1_led_toggle();

		/* 将格式化字符串写入buf */
		sprintf(showBuf, "%d", Uart2_RecvLenth % 10);
		/* 在数码管上显示showBuf中的字符串 */
		e1_tube_str_set(e1_tube_info, showBuf);

		e1_led_rgb_set(e1_led_info, 100, 0, 0);

		if (Uart2_RecvLenth > 0)
		{
			__disable_irq(); // 暂时禁用中断，避免数据竞争
			uint16_t len = Uart2_RecvLenth;
			Uart2_RecvLenth = 0;
			__enable_irq();
			for (int i = 0; i < len; i++)
			{
				char cmd = Uart2_RecvBuffer[i];
				switch (cmd)
				{
				case '9':
					e1_led_rgb_set(e1_led_info, 0, 0, 100); // 亮蓝灯
					break;
				case 'a':
					e1_led_rgb_set(e1_led_info, 0, 0, 0); // 关闭
					break;
				case 'A':
					e1_led_rgb_set(e1_led_info, 100, 100, 100); // 亮白灯
					break;
				}
			}
			len = 0; // 处理完清空长度
		}
		/* 延时100ms */
		delay(100);
	}
}

// void USART0_IRQHandler(void)
// {
// 	if (usart_interrupt_flag_get(USART0, USART_INT_FLAG_RBNE) != RESET)
// 	{
// 		usart_interrupt_flag_clear(USART0, USART_INT_FLAG_RBNE);

// 		Uart0_RecvBuffer[Uart0_RecvLenth] = usart_data_receive(USART0);
// 		Uart0_RecvLenth++;
// 		if (Uart0_RecvLenth == 1)
// 			Uart0_RecvLenth = 0;
// 	}
// }

// void USART1_IRQHandler(void)
// {
// 	if (usart_interrupt_flag_get(USART1, USART_INT_FLAG_RBNE) != RESET) // 接收缓冲存在数据
// 	{
// 		e1_led_rgb_set(e1_led_info, 0, 100, 0);
// 		usart_interrupt_flag_clear(USART1, USART_INT_FLAG_RBNE); // 清除中断标志位
// 		if (Uart1_RecvLenth < BUFFER_SIZE)
// 		{
// 			Uart1_RecvBuffer[Uart1_RecvLenth] = usart_data_receive(USART1); // 接收
// 			Uart1_RecvLenth++;												// 仅递增一次
// 		}
// 		else
// 		{
// 			// 缓冲区满时丢弃数据或重置指针
// 			Uart1_RecvLenth = 0;
// 		}
// 	}
// }

void USART2_IRQHandler(void)
{
	if (usart_interrupt_flag_get(USART2, USART_INT_FLAG_RBNE) != RESET) // 接收缓冲存在数据
	{
		e1_led_rgb_set(e1_led_info, 0, 100, 0);
		usart_interrupt_flag_clear(USART2, USART_INT_FLAG_RBNE); // 清除中断标志位
		if (Uart2_RecvLenth < BUFFER_SIZE)
		{
			Uart2_RecvBuffer[Uart2_RecvLenth] = usart_data_receive(USART2); // 接收
			Uart2_RecvLenth++;												// 仅递增一次
		}
		else
		{
			// 缓冲区满时丢弃数据或重置指针
			Uart2_RecvLenth = 0;
		}
	}
}
