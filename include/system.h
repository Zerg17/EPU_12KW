#pragma once
#ifndef SYSTEM
#define SYSTEM

#include <stm32h7xx.h>
#include "xprintf.h"
#include "delay.h"

#define BOAD 115200

#define LED_GREEN_ON GPIOB->BSRRL |= GPIO_BSRR_BS_0
#define LED_GREEN_OFF GPIOB->BSRRH |= GPIO_BSRR_BS_0
#define LED_GREEN_TOG GPIOB->ODR ^= GPIO_ODR_ODR_0

#define LED_YELLOW_ON GPIOE->BSRRL |= GPIO_BSRR_BS_1
#define LED_YELLOW_OFF GPIOE->BSRRH |= GPIO_BSRR_BS_1
#define LED_YELLOW_TOG GPIOE->ODR ^= GPIO_ODR_ODR_1

#define LED_RED_ON GPIOB->BSRRL |= GPIO_BSRR_BS_14
#define LED_RED_OFF GPIOB->BSRRH |= GPIO_BSRR_BS_14
#define LED_RED_TOG GPIOB->ODR ^= GPIO_ODR_ODR_14

void sysInit();

#endif