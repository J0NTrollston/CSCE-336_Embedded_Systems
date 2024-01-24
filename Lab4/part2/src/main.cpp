/*--------------------------------------------------------------------
Name:   Brandon Ramos
Date:   <date you started working on the file>  
Course: CSCE 236 Embedded Systems (Fall 2020) 
File:   main.cpp
HW/Lab: Lab 4, Real Time Events

Purp: Template program for Lab 4 to illustrate Real Time Events 

Doc:  Datasheet, TA and Prof Help and Schematic

Academic Integrity Statement: I certify that, while others may have 
assisted me in brain storming, debugging and validating this program, 
the program itself is my own work. I understand that submitting code 
which is the work of other individuals is a violation of the honor   
code.  I also understand that if I knowingly give my original work to 
another individual is also a violation of the honor code.
--------------------------------------------------------------------*/

#include <Arduino.h>

#define BUTTON PIND3

//LED pin 9 or Port B1
#define LED_PIN PINB1

ISR(INT1_vect){
  //INT1 interrupt handling code goes here
  PORTB |= (1<<LED_PIN);
}

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:

  //Set bits 3:2 for low request interrupt
  //also would work for logic change
  EICRA &= ~(1<<2);
  EICRA &= ~(1<<3);
  //Enable external interrupt for INT1
  EIMSK = (1<<1); 

  //Setup the button
  DDRD &= ~(1 << BUTTON); /* Input Button on Pin 3 */
  // PORTD |= 1 << BUTTON; /* Enable pullup on Pin 3 */

  DDRB |= (1<<LED_PIN); //set output for pin 9
  PORTB &= ~(1<<LED_PIN); //turn off
}

void loop() {
  // put your main code here, to run repeatedly:
  delayMicroseconds(2);
  if(((PIND & B00001000)>>3) == 1 ){
    PORTB &= ~(1<<LED_PIN);    
  }
}




// ISR(INT1_vect){
//   //INT1 interrupt handling code goes here
//   PORTB |= (1<<LED_PIN);
// }

// void setup() {
//   Serial.begin(9600);
//   // put your setup code here, to run once:

//   //Set bits 3:2 for falling edge request interrupt
//   EICRA |= (1<<3);
//   EICRA &= ~(1<<2);
//   //Enable external interrupt for INT1
//   EIMSK = (1<<1); 

//   //Setup the button
//   DDRD &= ~(1 << BUTTON); /* Input Button on Pin 3 */
//   // PORTD |= 1 << BUTTON; /* Enable pullup on Pin 3 */

//   DDRB |= (1<<LED_PIN); //set output for pin 9
//   PORTB &= ~(1<<LED_PIN); //turn off
// }

// void loop() {
//   // put your main code here, to run repeatedly:
//   // Serial.println((PIND & B00001000)>>3);
//   delayMicroseconds(2);
//   cli();
//   if(((PIND & B00001000)>>3) == 1 ){
//     PORTB &= ~(1<<LED_PIN);    
//   }
//   sei();
// }







