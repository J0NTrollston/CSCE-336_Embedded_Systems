/*--------------------------------------------------------------------
Name:   Brandon Ramos
Date:   9/28/2020
Course: CSCE 236 Embedded Systems (Fall 2020) 
HW/Lab: Project 1

Purp: Start of Robot

Doc:  Datasheets Schematic

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


void setup() {                
  Serial.begin(9600);
  Serial.println("Starting up...");

  DDRB_Reg |= (1<<trigPin); //set pin 9 to output
  DDRB_Reg &= ~(1<<echoPin); //set pin 8 to input
  DDRC_Reg |=  (1<<RightLED); //set pin 12 to output
  DDRC_Reg |= (1<<LeftLED);   //set pin 7 to output
  DDRD_Reg |= (1<<SERVO); //sets pin 3 to output
  DDRD_Reg |= (1<<EnA); //sets pin 5 to output
  DDRD_Reg |= (1<<EnB); //sets pin 6 to output
  DDRC_Reg |= (1<<In1); //sets pin 2 to output
  DDRC_Reg |= (1<<In2); //sets pin 4 to output
  DDRD_Reg |= (1<<In3); //sets pin 7 to output
  DDRC_Reg |= (1<<In4); //sets pin 12 to output

  //Init counter2 for Servo
  TCCR2A = 0;
  TCCR2A |= (1<< COM2A1) | (1<<COM2B1) | (1<<WGM20) | (1<<WGM01); //the inversion for phase correct
  TCCR2B |= (1<<CS22) | (1<<CS21) | (1<<CS20); //Clock T1 with prescalar of 1024
  OCR2A = 156; //top
  OCR2B = 23; //input capture
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

  //Init counter0 for Motors. Will be same as Counter/Timer2
  TCCR0A = (1<<COM0A1) | (1<<COM0B1) | (1<<WGM00) | (1<<WGM01);//on until OCR0B
  TCCR0B = (1<<CS00); //If you use prescaling, you will mess up delay() and millis()
  //Note: 125 is not half the speed, start around 200 and work up to 255
  // OCR0A = 200; //set speed for right wheel
  // OCR0B = 200; //set speed for left wheel 
  //disable interrupts
  // TIMSK0 = 0;
  // TIFR0 = 0;

  Serial.println("Finished setup!");
}

void checkArea(){
  servoLeft();
  myDelay(8);
  if(sonicSensor()<=12){
    //turn on left led for 2 seconds
    PORTC_Reg |= (1<<LeftLED);
    myDelay(8);
    PORTC_Reg &= ~(1<<LeftLED);
  }
  servoRight();
  myDelay(8);
  if(sonicSensor()<=12){
    //turn on right led for 2 seconds
    PORTC_Reg |= (1<<RightLED);
    myDelay(8);
    PORTC_Reg &= ~(1<<RightLED);
  }
  servoStraight();
  myDelay(8);
  if(sonicSensor()<=12){
    //turn on both leds for 2 seconds
    PORTC_Reg |= (1<<RightLED);
    PORTC_Reg |= (1<<LeftLED);
    myDelay(8);
    PORTC_Reg &= ~(1<<RightLED);
    PORTC_Reg &= ~(1<<LeftLED);
  }
}

/**
 * Keeps robot around a foot from the wall, but does not hit it and travels parallel
**/
void hugTheWall(){
  driveForward(8,155,155);
  servoStraight();
  myDelay(8);
  int range = sonicSensor();
  if(range >= 12 && range <= 18){
    //drive straight
    driveForward(8,155,155);
  }
  if(range < 12){
    //turn rightish
    driveRight(1,160,160);
    driveForward(8,155,155);
  }else if(range > 18){
    //turn leftish
    driveLeft(1,160,160);
    driveForward(8,155,155);
  }
}

void ObstacleAvoidance(){
  bool obstacle1 = false;
  bool obstacle2 = false;
  int range;
  while(obstacle1 == false){
    servoStraight();
    myDelay(4);
    range = sonicSensor();
    if(range > 12){
      servoLeft();
      myDelay(4);
      range = sonicSensor();
      if(range >= 12 && range <= 18){
        //drive straight
        driveForward(8,154,154);
      }
      if(range < 12){
        //turn rightish
        driveRight(1,160,160);
        driveForward(8,155,155);
      }else if(range > 18){
        //turn leftish
        driveLeft(1,160,160);
        driveForward(8,155,155);
      }
    }else{
      obstacle1 = true;
      driveRight(3,155,155);
      myDelay(1);
      driveForward(7,156,155);
      myDelay(1);
      driveLeft(1,173,173);
    }
  }

  while(obstacle2 == false){
    servoStraight();
    range =  sonicSensor();
    if(range > 12){
      driveForward(5,156,156);
    }else{
      obstacle2 = true;
      driveLeft(1,170,170);
      driveForward(9,155,155);
      driveRight(3,155,155);
      driveForward(6,155,155);
    }
  }
  while(1){
  servoLeft();
  myDelay(4);
  range = sonicSensor();
  if(range >= 12 && range <= 18){
    //drive straight
    driveForward(6,155,155);
  }
  if(range < 12){
    //turn rightish
    driveRight(1,160,160);
    driveForward(6,155,155);
  }else if(range > 18){
    //turn leftish
    driveLeft(1,155,155);
    driveForward(6,155,155);
  }
  }
}

void loop() {
   ObstacleAvoidance();
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
