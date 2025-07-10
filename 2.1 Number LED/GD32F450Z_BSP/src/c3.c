#include "uart.h"
#include "stdio.h"
#include "string.h"
#include "c3.h"
#include "delay.h"
#include "led.h"

char rec_buf[32];

uint8_t state;
/**********************************************************************************************
串口发送函数 sendbuf发送数据指针 len发送长度
***********************************************************************************************/
int Uart_write(char *sendbuf, int len)
{
	return uart_send_bytes(USART0,(uint8_t *)sendbuf,len);
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
		
		for(i = 0; i < 5; i++)             //读取返回数据
		{
				Uart_write("ATE0\r\n", strlen("ATE0\r\n"));    //检测AT命令是否正常
				recv_cnt += Uart_read(&recv_buf[recv_cnt], sizeof(recv_buf) - recv_cnt, 100);
				if(strstr(recv_buf,"OK") != NULL)
				{
					  return 1;
				}
		}
		return 0;
}

/*********************************************************************************************
函数名:    at_cmd
功能:      发送wifi at命令
入口参数:  *send_data待发送指令指针  *str_cmd 返回数据  wait_time:等待时间
出口参数： rec_date接收返回数据指针
返回值：   命令正常成功1  命令无相应返回0
作者：     ZZZ
日期:      2023/4/8
调用描述:  发送相应的at命令,判断返回是否正确
**********************************************************************************************/
uint8_t at_cmd(char *send_data,char *str_cmd,uint16_t wait_time)
{
	   int	recv_cnt = 0;
	   char	recv_buf[80] = {0};
	
     if(Uart_write(send_data, strlen(send_data)) <= 0)
	   return 0;
	   
	   recv_cnt = Uart_read(recv_buf, sizeof(recv_buf), wait_time);
		 if(recv_cnt <= 0)
	   return 0;
		 
		 if(strstr(recv_buf,str_cmd) != NULL)
		 return 1;
		 else
		 return 0;	 
}


/******************************************************************************************************************
函数名:    c3_wifi_net_status_get
功能:      获取模组网络状态
入口参数:  char *recv_buf 接收数据指针
出口参数： 
返回值：   wifi断开返回-1 重启返回-3 正常返回0
作者：     ZZZ
日期:      2023/4/8
调用描述:  解析接收数据判断状态
 *****************************************************************************************************************/
int c3_wifi_net_status_get(char *recv_buf)
{
		//读取返回数据
		char *rec = strstr(recv_buf,"ERROR");
		if (rec != NULL)
		{
				//printf("C3 ERROR\n");
		}

		rec = strstr(recv_buf,"+IPD,");
		if(rec == NULL)
		{
				rec = strstr(recv_buf,"CLOSED");
				if(rec != NULL)
				{
					return -1;
				}
		}

		rec = strstr(recv_buf,"+BLEDISCONN:");
		if(rec != NULL)
		{
			return -2;
		}
		
		
		rec = strstr(recv_buf,"ready\r\n");
		if(rec != NULL)
		{
				return -3;
		}
		
		return 0;
}



/*********************************************************************************************
函数名:    c3_wifi_tcp_init
功能:      初始化c3 wifi功能
入口参数:  wifi_run_state 初始化步骤
出口参数： wifi_run_state
返回值：   
作者：     ZZZ
日期:      2023/4/8
调用描述:  发送相应的at命令,初始化WIFI模块
**********************************************************************************************/
int c3_wifi_tcp_init(int wifi_run_state,char *rec_date)
{
		int		recv_cnt;
		char	recv_buf[80] = {0};
	  
	  switch(wifi_run_state)
		{
				case 1:	//关闭回显
				{
							if(Uart_write("ATE0\r\n", strlen("ATE0\r\n")) <= 0)
							{
									goto WIFI_ERR;
							}
							//读取返回数据
							recv_cnt = Uart_read(recv_buf, sizeof(recv_buf), 300);
							
							if(recv_cnt <= 0)
							{
									goto WIFI_ERR;
							}
							if(strstr(recv_buf,"OK") != NULL)
							{
									goto WIFI_OK;
							}
							break;
				}
				case 2:	//设置模式
				{
							if(Uart_write("AT+CWMODE=1\r\n", strlen("AT+CWMODE=1\r\n")) <= 0)
							{
									goto WIFI_ERR;
							}
							//读取返回数据
							recv_cnt = Uart_read(recv_buf, sizeof(recv_buf), 300);
							
							if(recv_cnt <= 0)
							{
									goto WIFI_ERR;
							}
							if(strstr(recv_buf,"OK") != NULL)
							{
									goto WIFI_OK;
							}
							break;
				}
				case 3://是否连接到网络
				{
							recv_cnt = 0;
							delay_ms(1000);
							if(Uart_write("AT+CWJAP?\r\n", strlen("AT+CWJAP?\r\n")) <= 0)
							{
									goto WIFI_ERR;
							}
							//读取返回数据
							recv_cnt = Uart_read(recv_buf, sizeof(recv_buf), 300);
							
							char *rec = strstr(recv_buf,"+CWJAP");
							if(rec != NULL)
							{
									memcpy(rec_date,recv_buf,recv_cnt);
									return 1;  //网络连接成功  跳过网络配置
							}
							if(recv_cnt <= 0)
							{
									goto WIFI_ERR;
							}
							if(strstr(recv_buf,"OK") != NULL)
							{
									goto WIFI_OK;
							}
							break;
				}
				case 4://配置WIFI信息
				{
							recv_cnt = 0;
							
							if(Uart_write("AT+CWJAP=\"atest001\",\"11111111\"\r\n", strlen("AT+CWJAP=\"atest001\",\"11111111\"\r\n")) <= 0)
							{
									goto WIFI_ERR;
							}
							//读取返回数据
							for(int x = 10;x != 0; x --)
							{
									recv_cnt += Uart_read(&recv_buf[recv_cnt], sizeof(recv_buf) - recv_cnt, 100);
									if(strstr(recv_buf,"ERROR") != NULL)
									{
										break;
									}
									if(strstr(recv_buf,"OK") != NULL)
									{
										goto WIFI_OK;
									}
							}
							goto WIFI_ERR;
							
				}
				case 5://查询网络注册是否成功
				{
							recv_cnt = 0;
							if(Uart_write("AT+CIFSR\r\n", strlen("AT+CIFSR\r\n")) <= 0)
							{
									goto WIFI_ERR;
							}
							//读取返回数据
							recv_cnt = Uart_read(&recv_buf[recv_cnt], sizeof(recv_buf) - recv_cnt, 300);
							if(recv_cnt <= 0)
							{
									break;
							}
							char *rec = strstr(recv_buf,"+CIFSR:STAIP,\"0.0.0.0\"");
							if(rec != NULL)
							{
									goto WIFI_ERR;
							}
							if(strstr(recv_buf,"OK") != NULL)
							{
									goto WIFI_OK;
							}
							break;
				}
				case 6:                        //配置网络IP和端口
				{
							recv_cnt = 0;
							if(Uart_write("AT+CIPSTART=\"TCP\",\"192.168.137.9\",8080\r\n", strlen("AT+CIPSTART=\"TCP\",\"192.168.137.9\",8080\r\n")) <= 0)
							{
									goto WIFI_ERR;
							}
							//读取返回数据
							for(int x = 10;x != 0; x --)
							{
									recv_cnt += Uart_read(&recv_buf[recv_cnt], (sizeof(recv_buf) - recv_cnt), 100);
									if(strstr(recv_buf,"ERROR") != NULL)
									{
											goto WIFI_ERR;
											//goto WIFI_OK;
									}
									if(strstr(recv_buf,"CONNECT") != NULL)
									{
											//break;
										  goto WIFI_OK;
									}
									if(strstr(recv_buf,"OK") != NULL)
									{
											goto WIFI_OK;
									}
					    }
			        break;
				}
				case  8:
				{
					    Uart_write("AT+RST\r\n", strlen("AT+RST\r\n"));
					    delay_ms(3000);
					    return -2;
				}	
				default:
				break;
		}
		WIFI_ERR:
			memcpy(rec_date,recv_buf,recv_cnt);
			return -1;

		WIFI_OK:

			LED_ON();
			delay(1000);
			LED_OFF();
			delay(1000);
			LED_ON();
			delay(1000);
			LED_OFF();
			delay(1000);
			memcpy(rec_date,recv_buf,recv_cnt);
			return 0;
}



/*********************************************************************************************
函数名:    c3_wifi_tcp_lead
功能:      初始化c3 wifi功能
入口参数:  *wifi_run_state 初始化步骤 *tcp_status:tcp状态
出口参数： &wifi_run_state *tcp_status
返回值：   无
作者：     ZZZ
日期:      2023/4/8
调用描述:  调用AT指令完成wifi初始化
**********************************************************************************************/
void c3_wifi_tcp_lead(int *wifi_run_state,int *tcp_status)
{
    char rec_buf[80]={0};
		int net_state;
  
    if(*tcp_status == -1)	
		{
				int wifi_rec = 0;
				wifi_rec = c3_wifi_tcp_init(*wifi_run_state,rec_buf);        //连接服务器
				if( wifi_rec == 0)
				{
						if(*wifi_run_state == 6)
						{
								*tcp_status = 0;
								*wifi_run_state = 1;
						}
						else
						{
							  *wifi_run_state = *wifi_run_state + 1;
						}
				}
				else if(wifi_rec == 1)
				{
						*wifi_run_state = 5;
				}
				else if(wifi_rec == -1)
				{
					  *wifi_run_state = 8;
        }		
				else if(wifi_rec == -2)
				{
					  *wifi_run_state = 1;
        }		
				
				net_state = c3_wifi_net_status_get(rec_buf);
				if(net_state == -1)
				*wifi_run_state = 8;
        else if(net_state == -3)
        *wifi_run_state = 1;					
		}
}



/*********************************************************************************************
函数名:    c3_wifi_tcp_send
功能:      c3 wifi发送数据
入口参数:  *send_data
出口参数： 无
返回值：   成功返回1,失败返回0
作者：     ZZZ
日期:      2023/4/8
调用描述:  发送wifi数据
**********************************************************************************************/
uint8_t c3_wifi_tcp_send(char *send_data)
{
	   uint8_t len;
	   char send_buffer[200];
	   char	recv_buf[80] = {0};

     len = strlen(send_data);
     memset(send_buffer,0,200);
	   sprintf(send_buffer,"AT+CIPSEND=%d\r\n",len);
	   Uart_write(send_buffer, strlen(send_buffer));
		 delay_ms(200);
	   memset(send_buffer,0,200);
     strncpy(send_buffer,(const char*)send_data,len);	
	   Uart_write(send_buffer,len);
	   Uart_read(recv_buf, sizeof(recv_buf), 300);
	   if(strstr(recv_buf,"SEND OK") != NULL)
	   len = 1;
		 else
		 len = 0;
		 
		 return len;
}


/*********************************************************************************************
函数名:    c3_wifi_tcp_receive
功能:      接收wifi下发数据
入口参数:  *rec_data:接收数据指针  wait_time:等待时间
出口参数： *rec_data
返回值：   实际接收长度
作者：     ZZZ
日期:      2023/4/8
调用描述:  接收wifi下发数据
**********************************************************************************************/
uint16_t c3_wifi_tcp_receive(char *rec_data,uint16_t wait_time)
{
			uint16_t rec_len;	
	    rec_len = Uart_read(rec_data,300,wait_time);
			return rec_len;
}
/********************************************************************************************
函数名:    reset_c3_module
功能:      重启模块
入口参数:  无
出口参数： 无
返回值：   无
作者：     ZZZ
日期:      2023/4/19
调用描述:  重启模块
*********************************************************************************************/
void reset_c3_module(void)
{
	    char	recv_buf[80] = {0};
		  uint8_t i;
			
			for(i=0;i<5;i++)
			{
						Uart_write("AT+RST\r\n", strlen("AT+RST\r\n"));
						Uart_read(recv_buf, sizeof(recv_buf), 300);
						if(strstr(recv_buf,"OK") != NULL)
						{
								break;
						} 
		  }
}

void c3_wifi_state(int *wifi_run_state,int *tcp_status)
{
      char rec_buf[80]={0};
			int net_state;

      net_state = c3_wifi_net_status_get(rec_buf);	
      if(net_state == -1)
			{
				  *wifi_run_state = 1;
				  *tcp_status = -1;
			}	
      else if(net_state == -3)
      {
				  *wifi_run_state = 1;
			}	
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

uint8_t c3_ble_init( void ){
	int i;
	int recv_cnt = 0;
	char recv_buf[64] = {0};
	uint8_t state = 0;
	
	for(i = 0; i < 5; i++)             //读取返回数据
		{
				Uart_write("ATE0\r\n", strlen("ATE0\r\n"));    //关闭回显
				recv_cnt += Uart_read(&recv_buf[recv_cnt], sizeof(recv_buf) - recv_cnt, 100);
				if(strstr(recv_buf,"OK") != NULL)
				{
					  state = 1;
				}
		}
	delay(100);
	if(state == 1)
	{
		for(i = 0; i < 5; i++)             //读取返回数据
		{
				Uart_write("AT+BLEINIT=2\r\n", strlen("AT+BLEINIT=2\r\n"));    //设置模块为 Server 
				recv_cnt += Uart_read(&recv_buf[recv_cnt], sizeof(recv_buf) - recv_cnt, 100);
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
				Uart_write("AT+BLEGATTSSRVCRE\r\n", strlen("AT+BLEGATTSSRVCRE\r\n"));    //创建 GATTS 服务
				recv_cnt += Uart_read(&recv_buf[recv_cnt], sizeof(recv_buf) - recv_cnt, 100);
				if(strstr(recv_buf,"OK") != NULL)
				{
					  state = 3;
				}
		}
	}
	delay(100);
	if(state == 3)
	{
		for(i = 0; i < 5; i++)             //读取返回数据
		{
				Uart_write("AT+BLEGATTSSRVSTART\r\n", strlen("AT+BLEGATTSSRVSTART\r\n"));    //Open GATTS 服务
				recv_cnt += Uart_read(&recv_buf[recv_cnt], sizeof(recv_buf) - recv_cnt, 100);
				if(strstr(recv_buf,"OK") != NULL)
				{
					  state = 4;
				}
		}
	}
	delay(100);
	if(state == 4)
	{
		for(i = 0; i < 5; i++)             //读取返回数据
		{
				Uart_write("AT+BLEADVDATA=\"02010606094333426C65\"\r\n", strlen("AT+BLEADVDATA==\"02010606094333426C65\"\r\n"));    //设置广播名称
				recv_cnt += Uart_read(&recv_buf[recv_cnt], sizeof(recv_buf) - recv_cnt, 100);
				if(strstr(recv_buf,"OK") != NULL)
				{
					  state = 5;
				}
		}
	}
	delay(100);
	if(state == 5)
	{
		for(i = 0; i < 5; i++)             //开启 BLE Broadcast
		{
				Uart_write("AT+BLEADVSTART\r\n", strlen("AT+BLEADVSTART\r\n"));   
				recv_cnt += Uart_read(&recv_buf[recv_cnt], sizeof(recv_buf) - recv_cnt, 100);
				if(strstr(recv_buf,"OK") != NULL)
				{
					  state = 6;
				}
		}
	}
	delay(100);
	if(state == 6)
	{
		for(i = 0; i < 5; i++)             //配置 BLE 透传模式，
		{
				Uart_write("AT+BLESPPCFG=1,1,6,1,5\r\n", strlen("AT+BLESPPCFG=1,1,6,1,5\r\n"));   
				recv_cnt += Uart_read(&recv_buf[recv_cnt], sizeof(recv_buf) - recv_cnt, 100);
				if(strstr(recv_buf,"OK") != NULL)
				{
					  state = 7;
				}
		}
	}
	delay(100);
	if(state == 7)
	{
		for(i = 0; i < 5; i++)             //开启透传模式
		{
				Uart_write("AT+BLESPP\r\n", strlen("AT+BLESPP\r\n"));   
				recv_cnt += Uart_read(&recv_buf[recv_cnt], sizeof(recv_buf) - recv_cnt, 100);
				if(strstr(recv_buf,"OK") != NULL)
				{
					  return 1;
				}
		}
	}
	return 0;
	
}






























































