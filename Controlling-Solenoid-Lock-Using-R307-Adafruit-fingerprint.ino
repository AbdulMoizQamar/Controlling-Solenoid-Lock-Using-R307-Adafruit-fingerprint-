#include <Adafruit_Fingerprint.h>
#include <HardwareSerial.h>

#define FINGERPRINT_SENSOR_RX 16 // Pin connected to fingerprint sensor TX (Green wire)
#define FINGERPRINT_SENSOR_TX 17 // Pin connected to fingerprint sensor RX (White wire)
#define SOLENOID_PIN 12 // Change to GPIO pin 12

HardwareSerial mySerial(1);

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup() {
  Serial.begin(9600);
  while (!Serial);
  delay(100);
  Serial.println("\n\nAdafruit finger detect test");

  mySerial.begin(57600, SERIAL_8N1, FINGERPRINT_SENSOR_RX, FINGERPRINT_SENSOR_TX);

  finger.begin(57600);
  delay(5);
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }

  finger.getTemplateCount();
  if (finger.templateCount == 0) {
    Serial.println("Sensor doesn't contain any fingerprint data. Please run the 'enroll' example.");
  } else {
    Serial.println("Waiting for valid finger...");
    Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  }

  pinMode(SOLENOID_PIN, OUTPUT);
}

void loop() {
  if (getFingerprintID() == 1) {
    unlockSolenoidLock();
    delay(5000); // Unlock duration
    lockSolenoidLock();
  }
  delay(50);
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK) return p;

  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
    return 1;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return 0;
  } else {
    Serial.println("Unknown error");
    return p;
  }
}

void unlockSolenoidLock() {
  digitalWrite(SOLENOID_PIN, HIGH); // Activate the relay to unlock
  Serial.println("Solenoid lock unlocked");
}

void lockSolenoidLock() {
  digitalWrite(SOLENOID_PIN, LOW); // Deactivate the relay to lock
  Serial.println("Solenoid lock locked");
}
