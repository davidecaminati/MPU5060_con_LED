/*  Progetto con GY-521 e LED RGB
    Scritta da: Davide Caminati
                www.caminatidavide.it
*/
#include <Wire.h>
#include <Servo.h>

const int MPU=0x68;  // I2C address of the MPU-6050

int16_t GyX, GyY; //Variabile int a 16bit


int pin_red = 3;
int pin_green = 5;

void setup(){
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  
  pinMode(pin_red,OUTPUT);
  pinMode(pin_green,OUTPUT);
}
void loop(){
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);                // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,14,true);  // request a total of 14 registers
  
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)

  int PosServo_X = map(GyX, -20000, 20000, 0, 255);
  int PosServo_Y = map(GyY, -20000, 20000, 0, 255);
/*
  if (PosServo_X<255){
  	Serial.println(PosServo_X);
  	//analogWrite(pin_red,PosServo_X);
  }
  if (PosServo_Y<255){
  	
  	Serial.println(PosServo_Y);
  	//analogWrite(pin_green,PosServo_Y);
  }
  */
  
  	Serial.print(PosServo_X);
  	Serial.print("\t");
  	Serial.println(PosServo_Y);
  	
  
}
