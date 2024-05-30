/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman
  Used by: Brandon Ramos for Embedded Systems Fall 2020 Course
  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/

// the setup function runs once when you press reset or power the board
void setup() {
  
  pinMode(LED_BUILTIN, OUTPUT); // initialize digital pin LED_BUILTIN as an output.

  //Here is where we turn on and off the light attached to pin 13
  for(int i=0;i<5;i++){
  digitalWrite(LED_BUILTIN, HIGH);  //a long on
  delay(1000);
  
  //since code is repeated twice, I simply shorten the code by another loop
  for(int j=0;j<2;j++){
  digitalWrite(LED_BUILTIN, LOW);   //a short off
  delay(500);   
  digitalWrite(LED_BUILTIN, HIGH);  //a short on
  delay(500);
  }
  
  digitalWrite(LED_BUILTIN, LOW);   //a long off
  delay(1000);
  digitalWrite(LED_BUILTIN, HIGH);  //a long on
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);   //a long off
  delay(1000);                    
 }
}

// the loop function runs over and over again forever
void loop(){}
