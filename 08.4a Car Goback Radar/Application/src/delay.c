#include "delay.h"
#include "gd32f4xx.h"
/*!
	\功能       延时
	\参数[输入] ms: 延时时间（毫秒）
	\参数[输出] 无
	\返回       无
*/
void delay_ms(unsigned int ms)	// 实测有问题，延时过短
{
	for(unsigned int i=0;i<ms;i++)
		for(unsigned int j=0;j<40000;j++);
}

void delay(uint32_t ms) {
    uint32_t i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 28000; j++) {
            __NOP();
					//	没有操作等同于阻塞等待
        }
    }
}