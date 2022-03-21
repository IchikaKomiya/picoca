#define LeftLED 11
#define RightLED 10
#define echoPin 15 // Echo Pin
#define trigPin 14 // Trigger Pin

// 音速の設定
int V = 340;

void sendTrigger(){
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
}

// 距離センサから距離を読み取る（単位:cm）
int getDepth(){
  sendTrigger();
  while(!digitalRead(echoPin)){ 
  }
  unsigned long t1 = micros();

  while(digitalRead(echoPin)){
  }
  unsigned long t2 = micros();
  unsigned long t = t2 - t1;
  return V * t /20000;
}

void setup() {
  // Raspberry Pi Pico内蔵LEDピンを出力に設定して点灯
  pinMode(25, OUTPUT);
  digitalWrite(25, HIGH);
  // LEDに接続されているピンを出力に設定
  pinMode(LeftLED, OUTPUT);
  pinMode(RightLED, OUTPUT);
  digitalWrite(LeftLED, HIGH);
  digitalWrite(RightLED, HIGH);

  Serial.begin(9600); // PCとシリアル接続を開始
  while (!Serial);    // PCとシリアル接続されるまで待機
  // 距離センサ用にピンの入出力を設定
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  // PCに"Start Pico!"を書き込む
  Serial.println("Start Pico!");
}

void loop() {
  int depth = 0;
  depth = getDepth();

  Serial.print(depth);
  Serial.println("cm");

  // もし距離センサが20cmより小さかったらLEDを点灯させる
  if(depth < 20){
    digitalWrite(LeftLED, HIGH);
    digitalWrite(RightLED, HIGH);
  }else{
    digitalWrite(LeftLED, LOW);
    digitalWrite(RightLED, LOW);
  }
  delay(500);
}
