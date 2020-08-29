#include<Servo.h>
int val =0;
int mspeed=1000;
int m1s=1000;
int m2s=1000;
int m3s=1000;
int m4s=1000;
bool change = true;

Servo m1;
Servo m2;
Servo m3;
Servo m4;


void setup() {
  m1.attach(11);
  m2.attach(10);
  m3.attach(9);
  m4.attach(6);
  Serial.begin(9600);
  m1.writeMicroseconds(1000); 
  m2.writeMicroseconds(1000); 
  m3.writeMicroseconds(1000); 
  m4.writeMicroseconds(1000); 
  delay(1000);
  m1.writeMicroseconds(1000); 
  m2.writeMicroseconds(1000); 
  m3.writeMicroseconds(1000); 
  m4.writeMicroseconds(1000); 
  delay(1000);
   m1.writeMicroseconds(1000); 
  m2.writeMicroseconds(1000); 
  m3.writeMicroseconds(1000); 
  m4.writeMicroseconds(1000); 
  delay(1000);
  m1.writeMicroseconds(1000); 
  m2.writeMicroseconds(1000); 
  m3.writeMicroseconds(1000); 
  m4.writeMicroseconds(1000); 
  delay(1000);
}

void loop() {
 if (Serial.available() > 0) {
    val = Serial.read();
    /*
    if (val == 'c'){
      m1s=mspeed;
      m2s=mspeed;
      m3s=mspeed;
      m4s=mspeed;
    }
    */
    if (val == 'a' ){
      mspeed+=10;
      m1s+=10;
      m2s+=10;
      m3s+=10;
      m4s+=10;
    }
    if (val == 'b'){
      mspeed-=10;
      m1s-=10;
      m2s-=10;
      m3s-=10;
      m4s-=10;
    }
    Serial.print(val);
 }

 m1.writeMicroseconds(1200);
 m2.writeMicroseconds(1200);
 m3.writeMicroseconds(1200);
 m4.writeMicroseconds(1200);
 /* 
 m1.writeMicroseconds(1000);
 m2.writeMicroseconds(1000);
 m3.writeMicroseconds(1000);
 m4.writeMicroseconds(1000);
 */
}
