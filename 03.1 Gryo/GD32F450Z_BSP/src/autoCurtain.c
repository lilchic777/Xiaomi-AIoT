#include "gd32f4xx.h"
#include "autoCurtain.h"
#include "i2c.h"
#include "e3.h"
#include "s2.h"

void E3_S2_AutoCurtain( void ){
	
	getLightval();
	if(lightval_){
		if(lightval_ <= 300){
			E3_Curtain_ReadState(e3_cur_addr.periph,e3_cur_addr.addr);
			E3_Curtain_ReadNum(e3_cur_addr.periph,e3_cur_addr.addr);
			if((curState != 1)&&(curNum != 100)){
				E3_Curtain_Opt(e3_cur_addr.periph,e3_cur_addr.addr,100);
			}
		}else if(lightval_ > 300 && lightval_ <= 400){
			E3_Curtain_ReadState(e3_cur_addr.periph,e3_cur_addr.addr);
			E3_Curtain_ReadNum(e3_cur_addr.periph,e3_cur_addr.addr);
			if((curState != 1)&&(curNum != 80)){
				E3_Curtain_Opt(e3_cur_addr.periph,e3_cur_addr.addr,80);
			}
		}else if(lightval_ > 400 && lightval_ <= 2500){
			E3_Curtain_ReadState(e3_cur_addr.periph,e3_cur_addr.addr);
			E3_Curtain_ReadNum(e3_cur_addr.periph,e3_cur_addr.addr);
			if((curState != 1)&&(curNum != 0)){
				E3_Curtain_Opt(e3_cur_addr.periph,e3_cur_addr.addr,0);
			}
		}else if(lightval_ > 2500){
			E3_Curtain_ReadState(e3_cur_addr.periph,e3_cur_addr.addr);
			E3_Curtain_ReadNum(e3_cur_addr.periph,e3_cur_addr.addr);
			if((curState != 1)&&(curNum != 100)){
				E3_Curtain_Opt(e3_cur_addr.periph,e3_cur_addr.addr,100);
			}
		}
	}
}

