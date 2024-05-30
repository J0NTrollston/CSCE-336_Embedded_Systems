

int8_t sub8(int8_t a, int8_t b){
  int8_t c = 0;
  c = a-b;
  return c;
}

// void sub16(int16_t){
//   int16_t d = 65501;
//   int16_t e = 65500;
//   int16_t f = d-e;
// }

// void sub32(){
//   int32_t g = 4294967201;
//   int32_t h = 4294967200;
//   int32_t i = g-h;
// }


void setup() {
  // put your setup code here, to run once
  
//  int8_t c = sub8(a, b);
volatile int8_t a = 201;
volatile int8_t b = 200;
int8_t c = a-b;
  
}


  

void loop() {
  // put your main code here, to run repeatedly:
}
