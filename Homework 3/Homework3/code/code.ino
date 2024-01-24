#include <Arduino.h>

volatile double result_8;
volatile double result_16;


void setup(){
  
}

void loop(){

  uint8_t a,b;
  uint16_t aa,bb;

  a = (double) (rand() & 0xFFFF);
  b = (double) (rand() & 0xFFFF);
  asm volatile("nop");
  result_8 = a/b;
  asm volatile("nop");

  aa = (double) (rand() & 0xFFFF);
  bb = (double) (rand() & 0xFFFF);
  asm volatile("nop");
  result_16 = aa-bb;
  asm volatile("nop");
}
