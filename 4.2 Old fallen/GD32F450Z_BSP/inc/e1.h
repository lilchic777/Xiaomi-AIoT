#ifndef E1_H
#define E1_H
#include "gd32f4xx.h"
#include "i2c.h"

#define HT16K33_ADDRESS_E1 0xE0
#define PCA9685PW_ADDRESS_E1 0xC0

#define ALL_LED_ON_L 0xFA
#define ALL_LED_ON_H 0xFB
#define ALL_LED_OFF_L 0xFC
#define ALL_LED_OFF_H 0xFD

#define LED0_ON_L 0x06
#define LED0_ON_H 0x07
#define LED0_OFF_L 0x08
#define LED0_OFF_H 0x09
#define LED1_ON_L 0x0A
#define LED1_ON_H 0x0B
#define LED1_OFF_L 0x0C
#define LED1_OFF_H 0x0D
#define LED2_ON_L 0x0E
#define LED2_ON_H 0x0F
#define LED2_OFF_L 0x10
#define LED2_OFF_H 0x11


extern i2c_addr_def e1_nixie_tube_addr;
extern i2c_addr_def e1_rgb_led_addr;

void E1_HT16K33_Init(uint32_t i2c_periph, uint8_t i2c_addr);
void E1_HT16K33_display_off(uint32_t i2c_periph,uint8_t i2c_addr);
void E1_HT16K33_display_data(uint32_t i2c_periph,uint8_t i2c_addr,uint8_t bit,uint8_t data);
void E1_HT16K33_clean( void );
void E1_I2C_ADDR_Init( void );
void E1_I2C_1_ADDR_Init( void );
void E1_PCA9685PW_Init(uint32_t i2c_periph, uint8_t i2c_addr);
void E1_PCA9685PW_off(uint32_t i2c_periph, uint8_t i2c_addr);
void setPWM(uint32_t i2c_periph,uint8_t i2c_addr,uint8_t num, uint16_t on, uint16_t off);
void PCA9685_rgb_led_control(uint32_t i2c_periph,uint8_t i2c_addr,uint8_t num);




#endif
