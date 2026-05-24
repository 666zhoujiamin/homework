#include <WiFi.h>
#include <WebServer.h>

// WiFi配置
const char* ssid = "OPPO Reno11 5G";
const char* password = "20060915zjm";

// 触摸引脚
#define TOUCH_PIN 4
#define THRESHOLD 500

WebServer server(80);

// 读取触摸值并提供给网页
void handleData() {
  int touchValue = touchRead(TOUCH_PIN);
  server.send(200, "text/plain", String(touchValue));
}

// 仪表盘网页（带AJAX实时刷新）
void handleRoot() {
  String html = R"rawliteral(
<!DOCTYPE html>
<html lang="zh-CN">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>ESP32 触摸传感器仪表盘</title>
  <style>
    body { font-family: Arial; text-align: center; margin-top: 80px; background-color: #f0f2f5; }
    .value-box { font-size: 80px; font-weight: bold; color: #2c3e50; margin: 30px 0; }
    .label { font-size: 20px; color: #7f8c8d; }
  </style>
</head>
<body>
  <h1>触摸传感器实时监控</h1>
  <div class="label">当前触摸值</div>
  <div class="value-box" id="touchValue">--</div>

  <script>
    // 每100ms拉取一次数据
    function updateValue() {
      fetch('/data')
        .then(res => res.text())
        .then(val => {
          document.getElementById('touchValue').textContent = val;
        });
    }
    setInterval(updateValue, 100);
  </script>
</body>
</html>
)rawliteral";
  server.send(200, "text/html; charset=UTF-8", html);
}

void setup() {
  Serial.begin(9600);
  delay(1000);

  // 连接WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi连接成功！");
  Serial.print("访问地址: http://");
  Serial.println(WiFi.localIP());

  // 路由绑定
  server.on("/", handleRoot);
  server.on("/data", handleData);
  server.begin();
}

void loop() {
  server.handleClient();
  // 串口也同步打印触摸值，方便调试
  Serial.print("Touch Value: ");
  Serial.println(touchRead(TOUCH_PIN));
  delay(100);
}