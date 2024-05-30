/*--------------------------------------------------------------------
Name: 	Brandon Ramos
Date: 	9/3/2020	
Course: CSCE 236 Embedded Systems (Fall 2020) 
File: 	Homework2_part3.cpp 
HW/Lab:	Homework 2, programming component

Purp: to flash the on board pin 13 LED 

Doc:	used datasheet for arduino and TA help


Academic Integrity Statement: I certify that, while others may have 
assisted me in brain storming, debugging and validating this program, 
the program itself is my own work. I understand that submitting code 
which is the work of other individuals is a violation of the honor   
code.  I also understand that if I knowingly give my original work to 
another individual is also a violation of the honor code.
--------------------------------------------------------------------*/
#include <Arduino.h>
#include <time.h>
#define ONBOARDLED (1<<5)

void setup() {
// put your setup code here, to run once://Declare this globally to prevent compiler optimizations
// This is especially important for 32 bit types
// uint8_t cntr8 = 0xff;
// for(cntr8 = 0; cntr8 < 255; cntr8++){
// }
  pinMode(LED_BUILTIN, OUTPUT);   // digital sensor is on digital pin 13
}



void loop() {


//turn on led for 6 seconds for 32 bit loop
  PORTB |= ONBOARDLED; //set high
  for(uint32_t i = 0; i < 12067295; i++){
    asm volatile("nop");
  }
  //blink once (off on off)
  PORTB &= ~ONBOARDLED;//set low
  delay(50);
  PORTB |= ONBOARDLED;
  delay(50);
  PORTB &= ~ONBOARDLED;//set low
  delay(50);

  //turn on led for 3 seconds for 16 bit loop
  PORTB |= ONBOARDLED;
   for(uint16_t j = 0; j < 65535; j++){
     for(uint16_t k = 0; k < 160; k++){
      asm volatile("nop");
     }
  }

  //blink twice (off on off on off)
  PORTB &= ~ONBOARDLED;
  delay(50);
  PORTB |= ONBOARDLED;
  delay(50);
  PORTB &= ~ONBOARDLED;
  delay(50);
  PORTB |= ONBOARDLED;
  delay(50);
  PORTB &= ~ONBOARDLED;
  delay(50);

  //turn on led for 2 seconds using 8 bit loop
   PORTB |= ONBOARDLED;
   for(uint16_t l = 0; l < 255; l++){
     for(uint16_t m = 0; m < 255; m++){
       for(uint16_t n = 0; n < 105; n++){
      asm volatile("nop");
       }
     }
  }
  PORTB &= ~ONBOARDLED;
  delay(1000);
}
