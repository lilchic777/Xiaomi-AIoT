#include "uart.h"

typedef struct
{
    uint8_t set_flag;
	  uint8_t set_value;
}ble_set_para;

extern ble_set_para ble_para;

int Uart_write(char *sendbuf, int len);
int Uart_read(char *recvbuf, int len, int timeout);
uint8_t c3_init(void);
uint8_t c3_ble_init( void );
