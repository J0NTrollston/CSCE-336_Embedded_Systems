#include <Servo.h>

Servo servo;
int pos=0;


void setup() {
  // put your setup code here, to run once:
  servo.attach(9);
}

void loop() {
servo.write(pos+20);
int firstMeasure=analogRead(A0);
delay(100);
servo.write(pos-20);
int secondMeasure=analogRead(A0);
delay(100);

if(firstMeasure-secondMeasure > 0){
  servo.write(pos-40);
  pos=pos-40;
}else{
  pos=pos+20;
}


}
