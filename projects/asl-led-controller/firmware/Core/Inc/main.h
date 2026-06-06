#ifndef __MAIN_H
#define __MAIN_H

#include "stm32g4xx_hal.h"

/* Left LED  — PA8 (Arduino D7, orange external LED) */
#define LED_L_PIN   GPIO_PIN_8
#define LED_L_PORT  GPIOA

/* Right LED — PB5 (Arduino D4, external LED + 330Ω to GND) */
#define LED_R_PIN   GPIO_PIN_5
#define LED_R_PORT  GPIOB

void Error_Handler(void);

#endif /* __MAIN_H */
