#include <Servo.h>
#include <NewPing.h> 

#define left_inp1 12
#define left_inp2 8
#define left_en 9
#define right_inp1 7
#define right_inp2 4
#define right_en 3

Servo servo_pin;
Servo esc_pin;
#define echo_pin A3
#define trigger_pin A2 

const int speed = 255;

void setup() {
  pinMode(left_inp1, OUTPUT);
  pinMode(left_inp2, OUTPUT);
  pinMode(left_en, OUTPUT);
  pinMode(right_inp1, OUTPUT);
  pinMode(right_inp2, OUTPUT);
  pinMode(right_en, OUTPUT);
  esc_pin.attach(A1);
  servo_pin.attach(A0);
  pinMode(echo_pin, INPUT);
  pinMode(trigger_pin, OUTPUT);
  servo_pin.write(90);
  esc_pin.writeMicroseconds(1000);
  delay(3000);
  Serial.begin(9600);
}

void moveForward() {
  analogWrite(left_en, speed);
  analogWrite(right_en, speed);
  digitalWrite(left_inp1, HIGH);
  digitalWrite(left_inp2, LOW);
  digitalWrite(right_inp1, HIGH);
  digitalWrite(right_inp2, LOW);
  esc_pin.writeMicroseconds(1200);
}
void moveBackward() {
  analogWrite(left_en, speed);
  analogWrite(right_en, speed);
  digitalWrite(left_inp1, LOW);
  digitalWrite(left_inp2, HIGH);
  digitalWrite(right_inp1, LOW);
  digitalWrite(right_inp2, HIGH);
  for(int i=1200;i>=1000;i--){
  esc_pin.writeMicroseconds(i);
  }
}
void stop() {
  analogWrite(left_en, 0);
  analogWrite(right_en, 0);
  digitalWrite(left_inp1, HIGH);
  digitalWrite(left_inp2, LOW);
  digitalWrite(right_inp1, HIGH);
  digitalWrite(right_inp2, LOW);
  for(int j=1200;j>=1000;j--){
  esc_pin.writeMicroseconds(j);
  }
}

void left() {
  analogWrite(left_en, speed);
  analogWrite(right_en, 0);
  digitalWrite(left_inp1, HIGH);
  digitalWrite(left_inp2, LOW);
  digitalWrite(right_inp1, HIGH);
  digitalWrite(right_inp2, LOW);
  esc_pin.writeMicroseconds(1200);
}

void right() {
  analogWrite(left_en, 0);
  analogWrite(right_en, speed);
  digitalWrite(left_inp1, HIGH);
  digitalWrite(left_inp2, LOW);
  digitalWrite(right_inp1, HIGH);
  digitalWrite(right_inp2, LOW);
  esc_pin.writeMicroseconds(1200);
}

float measureDistance() {
  digitalWrite(trigger_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_pin, LOW);

  float duration = pulseIn(echo_pin, HIGH);
  float distance = (duration * 0.0343) / 2;
  return distance;
}

void loop() {
   servo_pin.write(90);
  float distance = measureDistance();
  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);
  if (distance <= 25) {
    stop();
    delay(500);
    moveBackward();
    delay(500);
    stop();
    distanceRight = lookRight();
    delay(500);
    distanceLeft = lookLeft();
    delay(500);
    if ( distanceRight>=distanceLeft) {
      right();
       servo_pin.write(90);
      delay(6000);
      stop();
    } else if(distanceLeft >=distanceRight) {
     left();
      servo_pin.write(90);
      delay(6000);
      stop();
    }else {
      return;
    }
  } else {
    moveForward();
  }
}

float lookLeft() {
  servo_pin.write(0);
  delay(100);
  float distance1 = measureDistance();
  delay(500);
  return distance1;
}

float lookRight() {
  servo_pin.write(180);
  delay(100);
  float distance2 = measureDistance();
  delay(500);
  return distance2;
}
