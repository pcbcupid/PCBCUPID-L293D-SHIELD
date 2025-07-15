#ifndef PCBCUPID_L293D_H
#define PCBCUPID_L293D_H

#include <Arduino.h>
#ifdef ESP32
  #include <driver/ledc.h>
#endif

// Motor pin definitions
#define MOTOR1_A 2
#define MOTOR1_B 3
#define MOTOR2_A 1
#define MOTOR2_B 4
#define MOTOR3_A 5
#define MOTOR3_B 7
#define MOTOR4_A 0
#define MOTOR4_B 6

#define MOTORLATCH 15
#define MOTORENABLE 0
#define MOTORDATA 46
#define MOTORCLK 3

#define FORWARD 1
#define BACKWARD 2
#define RELEASE 3

class MotorController {
  public:
    MotorController();
    void enable();
    void latch_tx();
    boolean TimerInitalized;
};

class DCMotor {
  public:
    DCMotor(uint8_t num, uint8_t freq = 5000);
    void run(uint8_t cmd);
    void setSpeed(uint8_t speed);
  
  private:
    uint8_t motornum, pwmfreq;
};

#endif