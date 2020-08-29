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
  Serial.begin(9600);
  m1.attach(11);
  m2.attach(10);
  m3.attach(9);
  m4.attach(6);
  delay(1000);
  m1.write(40);
  m2.write(40);
  m3.write(40);
  m4.write(40);
  delay(1000);
  m1.write(40);
  m2.write(40);
  m3.write(40);
  m4.write(40);
  delay(1000);
  m1.write(40);
  m2.write(40);
  m3.write(40);
  m4.write(40);
}

void loop() {
  m1.write(50);
  m2.write(50);
  m3.write(50);
  m4.write(50);
}

