#define PWM_A 0
#define A1 1
#define A2 2

#define PWM_B 6
#define B1 7
#define B2 8

#define Left 0
#define Right 1

// LED設定
#define LeftLED 11
#define RightLED 10
#define BoardLED 25

void drive_A(int v) {
  if (v > 0) {
    v = min(v, 255);
    digitalWrite(A1, HIGH);
    digitalWrite(A2, LOW);
  } else {
    v = max(v, -255);
    digitalWrite(A1, LOW);
    digitalWrite(A2, HIGH);
  }
  analogWrite(PWM_A, abs(v));
}

void drive_B(int v) {
  if (v > 0) {
    v = min(v, 255);
    digitalWrite(B1, HIGH);
    digitalWrite(B2, LOW);
  } else {
    v = max(v, -255);
    digitalWrite(B1, LOW);
    digitalWrite(B2, HIGH);
  }
  analogWrite(PWM_B, abs(v));
}

void setup() {
  pinMode(BoardLED, OUTPUT);
  digitalWrite(BoardLED, HIGH);
  //モーターのピンを出力に変更
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(PWM_A, OUTPUT);
  pinMode(B1, OUTPUT);
  pinMode(B2, OUTPUT);
  pinMode(PWM_B, OUTPUT);
}

void loop() {
  // モーターを動かす
  drive_A(150);
  drive_B(150);
  delay(1000);
  drive_A(-150);
  drive_B(-150);
  delay(1000);
}
