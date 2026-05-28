#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "OPPO Reno11 5G";
const char* password = "20060915zjm";
const int LED_PIN = 2;

WebServer server(80);
int brightness = 0;

String makePage() {
  String html = R"rawliteral(
<!DOCTYPE html>
<html lang="zh-CN">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>无极调光器</title>
</head>
<body style="font-family:Arial; text-align:center; margin-top:50px;">
  <h1>LED 无极调光</h1>
  <input type="range" min="0" max="255" value="0" id="slider" style="width:80%;">
  <p>亮度值: <span id="value">0</span></p >
  
  <script>
    const slider = document.getElementById('slider');
    const valueDisplay = document.getElementById('value');
    
    slider.addEventListener('input', function() {
      const val = this.value;
      valueDisplay.textContent = val;
      fetch(`/set?b=${val}`);
    });
  </script>
</body>
</html>
)rawliteral";
  return html;
}

void handleRoot() {
  server.send(200, "text/html; charset=UTF-8", makePage());
}

void handleSet() {
  brightness = server.arg("b").toInt();
  brightness = constrain(brightness, 0, 255);
  server.send(200, "text/plain", "OK");
}

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  WiFi.begin(ssid, password);
  Serial.print("连接WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n连接成功");
  Serial.print("访问地址: http://");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/set", handleSet);
  server.begin();
}

void loop() {
  server.handleClient();

  // 模拟 PWM 调光（不用 ledc）
  if (brightness > 0) {
    digitalWrite(LED_PIN, HIGH);
    delayMicroseconds(brightness * 10);
  }
  digitalWrite(LED_PIN, LOW);
  delayMicroseconds((255 - brightness) * 10);
}
