#define APWM 0
#define A1 1
#define A2 2

#define BPWM 6
#define B1 7
#define B2 8

// SR-04
#define echoPin 15 // Echo Pin
#define trigPin 14 // Trigger Pin

int V = 340;

//LED
#define LeftLED 11
#define RightLED 10
#define BoardLED 25

void setup() {
  // Setup Motor
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(APWM, OUTPUT);
  pinMode(B1, OUTPUT);
  pinMode(B2, OUTPUT);
  pinMode(BPWM, OUTPUT);

  // LED
  pinMode(BoardLED, OUTPUT);
  pinMode(LeftLED, OUTPUT);
  pinMode(RightLED, OUTPUT);
  digitalWrite(25, HIGH);
  digitalWrite(LeftLED, HIGH);
  digitalWrite(RightLED, HIGH);

  // Serial通信をする場合
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Start Pico");
}

int getDepth(){
  int depth = 0;
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(11);
  digitalWrite(trigPin, LOW);

  unsigned long timeout = micros();
  while(!digitalRead(echoPin)){ 
    unsigned long timeout2 = micros() - timeout;
    if(timeout2 > 200000){
      digitalWrite(trigPin,HIGH);
      delayMicroseconds(11);
      digitalWrite(trigPin, LOW);
      timeout = micros();
    }
  }
  unsigned long t1 = micros();
  while(digitalRead(echoPin)){
  }
  unsigned long t2 = micros();
  unsigned long t = t2 - t1;
  depth = V * t /20000;
  Serial.print(depth);
  Serial.println("cm");
  return depth;
}

void loop() {
  int depth;
  depth = getDepth();

  if(depth > 20){
    digitalWrite(A1, HIGH);
    digitalWrite(A2, LOW);
    analogWrite(APWM, 50);
    digitalWrite(B1, HIGH);
    digitalWrite(B2, LOW);
    analogWrite(BPWM, 100);
  }else{
    digitalWrite(A1, LOW);
    digitalWrite(A2, HIGH);
    analogWrite(APWM, 100);
    digitalWrite(B1, LOW);
    digitalWrite(B2, HIGH);
    analogWrite(BPWM, 50);
  }
  delay(500);
}
