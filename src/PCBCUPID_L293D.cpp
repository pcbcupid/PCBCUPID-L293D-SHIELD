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
    
    // Initialize PWM enable pins
    pinMode(MOTOR1_PWM, OUTPUT);
    pinMode(MOTOR2_PWM, OUTPUT);
    pinMode(MOTOR3_PWM, OUTPUT);
    pinMode(MOTOR4_PWM, OUTPUT);
    
    // Enable all motor PWM pins
    digitalWrite(MOTOR1_PWM, HIGH);
    digitalWrite(MOTOR2_PWM, HIGH);
    digitalWrite(MOTOR3_PWM, HIGH);
    digitalWrite(MOTOR4_PWM, HIGH);
    
    latch_state = 0;
    MC.latch_tx();
    digitalWrite(enable_pin, LOW);  // Enable the motor driver
}

void PCBCUPID_MotorController::latch_tx(void) {
    digitalWrite(latch_pin, LOW);
    digitalWrite(data_pin, LOW);

    for (int8_t i = 7; i >= 0; i--) {
        digitalWrite(clk_pin, LOW);
        digitalWrite(data_pin, (latch_state & (1 << i)) ? HIGH : LOW);
        digitalWrite(clk_pin, HIGH);
    }
    digitalWrite(latch_pin, HIGH);
}

PCBCUPID_DCMotor::PCBCUPID_DCMotor(uint8_t num, uint16_t freq) {
    motornum = num;
    pwmfreq = freq;
    
    // Set PWM pin based on motor number
    switch (num) {
        case 1: pwm_pin = MOTOR1_PWM; break;
        case 2: pwm_pin = MOTOR2_PWM; break;
        case 3: pwm_pin = MOTOR3_PWM; break;
        case 4: pwm_pin = MOTOR4_PWM; break;
        default: pwm_pin = 0; break;
    }
    
    MC.enable();
    
    // Clear motor bits
    switch (num) {
        case 1:
            latch_state &= ~(1 << MOTOR1_A) & ~(1 << MOTOR1_B);
            break;
        case 2:
            latch_state &= ~(1 << MOTOR2_A) & ~(1 << MOTOR2_B);
            break;
        case 3:
            latch_state &= ~(1 << MOTOR3_A) & ~(1 << MOTOR3_B);
            break;
        case 4:
            latch_state &= ~(1 << MOTOR4_A) & ~(1 << MOTOR4_B);
            break;
    }
    MC.latch_tx();
    initPWM();
}

void PCBCUPID_DCMotor::initPWM(void) {
#ifdef ESP32
    if (!MC.TimerInitalized) {
        // Configure LEDC timer
        ledc_timer_config_t ledc_timer = {
            .speed_mode = LEDC_LOW_SPEED_MODE,
            .duty_resolution = LEDC_TIMER_8_BIT,
            .timer_num = LEDC_TIMER_0,
            .freq_hz = (uint32_t)pwmfreq,
            .clk_cfg = LEDC_AUTO_CLK
        };
        ledc_timer_config(&ledc_timer);
        MC.TimerInitalized = true;
    }
    
    // Configure LEDC channel for this motor
    ledc_channel_config_t ledc_channel = {
        .gpio_num = pwm_pin,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = (ledc_channel_t)(motornum - 1),
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER_0,
        .duty = 255,  // Full speed initially
        .hpoint = 0
    };
    ledc_channel_config(&ledc_channel);
#endif
}

void PCBCUPID_DCMotor::run(uint8_t cmd) {
    uint8_t a, b;
    
    // Get bit positions for this motor
    switch (motornum) {
        case 1: a = MOTOR1_A; b = MOTOR1_B; break;
        case 2: a = MOTOR2_A; b = MOTOR2_B; break;
        case 3: a = MOTOR3_A; b = MOTOR3_B; break;
        case 4: a = MOTOR4_A; b = MOTOR4_B; break;
        default: return;
    }
    
    latch_state &= ~((1 << a) | (1 << b));

    switch (cmd) {
        case FORWARD:
            latch_state |= (1 << a);
            break;
        case BACKWARD:
            latch_state |= (1 << b);
            break;
        case LEFT:
            latch_state |= (1 << a);
            break;
        case RIGHT:
            latch_state |= (1 << b);
            break;
        case RELEASE:  // Add this case for stopping
            // Clear both control bits for this motor
            latch_state &= ~(1 << a);
            latch_state &= ~(1 << b);
            break;
    }
    MC.latch_tx();
}

void PCBCUPID_DCMotor::setSpeed(uint8_t speed) {
#ifdef ESP32
    ledc_set_duty(LEDC_LOW_SPEED_MODE, (ledc_channel_t)(motornum - 1), speed);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, (ledc_channel_t)(motornum - 1));
#else
    analogWrite(pwm_pin, speed);
#endif
}

uint8_t getlatchstate(void) {
    return latch_state;
}



//{39, 216, 149, 106};