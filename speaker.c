/*
 * speaker.c
 *
 *  Created on: Jan 19, 2019
 *      Author: Rock Boynton
 * 
 * Implements functions specified in temp_sensor.h to use the MSOE dev board temperature sensor
 */

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include "speaker.h"
#include "delay.h"
#include "gpio.h"

static volatile GPIO* GPIOB = 0x40020400;

void temp_init() {
    // Enable GPIOB in RCC_AHB1ENR
	*(RCC_AHB1ENR) |= (1 << GPIOBEN);
    // Enable TIM3 in RCC_APB1ENR
	*(RCC_APB1ENR) |= (1 << TIM3_EN);
    // Configure GPIOB pin 4 for alternate function
    GPIOB->MODER |= ALETERNATE_FUNCTION << PB4;
    // Configure clock source – default (reset) is to use processor clock
    
	// Set half-period count in TIM3_ARR and TIM3_CCR1
	
    // Set output mode to “toggle on match” in TIM3_CCMR1
	
    // Enable output in TIM3_CCER
	
    // Enable counter in TIM3_CR1


}