# L293D Motor Driver Library (for ESP32)

This is a lightweight Arduino-compatible library to control up to **4 DC motors** using the **L293D motor Shield**

---

## 🚀 Features

- Supports **4 DC motors** (IN1–IN4) via L293D H-bridge
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

## 🧠 Notes

- This library is designed specifically for **ESP32**
- For non-ESP32 boards (like Uno/Nano) use Adafruit's AFMotor library instead.
---

## 📜 License

MIT License  
(c) 2025 PCBCUPID

---

## 🙌 Contributions Welcome

Feel free to fork, improve, or extend this library. Pull requests and issues are appreciated!
