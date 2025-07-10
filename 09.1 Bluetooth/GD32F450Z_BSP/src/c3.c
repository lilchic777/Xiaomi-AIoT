#include "uart.h"
#include "stdio.h"
#include "string.h"
#include "c3.h"
#include "delay.h"

ble_set_para ble_para;

/**********************************************************************************************
串口发送函数 sendbuf发送数据指针 len发送长度
***********************************************************************************************/
int Uart_write(char *sendbuf, int len)
{
	return uart_send_bytes(USART0, (uint8_t *)sendbuf, len);
}

/**********************************************************************************************
串口接收函数 recbuf发送数据指针 len接收长度 timeout等待时间
***********************************************************************************************/
int Uart_read(char *recvbuf, int len, int timeout)
{
	return uart_rece_bytes(USART0, (uint8_t *)recvbuf, len, timeout);
}

/*********************************************************************************************
函数名:    c3_init
功能:      检测WIFI模块AT命令是否正常
入口参数:  无
出口参数： 无
返回值：   AT命令正常返回1  命令无相应返回0
作者：     ZZZ
日期:      2023/4/6
调用描述:  判断C3模块是否存在
**********************************************************************************************/
uint8_t c3_init(void)
{
	int i;
	int recv_cnt = 0;
	char recv_buf[64] = {0};

	for (i = 0; i < 5; i++) // 读取返回数据
	{
		Uart_write("AT\r\n", strlen("AT\r\n")); // 检测AT命令是否正常
		recv_cnt += Uart_read(&recv_buf[recv_cnt], sizeof(recv_buf) - recv_cnt, 100);
		if (strstr(recv_buf, "OK") != NULL)
		{
			return 1;
		}
	}
	return 0;
}
/*********************************************************************************************
函数名:    c3_ble_init
功能:      关闭回显
入口参数:  无
出口参数： 无
返回值：   AT命令正常返回1  命令无相应返回0
作者：     AAA
日期:      2023/9/4
调用描述:  None
**********************************************************************************************/

uint8_t c3_ble_init(void)
{
	int i;
	int recv_cnt = 0;
	char recv_buf[64] = {0};
	uint8_t state = 0;

	for (i = 0; i < 5; i++) // 读取返回数据
	{
		Uart_write("ATE0\r\n", strlen("ATE0\r\n")); // 关闭回显
		recv_cnt += Uart_read(&recv_buf[recv_cnt], sizeof(recv_buf) - recv_cnt, 100);
		if (strstr(recv_buf, "OK") != NULL)
		{
			state = 1;
		}
	}
	delay(100);
	if (state == 1)
	{
		for (i = 0; i < 5; i++) // 读取返回数据
		{
			Uart_write("AT+BLEINIT=2\r\n", strlen("AT+BLEINIT=2\r\n")); // 设置模块为 Server
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
		for (i = 0; i < 5; i++) // 读取返回数据
		{
			Uart_write("AT+BLEGATTSSRVCRE\r\n", strlen("AT+BLEGATTSSRVCRE\r\n")); // 创建 GATTS 服务
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
		for (i = 0; i < 5; i++) // 读取返回数据
		{
			Uart_write("AT+BLEGATTSSRVSTART\r\n", strlen("AT+BLEGATTSSRVSTART\r\n")); // Open GATTS 服务
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
		for (i = 0; i < 5; i++) // 读取返回数据
		{
			Uart_write("AT+BLEADVDATA=\"02010606094333426C65\"\r\n", strlen("AT+BLEADVDATA==\"02010606094333426C65\"\r\n")); // 设置广播名称
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
		for (i = 0; i < 5; i++) // 开启 BLE Broadcast
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
		for (i = 0; i < 5; i++) // 配置 BLE 透传模式，
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
		for (i = 0; i < 5; i++) // 开启透传模式
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
