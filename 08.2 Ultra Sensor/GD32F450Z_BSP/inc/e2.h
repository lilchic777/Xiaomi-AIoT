#ifndef E2_H
#define E2_H
#include "i2c.h"
#define E2_FAN_ADDR 0xC8

extern i2c_addr_def e2_fan_addr;

void E2_PCA9685PW_Init( uint32_t i2c_periph, uint8_t i2c_addr );
void E2_PCA9685PW_Off( uint32_t i2c_periph, uint8_t i2c_addr );
void E2_PCA9685PW_PreScale( uint32_t i2c_periph, uint8_t i2c_addr, uint8_t set);
void E2_SetPWM(uint32_t i2c_periph,uint8_t i2c_addr,uint8_t num,uint16_t on,uint16_t off);
void E2_PCA9685PW_Speed(uint32_t i2c_periph,uint8_t i2c_addr,uint8_t speed);
void E2_FAN_ADDR_Init( void );

#endif
