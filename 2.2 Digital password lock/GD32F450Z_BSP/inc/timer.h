#ifndef TIMER_H
#define TIMER_H

#include "gd32f4xx.h"

#define TIMER0_FREQ 1000 // 1000Hz
#define TIMER1_FREQ 2000 // 2000Hz

void Timer0_Init( void );
void Timer0_Config( void );

void Timer1_Init( void );
void Timer1_Config( void );

#endif
