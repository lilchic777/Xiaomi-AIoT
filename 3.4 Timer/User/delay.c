#include "gd32f4xx.h"
#include "delay.h"

void delay(uint32_t ms) {
    uint32_t i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 28000; j++) {
            __NOP();
					//	û�в�����ͬ�������ȴ�
        }
    }
}


