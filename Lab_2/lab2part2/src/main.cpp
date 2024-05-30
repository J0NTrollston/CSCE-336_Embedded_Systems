/*--------------------------------------------------------------------
Name:   Brandon
Date:   9/10/2020
Course: CSCE 236 Embedded Systems (Fall 2020) 
File:   Lab2part2.cpp
HW/Lab: Lab 2

Purp:  Lab 2 Code

Doc:  Help from schematic, datasheet and help from TA: Patrick, Rainer and Dan

Academic Integrity Statement: I certify that, while others may have 
assisted me in brain storming, debugging and validating this program, 
the program itself is my own work. I understand that submitting code 
which is the work of other individuals is a violation of the honor   
code.  I also understand that if I knowingly give my original work to 
another individual is also a violation of the honor code.
--------------------------------------------------------------------*/

#include <Arduino.h>

// Definitions for Port B & D registors
#define PINB_Reg (*((volatile uint8_t *) 0x23))
#define DDRB_Reg (*((volatile uint8_t *) 0x24))
#define PORTB_Reg (*((volatile uint8_t *) 0x25))

#define PIND_Reg (*((volatile uint8_t *) 0x29))
#define DDRD_Reg (*((volatile uint8_t *) 0x2a))
#define PORTD_Reg (*((volatile uint8_t *) 0x2b))

// Definitions for LED assignments:
#define BOARD_LED 5   //pin 13 is PortB bit 5
#define RED_LED 1     //pin 9 is PortB bit 1  
#define GREEN_LED 2   //pin 10 is PortB bit 2
#define BLUE_LED 3    //pin 11 is PortB bit 3

#define BUTTON 5      //pin 5 is PortD bit 5

//Changing variables
unsigned long start, end = 0;

/**
 * Init all of the LEDs and test them
 **/ 
void LEDInit(){
 //Set pinmode for LEDs to output 
  DDRB_Reg |= (1 << BOARD_LED);
  DDRB_Reg |= (1 << RED_LED);
  DDRB_Reg |= (1 << GREEN_LED);
  DDRB_Reg |= (1 << BLUE_LED);

  //Turn all off
  PORTB_Reg &= ~(1 << BOARD_LED); //clear output
  PORTB_Reg &= ~(1 << RED_LED);   //clear output
  PORTB_Reg &= ~(1 << GREEN_LED); //clear output
  PORTB_Reg &= ~(1 << BLUE_LED);  //clear output

  //Test LEDs
  Serial.println("Testing LEDs...");
  PORTB_Reg |= (1 << BOARD_LED);  //set output
  PORTB_Reg |= (1 << RED_LED);    //set output
  delay(400);
  PORTB_Reg &= ~(1 << RED_LED);   //clear output
  PORTB_Reg |= (1 << GREEN_LED);  //set output
  delay(400);
  PORTB_Reg &= ~(1 << GREEN_LED); //clear output
  PORTB_Reg |= (1 << BLUE_LED);   //set output
  delay(400);
  PORTB_Reg &= ~(1 << BLUE_LED);   //clear output
  PORTB_Reg &= ~(1 << BOARD_LED);   //clear output
  Serial.println("Finished LED testing!");
  }

void setup() {                
  Serial.begin(9600);
  Serial.println("Starting up...");
  LEDInit();
  //Set pinmode for Button as input
  DDRD_Reg &= ~(1 << BUTTON);
  //Enable pullup 
  PORTD_Reg |= (1 << BUTTON);  //set output to enable pullup resistor

  //Init counter1
  TCCR1A = 0; //Normal mode 0xffff top, rolls over
  //clk I/O/64
  TCCR1B |= (1 << CS11) | (1 << CS10); //Clock T1 falling edge
  TCCR1C = 0;
  //Set counter to zero, high byte first
  TCNT1H = 0;
  TCNT1L = 0;  
  start = millis();
  //Make sure interrupts are disabled 
  TIMSK1 = 0;
  TIFR1 = 0;
  
  Serial.println("Finished setup!");
}

void loop() {
  //Print when clock reaches rollover and wait
  if(TCNT1 == 0xffff){
    end = millis();
    Serial.println(end - start);
    while(1){}
  }
}

//seconds = 1/16MHz * prescalar * 65535
//1 divider we get .00409 seconds
//8 divider we get .0327 seconds
//64 divider we get .262 seconds
//256 divider we get 1.04 seconds
//1024 divider we get 4.19 seconds