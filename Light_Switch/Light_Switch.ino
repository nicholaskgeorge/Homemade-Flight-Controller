#include<Servo.h>
int motion_1 = 2;
Servo s1;

void setup(){
  s1.attach(2);
}

void loop (){
//  delay(100); //this delay is to let the sensor settle down before taking a reading
//  int sensor_1 = digitalRead(motion_1);
//  if (sensor_1 == HIGH){
//    Serial.print("go");
//    s1.write(0);
//    delay(1000);
//    s1.write(90);
//    delay(1000);
//    s1.write(180);
//  }
    s1.write(0);
    delay(1000);
    s1.write(90);
    delay(1000);
    s1.write(180);
    delay(1000);
}
