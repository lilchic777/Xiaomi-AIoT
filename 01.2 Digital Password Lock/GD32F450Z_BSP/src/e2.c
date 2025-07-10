#include "gd32f4xx.h"
#include "e2.h"
#include "i2c.h"
#include "delay.h"

i2c_addr_def e2_fan_addr;

void E2_PCA9685PW_Init( uint32_t i2c_periph, uint8_t i2c_addr ){
	i2c_byte_write(i2c_periph,i2c_addr,0x0,0x0);
	//模式1
	delay(1000);
	E2_PCA9685PW_Off(i2c_periph,i2c_addr);
}

void E2_PCA9685PW_Off( uint32_t i2c_periph, uint8_t i2c_addr ){
	i2c_byte_write(i2c_periph,i2c_addr,0x6,0x0);
	i2c_byte_write(i2c_periph,i2c_addr,0x7,0x0);
	i2c_byte_write(i2c_periph,i2c_addr,0x8,0x0);
	i2c_byte_write(i2c_periph,i2c_addr,0x9,0x0);
	
	i2c_byte_write(i2c_periph,i2c_addr,0xFA,0x0);
	i2c_byte_write(i2c_periph,i2c_addr,0xFB,0x0);
	i2c_byte_write(i2c_periph,i2c_addr,0xFC,0x0);
	i2c_byte_write(i2c_periph,i2c_addr,0xFD,0x10);
}

void E2_PCA9685PW_PreScale( uint32_t i2c_periph, uint8_t i2c_addr, uint8_t set){
	i2c_byte_write(i2c_periph,i2c_addr,0xFE,set);
}

void E2_SetPWM(uint32_t i2c_periph,uint8_t i2c_addr,uint8_t num,uint16_t on,uint16_t off){
	i2c_byte_write(i2c_periph,i2c_addr,0x6+4*num,on);
	i2c_byte_write(i2c_periph,i2c_addr,0x7+4*num,on>>8);
	i2c_byte_write(i2c_periph,i2c_addr,0x8+4*num,off);
	i2c_byte_write(i2c_periph,i2c_addr,0x9+4*num,off>>8);
}


void E2_PCA9685PW_Speed(uint32_t i2c_periph,uint8_t i2c_addr,uint8_t speed){
	uint16_t off,on;

	if(speed > 100)
		speed = 100;

	on = 0x00;
	off = on + 0xfff*speed/100;
	E2_SetPWM(i2c_periph,i2c_addr,0,on,off);
}




void E2_FAN_ADDR_Init( void ){
	uint8_t i;
	
	for(i=0;i<4;i++){
		if(i2c_addr_poll(I2C0, E2_FAN_ADDR + i*2)){
			e2_fan_addr.periph = I2C0;
			e2_fan_addr.addr = E2_FAN_ADDR + i*2;
			e2_fan_addr.flag = 1;
			break;
		}
	}
	
	if(e2_fan_addr.flag != 1){
		for(i=0;i<4;i++){
			if(i2c_addr_poll(I2C0, E2_FAN_ADDR + i*2)){
				e2_fan_addr.periph = I2C0;
				e2_fan_addr.addr = E2_FAN_ADDR + i*2;
				e2_fan_addr.flag = 1;
				break;
			}
		}
	}
	
	if(e2_fan_addr.flag){
		E2_PCA9685PW_Init(e2_fan_addr.periph,e2_fan_addr.addr);
	}

}
