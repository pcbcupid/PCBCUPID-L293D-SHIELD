#include "PCBCUPID_L293D.h"

static uint8_t latch_state = 0;
static PCBCUPID_MotorController MC;

// Default constructor with your working pins
PCBCUPID_MotorController::PCBCUPID_MotorController(void) {
    latch_pin = MOTORLATCH;
    clk_pin = MOTORCLK;
    enable_pin = MOTORENABLE;
    data_pin = MOTORDATA;
    TimerInitalized = false;
}

// Custom pin constructor
PCBCUPID_MotorController::PCBCUPID_MotorController(uint8_t latch, uint8_t clk, uint8_t enable, uint8_t data) {
    latch_pin = latch;
    clk_pin = clk;
    enable_pin = enable;
    data_pin = data;
    TimerInitalized = false;
}

void PCBCUPID_MotorController::enable(void) {
    // Initialize control pins
    pinMode(latch_pin, OUTPUT);
    pinMode(clk_pin, OUTPUT);
    pinMode(enable_pin, OUTPUT);
    pinMode(data_pin, OUTPUT);
    
    latch_state = 0;

    latch_tx(); //reset latch
    
    digitalWrite(enable_pin, LOW);  // Enable the Shift Register
}

void PCBCUPID_MotorController::latch_tx(void) {
    digitalWrite(latch_pin, LOW);
    digitalWrite(data_pin, LOW);

    for (int i = 0; i < 8; i++) {
        digitalWrite(clk_pin, LOW);

        int b_data = latch_state & _BV(7-i);
        
        if (b_data) {
            Serial.print("1");
            digitalWrite(data_pin, HIGH);
        } else {
            Serial.print("0");
            digitalWrite(data_pin, LOW);
        }
        
        digitalWrite(clk_pin, HIGH);
    }
    digitalWrite(latch_pin, HIGH);
}

PCBCUPID_DCMotor::PCBCUPID_DCMotor(uint8_t num, uint16_t freq) {
    motornum = num;
    pwmfreq = freq;

    MC.enable();

  switch (num) {
  case 1:
    latch_state &= ~_BV(MOTOR1_A) & ~_BV(MOTOR1_B); // set both motor pins to 0
    MC.latch_tx();
    break;
  case 2:
    latch_state &= ~_BV(MOTOR2_A) & ~_BV(MOTOR2_B); // set both motor pins to 0
    MC.latch_tx();
    break;
  case 3:
    latch_state &= ~_BV(MOTOR3_A) & ~_BV(MOTOR3_B); // set both motor pins to 0
    MC.latch_tx();
    break;
  case 4:
    latch_state &= ~_BV(MOTOR4_A) & ~_BV(MOTOR4_B); // set both motor pins to 0
    MC.latch_tx();
    break;
  }
    Serial.printf("motor number set to %d",motornum);
}

void PCBCUPID_DCMotor::setSpeed(uint8_t speed) {
    switch(motornum)
    {
        case 1:
            analogWrite(MOTOR1_PWM, speed);
        break;
        case 2:
            analogWrite(MOTOR2_PWM, speed);
        break;
        case 3:
            analogWrite(MOTOR3_PWM, speed);
        break;
        case 4:
            analogWrite(MOTOR4_PWM, speed);
        break;
    }
}

void PCBCUPID_DCMotor::initPWM(int pwm_pin) {

    MC.TimerInitalized = true;
    Serial.printf("PWM init for %d motor",motornum);

}

void PCBCUPID_DCMotor::run(uint8_t cmd) {
  uint8_t a, b;

  switch (motornum) {
  case 1:
    a = MOTOR1_A; b = MOTOR1_B; break;
  case 2:
    a = MOTOR2_A; b = MOTOR2_B; break;
  case 3:
    a = MOTOR3_A; b = MOTOR3_B; break;
  case 4:
    a = MOTOR4_A; b = MOTOR4_B; break;
  default:
    return;
  }
  
 switch (cmd) {
  case FORWARD:
    latch_state |= _BV(a);
    latch_state &= ~_BV(b); 
    MC.latch_tx();
    break;
  case BACKWARD:
    latch_state &= ~_BV(a);
    latch_state |= _BV(b); 
    MC.latch_tx();
    break;
  case RELEASE:
    latch_state &= ~_BV(a);     // A and B both low
    latch_state &= ~_BV(b); 
    MC.latch_tx();
    break;
  }
}
