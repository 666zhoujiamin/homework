#define TOUCH_PIN 4
#define LED_PIN 2
#define THRESHOLD 500 // 需要根据实际测试修改此阈值

bool ledState = false;
int touchValue;
bool lastTouch=false;
unsigned long lastTriggerTime=0;
const unsigned long debounceDelay=50;
// 中断服务函数 (ISR)
void gotTouch() {
  touchValue=touchRead(TOUCH_PIN);
  bool currentTouch=(touchValue<THRESHOLD);
  unsigned long now=millis();
  if(currentTouch&&!lastTouch&&(now-lastTriggerTime)>debounceDelay){
  ledState = !ledState; 
  digitalWrite(LED_PIN, ledState); 
  Serial.println("中断");
  lastTriggerTime=now;
  }
  lastTouch=currentTouch;
}

void setup() {
  Serial.begin(9600);
  delay(1000);
  pinMode(LED_PIN, OUTPUT);
  
  // 绑定中断函数
  touchAttachInterrupt(TOUCH_PIN, gotTouch, THRESHOLD);
}

void loop() {
  // 主循环可以处理其他任务，或者置空
  // 注意：在某些ESP32核心版本中，loop中可能需要保留简单的代码以保持看门狗复位
  touchValue = touchRead(TOUCH_PIN);
  Serial.print("Touch Value: ");
  Serial.println(touchValue);
  delay(100);
}