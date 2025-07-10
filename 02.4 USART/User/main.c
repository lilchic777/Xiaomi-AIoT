/*************************************************************************************************************
����:     ���Ӵ��ڷ��͡�9����LED����������'a'����Ϩ��LED�����͡�A��LED��˸
�汾:     2023-5-17 V1.0
�޸ļ�¼: ��
����:     ZZZ
*************************************************************************************************************/

#include "gd32f4xx.h"
#include "led.h"
#include "uart.h"
#include "delay.h"
#include <string.h>

#define BUFFER_SIZE 64

uint8_t buffer;
uint8_t sndBuf[2] = {0x99, 0x01};

// �������ݽ��ջ���
uint8_t Uart0_RecvBuffer[1];
uint16_t Uart0_RecvLenth = 0;

uint8_t Uart2_RecvBuffer[BUFFER_SIZE]; // ���ӻ������������������ݸ���
uint16_t Uart2_RecvLenth = 0;

void UserInit(void);
void usartrec(void);

void UserInit(void)
{
	LED_Init();
	uart_init(USART2);
	__enable_irq(); // �ؼ��ж�ʹ��[1](@ref)
}

int main(void)
{
	UserInit();
	memset(Uart2_RecvBuffer, 0, 1);
	LED_ON();
	delay(2000);
	LED_OFF();
	while (1)
	{

		uart_send_bytes(USART2, sndBuf, 2);
		delay(1000);
		LED_BLINK();

		// if (Uart2_RecvLenth > 0)
		// {
		// 	uint8_t cmd = Uart2_RecvBuffer[0];
		// 	Uart2_RecvLenth = 0; // ������ɺ�����ָ��
		// 	switch (cmd)
		// 	{
		// 	case 0x39: // 0x39 - 9
		// 		LED_ON();
		// 		break;
		// 	case 0x61: // 0x61 - a
		// 		LED_OFF();
		// 		break;
		// 	case 0x41: // 0x41 - A
		// 		LED_BLINK();
		// 		break;
		// 	}
		// 	// if(cmd)	LED_BLINK();
		// }
		delay(200);
	}
}

void USART0_IRQHandler(void)
{
	if (usart_interrupt_flag_get(USART0, USART_INT_FLAG_RBNE) != RESET)
	{
		usart_interrupt_flag_clear(USART0, USART_INT_FLAG_RBNE);

		Uart0_RecvBuffer[Uart0_RecvLenth] = usart_data_receive(USART0);
		Uart0_RecvLenth++;
		if (Uart0_RecvLenth == 1)
			Uart0_RecvLenth = 0;
	}
}

void USART2_IRQHandler(void)
{
	if (usart_interrupt_flag_get(USART2, USART_INT_FLAG_RBNE) != RESET) // ���ջ����������
	{
		usart_interrupt_flag_clear(USART2, USART_INT_FLAG_RBNE); // ����жϱ�־λ
		if (Uart2_RecvLenth < BUFFER_SIZE)
		{
			Uart2_RecvBuffer[Uart2_RecvLenth] = usart_data_receive(USART2); // ����
			Uart2_RecvLenth++;												// ������һ��
		}
		else
		{
			// ��������ʱ�������ݻ�����ָ��
			Uart2_RecvLenth = 0;
		}
	}
}
