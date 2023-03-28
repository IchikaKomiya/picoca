// LED
#define LeftLED 11
#define RightLED 10
#define BoardLED 25

// 距離センサ
#define echoPin 15 // Echo Pin
#define trigPin 14 // Trigger Pin
// 音速の設定
int V = 340;

// モーター
#define PWM_A 0
#define A1 1
#define A2 2

#define PWM_B 6
#define B1 7
#define B2 8

#define Left 0
#define Right 1

// PID定数
double K_p = 0.06;
double K_i = 0.000001;
double K_d = 1;

// 目標距離
double target_distance = 20.0;

// PID変数
double error = 0.0;
double last_error = 0.0;
double error_sum = 0.0;

// 距離センサに計測用信号を送るように命令
void sendTrigger(){
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(11);
  digitalWrite(trigPin, LOW);
}

// 距離センサから距離を読み取る（単位:cm）
int getDepth(){
  sendTrigger();

  unsigned long timeout = micros();
  while(!digitalRead(echoPin)){ 
    unsigned long timeout2 = micros() - timeout;
    if(timeout2 > 200000){
      Serial.println("Depth Sensor Timeout");
      sendTrigger();
      timeout = micros();
    }
  }
  unsigned long t1 = micros();

  while(digitalRead(echoPin)){
  }
  unsigned long t2 = micros();
  unsigned long t = t2 - t1;
  int depth = V * t / 20000;
  Serial.println(depth);
  return depth;
}

void drive_A( int v){
  if(v>0){
    v = min(v, 255);
    digitalWrite(A1, HIGH);
    digitalWrite(A2, LOW);
  }else{
    v = max(v, -255);
    digitalWrite(A1, LOW);
    digitalWrite(A2, HIGH);
  }
  analogWrite(PWM_A, abs(v));
}

void drive_B( int v){
  if(v>0){
    v = min(v, 255);
    digitalWrite(B1, HIGH);
    digitalWrite(B2, LOW);
  }else{
    v = max(v, -255);
    digitalWrite(B1, LOW);
    digitalWrite(B2, HIGH);
  }
  analogWrite(PWM_B, abs(v));
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
  //モーターのピンを出力に変更
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(PWM_A, OUTPUT);
  pinMode(B1, OUTPUT);
  pinMode(B2, OUTPUT);
  pinMode(PWM_B, OUTPUT);

  Serial.begin(9600); // PCとシリアル接続を開始
  // パソコンから外して使用するときはコメントアウト
  // while (!Serial);    // PCとシリアル接続されるまで待機
  // 距離センサ用にピンの入出力を設定
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  // PCに"Start Pico!"を書き込む
  Serial.println("Start Pico!");

}

void loop() {
  double depth = 0;
  // モーターの最大速度
  int max_speed = 255;

  // 制御周期
  unsigned long dt = 100;

  // ループ開始時刻
  unsigned long last_time = millis();

  while (true) {
    
    // 制御周期を計算
    unsigned long now = millis();
    unsigned long elapsed_time = now - last_time;

    // 制御周期がまだ経過していない場合は何もしない
    if (elapsed_time < dt) {
      delay(1);
    } else {
      // 距離センサの値を取得
      int distance = getDepth();

      // 誤差を計算
      error = target_distance - (double)distance;

      // 誤差の和を更新
      error_sum += error * elapsed_time;

      // 誤差の差分を計算
      double error_diff = (error - last_error) / elapsed_time;

      // PID制御量を計算
      double pid_output = K_p * error + K_i * error_sum + K_d * error_diff;

      // モーターの回転速度を計算
      int speed = max_speed * pid_output;
      // モーターを回す
      drive_A(speed);
      drive_B(speed);

      // 誤差の更新
      last_error = error;

      // ループ開始時刻を更新
      last_time = now;
    }
  }
}
