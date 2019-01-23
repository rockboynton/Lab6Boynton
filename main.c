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
#define DEBUG 5

// User input buffer
#define BUFFER_SIZE 30

// Initialize variables to be used 
char buffer[BUFFER_SIZE+1];
Tone SONG[] = { // Imperial March
	// {NOTE, DURATION}
	{A3, Q}, 
	{C0, 1+Q}, // C0 is inaudible, acts as a delay
    {A3,Q},
    {C0, 1+Q},
    {A3,Q},
    {C0, 1+Q},
    {F3,E+S},
    {C0, 1+E+S},
    {C4,S},
    {C0, 1+S},
    
    {A3,Q},
    {C0, 1+Q},
    {F3,E+S},
    {C0, 1+E+S},
    {C4,S},
    {C0, 1+S},
    {A3,H},
    {C0, 1+H},
    
    {E4,Q}, 
    {C0, 1+Q}, 
    {E4,Q},
    {C0, 1+Q},
    {E4,Q},
    {C0, 1+Q},
    {F4,E+S},
    {C0, 1+E+S},
    {C4,S},
    {C0, 1+S},
    
    {Ab3,Q},
    {C0, 1+Q},
    {F3,E+S},
    {C0, 1+E+S},
    {C4,S},
    {C0, 1+S},
    {A3,H},
    {C0, 1+H},
    
    {A4,Q},
    {C0, 1+Q},
    {A3,E+S},
    {C0, 1+E+S},
    {A3,S},
    {C0, 1+S},
    {A4,Q},
    {C0, 1+Q},
    {Ab4,E+S},
    {C0, 1+E+S},
    {G4,S},
    {C0, 1+S},
    
    {Gb4,S},
    {C0, 1+S},
    {E4,S},
    {C0, 1+S},
    {F4,E},
    {C0, 1+E},
    {C0, 1+E},//PAUSE
    {Bb3,E},
    {C0, 1+E},
    {Eb4,Q},
    {C0, 1+Q},
    {D4,E+S},
    {C0, 1+E+S},
    {Db4,S},
    {C0, 1+S},
    
    {C4,S},
    {C0, 1+S},
    {B3,S},
    {C0, 1+S},
    {C4,E},
    {C0, 1+E},
    {C0, 1+E},//PAUSE QUASI FINE RIGA
    {F3,E},
    {C0, 1+E},
    {Ab3,Q},
    {C0, 1+Q},
    {F3,E+S},
    {C0, 1+E+S},
    {A3,S},
    {C0, 1+S},
    
    {C4,Q},
    {C0, 1+Q},
    {A3,E+S},
    {C0, 1+E+S},
    {C4,S},
    {C0, 1+S},
    {E4,H},
    {C0, 1+H},
    
    {A4,Q},
    {C0, 1+Q},
    {A3,E+S},
    {C0, 1+E+S},
    {A3,S},
    {C0, 1+S},
    {A4,Q},
    {C0, 1+Q},
    {Ab4,E+S},
    {C0, 1+E+S},
    {G4,S},
    {C0, 1+S},
    
    {Gb4,S},
    {C0, 1+S},
    {E4,S},
    {C0, 1+S},
    {F4,E},
    {C0, 1+E},
    {C0, 1+E},//PAUSE
    {Bb3,E},
    {C0, 1+E},
    {Eb4,Q},
    {C0, 1+Q},
    {D4,E+S},
    {C0, 1+E+S},
    {Db4,S},
    {C0, 1+S},
    
    {C4,S},
    {C0, 1+S},
    {B3,S},
    {C0, 1+S},
    {C4,E},
    {C0, 1+E},
    {C0, 1+E},//PAUSE QUASI FINE RIGA
    {F3,E},
    {C0, 1+E},
    {Ab3,Q},
    {C0, 1+Q},
    {F3,E+S},
    {C0, 1+E+S},
    {C4,S},
    {C0, 1+S},
    
    {A3,Q},
    {C0, 1+Q},
    {F3,E+S},
    {C0, 1+E+S},
    {C4,S},
    {C0, 1+S},
    {A3,H},
    {C0, 1+H},
    
    {C0, 2*H},
};

// File scope helper methods
static void play_song(Tone song[]);


// main
int main() {
	
	// Initialize hardware
	init_usart2(19200,F_CPU);
	led_init();
	lcd_init();
	key_init();
	temp_init();
	speaker_init();

	// --------------------- THERMOMETER TEST CODE -------------------
	if (DEBUG == 1) {
		uint16_t voltage;
		while (1) {
			voltage = temp_voltage();
			lcd_print_num(voltage);
			delay_1ms(500);
			lcd_clear();
			lcd_print_num(temp_current_celsius(voltage));
			delay_1ms(500);
			lcd_clear();
			lcd_print_num(temp_current_fahrenheit(voltage));
			delay_1ms(500);
			lcd_clear();
			delay_1ms(500);
		}
	}
	//-----------------------------------------------------------

	// --------------------- KEYPAD TEST CODE -------------------
	if (DEBUG == 2) {
			uint8_t key;
			while (1) {
				lcd_clear();
				key = key_getChar();
				lcd_write_data(key);
				delay_1ms(500);
			}
	}
	//-----------------------------------------------------------

	// --------------------- LED TEST CODE -------------------
	if (DEBUG == 3) {
			while (1) {
				led_allOff();
				for (int i = 0; i < 10; i++) {
					led_on(i);
					delay_1ms(500);
				}
			}
	}
	//-----------------------------------------------------------

	// --------------------- USART TEST CODE -------------------
	if (DEBUG == 4) {
		char entry[20];
			while (1) {
				printf("Enter name: ");
				gets(entry);
				delay_1ms(500);
				printf("Your name: %s\n", entry);
				delay_1ms(1000);
			}
	}
	//-----------------------------------------------------------

	// --------------------- SPEAKER TEST CODE -------------------
	if (DEBUG == 5) {
		char entry[20];
			while (1) {
				play_song(&SONG);
			}
	}
	//-----------------------------------------------------------

	// Main program 
	// Never return
	print_help_screen();
	while (1) {
		
	}
	// Never returns
	return 0;
}

static void print_help_screen() { // TODO
	printf(	"Read memory (Command 'r'): Specify address to read value from memory.\n"
			"Write memory (Command 'w'): Specify address and value to write at address.\n"
			"Dump memory (Command 'd'):  Specify starting address and number of words\n" 
			"							 to dump.\n"
			"Help (Command 'h'):         Prints this interface\n\n");
}

static void play_song(Tone * song[]) {

}
