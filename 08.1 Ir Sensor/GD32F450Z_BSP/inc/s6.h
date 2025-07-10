#ifndef S6_H
#define S6_H
#include "i2c.h"

#define GD32F330_ADDRESS_S6    	  0x58		//0x58,0x5A,0x5C,0x5E
#define	GD32F330_READ_CMD		  0xAA		//超声波距离值,单位mm,2字节,连续读取2字节数据

extern i2c_addr_def s6_uso_addr;
extern uint8_t recvData[2];
extern uint16_t usoData;

typedef struct
{
   i2c_addr_def ult_addr[4];
}s6_addr_def;

void S6_US_Get(uint32_t i2c_periph, uint8_t i2c_addr);
void S6_US_ADDR_Init( void );

#endif
