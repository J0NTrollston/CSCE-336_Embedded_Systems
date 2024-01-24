/*--------------------------------------------------------------------
Name:   Brandon Ramos
Date:   9/28/2020
Course: CSCE 236 Embedded Systems (Fall 2020) 
HW/Lab: Project KYLE

Purp: Start of Robot

Doc:  Datasheets and course website, powerpoints

Academic Integrity Statement: I certify that, while others may have 
assisted me in brain storming, debugging and validating this program, 
the program itself is my own work. I understand that submitting code 
which is the work of other individuals is a violation of the honor   
code.  I also understand that if I knowingly give my original work to 
another individual is also a violation of the honor code.
--------------------------------------------------------------------*/

// Definitions for Port B, C & D registors
#define PINB_Reg (*((volatile uint8_t *) 0x23)) //Reads the state of INPUT pin
#define DDRB_Reg (*((volatile uint8_t *) 0x24)) // I/O register, if set high the state is an output
#define PORTB_Reg (*((volatile uint8_t *) 0x25)) //Determines if pin is HIGH or LOW

#define PINC_Reg (*((volatile uint8_t *) 0x26)) //Reads the state of INPUT pin
#define DDRC_Reg (*((volatile uint8_t *) 0x27)) // I/O register, if set high the state is an output
#define PORTC_Reg (*((volatile uint8_t *) 0x28)) //Determines if pin is HIGH or LOW

#define PIND_Reg (*((volatile uint8_t *) 0x29)) //Reads the state of INPUT pin
#define DDRD_Reg (*((volatile uint8_t *) 0x2a)) // I/O register, if set high the state is an output
#define PORTD_Reg (*((volatile uint8_t *) 0x2b)) //Determines if pin is HIGH or LOW

#define BOARD_LED 5   //pin 13 is PortB bit 5
#define LeftLED 0     //pin A0 is PortC bit 0
#define RightLED 1    //pin A1 is PortC bit 1
#define SERVO 3     //pin 9 is PORTD bit 1
#define trigPin 1 //pin 9 is PortB bit 1
#define echoPin 0 // pin 8 is PortB bit 0

/**
 * Motor is setup so that forward is In1 and In4
 *                        backward is In2 and In3
 *                        left is In2 and In4
 *                        right is In1 and In3
 * 
 * EnX are modulated by PMW timer0 and will give the motor an "average"
 *      voltage so that we dont run at 100% power all the time.
 * 
 * **/
#define In1 2       //pin A2 is PortC bit 2
#define In2 3       //pin A3 is PortD bit 3
#define In3 7       //pin 7 is PortD bit 7
#define In4 4       //pin A4 is PortB bit 4
#define EnA 5       //pin 5 is PortD bit 5
#define EnB 6       //pin 6 is PortD bit 6

void servoLeft();
void servoRight();
void servoStraight();

int sonicSensor();

void myDelay(int quarterSeconds);
void myDelay12Microseconds(int numOfMicroSeconds);

void driveForward(int numOfQuarterseconds, int compareRegA, int compareRegB);
void driveBackward(int numOfQuarterseconds, int compareRegA, int compareRegB);
void driveLeft(int numOfQuarterseconds, int compareRegA, int compareRegB);
void driveRight(int numOfQuarterseconds, int compareRegA, int compareRegB);

