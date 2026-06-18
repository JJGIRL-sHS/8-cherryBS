const int lightPin = A0;

void setup() {
  Serial.begin(115200);
  pinMode(lightPin, INPUT);
}

void loop() {
  int lightValue = analogRead(lightPin);
  Serial.println(lightValue);

  delay(500);
}
