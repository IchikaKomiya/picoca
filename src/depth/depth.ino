#define LeftLED 11
#define RightLED 10
#define BoardLED 25
#define echoPin 15  // Echo Pin
#define trigPin 14  // Trigger Pin

// 音速の設定
int V = 340;

// 距離センサに計測用信号を送るように命令
void sendTrigger() {
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(11);
  digitalWrite(trigPin, LOW);
}

// 距離センサから距離を読み取る（単位:cm）
int getDepth() {
  sendTrigger();

  unsigned long timeout = micros();
  while (!digitalRead(echoPin)) {
    unsigned long timeout2 = micros() - timeout;
    if (timeout2 > 200000) {
      sendTrigger();
      timeout = micros();
    }
  }
  unsigned long t1 = micros();
  while (digitalRead(echoPin)) {
  }
  unsigned long t2 = micros();
  unsigned long t = t2 - t1;
  return V * t / 20000;
}

void setup() {
  // Raspberry Pi Pico内蔵LEDピンを出力に設定して点灯
  pinMode(BoardLED, OUTPUT);
  digitalWrite(BoardLED, HIGH);
  // LEDに接続されているピンを出力に設定
  pinMode(LeftLED, OUTPUT);
  pinMode(RightLED, OUTPUT);
  digitalWrite(LeftLED, HIGH);
  digitalWrite(RightLED, HIGH);

  Serial.begin(9600);  // PCとシリアル接続を開始
  /* 
   * USBを外し電池で扱う場合は、下記のwhile文をコメントアウト 
   */
  while (!Serial)
    ;  // PCとシリアル接続されるまで待機

  // 距離センサ用にピンの入出力を設定
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
}

void loop() {
  int depth = 0;
  while (true) {
    // 距離センサの値を取得する
    depth = getDepth();

    Serial.print(depth);
    Serial.println("cm");

    // もし距離センサが20cmより小さかったらLEDを点灯させる
    if (depth < 20) {
      digitalWrite(LeftLED, HIGH);
      digitalWrite(RightLED, HIGH);
      digitalWrite(BoardLED, HIGH);
    } else {
      digitalWrite(LeftLED, LOW);
      digitalWrite(RightLED, LOW);
      digitalWrite(BoardLED, LOW);
    }
    // 0.5秒待つ
    delay(500);
  }
}
