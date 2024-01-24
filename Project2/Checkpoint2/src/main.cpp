/*--------------------------------------------------------------------
Name:   Jeffrey Falkinburg
Date:   24 Mar 19  
Course: CSCE 236 Embedded Systems (Fall 2020) 
File:   project2.iso
HW/Lab: Lab 5/Project 2, Decoding an IR Packet

Purp: Uses counters and interrupts to decode an IR packet for a 
    remote. 

Doc:  <list the names of the people who you helped>
    <list the names of the people who assisted you>

Academic Integrity Statement: I certify that, while others may have 
assisted me in brain storming, debugging and validating this program, 
the program itself is my own work. I understand that submitting code 
which is the work of other individuals is a violation of the honor   
code.  I also understand that if I knowingly give my original work to 
another individual is also a violation of the honor code.
--------------------------------------------------------------------*/
#include <avr/io.h>
#include <Arduino.h>
#include "ir_decoder.h"
#include "motors.h"
#include <math.h>

#define SAMPLE_SIZE       34
#define   BIT0            0x00000001
volatile uint32_t irPacket;
volatile uint8_t  newIrPacket = FALSE;
volatile uint16_t packetData[34];
volatile uint8_t  packetIndex = 0;



uint32_t powersOfTwo(uint32_t n){
  if(n==0){
    return 1;
  }
  uint32_t sum = 1;
  for(uint32_t i=1;i<n+1;i++){
    sum *=2;
  }
  // Serial.println(sum);
  return sum;
}

uint32_t irPacketFind(){

  uint32_t sum = 0;
  for(uint32_t i = SAMPLE_SIZE-1; i > 1 ; i--){
     
    if(packetData[i]>200){
      uint32_t exponent = 33-i;
      sum +=powersOfTwo(exponent);
    }
    // Serial.println(sum,HEX);
  }
  return sum;
}



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
  DDRD_Reg |= (1<<In2); //sets pin 4 to output
  DDRD_Reg |= (1<<In3); //sets pin 7 to output
  DDRB_Reg |= (1<<In4); //sets pin 12 to output

  //Init counter2 for Servo
  TCCR2A = 0;
  TCCR2A |= (1<< COM2A1) | (1<<COM2B1) | (1<<WGM20) | (1<<WGM01); //the inversion for phase correct
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

  //Init counter0 for Motors. Will be same as Counter/Timer2
  TCCR0A = (1<<COM0A1) | (1<<COM0B1) | (1<<WGM00) | (1<<WGM01);//on until OCR0B
  TCCR0B = (1<<CS00); //If you use prescaling, you will mess up delay() and millis()
  IR_Decoder_Setup();
  sei(); /* Enable Global Interrupts*/
}

/*
 * main loop
 */
void loop() {

  /* Check if new IR packet has arrived bad way */ 
//  if (packetIndex > 33) {
//    packetIndex = 0;
//  } // end if new IR packet arrived
  /* Check if new IR packet has arrived better way */ 
  if (newIrPacket == TRUE){
    irPacket = irPacketFind();
	//code to convert packetData[] counts to 32 bit irpacket
	// Serial.println(irPacket, HEX);
    newIrPacket = FALSE;
  } //end if newIrPacket
  
  /* Do something with new IR packet */ 
  if (irPacket == Up_Button || irPacket == Elegoo_Up_Button){    
    Serial.println("Up_Button");
    driveForward(3);
    irPacket = 0;     // Clear irPacket
  } //end if
  if (irPacket == Elegoo_Down_Button){    
    Serial.println("Down_Button");
    driveBackward(3);
    irPacket = 0;     // Clear irPacket
  } //end if
  if (irPacket == Elegoo_Left_Button){    
    Serial.println("Left_Button");
    driveLeft(1);
    irPacket = 0;     // Clear irPacket
  } //end if
  if (irPacket == Elegoo_Right_Button){    
    Serial.println("Right_Button");
    driveRight(1);
    irPacket = 0;     // Clear irPacket
  } //end if
  if (irPacket == Elegoo_Star_Button){    
    Serial.println("Star_Button");
    increaseSpeed();
    irPacket = 0;     // Clear irPacket
  } //end if
  if (irPacket == Elegoo_Pound_Button){    
    Serial.println("Pound_Button");
    decreaseSpeed();
    irPacket = 0;     // Clear irPacket
  } //end if

}// end loop




// -----------------------------------------------------------------------
// Since the IR decoder is connected to INT0, we want an interrupt
// to occur every time that the pin changes - this will occur on
// a positive edge and a negative edge.
//
// Negative Edge:
// The negative edge is associated with end of the logic 1 half-bit and
// the start of the logic 0 half of the bit.  The timer contains the
// duration of the logic 1 pulse, so we'll pull that out, process it
// and store the bit in the global irPacket variable. Going forward there
// is really nothing interesting that happens in this period, because all
// the logic 0 half-bits have the same period.  So we will turn off
// the timer interrupts and wait for the next (positive) edge on INT0
//
// Positive Edge:
// The positive edge is associated with the end of the logic 0 half-bit
// and the start of the logic 1 half-bit.  There is nothing to do in
// terms of the logic 0 half bit because it does not encode any useful
// information.  On the other hand, we are going into the logic 1 half bit
// and the portion which determines the bit value, the start of the
// packet, or if the timer rolls over, the end of the ir packet.
// Since the duration of this half-bit determines the outcome
// we will turn on the timer and its associated interrupt.
// -----------------------------------------------------------------------

ISR(INT0_vect){

  uint8_t   pin;
  uint16_t  pulseDuration;      // The timer is 16-bits

  if (IR_DECODER_PIN)   pin=1;  else pin=0;

  switch (pin) {          // read the current pin level
    case 0:           // !!!!!!!!!NEGATIVE EDGE!!!!!!!!!!
      pulseDuration = TCNT1;    //**Note** Timer Count register is 16-bits
      packetData[packetIndex++] = pulseDuration;
      LOW_2_HIGH;               // Set up pin INT0 on positive edge
								//Disable interrupt on match with OCR1A
                TIMSK1 &= ~(1<<OCIE1A);
      
      break;

    case 1:             // !!!!!!!!POSITIVE EDGE!!!!!!!!!!!
      TCNT1 = 0x0000;           // time measurements are based at time 
								// Clear Timer/Counter1, Output Compare A Match Flag by writing 1 
                TIFR1 |= (1<<OCF1A);
								// Enable interrupt on match with OCR1A
                TIMSK1 |= (1<<OCIE1A);
      HIGH_2_LOW;               // Set up pin INT0 on falling edge
      break;
  } // end switch

} // end pinChange ISR

// -----------------------------------------------------------------------
//            0 half-bit  1 half-bit    TIMER 1 COUNTS    TIMER 1 COUNTS
//  Logic 0   xxx
//  Logic 1
//  Start
//  End
//
// -----------------------------------------------------------------------
/**
 * This function is called whenever the timer 1 output compare match OCR1A
 * is generated.
 **/
ISR(TIMER1_COMPA_vect){

							// Disable interrupt on match with OCR1A
              TIMSK1 &= ~(1<<OCIE1A);
              packetIndex=0;
              newIrPacket = TRUE;
}