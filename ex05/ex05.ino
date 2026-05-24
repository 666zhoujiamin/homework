#define TOUCH_PIN 4
#define LED_PIN 16
#define THRESHOLD 500
const unsigned long debounceDelay=50;

// PWM呼吸灯参数
const int freq = 5000;
const int resolution = 8;

// 档位相关 1慢 2中 3快
int speedLevel = 1;
bool lastTouch=false;
unsigned long lastTriggerTime=0;
int touchValue;

// 触摸中断函数
void gotTouch() {
  touchValue=touchRead(TOUCH_PIN);
  bool currentTouch=(touchValue<THRESHOLD);
  unsigned long now=millis();
  
  if(currentTouch&&!lastTouch&&(now-lastTriggerTime)>debounceDelay){
    // 循环切换档位 1->2->3->1
    speedLevel++;
    if(speedLevel > 3){
      speedLevel = 1;
    }
    Serial.print("切换至档位：");
    Serial.println(speedLevel);
    lastTriggerTime=now;
  }
  lastTouch=currentTouch;
}

void setup() {
  Serial.begin(9600);
  delay(1000);
  // 绑定PWM输出
  ledcAttach(LED_PIN, freq, resolution);
  // 绑定触摸中断
  touchAttachInterrupt(TOUCH_PIN, gotTouch, THRESHOLD);
  Serial.println("初始化完成，当前档位1");
}

void loop() {
  // 串口打印触摸数值
  touchValue = touchRead(TOUCH_PIN);
  Serial.print("Touch Value: ");
  Serial.println(touchValue);

  // 根据档位设定呼吸延时，控制速度
  int breathDelay;
  switch(speedLevel){
    case 1: breathDelay = 30; break;  // 慢速
    case 2: breathDelay = 15; break;  // 中速
    case 3: breathDelay = 5;  break;  // 快速
    default: breathDelay = 30;
  }

  // 呼吸渐亮
  for(int i=0;i<=255;i++){
    ledcWrite(LED_PIN,i);
    delay(breathDelay);
  }
  // 呼吸渐暗
  for(int i=255;i>=0;i--){
    ledcWrite(LED_PIN,i);
    delay(breathDelay);
  }
}