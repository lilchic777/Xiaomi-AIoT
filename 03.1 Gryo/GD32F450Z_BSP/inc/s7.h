#ifndef S7_H
#define S7_H
#include "i2c.h"
#define Sensor_IR_ADDR 0x30

extern i2c_addr_def s7_ir_addr;
extern uint8_t irOut;
extern uint8_t irState;

void S7_IR_Init( uint32_t i2c_periph, uint8_t i2c_addr );
void S7_IR_Get(uint32_t i2c_periph, uint8_t i2c_addr);
void S7_IR_ADDR_Init( void );

#endif
