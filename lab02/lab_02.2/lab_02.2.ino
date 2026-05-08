// 定义LED引脚，ESP32通常板载LED连接在GPIO 2
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
  digitalWrite(ledPin_G, HIGH);  
  digitalWrite(ledPin_R, HIGH);
  digitalWrite(ledPin_Y, HIGH);
 // 点亮LED
  Serial.println("LED ON");    // 串口输出提示
  delay(1000);                 // 保持1秒（1000毫秒）
  
  digitalWrite(ledPin_G, LOW);  
  digitalWrite(ledPin_R, LOW); 
  digitalWrite(ledPin_Y, LOW);
  // 熄灭LED
  Serial.println("LED OFF");   // 串口输出提示
  delay(1000);                 // 保持1秒
}