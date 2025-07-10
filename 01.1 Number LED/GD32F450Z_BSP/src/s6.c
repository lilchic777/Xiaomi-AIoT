#include "gd32f4xx.h"
#include "s6.h"
#include "i2c.h"

i2c_addr_def s6_uso_addr;
uint8_t recvData[2];
uint16_t usoData;

void S6_US_Get(uint32_t i2c_periph, uint8_t i2c_addr){
	i2c_read(i2c_periph,i2c_addr,GD32F330_READ_CMD,recvData,2);
	usoData  = (recvData[0] << 8) + recvData[1];
}
void S6_US_ADDR_Init( void ){
	uint8_t i;

	for(i=0;i<4;i++)
	{
		if(i2c_addr_poll(I2C0,GD32F330_ADDRESS_S6 + i*2)){
			s6_uso_addr.periph = I2C0;
			s6_uso_addr.addr = GD32F330_ADDRESS_S6 + i*2;
			s6_uso_addr.flag = 1;
		}else if(i2c_addr_poll(I2C1,GD32F330_ADDRESS_S6 + i*2)){
			s6_uso_addr.periph = I2C1;
			s6_uso_addr.addr = GD32F330_ADDRESS_S6 + i*2;
			s6_uso_addr.flag = 1;
		}
	}
	
	for(i=0;i<4;i++)
	{
	if(s6_uso_addr.flag != 1){
		if(i2c_addr_poll(I2C0,GD32F330_ADDRESS_S6 + i*2)){
		s6_uso_addr.periph = I2C0;
		s6_uso_addr.addr = GD32F330_ADDRESS_S6 + i*2;
		s6_uso_addr.flag = 1;
	}else if(i2c_addr_poll(I2C1,GD32F330_ADDRESS_S6 + i*2)){
		s6_uso_addr.periph = I2C1;
		s6_uso_addr.addr = GD32F330_ADDRESS_S6 + i*2;
		s6_uso_addr.flag = 1;
			}
		}
	}
	
	if(s6_uso_addr.flag){
		
	}
}
