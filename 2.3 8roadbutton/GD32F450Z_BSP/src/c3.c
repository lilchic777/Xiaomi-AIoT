#include "uart.h"
#include "stdio.h"
#include "string.h"
#include "c3.h"
#include "delay.h"
#include "led.h"

char rec_buf[32];

uint8_t state;
/**********************************************************************************************
���ڷ��ͺ��� sendbuf��������ָ�� len���ͳ���
***********************************************************************************************/
int Uart_write(char *sendbuf, int len)
{
	return uart_send_bytes(USART0,(uint8_t *)sendbuf,len);
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
		
		for(i = 0; i < 5; i++)             //��ȡ��������
		{
				Uart_write("ATE0\r\n", strlen("ATE0\r\n"));    //���AT�����Ƿ�����
				recv_cnt += Uart_read(&recv_buf[recv_cnt], sizeof(recv_buf) - recv_cnt, 100);
				if(strstr(recv_buf,"OK") != NULL)
				{
					  return 1;
				}
		}
		return 0;
}

/*********************************************************************************************
������:    at_cmd
����:      ����wifi at����
��ڲ���:  *send_data������ָ��ָ��  *str_cmd ��������  wait_time:�ȴ�ʱ��
���ڲ����� rec_date���շ�������ָ��
����ֵ��   ���������ɹ�1  ��������Ӧ����0
���ߣ�     ZZZ
����:      2023/4/8
��������:  ������Ӧ��at����,�жϷ����Ƿ���ȷ
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
������:    c3_wifi_net_status_get
����:      ��ȡģ������״̬
��ڲ���:  char *recv_buf ��������ָ��
���ڲ����� 
����ֵ��   wifi�Ͽ�����-1 ��������-3 ��������0
���ߣ�     ZZZ
����:      2023/4/8
��������:  �������������ж�״̬
 *****************************************************************************************************************/
int c3_wifi_net_status_get(char *recv_buf)
{
		//��ȡ��������
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
������:    c3_wifi_tcp_init
����:      ��ʼ��c3 wifi����
��ڲ���:  wifi_run_state ��ʼ������
���ڲ����� wifi_run_state
����ֵ��   
���ߣ�     ZZZ
����:      2023/4/8
��������:  ������Ӧ��at����,��ʼ��WIFIģ��
**********************************************************************************************/
int c3_wifi_tcp_init(int wifi_run_state,char *rec_date)
{
		int		recv_cnt;
		char	recv_buf[80] = {0};
	  
	  switch(wifi_run_state)
		{
				case 1:	//�رջ���
				{
							if(Uart_write("ATE0\r\n", strlen("ATE0\r\n")) <= 0)
							{
									goto WIFI_ERR;
							}
							//��ȡ��������
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
				case 2:	//����ģʽ
				{
							if(Uart_write("AT+CWMODE=1\r\n", strlen("AT+CWMODE=1\r\n")) <= 0)
							{
									goto WIFI_ERR;
							}
							//��ȡ��������
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
				case 3://�Ƿ����ӵ�����
				{
							recv_cnt = 0;
							delay_ms(1000);
							if(Uart_write("AT+CWJAP?\r\n", strlen("AT+CWJAP?\r\n")) <= 0)
							{
									goto WIFI_ERR;
							}
							//��ȡ��������
							recv_cnt = Uart_read(recv_buf, sizeof(recv_buf), 300);
							
							char *rec = strstr(recv_buf,"+CWJAP");
							if(rec != NULL)
							{
									memcpy(rec_date,recv_buf,recv_cnt);
									return 1;  //�������ӳɹ�  ������������
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
				case 4://����WIFI��Ϣ
				{
							recv_cnt = 0;
							
							if(Uart_write("AT+CWJAP=\"atest001\",\"11111111\"\r\n", strlen("AT+CWJAP=\"atest001\",\"11111111\"\r\n")) <= 0)
							{
									goto WIFI_ERR;
							}
							//��ȡ��������
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
				case 5://��ѯ����ע���Ƿ�ɹ�
				{
							recv_cnt = 0;
							if(Uart_write("AT+CIFSR\r\n", strlen("AT+CIFSR\r\n")) <= 0)
							{
									goto WIFI_ERR;
							}
							//��ȡ��������
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
				case 6:                        //��������IP�Ͷ˿�
				{
							recv_cnt = 0;
							if(Uart_write("AT+CIPSTART=\"TCP\",\"192.168.137.9\",8080\r\n", strlen("AT+CIPSTART=\"TCP\",\"192.168.137.9\",8080\r\n")) <= 0)
							{
									goto WIFI_ERR;
							}
							//��ȡ��������
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
������:    c3_wifi_tcp_lead
����:      ��ʼ��c3 wifi����
��ڲ���:  *wifi_run_state ��ʼ������ *tcp_status:tcp״̬
���ڲ����� &wifi_run_state *tcp_status
����ֵ��   ��
���ߣ�     ZZZ
����:      2023/4/8
��������:  ����ATָ�����wifi��ʼ��
**********************************************************************************************/
void c3_wifi_tcp_lead(int *wifi_run_state,int *tcp_status)
{
    char rec_buf[80]={0};
		int net_state;
  
    if(*tcp_status == -1)	
		{
				int wifi_rec = 0;
				wifi_rec = c3_wifi_tcp_init(*wifi_run_state,rec_buf);        //���ӷ�����
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
������:    c3_wifi_tcp_send
����:      c3 wifi��������
��ڲ���:  *send_data
���ڲ����� ��
����ֵ��   �ɹ�����1,ʧ�ܷ���0
���ߣ�     ZZZ
����:      2023/4/8
��������:  ����wifi����
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
������:    c3_wifi_tcp_receive
����:      ����wifi�·�����
��ڲ���:  *rec_data:��������ָ��  wait_time:�ȴ�ʱ��
���ڲ����� *rec_data
����ֵ��   ʵ�ʽ��ճ���
���ߣ�     ZZZ
����:      2023/4/8
��������:  ����wifi�·�����
**********************************************************************************************/
uint16_t c3_wifi_tcp_receive(char *rec_data,uint16_t wait_time)
{
			uint16_t rec_len;	
	    rec_len = Uart_read(rec_data,300,wait_time);
			return rec_len;
}
/********************************************************************************************
������:    reset_c3_module
����:      ����ģ��
��ڲ���:  ��
���ڲ����� ��
����ֵ��   ��
���ߣ�     ZZZ
����:      2023/4/19
��������:  ����ģ��
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
������:    c3_ble_init
����:      �رջ���
��ڲ���:  ��
���ڲ����� ��
����ֵ��   AT������������1  ��������Ӧ����0
���ߣ�     AAA
����:      2023/9/4
��������:  None
**********************************************************************************************/

uint8_t c3_ble_init( void ){
	int i;
	int recv_cnt = 0;
	char recv_buf[64] = {0};
	uint8_t state = 0;
	
	for(i = 0; i < 5; i++)             //��ȡ��������
		{
				Uart_write("ATE0\r\n", strlen("ATE0\r\n"));    //�رջ���
				recv_cnt += Uart_read(&recv_buf[recv_cnt], sizeof(recv_buf) - recv_cnt, 100);
				if(strstr(recv_buf,"OK") != NULL)
				{
					  state = 1;
				}
		}
	delay(100);
	if(state == 1)
	{
		for(i = 0; i < 5; i++)             //��ȡ��������
		{
				Uart_write("AT+BLEINIT=2\r\n", strlen("AT+BLEINIT=2\r\n"));    //����ģ��Ϊ Server 
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
		for(i = 0; i < 5; i++)             //��ȡ��������
		{
				Uart_write("AT+BLEGATTSSRVCRE\r\n", strlen("AT+BLEGATTSSRVCRE\r\n"));    //���� GATTS ����
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
		for(i = 0; i < 5; i++)             //��ȡ��������
		{
				Uart_write("AT+BLEGATTSSRVSTART\r\n", strlen("AT+BLEGATTSSRVSTART\r\n"));    //Open GATTS ����
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
		for(i = 0; i < 5; i++)             //��ȡ��������
		{
				Uart_write("AT+BLEADVDATA=\"02010606094333426C65\"\r\n", strlen("AT+BLEADVDATA==\"02010606094333426C65\"\r\n"));    //���ù㲥����
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
		for(i = 0; i < 5; i++)             //���� BLE Broadcast
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
		for(i = 0; i < 5; i++)             //���� BLE ͸��ģʽ��
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
		for(i = 0; i < 5; i++)             //����͸��ģʽ
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






























































