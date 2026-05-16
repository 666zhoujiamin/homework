// ex03 SOS闪烁（三灯同步版）
const int ledPin_R = 2;   // 红灯
const int ledPin_G = 16;  // 绿灯
const int ledPin_Y = 5;   // 黄灯

unsigned long previousMillis = 0;
int state = 0;    // 状态机：0=空闲, 1=短闪, 2=长闪, 3=结束停顿
int count = 0;    // 当前闪烁次数计数
bool ledState = LOW;

// 时间参数（符合SOS标准节奏）
const long shortOn = 200;
const long shortOff = 200;
const long longOn = 600;
const long longOff = 200;
const long sos_pause = 2000; // 避免和系统pause()重名

void setup() {
  // 初始化所有三个LED引脚为输出模式
  pinMode(ledPin_R, OUTPUT);
  pinMode(ledPin_G, OUTPUT);
  pinMode(ledPin_Y, OUTPUT);
  
  // 初始化所有LED为熄灭状态
  digitalWrite(ledPin_R, LOW);
  digitalWrite(ledPin_G, LOW);
  digitalWrite(ledPin_Y, LOW);
}

void loop() {
  unsigned long currentMillis = millis();

  switch (state) {
    // 第一阶段：3次短闪
    case 0:
      if (count < 3) {
        if (ledState == LOW && currentMillis - previousMillis >= shortOff) {
          ledState = HIGH;
          previousMillis = currentMillis;
          // 三个灯同时亮
          digitalWrite(ledPin_R, HIGH);
          digitalWrite(ledPin_G, HIGH);
          digitalWrite(ledPin_Y, HIGH);
        } 
        else if (ledState == HIGH && currentMillis - previousMillis >= shortOn) {
          ledState = LOW;
          previousMillis = currentMillis;
          // 三个灯同时灭
          digitalWrite(ledPin_R, LOW);
          digitalWrite(ledPin_G, LOW);
          digitalWrite(ledPin_Y, LOW);
          count++;
        }
      } else {
        count = 0;
        state = 1; // 切换到长闪阶段
      }
      break;

    // 第二阶段：3次长闪
    case 1:
      if (count < 3) {
        if (ledState == LOW && currentMillis - previousMillis >= longOff) {
          ledState = HIGH;
          previousMillis = currentMillis;
          // 三个灯同时亮
          digitalWrite(ledPin_R, HIGH);
          digitalWrite(ledPin_G, HIGH);
          digitalWrite(ledPin_Y, HIGH);
        } 
        else if (ledState == HIGH && currentMillis - previousMillis >= longOn) {
          ledState = LOW;
          previousMillis = currentMillis;
          // 三个灯同时灭
          digitalWrite(ledPin_R, LOW);
          digitalWrite(ledPin_G, LOW);
          digitalWrite(ledPin_Y, LOW);
          count++;
        }
      } else {
        count = 0;
        state = 2; // 切换到第二次短闪阶段
      }
      break;

    // 第三阶段：3次短闪
    case 2:
      if (count < 3) {
        if (ledState == LOW && currentMillis - previousMillis >= shortOff) {
          ledState = HIGH;
          previousMillis = currentMillis;
          // 三个灯同时亮
          digitalWrite(ledPin_R, HIGH);
          digitalWrite(ledPin_G, HIGH);
          digitalWrite(ledPin_Y, HIGH);
        } 
        else if (ledState == HIGH && currentMillis - previousMillis >= shortOn) {
          ledState = LOW;
          previousMillis = currentMillis;
          // 三个灯同时灭
          digitalWrite(ledPin_R, LOW);
          digitalWrite(ledPin_G, LOW);
          digitalWrite(ledPin_Y, LOW);
          count++;
        }
      } else {
        count = 0;
        previousMillis = currentMillis;
        state = 3; // 切换到结束停顿
      }
      break;

    // SOS结束后的长停顿
    case 3:
      if (currentMillis - previousMillis >= sos_pause) {
        previousMillis = currentMillis;
        state = 0; // 重新开始下一轮SOS
      }
      break;
  }
}