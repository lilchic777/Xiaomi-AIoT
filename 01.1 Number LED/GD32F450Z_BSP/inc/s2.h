#ifndef S2_H
#define S2_H
#include "i2c.h"

#define Sensor_Light_ADDR 0x46
#define Sensor_TempHumid_ADDR 0x88
#define Sensor_Gyro_ADDR 0xD0

#define CL 0x13	//连续低精度
#define CH 0x10	//连续高精度
#define CH2 0x11	//连续高精度2
#define OL 0x23	//单次低精度
#define OH 0x20	//单次高精度
#define OH2 0x21	//单次高精度2


extern i2c_addr_def s2_light_addr;
extern i2c_addr_def s2_gryo_addr;
extern i2c_addr_def s2_temp_addr;

extern uint8_t lightval[2];
extern uint16_t lightval_full;
extern float lightval_;

extern uint8_t tempHumid[6];
extern uint64_t tempHumid_;
extern uint16_t temp;
extern uint16_t temp_;
extern uint16_t humid;
extern uint16_t humid_;

extern uint16_t accRes;
extern float angRes;
extern uint8_t data[14];
extern int16_t x_acc_;
extern int16_t y_acc_;
extern int16_t z_acc_;
extern int16_t x_ang_;
extern int16_t y_ang_;
extern int16_t z_ang_;
extern float ang_x;
extern float ang_y;
extern float ang_z;
extern float acc_x;
extern float acc_y;
extern float acc_z;

void S2_Light_Init(uint32_t i2c_periph, uint8_t i2c_addr);
void S2_Light_Continous_Hires(uint32_t i2c_periph, uint8_t i2c_addr);
void S2_Light_Continous_Hires2(uint32_t i2c_periph, uint8_t i2c_addr);
void S2_Light_Continous_Lores(uint32_t i2c_periph, uint8_t i2c_addr);
void S2_Light_OneTime_Hires(uint32_t i2c_periph, uint8_t i2c_addr);
void S2_Light_OneTime_Hires2(uint32_t i2c_periph, uint8_t i2c_addr);
void S2_Light_OneTime_Lores(uint32_t i2c_periph, uint8_t i2c_addr);
void getLightval( void );

void S2_TempHumid_Init(uint32_t i2c_periph, uint8_t i2c_addr);
void S2_TempHumid_Single_Shot(uint32_t i2c_periph, uint8_t i2c_addr);

void S2_Gryo_Init( uint32_t i2c_periph, uint8_t i2c_addr );
void S2_Gryo_Settings(uint32_t i2c_periph,uint8_t i2c_addr);

uint16_t s2_icm20608_accel_scaleget(uint32_t i2c_periph,uint8_t i2c_addr);
float s2_icm20608_gyro_scaleget(uint32_t i2c_periph,uint8_t i2c_addr);
void getAccAng( void );

void S2_Light_ADDR_Init( void );
void S2_TempHumid_ADDR_Init( void );
void S2_Gryo_ADDR_Init( void );


#endif
