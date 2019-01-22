/*
 * speaker.h 
 * 
 * API for interfacing with the MSOE dev board piezo speaker
 */

//Include Guards 
#ifndef SPEAKER_H_
#define SPEAKER_H_

// TIM3_CH1 pin assignmenr for GPIOB
#define PB4 4

/**
 * Initialize the Speaker GPIO port and peripheral clocks.
 */
void temp_init();


#endif