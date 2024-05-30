/*--------------------------------------------------------------------
Name: 	Brandon Ramos
Date: 	9/3/2020	
Course: CSCE 236 Embedded Systems (Fall 2020) 
File: 	Homework2_part3.cpp 
HW/Lab:	Homework 2, programming component

Purp: to flash the on board pin 13 LED 

Doc:	used datasheet for arduino


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
Serial.begin(9600);
// put your setup code here, to run once://Declare this globally to prevent compiler optimizations
// This is especially important for 32 bit types
uint8_t cntr8 = 0xff;
for(cntr8 = 0; cntr8 < 255; cntr8++){

}
  pinMode(LED_BUILTIN, OUTPUT);   // digital sensor is on digital pin 13
}



void loop() {
  PORTB |= ONBOARDLED; //set high before the loop
  delay(1000);
  PORTB &= ~ONBOARDLED;//set low before entering loop

//measure time
time_t begin, end;
time(&begin);
  for(uint8_t i = 0; i < 255; i++){
    for(uint8_t j = 0; j< 255; j++){
      for(uint8_t k = 0; k< 255; k++){
        asm volatile("nop");
      }
    }
  }
//stop measureing time
time(&end);
double elapsed = difftime(end,begin);
Serial.print(elapsed);
Serial.print("\n");
  PORTB |= ONBOARDLED; //set high after the loop
}
