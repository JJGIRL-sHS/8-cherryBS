#include <ArduinoJson.h>
#include <Servo.h>

const int lightPin = A0;
const int servoPin = 9;

unsigned long lastSentTime = 0;
const int interval = 1000;

Servo myServo;

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(50);

  pinMode(lightPin, INPUT);

  myServo.attach(servoPin);

  myServo.write(90);
}

void loop() {
  
  if (Serial.available() > 0) {
    JsonDocument doc;

    DeserializationError error = deserializeJson(doc, Serial);

    if (!error) {
      // TODO:

    }
  }

  unsigned long currentTime = millis();
  if (currentTime - lastSentTime >= interval) {
    int value = analogRead(lightPin);

    JsonDocument doc;

    // TODO:

    serializeJson(doc, Serial);
    Serial.println();

    lastSentTime = currentTime;
  }
}
