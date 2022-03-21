#define LeftLED 11
#define RightLED 10

void setup() {
  // Raspberry Pi Pico内蔵LEDピンを出力に設定
  pinMode(25, OUTPUT);
  // LEDに接続されているピンを出力に設定
  pinMode(LeftLED, OUTPUT);
  pinMode(RightLED, OUTPUT);

  // LEDを点灯させる
  digitalWrite(LeftLED, HIGH);
  digitalWrite(RightLED, HIGH);
  digitalWrite(25, HIGH);
  // 1秒待機(1000m秒)
  delay(1000);
}

void loop() {
  // LEDを5回点滅させる
  for(int i=0; i<5; i++){
    // LEDを点灯させる
    digitalWrite(LeftLED, HIGH);
    digitalWrite(RightLED, HIGH);
    delay(500);
    // LEDを消灯
    digitalWrite(LeftLED, LOW);
    digitalWrite(RightLED, LOW);
    delay(500);
  } 
  // 2秒待つ
  delay(2000);
}
