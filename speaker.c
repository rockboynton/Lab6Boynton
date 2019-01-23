/*
 * speaker.c
 *
 *  Created on: Jan 19, 2019
 *      Author: Rock Boynton
 * 
 * Implements functions specified in speaker.h to use the MSOE dev board piezo speaker
 */

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include "speaker.h"
#include "delay.h"
#include "gpio.h"

static volatile GPIO* GPIOB = 0x40020400;
static volatile TIMER* TIM3 = TIM3_BASE;

void speaker_init() {
    // Enable GPIOB in RCC_AHB1ENR
	*(RCC_AHB1ENR) |= (1 << GPIOBEN);
    // Enable TIM3 in RCC_APB1ENR
	*(RCC_APB1ENR) |= (1 << TIM3_EN);
    // Configure GPIOB pin 4 for alternate function
    GPIOB->MODER |= ALTERNATE_FUNCTION << PB4;
    // Configure clock source – default (reset) is to use processor clock
    
	// Set half-period count in TIM3_ARR and TIM3_CCR1
	
    // Set output mode to “toggle on match” in TIM3_CCMR1
	
    // Enable output in TIM3_CCER
	
    // Enable counter in TIM3_CR1
}

void play_tone(Tone* tone) {
	// Set half-period count in TIM3_ARR and TIM3_CCR1
    uint16_t ticks = (uint16_t) (CLK_SPEED *  (1 / (*tone).note)) / 2;
    TIM3->ARR = ticks;
    TIM3->CCR1 = ticks;

    // Set output mode to “toggle on match” in TIM3_CCMR1
    TIM3->CCMR1 = (0b011 << 4); // OC1M=011 - toggle on match

    // Enable output in TIM3_CCER
    TIM3->CCER = 1; // CC1E = 1

    // Enable counter in TIM3_CR1 to begin playing tone
    TIM3->CR1 = 1; // CEN = 1
    
    delay_1ms((*tone).duration);

    // Disable counter in TIM3_CR1 to end playing tone
    TIM3->CR1 = 0; // CEN = 1
}