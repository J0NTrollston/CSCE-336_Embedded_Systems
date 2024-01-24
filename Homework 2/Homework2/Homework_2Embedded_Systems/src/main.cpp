/*--------------------------------------------------------------------
Name: 	Brandon Ramos
Date: 	9/3/2020	
Course: CSCE 236 Embedded Systems (Fall 2020) 
File: 	Homework_2Embedded_Systems.cpp
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
#define ONBOARD_LED (1<<5)

int inByte = 0;    // incoming serial byte
uint8_t flag = 0; //flag for f or s

void setup() {
  // start serial port at 9600 bps:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  pinMode(LED_BUILTIN, OUTPUT);   // digital sensor is on digital pin 13
}

void loop() {
  // if we get a valid byte, read analog ins:
  if (Serial.available() > 0) {
    // get incoming byte:
    inByte = Serial.read();

    //set flag to 0 meaning fast otherwise slow = 1
    if(inByte == 102 || inByte == 70){
      flag = 0;
      inByte = Serial.read();
    }else if(inByte == 115 || inByte == 83){
      flag = 1;
      inByte = Serial.read();
    }
    
    //check to see if flag is fast or slow and blink accordingly
    if(flag == 0 ){
      for(uint8_t i = 0; i < inByte-48; i++){
        PORTB |= ONBOARD_LED; //set pin 13 to high
        delay(200);
        PORTB &= ~ONBOARD_LED;//set pin 13 to low
        delay(200);
     }
     }else if(flag == 1){
       for(uint8_t i = 0; i < inByte-48; i++){
         PORTB |= ONBOARD_LED; //set pin 13 to high
        delay(400);
        PORTB &= ~ONBOARD_LED;//set pin 13 to low
        delay(400);
       }
    }
    Serial.write(inByte);
  }
}


