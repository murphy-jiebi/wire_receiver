#ifndef _BSP_LED_H
#define _BSP_LED_H

#include "main.h" 	


void LedInit(void);

void LedRefresh(uint8_t *state);

void BatVoltRefreash(uint8_t volt);

#endif

