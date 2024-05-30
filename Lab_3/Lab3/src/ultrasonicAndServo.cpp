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

void servoLeft(){
  // Serial.println("Servo Looks Left");  
  OCR2B = 18; //value so servo turns left
}
void servoStraight(){
  // Serial.println("Servo Looks Ahead");
  OCR2B = 10; //value so servo straightens out
}
void servoRight(){
  // Serial.println("Servo Looks Right");
  OCR2B = 3; //value so servo turns right
}

int sonicSensor(){
  int distance; //value that is returned
  unsigned long echo; //will hold the #cycles it took for pulse 
  double distanceInInches; //conversion

  // Clears the trigPin
  PORTB_Reg &= ~(1<<trigPin);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  PORTB_Reg |= (1<<trigPin);
  delayMicroseconds(10);
  PORTB_Reg &= ~(1<<trigPin);
  TCNT1 = 0;//resets timer to 0
  delay(500);
  echo = ICR1; //ICR1 will be 
  // Serial.println(ICR1);

  //echo*(8/2)*340m/s*39.37in/m 
  //8 is prescaler, 2 is half the distance
  distanceInInches = (echo*4*340*39.37);
  distanceInInches = distanceInInches/16000000;
  distanceInInches -= 3;
  distance = distanceInInches;
  // Serial.print("Object is: ");
  if(distance < 0){ distance=0;}
  Serial.print(distance);
  Serial.println(" Inches away!");

  return distance; //return value in inches
}