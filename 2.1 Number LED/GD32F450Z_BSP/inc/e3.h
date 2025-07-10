#ifndef E3_H
#define E3_H
#include "i2c.h"
#define GD32F330_E3_ADDR 0x38

extern i2c_addr_def e3_cur_addr;
extern uint8_t curState;
extern uint8_t curNum;

void E3_Curtain_Opt(uint32_t i2c_periph,uint8_t i2c_addr, uint8_t opt);
void E3_Curtain_ReadState(uint32_t i2c_periph,uint8_t i2c_addr);
void E3_Curtain_ReadNum(uint32_t i2c_periph,uint8_t i2c_addr);
void E3_Curtain_ADDR_Init( void );


#endif
