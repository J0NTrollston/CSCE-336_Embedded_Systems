#include <Servo.h>

Servo servo;
int pos=0;


void setup() {
  // put your setup code here, to run once:
  servo.attach(9);
}

void loop() {
  // put your main code here, to run repeatedly:
int photoresistorL = analogRead(A0);
int photoresistorR = analogRead(A1);

if(photoresistorL-photoresistorR < 0){
  servo.write(pos--);
  delay(15);
}else{
  servo.write(pos++);
  delay(15);
}

}
