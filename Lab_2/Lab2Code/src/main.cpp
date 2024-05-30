/*--------------------------------------------------------------------
Name:   Brandon
Date:   9/10/2020
Course: CSCE 236 Embedded Systems (Fall 2020) 
File:   Lab2Code.cpp
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
#include <math.h>

// Definitions for Port B & D registors
#define PINB_Reg (*((volatile uint8_t *) 0x23)) //Reads the state of INPUT pin
#define DDRB_Reg (*((volatile uint8_t *) 0x24)) // I/O register, if set high the state is an output
#define PORTB_Reg (*((volatile uint8_t *) 0x25)) //Determines if pin is HIGH or LOW

#define PIND_Reg (*((volatile uint8_t *) 0x29)) //Reads the state of INPUT pin
#define DDRD_Reg (*((volatile uint8_t *) 0x2a)) // I/O register, if set high the state is an output
#define PORTD_Reg (*((volatile uint8_t *) 0x2b)) //Determines if pin is HIGH or LOW

// Definitions for LED assignments:
#define BOARD_LED 5   //pin 13 is PortB bit 5
#define RED_LED 1     //pin 9 is PortB bit 1  
#define GREEN_LED 2   //pin 10 is PortB bit 2
#define BLUE_LED 3    //pin 11 is PortB bit 3

#define BUTTON 5      //pin 5 is PortD bit 5


//Changing variables
int buttonState = 0;
uint8_t buttonPressed = 0;

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

//Setup before loop
void setup() {                
  Serial.begin(9600);
  Serial.println("Starting up.....");
  LEDInit();

  //Set pinmode for Button as input
  DDRD_Reg &= ~(1 << BUTTON);
  //Enable pullup 
  PORTD_Reg |= (1 << BUTTON);  //set output to enable pullup resistor
  //Init counter1
  TCCR1A = 0; //Normal mode 0xffff top, rolls over
  

  // TCCR1B |= (1 << CS12) | (1 << CS11); //Clock T1 falling edge for initial checkoffs
  TCCR1B |= (1 << CS10) | (1 << CS11); //Clock T1 falling edge 64 divider for later code
  TCCR1C = 0;
  //Set counter to zero, high byte first
  TCNT1H = 0;
  TCNT1L = 0;  
  //Make sure interrupts are disabled 
  TIMSK1 = 0;
  TIFR1 = 0;

  pinMode(8,INPUT);
  Serial.println("Finished setup!");
}

//For Checkoff 1
void CountingButtonPressesWithCounter(){
  unsigned int temp = TCNT1;
  delay(100);

  //check when button has bounced
  if((TCNT1 - temp) > 1){
    Serial.print("Warning: Button Bounced: TCNT1: ");
    Serial.println(TCNT1);
  }
  if((TCNT1 - temp) == 1){
    Serial.print("TCNT1: ");
    Serial.println(TCNT1);
  }
}

//For Checkoff 3
void UsingCounterToMeasureButtonBounce(){
   buttonState = digitalRead(8);
  //check for button press
  if(buttonState == HIGH){
    buttonPressed++;

    //reset clock register and ICR1
    TCNT1 = 0;
    ICR1 = 0;
      
    delay(1); // delay for stability
    //Check if button bounced or not
    if(ICR1 != 0){
      //bounce occured
      Serial.print("Bounce Occured, it took: ");
      double seconds = ((1/16000000.0) * 64 * ICR1 * pow(10,6));
      Serial.print(seconds);
      Serial.println(" Microseconds");
    }else{
      Serial.print("Button Pressed ");
      Serial.println(buttonPressed);
    }
  }
}

//For Checkoff 4
void MoreBounceDetection(){
  buttonState = digitalRead(8);
  //check if button is pressed
  if(buttonState == HIGH){
    buttonPressed++;
    //stays in while loop while button is held down
    while(buttonState == HIGH){
      buttonState = digitalRead(8);
    }
     
    //Reset clock register and ICR1
    TCNT1 = 0;
    ICR1 = 0;
      
    delay(1); //delay for stability

    //Check if button bounced or not
    if(ICR1 != 0){
      //bounce occured
      Serial.print("Bounce Occured, it took: ");
      double seconds = ((1/16000000.0) * 64 * ICR1 * pow(10,6));
      Serial.print(seconds);
      Serial.println(" Microseconds");
    }else{
      Serial.print("Button Pressed ");
      Serial.println(buttonPressed);
    }
  }
}

//For Checkoff 5
void TimingButtonPresses(){
  buttonState = digitalRead(8);
  unsigned long delaySeconds = millis();

  //Check for button state high
  if(buttonState == HIGH){
    buttonPressed++;

    //Keep in while loop while pressed down
    while(buttonState == HIGH){
      buttonState = digitalRead(8);
    }
    
    //Print how long button was pressed
    Serial.print("Button Pressed Down for ");
      Serial.print(millis()-delaySeconds);
      Serial.println(" milliSeconds");
    
    //Reset clock register and ICR1
    TCNT1 = 0;
    ICR1 = 0;
      
    delay(1);
    if(ICR1 != 0){
      //bounce occured
      Serial.print("Bounce Occured, it took: ");
      double seconds = ((1/16000000.0) * 64 * ICR1 * pow(10,6));
      Serial.print(seconds);
      Serial.println(" Microseconds");
    }else{
      Serial.print("Button Pressed ");
      Serial.println(buttonPressed);
    }
  }  
}

void loop() {
// CountingButtonPressesWithCounter(); //Checkoff 1
// UsingCounterToMeasureButtonBounce(); //Checkoff 3
// MoreBounceDetection(); //Checkoff 4
// TimingButtonPresses(); //Checkoff 5
}
