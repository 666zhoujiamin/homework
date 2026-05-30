#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "OPPO Reno11 5G";
const char* password = "20060915zjm";
const int LED_PIN = 2;

WebServer server(80);
int targetBrightness = 0;   // 目标亮度（来自网页滑块）
int currentBrightness = 0;  // 当前实际亮度（平滑变化中）
unsigned long lastUpdate = 0;
const long updateInterval = 20; // 每20ms更新一次亮度，足够平滑

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
  targetBrightness = server.arg("b").toInt();
  targetBrightness = constrain(targetBrightness, 0, 255);
  server.send(200, "text/plain", "OK");
}

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  // 初始关灯
  analogWrite(LED_PIN, 0);

  WiFi.begin(ssid, password);
  Serial.print("连接WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
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

  unsigned long now = millis();
  if (now - lastUpdate >= updateInterval) {
    lastUpdate = now;

    // 用sin函数做平滑过渡，让亮度变化没有顿挫感
    float diff = targetBrightness - currentBrightness;
    if (abs(diff) > 0) {
      // 用sin的0~π区间做缓变，速度柔和，不会突然跳变
      float t = 1.0 - abs(diff) / 255.0; // 距离目标越近，变化越慢
      float smoothFactor = sin(t * PI / 2); // sin(0~π/2)是0→1的缓升曲线
      int step = diff * smoothFactor * 0.1; // 步长系数，0.1控制平滑度
      currentBrightness += step;
      currentBrightness = constrain(currentBrightness, 0, 255);
    }

    // 输出PWM
    analogWrite(LED_PIN, currentBrightness);
  }
}