#include "PCBCUPID_L293D.h"

// ESP32-specific PWM configuration
#ifdef ESP32
  #define PWM_FREQ 5000    // 5kHz PWM frequency
  
  // LEDC channel assignments (use proper enum values)
  const ledc_channel_t pwmChannels[4] = {
    LEDC_CHANNEL_0,
    LEDC_CHANNEL_1,
    LEDC_CHANNEL_2,
    LEDC_CHANNEL_3
  };
  
  // PWM GPIO pins
  const uint8_t motorPwmPins[4] = {14, 4, 1, 2};
#endif

static uint8_t latch_state;
static MotorController MC;

MotorController::MotorController() {
    TimerInitalized = false;
}

void MotorController::enable() {
  pinMode(MOTORLATCH, OUTPUT);
  pinMode(MOTORENABLE, OUTPUT);
  pinMode(MOTORDATA, OUTPUT);
  pinMode(MOTORCLK, OUTPUT);

  latch_state = 0;
  latch_tx();
  digitalWrite(MOTORENABLE, LOW);
}

void MotorController::latch_tx() {
  digitalWrite(MOTORLATCH, LOW);
  digitalWrite(MOTORDATA, LOW);

  for (uint8_t i=0; i<8; i++) {
    digitalWrite(MOTORCLK, LOW);
    digitalWrite(MOTORDATA, (latch_state & _BV(7-i)) ? HIGH : LOW);
    digitalWrite(MOTORCLK, HIGH);
  }
  digitalWrite(MOTORLATCH, HIGH);
}

// Initialize PWM for a motor
void initPWM(uint8_t motorNum, uint8_t freq) {
#ifdef ESP32
  if (motorNum < 1 || motorNum > 4) return;
  
  // Configure timer (only needs to be done once)
  if (motorNum == 1) {
    ledc_timer_config_t timer_conf = {
      .speed_mode = LEDC_LOW_SPEED_MODE,
      .duty_resolution = LEDC_TIMER_8_BIT,
      .timer_num = LEDC_TIMER_0,
      .freq_hz = freq,
      .clk_cfg = LEDC_AUTO_CLK
    };
    ledc_timer_config(&timer_conf);
  }

  // Configure channel
  ledc_channel_config_t channel_conf = {
    .gpio_num = motorPwmPins[motorNum-1],
    .speed_mode = LEDC_LOW_SPEED_MODE,
    .channel = pwmChannels[motorNum-1],
    .intr_type = LEDC_INTR_DISABLE,
    .timer_sel = LEDC_TIMER_0,
    .duty = 0,
    .hpoint = 0
  };
  ledc_channel_config(&channel_conf);
#endif
}

// Set PWM for a motor
void setPWM(uint8_t motorNum, uint8_t speed) {
#ifdef ESP32
  if (motorNum < 1 || motorNum > 4) return;
  ledc_set_duty(LEDC_LOW_SPEED_MODE, pwmChannels[motorNum-1], speed);
  ledc_update_duty(LEDC_LOW_SPEED_MODE, pwmChannels[motorNum-1]);
#endif
}

DCMotor::DCMotor(uint8_t num, uint8_t freq) {
  motornum = num;
  pwmfreq = freq;
  MC.enable();

  switch (num) {
    case 1:
      latch_state &= ~_BV(MOTOR1_A) & ~_BV(MOTOR1_B);
      break;
    case 2:
      latch_state &= ~_BV(MOTOR2_A) & ~_BV(MOTOR2_B);
      break;
    case 3:
      latch_state &= ~_BV(MOTOR3_A) & ~_BV(MOTOR3_B);
      break;
    case 4:
      latch_state &= ~_BV(MOTOR4_A) & ~_BV(MOTOR4_B);
      break;
  }
  MC.latch_tx();
  initPWM(num, freq);
}

void DCMotor::run(uint8_t cmd) {
  uint8_t a, b;
  switch (motornum) {
    case 1: a = MOTOR1_A; b = MOTOR1_B; break;
    case 2: a = MOTOR2_A; b = MOTOR2_B; break;
    case 3: a = MOTOR3_A; b = MOTOR3_B; break;
    case 4: a = MOTOR4_A; b = MOTOR4_B; break;
    default: return;
  }
  
  switch (cmd) {
    case FORWARD:
      latch_state |= _BV(a);
      latch_state &= ~_BV(b);
      break;
    case BACKWARD:
      latch_state &= ~_BV(a);
      latch_state |= _BV(b);
      break;
    case RELEASE:
      latch_state &= ~_BV(a);
      latch_state &= ~_BV(b);
      break;
  }
  MC.latch_tx();
}

void DCMotor::setSpeed(uint8_t speed) {
  setPWM(motornum, speed);
}