#include "uart.h"
#include "stdio.h"
#include "string.h"
#include "c3.h"
#include "delay.h"

ble_set_para ble_para;

/**********************************************************************************************
���ڷ��ͺ��� sendbuf��������ָ�� len���ͳ���
***********************************************************************************************/
int Uart_write(char *sendbuf, int len)
{
	return uart_send_bytes(USART0, (uint8_t *)sendbuf, len);
}

/**********************************************************************************************
���ڽ��պ��� recbuf��������ָ�� len���ճ��� timeout�ȴ�ʱ��
***********************************************************************************************/
int Uart_read(char *recvbuf, int len, int timeout)
{
	return uart_rece_bytes(USART0, (uint8_t *)recvbuf, len, timeout);
}

/*********************************************************************************************
������:    c3_init
����:      ���WIFIģ��AT�����Ƿ�����
��ڲ���:  ��
���ڲ����� ��
����ֵ��   AT������������1  ��������Ӧ����0
���ߣ�     ZZZ
����:      2023/4/6
��������:  �ж�C3ģ���Ƿ����
**********************************************************************************************/
uint8_t c3_init(void)
{
	int i;
	int recv_cnt = 0;
	char recv_buf[64] = {0};

	for (i = 0; i < 5; i++) // ��ȡ��������
	{
		Uart_write("AT\r\n", strlen("AT\r\n")); // ���AT�����Ƿ�����
		recv_cnt += Uart_read(&recv_buf[recv_cnt], sizeof(recv_buf) - recv_cnt, 100);
		if (strstr(recv_buf, "OK") != NULL)
		{
			return 1;
		}
	}
	return 0;
}
/*********************************************************************************************
������:    c3_ble_init
����:      �رջ���
��ڲ���:  ��
���ڲ����� ��
����ֵ��   AT������������1  ��������Ӧ����0
���ߣ�     AAA
����:      2023/9/4
��������:  None
**********************************************************************************************/

uint8_t c3_ble_init(void)
{
	int i;
	int recv_cnt = 0;
	char recv_buf[64] = {0};
	uint8_t state = 0;

	for (i = 0; i < 5; i++) // ��ȡ��������
	{
		Uart_write("ATE0\r\n", strlen("ATE0\r\n")); // �رջ���
		recv_cnt += Uart_read(&recv_buf[recv_cnt], sizeof(recv_buf) - recv_cnt, 100);
		if (strstr(recv_buf, "OK") != NULL)
		{
			state = 1;
		}
	}
	delay(100);
	if (state == 1)
	{
		for (i = 0; i < 5; i++) // ��ȡ��������
		{
			Uart_write("AT+BLEINIT=2\r\n", strlen("AT+BLEINIT=2\r\n")); // ����ģ��Ϊ Server
			recv_cnt += Uart_read(&recv_buf[recv_cnt], sizeof(recv_buf) - recv_cnt, 100);
			if (strstr(recv_buf, "OK") != NULL)
			{
				state = 2;
			}
		}
	}
	delay(100);
	if (state == 2)
	{
		for (i = 0; i < 5; i++) // ��ȡ��������
		{
			Uart_write("AT+BLEGATTSSRVCRE\r\n", strlen("AT+BLEGATTSSRVCRE\r\n")); // ���� GATTS ����
			recv_cnt += Uart_read(&recv_buf[recv_cnt], sizeof(recv_buf) - recv_cnt, 100);
			if (strstr(recv_buf, "OK") != NULL)
			{
				state = 3;
			}
		}
	}
	delay(100);
	if (state == 3)
	{
		for (i = 0; i < 5; i++) // ��ȡ��������
		{
			Uart_write("AT+BLEGATTSSRVSTART\r\n", strlen("AT+BLEGATTSSRVSTART\r\n")); // Open GATTS ����
			recv_cnt += Uart_read(&recv_buf[recv_cnt], sizeof(recv_buf) - recv_cnt, 100);
			if (strstr(recv_buf, "OK") != NULL)
			{
				state = 4;
			}
		}
	}
	delay(100);
	if (state == 4)
	{
		for (i = 0; i < 5; i++) // ��ȡ��������
		{
			Uart_write("AT+BLEADVDATA=\"02010606094333426C65\"\r\n", strlen("AT+BLEADVDATA==\"02010606094333426C65\"\r\n")); // ���ù㲥����
			recv_cnt += Uart_read(&recv_buf[recv_cnt], sizeof(recv_buf) - recv_cnt, 100);
			if (strstr(recv_buf, "OK") != NULL)
			{
				state = 5;
			}
		}
	}
	delay(100);
	if (state == 5)
	{
		for (i = 0; i < 5; i++) // ���� BLE Broadcast
		{
			Uart_write("AT+BLEADVSTART\r\n", strlen("AT+BLEADVSTART\r\n"));
			recv_cnt += Uart_read(&recv_buf[recv_cnt], sizeof(recv_buf) - recv_cnt, 100);
			if (strstr(recv_buf, "OK") != NULL)
			{
				state = 6;
			}
		}
	}
	delay(100);
	if (state == 6)
	{
		for (i = 0; i < 5; i++) // ���� BLE ͸��ģʽ��
		{
			Uart_write("AT+BLESPPCFG=1,1,6,1,5\r\n", strlen("AT+BLESPPCFG=1,1,6,1,5\r\n"));
			recv_cnt += Uart_read(&recv_buf[recv_cnt], sizeof(recv_buf) - recv_cnt, 100);
			if (strstr(recv_buf, "OK") != NULL)
			{
				state = 7;
			}
		}
	}
	delay(100);
	if (state == 7)
	{
		for (i = 0; i < 5; i++) // ����͸��ģʽ
		{
			Uart_write("AT+BLESPP\r\n", strlen("AT+BLESPP\r\n"));
			recv_cnt += Uart_read(&recv_buf[recv_cnt], sizeof(recv_buf) - recv_cnt, 100);
			if (strstr(recv_buf, "OK") != NULL)
			{
				return 1;
			}
		}
	}
	return 0;
}
