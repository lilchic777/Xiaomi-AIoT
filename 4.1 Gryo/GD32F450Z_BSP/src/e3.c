#include "gd32f4xx.h"
#include "i2c.h"
#include "e3.h"

i2c_addr_def e3_cur_addr;
uint8_t curState;
uint8_t curNum;

void E3_Curtain_Opt(uint32_t i2c_periph,uint8_t i2c_addr, uint8_t opt){
	i2c_byte_write(i2c_periph,i2c_addr,0x03,opt);

}

void E3_Curtain_ReadState(uint32_t i2c_periph,uint8_t i2c_addr){
	i2c_read(i2c_periph,i2c_addr,0x01,&curState,1);
}

void E3_Curtain_ReadNum(uint32_t i2c_periph,uint8_t i2c_addr){
	i2c_read(i2c_periph,i2c_addr,0x02,&curNum,1);
}

void E3_Curtain_ADDR_Init( void ){
	uint8_t i;
	
	for(i=0;i<4;i++){
	if(i2c_addr_poll(I2C0,GD32F330_E3_ADDR + i*2)){
		e3_cur_addr.periph = I2C0;
		e3_cur_addr.addr = GD32F330_E3_ADDR + i*2;
		e3_cur_addr.flag = 1;
	}else if(i2c_addr_poll(I2C1,GD32F330_E3_ADDR + i*2)){
		e3_cur_addr.periph = I2C1;
		e3_cur_addr.addr = GD32F330_E3_ADDR + i*2;
		e3_cur_addr.flag = 1;
		}
	}
	
	if(e3_cur_addr.flag != 1){
		for(i=0;i<4;i++){
		if(i2c_addr_poll(I2C0,GD32F330_E3_ADDR + i*2)){
			e3_cur_addr.periph = I2C0;
			e3_cur_addr.addr = GD32F330_E3_ADDR + i*2;
			e3_cur_addr.flag = 1;
		}else if(i2c_addr_poll(I2C1,GD32F330_E3_ADDR + i*2)){
			e3_cur_addr.periph = I2C1;
			e3_cur_addr.addr = GD32F330_E3_ADDR + i*2;
			e3_cur_addr.flag = 1;
			}
		}
	}
	
	if(e3_cur_addr.flag){
		
	}
}













