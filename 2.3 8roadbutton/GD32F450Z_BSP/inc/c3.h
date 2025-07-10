#include "uart.h"


extern int Uart_write(char *sendbuf, int len);
extern int Uart_read(char *recvbuf, int len, int timeout);
uint8_t c3_init(void);
int c3_wifi_tcp_init(int wifi_run_state,char *rec_date);
void c3_wifi_tcp_lead(int *wifi_run_state,int *tcp_status);
uint8_t c3_wifi_tcp_send(char *send_data);
uint16_t c3_wifi_tcp_receive(char *rec_data,uint16_t wait_time);
void c3_wifi_state(int *wifi_run_state,int *tcp_status);
void reset_c3_module(void);
uint8_t c3_ble_init( void );
