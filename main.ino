#include "DualVNH5019MotorShield.h"
DualVNH5019MotorShield motor;

unsigned char serial_in[7]={};
int i=0;
int analogPin = 3;   // potentiometer connected to analog pin 3
int val = 0, comp;

void setup(){
  Serial.begin(19200);
  motor.init();
}

void loop(){
  motor_move();
  servo();
  Serial.println(comp); 
  if (Serial.available() > 0) {
      if (i==6){i=0;}
      i++;
      serial_in[i]=Serial.read();
      }

}
void servo()
{
  if(comp<map(serial_in[4],208,48, 14, 6)){
    motor.setM2Speed(-100);}
  else if(comp>map(serial_in[4],208,48, 14, 6)){
    motor.setM2Speed(100);}
  else{
    motor.setM2Speed(0);}
  comp=analogRead(analogPin)/50;
}
void motor_move()
{
  if(serial_in[1]<127){
      motor.setM1Speed(map(serial_in[1],127,50, 0, -400));
  }
  else if(serial_in[1]>129){
      motor.setM1Speed(map(serial_in[1],129,210, 0, 400));
  }
  else{
      motor.setM1Speed(0);
  }
}
