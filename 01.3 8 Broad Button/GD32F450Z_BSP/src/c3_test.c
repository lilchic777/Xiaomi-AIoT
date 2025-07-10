#include "gd32f4xx.h"
#include "c3_test.h"
#include "delay.h"
#include "c3.h"
#include "uart.h"
#include <string.h>
#include "led.h"

void test( void ){
	uint8_t i;
	int recv_cnt = 0;
	char recv_buf[64];
	uint8_t state = 0;
	
	for(i = 0; i < 5; i++)             //读取返回数据
		{
				Uart_write("ATE0\r\n", strlen("ATE0\r\n"));    //关闭回显
				memset(recv_buf,0,64);
				recv_cnt = Uart_read(recv_buf, sizeof(recv_buf), 100);
				if(recv_cnt <= 0)
					state = 97;
				if(strstr(recv_buf,"OK") != NULL)
				{
					  state = 1;
						break;
				}
		}
	delay(100);
	if(state == 1)
	{
		for(i = 0; i < 5; i++)             //读取返回数据
		{
				Uart_write("AT+CWMODE=2\r\n", strlen("AT+CWMODE=2\r\n"));    //设置模块为Station Mode
				memset(recv_buf,0,64);
				recv_cnt = Uart_read(recv_buf, sizeof(recv_buf), 100);
				if(recv_cnt <= 0)
					state = 98;
				if(strstr(recv_buf,"OK") != NULL)
				{
					  state = 2;
				}
		}
	}
	delay(100);
	if(state == 2)
	{
		for(i = 0; i < 5; i++)             //读取返回数据
		{
				Uart_write("AT+CWSAP=\"C3_WiFi\",\"11111111\",5,3", strlen("AT+CWSAP=\"C3_WiFi\",\"11111111\",5,3"));    //设置模块为SoftAP Mode
				memset(recv_buf,0,64);
				recv_cnt = Uart_read(recv_buf, sizeof(recv_buf), 100);
				if(recv_cnt <= 0)
					state = 98;
				if(strstr(recv_buf,"OK") != NULL)
				{
					  state = 3;
						LED_ON();
						delay(1500);
				}
		}
	}
	delay(100);
}



