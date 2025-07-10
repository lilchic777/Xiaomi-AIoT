#include "gd32f4xx.h"
#include "s7.h"
#include "i2c.h"
#include "timer.h"

i2c_addr_def s7_ir_addr;
uint8_t irOut;
uint8_t irState;

void S7_IR_Init(uint32_t i2c_periph, uint8_t i2c_addr){
	i2c_byte_write(i2c_periph,i2c_addr,0x02,0x00);
	i2c_byte_write(i2c_periph,i2c_addr,0x03,0xFF);
}

void S7_IR_Get(uint32_t i2c_periph, uint8_t i2c_addr){
	i2c_read(i2c_periph,i2c_addr,0x00,&irOut,1);
	if (irOut & 0x01){
		irState = 1;
	}else{
		irState = 0;
	}
	delay(8000);
}
	
void S7_IR_ADDR_Init( void ){
	uint8_t i;
	for(i=0;i<4;i++){
		if(i2c_addr_poll(I2C0,Sensor_IR_ADDR + i*2)){
			s7_ir_addr.periph = I2C0;
			s7_ir_addr.addr = Sensor_IR_ADDR + i*2;
			s7_ir_addr.flag = 1;
			break;
		}else if(i2c_addr_poll(I2C1,Sensor_IR_ADDR + i*2)){
			s7_ir_addr.periph = I2C1;
			s7_ir_addr.addr = Sensor_IR_ADDR + i*2;
			s7_ir_addr.flag = 1;
			break;
		}
	}
	for(i=0;i<4;i++){
		if(s7_ir_addr.flag != 1){
			if(i2c_addr_poll(I2C0,Sensor_IR_ADDR + i*2)){
			s7_ir_addr.periph = I2C0;
			s7_ir_addr.addr = Sensor_IR_ADDR + i*2;
			s7_ir_addr.flag = 1;
			break;
		}else if(i2c_addr_poll(I2C1,Sensor_IR_ADDR + i*2)){
			s7_ir_addr.periph = I2C1;
			s7_ir_addr.addr = Sensor_IR_ADDR + i*2;
			s7_ir_addr.flag = 1;
			break;
			}
		}
	}
	
	if(s7_ir_addr.flag){
		S7_IR_Init(s7_ir_addr.periph,s7_ir_addr.addr);
	}

}
