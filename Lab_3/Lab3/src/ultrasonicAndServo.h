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

// Definitions for Port B & D registors
#define PINB_Reg (*((volatile uint8_t *) 0x23)) //Reads the state of INPUT pin
#define DDRB_Reg (*((volatile uint8_t *) 0x24)) // I/O register, if set high the state is an output
#define PORTB_Reg (*((volatile uint8_t *) 0x25)) //Determines if pin is HIGH or LOW

#define PIND_Reg (*((volatile uint8_t *) 0x29)) //Reads the state of INPUT pin
#define DDRD_Reg (*((volatile uint8_t *) 0x2a)) // I/O register, if set high the state is an output
#define PORTD_Reg (*((volatile uint8_t *) 0x2b)) //Determines if pin is HIGH or LOW

// Definitions for LED assignments:
#define BOARD_LED 5   //pin 13 is PortB bit 5
#define LeftLED 7     //pin 7 is PortD bit 7
#define RightLED 4    //pin 12 is PortB bit 4
#define SERVO 3     //pin 9 is PORTD bit 1
#define trigPin 1 //pin 9 is PortB bit 1
#define echoPin 0 // pin 8 is PortB bit 0

void servoLeft();
void servoRight();
void servoStraight();

int sonicSensor();

