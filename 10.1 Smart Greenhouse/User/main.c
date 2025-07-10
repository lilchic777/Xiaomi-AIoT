/*************************************************************************************************************
功能:    通过zigbee通信可以实时监测模拟智慧温室大棚的温湿度，光照，并在数码管上进行显示
版本:     2023-5-17 V1.0
修改记录: 无
作者:     ZZZ
*************************************************************************************************************/
#include "gd32f4xx.h"
#include "BoardSys.h"
#include "led.h"
#include "timer.h"
#include "SysTick.h"

uint32_t se = 0;

void SysTick_Init( void );
void UserInit( void );


void SysTick_Init( void ){
	systick_clksource_set(SYSTICK_CLKSOURCE_HCLK);
	SysTick_Config(200000*1500);

}

void UserInit( void ){
	i2c0_gpio_config();
	i2c0_config();
	
	i2c1_gpio_config();
	i2c1_config();
	
	S1_I2C_ADDR_Init();
	
	E1_I2C_ADDR_Init();
	E1_I2C_1_ADDR_Init();
	E2_FAN_ADDR_Init();
	E3_Curtain_ADDR_Init();
	S2_Light_ADDR_Init();
	S2_TempHumid_ADDR_Init();
	S2_Gryo_ADDR_Init();
	S5_NFC_ADDR_Init();
	S6_US_ADDR_Init();
	S7_IR_ADDR_Init();

}

int main( void ){

	UserInit();
	while(1){
		S1();
		delay_ms(1500);
		if (output == 1){
			E3_Curtain_ReadState(e3_cur_addr.periph,e3_cur_addr.addr);
			E3_Curtain_ReadNum(e3_cur_addr.periph,e3_cur_addr.addr);
			if((curState != 1)&&(curNum != 100)){
				E3_Curtain_Opt(e3_cur_addr.periph,e3_cur_addr.addr,100);
			}
			E3_Curtain_ReadState(e3_cur_addr.periph,e3_cur_addr.addr);
			E3_Curtain_ReadNum(e3_cur_addr.periph,e3_cur_addr.addr);
			if(curState != 1&&(curNum != 0)){
				E3_Curtain_Opt(e3_cur_addr.periph,e3_cur_addr.addr,0);
			}
		output = 0;
	}
	else if(output == 2){
		
		E2_PCA9685PW_Speed(e2_fan_addr.periph,e2_fan_addr.addr,80);
		output = 0;
	}
	else if(output == 3){
		S5_NFC_Rec(s5_nfc_addr.periph,s5_nfc_addr.addr);
		output = 0;
	}
	else if(output == 4){
		E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,4,0);
		output = 0;
	}
	else if(output == 5){
		for(int i=0;i<10;i++){
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,1,i);
			delay_ms(1000);
		}
		output = 0;
	}
	else if(output == 6){
		getLightval();
		if (lightval_ < 10000){
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,1,(int)((int)(lightval_/1000)%10));
			delay_ms(1500);
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,2,(int)((int)(lightval_/100)%10));
			delay_ms(1500);
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,3,(int)((int)(lightval_/10)%10));
			delay_ms(1500);
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,4,(int)((int)lightval_%10));
			delay_ms(1500);}
		else if (lightval_ >= 10000){
			lightval_ = 9999;
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,1,(int)((int)(lightval_/1000)%10));
			delay_ms(1500);
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,2,(int)((int)(lightval_/100)%10));
			delay_ms(1500);
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,3,(int)((int)(lightval_/10)%10));
			delay_ms(1500);
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,4,(int)((int)lightval_%10));
			delay_ms(1500);}
		output = 0;
	}
	else if(output == 7){
		for(int i=0;i<=19;i++){
			if(i<=9){
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,4,i);
			delay_ms(1000);
			}
			else if(i>10){
			E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,4,i%10);
			delay_ms(1000);
			}
			
			if(i==9){
				E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,4,0);
				E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,3,1);
				delay_ms(1000);
			}
			else if(i==19){
				E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,4,0);
				E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,3,2);
				delay_ms(1000);
				break;
			}
			
		}
		output = 0;
	}
	else if(output == 8){
		for(int i=0;i<4;i++){
			PCA9685_rgb_led_control(e1_rgb_led_addr.periph,e1_rgb_led_addr.addr,i);
			delay_ms(5000);
		}
		output = 0;
	}
	else if(output == 9){
		S6_US_Get(s6_uso_addr.periph,s6_uso_addr.addr);
		output = 0;
	}
	else if(output == 10){
		S7_IR_Init(s7_ir_addr.periph,s7_ir_addr.addr);
		S7_IR_Get(s7_ir_addr.periph,s7_ir_addr.addr);
	}
	else if(output == 11){
		S2_Gryo_Init(s2_gryo_addr.periph,s2_gryo_addr.addr);
		delay_ms(1000);
		S2_Gryo_Settings(s2_gryo_addr.periph,s2_gryo_addr.addr);
		getAccAng();
	}	
	else if(output == 12){
		S2_TempHumid_Init(s2_temp_addr.periph,s2_temp_addr.addr);
		delay_ms(1000);
		S2_TempHumid_Single_Shot(s2_temp_addr.periph,s2_temp_addr.addr);
		E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,1,(temp_/10)%10);
		delay_ms(1500);
		E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,2,(temp_)%10);
		delay_ms(1500);
		E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,3,(humid_/10)%10);
		delay_ms(1500);
		E1_HT16K33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,4,(humid_)%10);
		delay_ms(1500);
		output = 0;
		}
	}
}








