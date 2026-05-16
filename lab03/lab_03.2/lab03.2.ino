// 定义LED引脚
const int ledPin_R = 2;  
const int ledPin_G = 16;
const int ledPin_Y = 5; 

// 设置PWM属性
const int freq = 5000;          // 频率 5000Hz
const int resolution = 8;       // 分辨率 8位 (0-255)

void setup() {
  Serial.begin(9600);

  // 【新版用法】直接将引脚、频率和分辨率绑定
  // 它会自动返回一个关联的通道（如果需要的话）
  ledcAttach(ledPin_R, freq, resolution);
  ledcAttach(ledPin_G, freq, resolution);
  ledcAttach(ledPin_Y, freq, resolution);
}

void loop() {
  // 红到绿
  for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){   
    ledcWrite(ledPin_R, 255-dutyCycle);
    ledcWrite(ledPin_G, dutyCycle);   
    ledcWrite(ledPin_Y, 0);
    delay(10);
  }

  // 绿到黄
  for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){   
    ledcWrite(ledPin_R, 0);
    ledcWrite(ledPin_G, 255-dutyCycle);   
    ledcWrite(ledPin_Y, dutyCycle);
    delay(10);
  }

   // 黄到红
    for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){   
    ledcWrite(ledPin_R, dutyCycle);
    ledcWrite(ledPin_G, 0);   
    ledcWrite(ledPin_Y, 255-dutyCycle);
    delay(10);
    }
  
  Serial.println("Breathing cycle completed");
}
