/*--------------------------------------------------------------------
Name:   Brandon Ramos
Date:   9/28/2020
Course: CSCE 236 Embedded Systems (Fall 2020) 
HW/Lab: Project KYLE

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
#include "motors.h"

/**
 * Turns servo 90 degrees to the left.
**/
void servoLeft(){
  Serial.println("Servo Looks Left");  
  OCR2B = 38; //value so servo turns left.
}
/**
 * Turns servo so that it is looking straight ahead.
**/
void servoStraight(){
  Serial.println("Servo Looks Ahead");
  OCR2B = 22; //value so servo straightens out
}
/**
 * Turns servo 90 degrees to the right
**/
void servoRight(){
  Serial.println("Servo Looks Right");
  OCR2B =7; //value so servo turns right 
}

/**
 * Function returns distance of an object in inches with the ultrasonic sensor.
**/
int sonicSensor(){
  int distance; //value that is returned
  unsigned long echo; //will hold the #cycles it took for pulse 
  double distanceInInches; //conversion

  // Clears the trigPin
  PORTB_Reg &= ~(1<<trigPin);
  myDelay12Microseconds(3);
  // Sets the trigPin on HIGH state for 10 micro seconds
  PORTB_Reg |= (1<<trigPin);
  myDelay12Microseconds(1);
  PORTB_Reg &= ~(1<<trigPin);
  TCNT1 = 0;//resets timer to 0
  myDelay(2);
  echo = ICR1; //ICR1 will be 

  //echo*(8/2)*340m/s*39.37in/m 
  //8 is prescaler, 2 is half the distance
  distanceInInches = (echo*4*340*39.37);
  distanceInInches = distanceInInches/16000000;
  distanceInInches -= 3; //sensor is 3 inches off so we correct that
  distance = distanceInInches;
  Serial.print("Object is: ");
  if(distance < 0){ distance=0;}
  Serial.print(distance);
  Serial.println(" Inches away!");

  return distance; //return value in inches
}

/**
 * will be from 160 to 255 and will be how long we send a pulse for PWM
 * numOfQuarterseconds will be for how long we run the motor
 * compareRegB wil be the value for power in motor
 **/
void driveForward(int numOfQuarterseconds, int compareRegA, int compareRegB){
  //OCR0A-OCR0B=19 to go straight
  OCR0A = compareRegA;
  OCR0B = compareRegB;
  PORTC_Reg |= (1<<In1);
  PORTB_Reg |= (1<<In4);
  PORTD_Reg &= ~(1<<In3);
  PORTD_Reg &= ~(1<<In2);
  myDelay(numOfQuarterseconds);
  //turn off all motors and stop giving power
  OCR0A = 0;
  OCR0B = 0;
  PORTC_Reg &= ~(1<<In1);
  PORTB_Reg &= ~(1<<In4);
  PORTD_Reg &= ~(1<<In3);
  PORTD_Reg &= ~(1<<In2);
  myDelay(numOfQuarterseconds);
}
/**
 * numOfQuarterseconds will be for how long the motors are on for
 * compareRegA will be pwm pulse width where 160 is min, 255 is max
**/
void driveBackward(int numOfQuarterseconds, int compareRegA, int compareRegB){
  OCR0A = compareRegA;
  OCR0B = compareRegB;
  PORTD_Reg &= ~(1<<In1);
  PORTB_Reg &= ~(1<<In4);
  PORTD_Reg |= (1<<In3);
  PORTD_Reg |= (1<<In2);
  myDelay(numOfQuarterseconds);
  //turn off all motors and stop giving power
  OCR0A = 0;
  OCR0B = 0;
  PORTD_Reg &= ~(1<<In1);
  PORTB_Reg &= ~(1<<In4);
  PORTD_Reg &= ~(1<<In3);
  PORTD_Reg &= ~(1<<In2);
  myDelay(numOfQuarterseconds);
}
/**
 * numOfQuarterseconds will be for how long the motors are on for
 * compareRegA will be pwm pulse width where 160 is min, 255 is max
**/
void driveLeft(int numOfQuarterseconds, int compareRegA, int compareRegB){
  OCR0A = compareRegA;
  OCR0B = compareRegB;
  PORTD_Reg &= ~(1<<In1);
  PORTB_Reg |= (1<<In4);
  PORTD_Reg &= ~(1<<In3);
  PORTD_Reg |= (1<<In2);
  myDelay(numOfQuarterseconds);
  //turn off all motors and stop giving power
  OCR0A = 0;
  OCR0B = 0;
  PORTD_Reg &= ~(1<<In1);
  PORTB_Reg &= ~(1<<In4);
  PORTD_Reg &= ~(1<<In3);
  PORTD_Reg &= ~(1<<In2);
  myDelay(numOfQuarterseconds);
}
/**
 * numOfQuarterseconds will be for how long the motors are on for
 * compareRegA will be pwm pulse width where 160 is min, 255 is max
**/
void driveRight(int numOfQuarterseconds, int compareRegA, int compareRegB){
  OCR0A = compareRegA;
  OCR0B = compareRegB;
  PORTD_Reg |= (1<<In1);
  PORTB_Reg &= ~(1<<In4);
  PORTD_Reg |= (1<<In3);
  PORTD_Reg &= ~(1<<In2);
  myDelay(numOfQuarterseconds);
  //turn off all motors and stop giving power
  OCR0A = 0;
  OCR0B = 0;
  PORTD_Reg &= ~(1<<In1);
  PORTB_Reg &= ~(1<<In4);
  PORTD_Reg &= ~(1<<In3);
  PORTD_Reg &= ~(1<<In2);
  myDelay(numOfQuarterseconds);
}


/**
 * delay function where 
 * make it so that you go through a for loop with a no op
 * check out one of the labs, you may have a head start
 * 12 gives 4 quarterseconds to be 1064 seconds
**/
void myDelay(int quarterSeconds){
  // unsigned long i = millis();
  for(int loop = 0; loop < quarterSeconds; loop++)  {
    for(uint16_t l = 0; l < 255; l++){
      for(uint16_t m = 0; m < 255; m++){
        for(uint16_t n = 0; n < 7; n++){
          asm volatile("nop");
        }
      }
    }
  }
  // unsigned long f = millis();
  // Serial.println(f-i);
}

/**
 * numOfMicroSeconds gives 12 microseconds per pass
**/
void myDelay12Microseconds(int numOfMicroSeconds){
  // unsigned long i = micros();
  for(int loop = 0; loop < numOfMicroSeconds; loop++)  {
    for(uint16_t l = 0; l < 30; l++){
      asm volatile("nop");
    }
  }
  // unsigned long f = micros();
  // Serial.println(f-i);
}

