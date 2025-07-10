#ifndef S1_H
#define S1_H

#include "i2c.h"
#include "gd32f4xx.h"


#define out
#define HT16K33_ADDRESS_S1      0xE8

/* HT16K33  CMD */
#define	S1_SYSTEM_ON				        0x21
#define	S1_SET_INT_NONE		          0xA0
#define	S1_DISPLAY_ON			          0x81
#define	S1_DISPLAY_OFF			        0x80
#define	S1_DIMMING_SET_DEFAULT		  0xEF

#define	KEYKS0				          0x40

#define SWN                     0xFF
#define SW1                     0x01
#define SW2                     0x02
#define SW3                     0x03
#define SW4                     0x04
#define SW5                     0x05
#define SW6                     0x06
#define SW7                     0x07
#define SW8                     0x08
#define SW9                     0x09
#define SWA                     '*'
#define SW0                     0x00
#define SWC                     '#'
#define GD32F330_ADDRESS_S6    	0x58
#define	GD32F330_READ_CMD				0xAA

typedef struct
{
   i2c_addr_def key_addr[4];
}s1_addr_def;

extern uint8_t color;
extern uint8_t output;
extern uint8_t keyvalue[6];

extern i2c_addr_def s1_key_addr;
extern uint8_t s1_key_scan(uint32_t i2c_periph,uint8_t i2c_addr);

void S1_HT16K33_Init(uint32_t i2c_periph, uint8_t i2c_addr);
void S1_HT16K33_KeyScan(uint32_t i2c_periph, uint8_t i2c_addr);
void S1( void );
void S1_I2C_ADDR_Init(void);
#endif



