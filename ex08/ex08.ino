#include <WiFi.h>
#include <WebServer.h>

// WIFI 设置
const char* ssid = "OPPO Reno11 5G";
const char* password = "20060915zjm";

WebServer server(80);

#define TOUCH_PIN 4
#define LED_PIN 2
#define THRESHOLD 500

bool isArmed = false;    // 布防状态
bool isAlarming = false; // 报警锁定状态

void gotTouch() {
  if (isArmed) {
    isAlarming = true;
  }
}

const char HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html>
<head>
<meta charset="UTF-8">
<title>安防主机</title>
</head>
<body style="text-align:center; font-size:24px;">
  <h2>ESP32 安防报警</h2>
  <button onclick="fetch('/arm')" style="padding:10px 20px; font-size:20px;">布防 Arm</button>
  <button onclick="fetch('/disarm')" style="padding:10px 20px; font-size:20px;">撤防 Disarm</button>
</body>
</html>
)rawliteral";

void handleRoot() {
  server.send(200, "text/html", HTML);
}
//布防
void handleArm() {
  isArmed = true;
  isAlarming = false;
  digitalWrite(LED_PIN, LOW);
  server.send(200, "text/plain", "Armed");
}

// 撤防
void handleDisarm() {
  isArmed = false;
  isAlarming = false;
  digitalWrite(LED_PIN, LOW);
  server.send(200, "text/plain", "Disarmed");
}

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  touchAttachInterrupt(TOUCH_PIN, gotTouch, THRESHOLD);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.println("WiFi OK");
  Serial.println("IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/arm", handleArm);
  server.on("/disarm", handleDisarm);
  server.begin();
}

void loop() {
  server.handleClient();

  if (isAlarming) {
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    delay(100);
  }

  delay(100); 
}