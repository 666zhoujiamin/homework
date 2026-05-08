const int ledPin_G = 2;
const int ledPin_R = 16;
const int ledPin_Y = 5;

void setup() {
  // 初始化串口通信，设置波特率为115200
  Serial.begin(9600);
  // 将LED引脚设置为输出模式
  pinMode(ledPin_G, OUTPUT);
  pinMode(ledPin_R, OUTPUT);
  pinMode(ledPin_Y, OUTPUT);
}
void loop() {
// S: 短闪3次
for(int i=0; i<3; i++) { digitalWrite(ledPin_G, HIGH); delay(200); digitalWrite(ledPin_G, LOW); delay(200); }
delay(500); // 字母间隔
// O: 长闪3次
for(int i=0; i<3; i++) { digitalWrite(ledPin_R, HIGH); delay(600); digitalWrite(ledPin_R, LOW); delay(200); }
delay(500);
// S: 短闪3次
for(int i=0; i<3; i++) { digitalWrite(ledPin_Y, HIGH); delay(200); digitalWrite(ledPin_Y, LOW); delay(200); }
delay(2000); // 单词间隔
}