#include <Arduino.h>
//#include <Servo.h>

#define LEDBlue (1<<7);
#define LEDGreen (1<<6);
#define LEDRed (1<<5);


//set constants of led pints of DDRx
const int ledPinB = 7;
const int ledPinG = 6;
const int ledPinR = 5;
const int buttonPin = 4;
//Servo myservo;
int buttonState = 0; //changing variable


void setup() {
//set the RGB LED pins
pinMode(ledPinR, OUTPUT);
pinMode(ledPinG, OUTPUT);
pinMode(ledPinB, OUTPUT);
pinMode(buttonPin, INPUT);
//myservo.attach(9);

}

//Have the RGB LED turn all lights on and off
// void RGBLED(){
//    PORTD |= LEDRed; //set red to high?
//   delay(1000);
//   PORTD &= ~LEDRed //set red to low
//   delay(1000);

//    PORTD |= LEDGreen; //set green to high?
//   delay(1000);
//   PORTD &= ~LEDGreen //set green to low
//   delay(1000);

//    PORTD |= LEDBlue; //set blue to high?
//   delay(1000);
//   PORTD &= ~LEDBlue //set blue to low
//   delay(1000);
// }


//checkoff2 where you use a button to go through
// a sequence of colors
void LEDCheckoff2(){
  PORTD |= LEDRed;//red high  R
  delay(500);
  PORTD |= LEDGreen;//green high  RG
  delay(500);
  PORTD &= ~LEDRed;//red low  G
  delay(500);
  PORTD |= LEDBlue;//blue high  GB
  delay(500);
  PORTD &= LEDGreen;//green low  B
  delay(500);
  PORTD |= LEDRed;//red high  RB
  delay(500);
  PORTD &= ~LEDRed;//red low
  PORTD &= ~LEDBlue;//blue low
  PORTD &= ~LEDGreen;
}

// void servotest(){
//      int buttonPin = 4;
//   int buttonState = digitalRead(buttonPin);
//   if(buttonState == HIGH){
//     for (pos = 90; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
//     myservo.write(pos);              // tell servo to go to position in variable 'pos'
//     delay(15);                       // waits 15ms for the servo to reach the position
//   } 
//   delay(100);
//   for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
//     // in steps of 1 degree
//     myservo.write(pos);              // tell servo to go to position in variable 'pos'
//     delay(15);                       // waits 15ms for the servo to reach the position
//   }
//   delay(100);

//   for (pos = 90; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
//     // in steps of 1 degree
//     myservo.write(pos);              // tell servo to go to position in variable 'pos'
//     delay(15);                       // waits 15ms for the servo to reach the position
//   }
//   delay(100);
//   for (pos = 180; pos >= 90; pos -= 1) { // goes from 180 degrees to 0 degrees
//     myservo.write(pos);              // tell servo to go to position in variable 'pos'
//     delay(15);                       // waits 15ms for the servo to reach the position
//   }
//   delay(100);
// }
//}

void loop() {
  buttonState = digitalRead(buttonPin);
  if(buttonState == HIGH){
  LEDCheckoff2();
  }

  //servotest();
}


//Checkoff 3 i used a 100ohm resistor and min=0 and max=around 800 with my IPhone light
//Checkoff 4 when not in light, the resistance of the photoresisor is high, when in light it is low
//so when not covered i get 391ohms and covered i get 15kohms