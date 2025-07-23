// PCBCUPID L293D Motor Shield Library
// Corrected motor control bit mappings

#ifndef _PCBCUPID_L293D_h_
#define _PCBCUPID_L293D_h_

#include <inttypes.h>
#include <Arduino.h>

#include "driver/ledc.h"
// PWM frequency definitions for ESP32
#define MOTOR_64KHZ   64000
#define MOTOR_32KHZ   32000
#define MOTOR_16KHZ   16000
#define MOTOR_8KHZ    8000
#define MOTOR_4KHZ    4000
#define MOTOR_2KHZ    2000
#define MOTOR_1KHZ    1000

#define DC_MOTOR_PWM_RATE   MOTOR_16KHZ    // Default PWM rate for DC motors

// Bit positions for motor control in shift register
#define MOTOR1_A 2
#define MOTOR1_B 3
#define MOTOR2_A 1
#define MOTOR2_B 4
#define MOTOR3_A 0
#define MOTOR3_B 6
#define MOTOR4_A 5
#define MOTOR4_B 7

// Constants that the user passes in to the motor calls
#define FORWARD 1
#define BACKWARD 2
#define BRAKE 3
#define RELEASE 4

// ESP32 pin names for interface to 74HCT595 shift register
#define MOTORLATCH 15
#define MOTORCLK 3
#define MOTORENABLE 0
#define MOTORDATA 6

// PWM enable pins (from your working code)
#define MOTOR1_PWM 14
#define MOTOR2_PWM 4
#define MOTOR3_PWM 2
#define MOTOR4_PWM 1

class PCBCUPID_MotorController
{
  public:
    PCBCUPID_MotorController(void);
    PCBCUPID_MotorController(uint8_t latch, uint8_t clk, uint8_t enable, uint8_t data);
    void enable(void);
    friend class PCBCUPID_DCMotor;
    void latch_tx(void);
    uint8_t TimerInitalized;
    
  private:
    uint8_t latch_pin, clk_pin, enable_pin, data_pin;
};

class PCBCUPID_DCMotor
{
 public:
  PCBCUPID_DCMotor(uint8_t motornum, uint16_t freq = DC_MOTOR_PWM_RATE);
  void run(uint8_t cmd);
  void setSpeed(uint8_t speed);

 private:
  uint8_t motornum;
  uint16_t pwmfreq;
  void initPWM(int pwm_pin);
};
#endif
