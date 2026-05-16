const int ledPin_R = 2;
const int ledPin_G = 16;
const int ledPin_Y = 5;
unsigned long previousMillis = 0;
const long interval = 500; // 1Hz闪烁：周期1000ms，高低电平各500ms

void setup() {
  pinMode(ledPin_R, OUTPUT);
  pinMode(ledPin_G, OUTPUT);
  pinMode(ledPin_Y, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    digitalWrite(ledPin_R, !digitalRead(ledPin_R)); 
    digitalWrite(ledPin_G, !digitalRead(ledPin_G));
    digitalWrite(ledPin_Y, !digitalRead(ledPin_Y));
    // 翻转LED状态
  }
}