/*
 * main.c
 *
 * Plays a song using piezo speaker on MSOE dev board.
 * 
 * The following menu options are implemented:
 * 				
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "uart_driver.h"
#include "led.h"
#include "lcd.h"
#include "keypad.h"
#include "delay.h"
#include "temp_sensor.h"
#include "speaker.h"

#define F_CPU 16000000UL

// 0 = main program
// 1 = Thermometer tests
// 2 = Keypad tests
// 3 = LED tests
// 4 = USART tests
// 5 = Speaker tests
#define DEBUG 0

// User input buffer
#define BUFFER_SIZE 30

// Initialize variables to be used 
char buffer[BUFFER_SIZE+1];
Tone SONG[] = { // Imperial March
	// {NOTE, DURATION}
	{A3, Q}, 
	{C0, 1}, // C0 is inaudible, acts as a small delay to seperate notes
    {A3,Q},
    {C0, 1},
    {A3,Q},
    {C0, 1},
    {F3,E+S},
    {C0, 1},
    {C4,S},
    {C0, 1},
    
    {A3,Q},
    {C0, 1},
    {F3,E+S},
    {C0, 1},
    {C4,S},
    {C0, 1},
    {A3,H},
    {C0, 1},
    
    {E4,Q}, 
    {C0, 1}, 
    {E4,Q},
    {C0, 1},
    {E4,Q},
    {C0, 1},
    {F4,E+S},
    {C0, 1},
    {C4,S},
    {C0, 1},
    
    {Ab3,Q},
    {C0, 1},
    {F3,E+S},
    {C0, 1},
    {C4,S},
    {C0, 1},
    {A3,H},
    {C0, 1},
    
    {A4,Q},
    {C0, 1},
    {A3,E+S},
    {C0, 1},
    {A3,S},
    {C0, 1},
    {A4,Q},
    {C0, 1},
    {Ab4,E+S},
    {C0, 1},
    {G4,S},
    {C0, 1},
    
    {Gb4,S},
    {C0, 1},
    {E4,S},
    {C0, 1},
    {F4,E},
    {C0, 1},
    {C0, 1},//PAUSE
    {Bb3,E},
    {C0, 1},
    {Eb4,Q},
    {C0, 1},
    {D4,E+S},
    {C0, 1},
    {Db4,S},
    {C0, 1},
    
    {C4,S},
    {C0, 1},
    {B3,S},
    {C0, 1},
    {C4,E},
    {C0, 1},
    {C0, 1},//PAUSE QUASI FINE RIGA
    {F3,E},
    {C0, 1},
    {Ab3,Q},
    {C0, 1},
    {F3,E+S},
    {C0, 1},
    {A3,S},
    {C0, 1},
    
    {C4,Q},
    {C0, 1},
    {A3,E+S},
    {C0, 1},
    {C4,S},
    {C0, 1},
    {E4,H},
    {C0, 1},
    
    {A4,Q},
    {C0, 1},
    {A3,E+S},
    {C0, 1},
    {A3,S},
    {C0, 1},
    {A4,Q},
    {C0, 1},
    {Ab4,E+S},
    {C0, 1},
    {G4,S},
    {C0, 1},
    
    {Gb4,S},
    {C0, 1},
    {E4,S},
    {C0, 1},
    {F4,E},
    {C0, 1},
    {C0, 1},//PAUSE
    {Bb3,E},
    {C0, 1},
    {Eb4,Q},
    {C0, 1},
    {D4,E+S},
    {C0, 1},
    {Db4,S},
    {C0, 1},
    
    {C4,S},
    {C0, 1},
    {B3,S},
    {C0, 1},
    {C4,E},
    {C0, 1},
    {C0, 1},//PAUSE QUASI FINE RIGA
    {F3,E},
    {C0, 1},
    {Ab3,Q},
    {C0, 1},
    {F3,E+S},
    {C0, 1},
    {C4,S},
    {C0, 1},
    
    {A3,Q},
    {C0, 1},
    {F3,E+S},
    {C0, 1},
    {C4,S},
    {C0, 1},
    {A3,H},
    {C0, 1},
    
    {C0, 2*H},
};

// File scope helper methods
static void print_help_screen();
static void play_song(Tone song[], int length);


// main
int main() {
	
	// Initialize hardware
	init_usart2(19200,F_CPU);
	led_init();
	lcd_init();
	key_init();
	temp_init();
	speaker_init();

	// --------------------- SPEAKER TEST CODE -------------------
	if (DEBUG == 5) {
		char entry[20];
			while (1) {
				play_song(SONG, (sizeof(SONG) / sizeof(SONG[0])));
			}
	}
	//-----------------------------------------------------------

	// Main program 
	// Never return
	print_help_screen();
	while (1) {
		printf("Press any key to play \"Imperial March\": ");
		scanf("%s", buffer);
		while ((getchar()) != '\n'); // clear input buffer
		switch (buffer[0]) { // reads first character from input text	
			default:
				play_song(SONG, (sizeof(SONG) / sizeof(SONG[0])));
				break;
		}
	}
	// Never returns
	return 0;
}

// No help screen neccasary
static void print_help_screen() { 
	printf("");
}

static void play_song(Tone song[], int length) {
	for (int i = 0; i < length; i++) {
		play_tone(&(song[i]));
	}
}
