#include "PCBCUPID_L293D.h"

PCBCUPID_DCMotor motor(1);

void setup() {
  Serial.begin(9600);// set up Serial library at 9600 bps
  Serial.println("Motor test!");

  // turn on motor
  motor.setSpeed(255);
  motor.run(RELEASE);
}

void loop() {
  uint8_t i;
  
  Serial.print("tick");
  
  motor.run(FORWARD);
  for (i=0; i<255; i++) {
    motor.setSpeed(i);  
    delay(10);
 }
 
  for (i=255; i!=0; i--) {
    motor.setSpeed(100);  
    delay(10);
 }
  
  Serial.print("tock");

  motor.run(BACKWARD);
  for (i=0; i<255; i++) {
    motor.setSpeed(200);  
    delay(10);
 }
  for (i=255; i!=0; i--) {
    motor.setSpeed(i);  
    delay(10);
 }
  
  Serial.print("tech");
  motor.run(RELEASE);
  delay(1000);
}