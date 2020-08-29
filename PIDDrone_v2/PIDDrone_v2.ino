
#include <Wire.h>
#include<Servo.h>
int val =0;
double mspeed=1000;
int m1s=1000;
int m2s=1000;
int m3s=1000;
int m4s=1000;
bool change = true;

Servo m1;
Servo m2;
Servo m3;
Servo m4;
/*MPU-6050 gives you 16 bits data so you have to create some 16int constants
 * to store the data for accelerations and gyro*/

int16_t Acc_rawX, Acc_rawY, Acc_rawZ,Gyr_rawX, Gyr_rawY, Gyr_rawZ;
 

float Acceleration_angle[2];
float Gyro_angle[2];
float Total_angle[2];




float elapsedTime, time, timePrev;
int i;
float rad_to_deg = 180/3.141592654;

float PIDy,PIDx, pwmLeft, pwmRight, errorx,errory, previous_errory,previous_errorx;
float pid_px=0;
float pid_ix=0;
float pid_dx=0;
float pid_py=0;
float pid_iy=0;
float pid_dy=0;
/////////////////PID CONSTANTS/////////////////
double kpx=6;//3.55
double kix=0;//0.003
double kdx=4;//2.05
double kpy=10;//3.55
double kiy=0;//0.003
double kdy=2;//2.05
///////////////////////////////////////////////

double throttle=1300; //initial value of throttle to the motors
float desired_anglex = 0; //This is the angle in which we whant the
                         //balance to stay steady
float desired_angley = 0;


void setup() {
  Wire.begin(); //begin the wire comunication
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(9600);
  time = millis(); //Start counting time in milliseconds
  /*In order to start up the ESCs we have to send a min value
   * of PWM to them before connecting the battery. Otherwise
   * the ESCs won't start up or enter in the configure mode.
   * The min value is 1000us and max is 2000us, REMEMBER!*/
   /*Give some delay, 7s, to have time to connect
                *the propellers and let everything start up*/ 
  m1.attach(11);
  m2.attach(10);
  m3.attach(9);
  m4.attach(6);
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
  delay(7000);
}//end of setup void

void loop() {
/////////////////////////////I M U/////////////////////////////////////
    timePrev = time;  // the previous time is stored before the actual time read
    time = millis();  // actual time read
    elapsedTime = (time - timePrev) / 1000; 
   
     Wire.beginTransmission(0x68);
     Wire.write(0x3B); //Ask for the 0x3B register- correspond to AcX
     Wire.endTransmission(false);
     Wire.requestFrom(0x68,6,true); 
    
     Acc_rawX=Wire.read()<<8|Wire.read(); //each value needs two registres
     Acc_rawY=Wire.read()<<8|Wire.read();
     Acc_rawZ=Wire.read()<<8|Wire.read();

     Acceleration_angle[0] = atan((Acc_rawY/16384.0)/sqrt(pow((Acc_rawX/16384.0),2) + pow((Acc_rawZ/16384.0),2)))*rad_to_deg;
     /*---Y---*/
     Acceleration_angle[1] = atan(-1*(Acc_rawX/16384.0)/sqrt(pow((Acc_rawY/16384.0),2) + pow((Acc_rawZ/16384.0),2)))*rad_to_deg;
    
   Wire.beginTransmission(0x68);
   Wire.write(0x43); //Gyro data first adress
   Wire.endTransmission(false);
   Wire.requestFrom(0x68,4,true); //Just 4 registers
   
   Gyr_rawX=Wire.read()<<8|Wire.read(); //Once again we shif and sum
   Gyr_rawY=Wire.read()<<8|Wire.read();

   /*---X---*/
   Gyro_angle[0] = Gyr_rawX/131.0; 
   /*---Y---*/
   Gyro_angle[1] = Gyr_rawY/131.0;

   /*Now in order to obtain degrees we have to multiply the degree/seconds
   *value by the elapsedTime.*/
   /*Finnaly we can apply the final filter where we add the acceleration
   *part that afects the angles and ofcourse multiply by 0.98 */

   /*---X axis angle---*/
   //(turning forward is positive back is negative. add 6 for error)
   Total_angle[0] = 0.98 *(Total_angle[0] + Gyro_angle[0]*elapsedTime) + 0.02*Acceleration_angle[0];
   /*---Y axis angle---*/
   //Left Right (when pointing to the front right is negative and left is positive. add 2.70 to fix error )
   Total_angle[1] = 0.98 *(Total_angle[1] + Gyro_angle[1]*elapsedTime) + 0.02*Acceleration_angle[1];
   //Serial.println("x");
   //Serial.println(Total_angle[0]);
   Serial.println("y");
   Serial.println(Total_angle[1]);
   /*Now we have our angles in degree and values from -10º0 to 100º aprox*/
 //NOTE: it takes about 12 seconds for the angle values to come and give it about 10 more seconds before you start flying because it has to fix itself first
  if (Serial.available() > 0) {
      val = Serial.read();
      if (val == 'a'){
        mspeed+=10;
      }
      if (val == 'b'){
        mspeed-=10;
      }
  }
  //PID Control
  
  errory = (Total_angle[1]+1) - desired_angley;
  errorx = (Total_angle[0]+10) - desired_anglex;
  //Serial.print(errorx);
  // proportinal control
  pid_py = kpy*errory;
  pid_px = kpx*errorx;

  //integral control
  if(-3 <errory <3)
  {
    pid_iy = pid_iy+(kiy*errory);  
  }
  if(-3 <errorx <3)
  {
    pid_ix = pid_ix+(kix*errorx);  
  }

  //derivative control
  pid_dy = kdy*((errory - previous_errory)/elapsedTime);
  pid_dx = kdx*((errorx - previous_errorx)/elapsedTime);
  //Sum of PID
  PIDy = pid_py+pid_iy+pid_dy;
  PIDx = pid_px+pid_ix+pid_dx;
  if(PIDy < -400)
  {
    PIDy=-400;
  }
  if(PIDy > 400)
  {
    PIDy=400;
  }
  if(PIDx < -400)
  {
    PIDx=-400;
  }
  if(PIDx > 400)
  {
    PIDx=400;
  }
  /*
   * m1 is front left
   * m2 is front right
   * m3 is back left
   * m4 is back right
   */
  // applying PID correction
  if(mspeed<1020){
    PIDx=0;
    PIDy=0;
    m1s,m2s,m3,m4s = 1000;
  }
  if(mspeed<1000){
    mspeed=1000;
  }
  if(mspeed>1700){
    mspeed=1700;
  }
  //Serial.println(PIDy);
  //Serial.print(PIDx);
  m1s = mspeed+PIDy+PIDx;
  m2s = mspeed-PIDy+PIDx;
  m3s = mspeed+PIDy-PIDx;
  m4s = mspeed-PIDy-PIDx;
  //1020 ms is the base
  if( m1s>2000){
    m1s = 2000;
  }
  if(m1s<1000){
    m1s=1000;
  }
  if(m2s>2000){
    m2s = 2000;
  }
  if(m2s<1000){
    m2s=1000;
  }
  if(m3s>2000){
    m3s = 2000;
  }
  if(m3s<1000){
    m3s=1000;
  }
  if(m4s>2000){
    m4s = 2000;
  }
  if(m4s<1000){
    m4s=1000;
  }
  m1.writeMicroseconds(m1s);
  m2.writeMicroseconds(m2s);
  m3.writeMicroseconds(m3s+5);
  m4.writeMicroseconds(m4s);
  previous_errory = errory;
  previous_errorx = errorx;
}//end of loop void
