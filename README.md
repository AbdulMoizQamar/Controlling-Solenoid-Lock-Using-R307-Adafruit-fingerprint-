# Controlling-Solenoid-Lock-Using-R307-Adafruit-fingerprint-
**To control a solenoid lock using the R307 fingerprint sensor and Arduino, you can follow these steps:**

**Components Required:**
R307 Fingerprint Sensor
Esp32
12V Solenoid Lock
Relay Module
Power Supply (12V for the solenoid)
Jumper Wires

**Explanation of Connections:**
Fingerprint Sensor:
Connect the VCC pin of the fingerprint sensor to the 3.3V pin on the ESP32.
Connect the GND pin of the fingerprint sensor to the GND pin on the ESP32.
Connect the TX pin of the fingerprint sensor to GPIO16 (RX2) on the ESP32.
Connect the RX pin of the fingerprint sensor to GPIO17 (TX2) on the ESP32.
**Solenoid Lock:**
Connect the VCC pin of the relay module to the 3.3V pin on the ESP32.
Connect the GND pin of the relay module to the GND pin on the ESP32.
Connect the IN1 pin of the relay module to GPIO12 on the ESP32.
Connect the COM pin of the relay module to the positive terminal of the 12V power supply.
Connect the NO pin of the relay module to the positive wire of the solenoid lock.
Connect the negative wire of the solenoid lock to the negative terminal of the 12V power supply.
