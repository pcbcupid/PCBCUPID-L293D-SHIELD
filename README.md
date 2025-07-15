# L293D Motor Driver Library (for ESP32)

This is a lightweight Arduino-compatible library to control up to **4 DC motors** using the **L293D motor driver** and the **ESP32 LEDC PWM hardware**.

---

## 🚀 Features

- Supports **4 DC motors** (IN1–IN4) via L293D H-bridge
- Uses **ESP32 LEDC PWM** for smooth motor speed control
- Simple API for:
  - `run(FORWARD / BACKWARD / RELEASE)`
  - `setSpeed(0–255)`
- Customizable PWM frequency for each motor
- Internal software-based H-bridge latch logic for direction control

---

## 📦 Installation

1. Clone this repository or download the ZIP.
2. Copy the folder to your Arduino libraries directory:
   ```
   Documents/Arduino/libraries/PCBCUPID_L293D
   ```
3. Restart the Arduino IDE.

---

## 📌 Usage

```cpp
#include <PCBCUPID_L293D.h>

// Create a motor on channel 1 at 5 kHz PWM
DCMotor motor1(1, 5000);

void setup() {
  motor1.setSpeed(200);     // Set speed (0-255)
  motor1.run(FORWARD);      // Run forward
}

void loop() {
  // Your logic here
}
```

---

## ⚙️ Pin Mapping

| Motor | PWM GPIO | LEDC Channel |
|-------|-----------|--------------|
| M1    | GPIO 6    | Channel 0    |
| M2    | GPIO 3    | Channel 1    |
| M3    | GPIO 15   | Channel 2    |
| M4    | GPIO 0    | Channel 3    |

> Modify `motorPwmPins[]` in the `.cpp` file to match your hardware.

---

## 🧠 Notes

- This library is designed specifically for **ESP32** using **LEDC** (low-level PWM hardware).
- For non-ESP32 boards (like Uno/Nano), use `analogWrite()` or Adafruit's AFMotor library instead.
- `MOTORENABLE`, `MOTORLATCH`, `MOTORDATA`, and `MOTORCLK` are digital control pins (H-bridge latch); configure as needed in `PCBCUPID_L293D.h`.

---

## 📜 License

MIT License  
(c) 2024 PCBCUPID, Keerti

---

## 🙌 Contributions Welcome

Feel free to fork, improve, or extend this library. Pull requests and issues are appreciated!
