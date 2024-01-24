/*--------------------------------------------------------------------
Name:   Brandon Ramos
Date:   9/28/2020
Course: CSCE 236 Embedded Systems (Fall 2020) 
HW/Lab: Lab 3

Purp: Start of Robot

Doc:  Datasheets and course website, powerpoints and TA help

Academic Integrity Statement: I certify that, while others may have 
assisted me in brain storming, debugging and validating this program, 
the program itself is my own work. I understand that submitting code 
which is the work of other individuals is a violation of the honor   
code.  I also understand that if I knowingly give my original work to 
another individual is also a violation of the honor code.
--------------------------------------------------------------------*/

#include <Arduino.h>
#include <avr/io.h>
#include "ultrasonicAndServo.h"


void setup() {                
  Serial.begin(9600);
  Serial.println("Starting up...");

  DDRD_Reg |= (1<<SERVO); //sets pin 3 to output
  DDRB_Reg |= (1<<trigPin); //set pin 9 to output
  DDRB_Reg &= ~(1<<echoPin); //set pin 8 to input
  DDRB_Reg |=  (1<<RightLED); //set pin 12 to output
  DDRD_Reg |= (1<<LeftLED);   //set pin 7 to output

  //Init counter2 for Servo
  TCCR2A = 0;
  TCCR2A |= (1<< COM2A1) | (1<<COM2B1) | (1<<WGM20); //the inversion for phase correct
  TCCR2B |= (1<<CS22) | (1<<CS21) | (1<<CS20); //Clock T1 with prescalar of 1024
  OCR2A = 156; //top
  OCR2B = 10; //input capture
  //Make sure interrupts are disabled 
  TIMSK2 = 0;
  TIFR2 = 0;
  
  //Init counter 1 for Ultrasonic Sensor
  TCCR1A = 0; //0xffff top, rolls over
  TCCR1B = (1<<CS11);//8 prescaler
  TCCR1C = 0;
  //set counter to zero, high byte first
  TCNT1H = 0;
  TCNT1L = 0;
  //make sure inerrupts are disabled
  TIMSK1 = 0;
  TIFR1 = 0;

  Serial.println("Finished setup!");
}

void checkoff3(){
  // int  race = sonicSensor();
  servoLeft();
  delay(2000);
  if(sonicSensor()<=12){
    //turn on left led for 2 seconds
    PORTD_Reg |= (1<<LeftLED);
    delay(2000);
    PORTD_Reg &= ~(1<<LeftLED);
  }
  servoRight();
  delay(2000);
  if(sonicSensor()<=12){
    //turn on right led for 2 seconds
    PORTB_Reg |= (1<<RightLED);
    delay(2000);
    PORTB_Reg &= ~(1<<RightLED);
  }
  servoStraight();
  delay(2000);
  if(sonicSensor()<=12){
    //turn on both leds for 2 seconds
    PORTB_Reg |= (1<<RightLED);
    PORTD_Reg |= (1<<LeftLED);
    delay(2000);
    PORTB_Reg &= ~(1<<RightLED);
    PORTD_Reg &= ~(1<<LeftLED);
  }
}

// //data for graph
// void checkoff3_5(){
//   servoStraight();
//   delay(500);
//   int temp = sonicSensor();
//   delay(3000);
//    temp = sonicSensor();
//   delay(3000);
//    temp = sonicSensor();
//   delay(3000);
// }

void loop() {
// servoLeft();
// delay(1000);
// servoRight();
// delay(1000);
// servoStraight();
// delay(1000);
// sonicSensor();
checkoff3();
}

/**
 * Ultrasonic Sensor Boards
 * 1.) 340meters/second
 * 2.)t=(2in)(2.54/1in)(1m/100cm)/(340m/s)=149.4us
 * 3.)Range(2cm->4m) and apparently has a 3mm accuracy
 * 4.)Minimum measurement cycle is 60ms where the working frequency is 25ms
 * 
 * 5.)If it takes longern than 8/340=23ms to come back then dont use the info
 * 6.)
 * 7.)
 * 8.)No, it will need a delay since the code is ran long after it still moves
 * 9.)send many and stop
 * 10.)
 **/
