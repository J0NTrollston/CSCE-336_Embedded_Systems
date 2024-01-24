/*--------------------------------------------------------------------
Name: 	Brandon Ramos
Date: 	9/20/2020	
Course: CSCE 236 Embedded Systems (Fall 2020) 
File: 	main.cpp
HW/Lab:	Homework 3

Doc:	used datasheet for arduino and TA help


Academic Integrity Statement: I certify that, while others may have 
assisted me in brain storming, debugging and validating this program, 
the program itself is my own work. I understand that submitting code 
which is the work of other individuals is a violation of the honor   
code.  I also understand that if I knowingly give my original work to 
another individual is also a violation of the honor code.
--------------------------------------------------------------------*/
#include <Arduino.h>
#include "morse.h"

// Definitions for Port B, D and C registors
#define PINB_Reg (*((volatile uint8_t *) 0x23)) //Reads the state of INPUT pin
#define DDRB_Reg (*((volatile uint8_t *) 0x24)) // I/O register, if set high the state is an output
#define PORTB_Reg (*((volatile uint8_t *) 0x25)) //Determines if pin is HIGH or LOW

#define PIND_Reg (*((volatile uint8_t *) 0x29)) //Reads the state of INPUT pin
#define DDRD_Reg (*((volatile uint8_t *) 0x2a)) // I/O register, if set high the state is an output
#define PORTD_Reg (*((volatile uint8_t *) 0x2b)) //Determines if pin is HIGH or LOW

#define PINC_Reg (*((volatile uint8_t *) 0x26))  //Reads the state of INPUT pin
#define DDRC_Reg (*((volatile uint8_t *) 0x27)) // I/O register, if set high the state is an output
#define PORTC_Reg (*((volatile uint8_t *) 0x28)) //Determines if pin is HIGH or LOW

// Definitions for LED assignments:
#define BOARD_LED (1<<5)   //pin 13 is PortB bit 5
#define button (1<<2)      //PC2 is A2 Analog in

//Variables
char c0 = 'x';
char c1 = 'x';
char c2 = 'x';
char c3 = 'x';

void testRGBLED(){
    //set pinmode for LEDss to output
    DDRB_Reg |= BOARD_LED;
    DDRB_Reg |= LED_RED;
    DDRB_Reg |= LED_GREEN;
    DDRB_Reg |= LED_BLUE;

    //turn all off
    PORTB_Reg &= ~BOARD_LED;
    PORTB_Reg &= ~LED_RED;
    PORTB_Reg &= ~LED_GREEN;
    PORTB_Reg &= ~LED_BLUE;

    //Test LEDs
    Serial.print("Tesing RGB LED");
    PORTB_Reg |= BOARD_LED; //set output
    PORTB_Reg |= LED_RED;   //set output
    delay(400);
    PORTB_Reg &= ~LED_RED;   //clear output
    PORTB_Reg |= LED_GREEN;  //set output
    delay(400);
    PORTB_Reg &= ~LED_GREEN; //clear output
    PORTB_Reg |= LED_BLUE;   //set output
    delay(400);
    PORTB_Reg &= ~LED_BLUE;   //clear output
    PORTB_Reg &= ~BOARD_LED;   //clear output
    Serial.println("Finished LED testing!");
    
}

void setup(){
    Serial.begin(9600);

    //Test rgb leds
    testRGBLED();
    delay(500);

    //Blink "Hi"
    morseBlinkChar(LED_GREEN,'H');
    morseBlinkChar(LED_RED,'i');
    
    //Test the string function
    // morseBlinkString(LED_GREEN,"sos",3);

    //set pinmode for button as input
    DDRC_Reg &= ~button;
    //enable pullup
    PORTC_Reg |= button; //set the output to enable pullup resistor
}



void loop(){
int time = 0;
int tempTime = 0;
// unsigned int temp = TCNT1;

    //delay to deal with button bounce is sufficient
    delay(10);

    //Check for button press and length of press
    if(digitalRead(A2)==0){
        tempTime = millis();
        while(digitalRead(A2)==0){}
        time = millis() - tempTime;
        if(time < 500){
            Serial.println('d');
            c0 = c1;
            c1 = c2;
            c2 = c3;
            c3 = 'd';
        }else if(time > 500){
            Serial.println('D');
            c0 = c1;
            c1 = c2;
            c2 = c3;
            c3 = 'D';
        }
        
        //decide if user typed in 'r' 'g' or 'b'
        if((c1 == 'd') & (c2 == 'D') & (c3 == 'd')){
            PORTB_Reg |= LED_RED;
            delay(1000);
            PORTB_Reg &= ~LED_RED;
        }else if((c1 == 'D') & (c2 == 'D') & (c3 == 'd')){
            PORTB_Reg |= LED_GREEN;
            delay(1000);
            PORTB_Reg &= ~LED_GREEN;
        }else if((c0 == 'D') & (c1 == 'd') & (c2 == 'd') & (c3 == 'd')){
            PORTB_Reg |= LED_BLUE;
            delay(1000);
            PORTB_Reg &= ~LED_BLUE;
        }

    }

    //If no button press, print "s" for long pause
    tempTime = millis();
    while(digitalRead(A2)==1){
        time = millis()-tempTime;
        if(time>1000){
            Serial.println("s");
            c0 = 'x';
            c1 = 'x';
            c2 = 'x'; //to reset
            c3 = 'x';
            while(digitalRead(A2)==1){}
        }
    }
}

