#ifndef __UART_H__
#define __UART_H__

#include "gd32f4xx.h"

#define  out

typedef enum
{
    STATE_RX_IDLE,		//����           
    STATE_RX_RECEIVING,	//���ݽ�����
    STATE_RX_ERROR,		//���մ���
    STATE_RX_RECEIVED	//���ݽ������
}UartRecvState_t;


void uart_init(uint32_t usart_periph);
void timer3_init(void);
// void delay_ms(uint16_t mstime);
uint16_t uart_send_bytes(uint32_t usart_periph, uint8_t *data, uint16_t len);
uint16_t uart_rece_bytes(uint32_t usart_periph, uint8_t *data, uint16_t len, uint16_t timeout);
uint16_t uart_recv_bytes(uint32_t usart_periph,out uint8_t *data, uint16_t len);
void TIMER3_IRQHandler(void);
void USART0_IRQHandler(void);
void USART2_IRQHandler(void);
#endif


