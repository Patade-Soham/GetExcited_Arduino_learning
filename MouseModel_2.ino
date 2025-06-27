#include <AFMotor.h>  
#include <NewPing.h>
#include <Servo.h> 

#define TRIG_PIN A0 
#define ECHO_PIN A1 
#define MAX_DISTANCE 200 
#define MAX_SPEED 190
#define MAX_SPEED_OFFSET 20

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 

AF_DCMotor motor1(1, MOTOR12_64KHZ);  
AF_DCMotor motor2(2, MOTOR12_64KHZ);  
AF_DCMotor motor3(3, MOTOR34_64KHZ);  
AF_DCMotor motor4(4, MOTOR34_64KHZ);  

Servo myservo;

boolean goesForward = false;
int distance = 100;
int speedSet = 0;

void setup() {
  myservo.attach(10);
  myservo.write(90);  
  delay(1000);

  distance = readPing();
  delay(100);
}

void loop() {
  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);

  if (distance <= 30) {
    moveStop();
    delay(300);
    moveBackward();
    delay(1000);
    moveStop();
    delay(300);

    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);

    if (distanceRight >= distanceLeft) {
      turnRight();
      delay(1000);
    } else {
      turnLeft();
      delay(1000);
    }
    moveStop();
  } else {
    moveForward();
  }

  distance = readPing();
}

int readPing() {
  delay(200);
  int cm = sonar.ping_cm();
  if (cm == 0) cm = 250;
  return cm;
}

int lookRight() {
  myservo.write(30); 
  delay(500);
  int dist = readPing();
  delay(100);
  myservo.write(90);  
  return dist;
}

int lookLeft() {
  myservo.write(150);  
  delay(500);
  int dist = readPing();
  delay(100);
  myservo.write(90);  
  return dist;
}

void moveStop() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void moveForward() {
  if (!goesForward) {
    goesForward = true;
    speedSet = MAX_SPEED;

    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    motor3.setSpeed(speedSet - MAX_SPEED_OFFSET);
    motor4.setSpeed(speedSet - MAX_SPEED_OFFSET);

    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
  }
}

void moveBackward() {
  goesForward = false;
  speedSet = MAX_SPEED;

  motor1.setSpeed(speedSet);
  motor2.setSpeed(speedSet);
  motor3.setSpeed(speedSet - MAX_SPEED_OFFSET);
  motor4.setSpeed(speedSet - MAX_SPEED_OFFSET);

  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  delay(1000);
}

void turnRight() {
  goesForward = false;
  motor1.setSpeed(MAX_SPEED);
  motor2.setSpeed(MAX_SPEED);
  motor3.setSpeed(MAX_SPEED);
  motor4.setSpeed(MAX_SPEED);

  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  delay(1000);
}

void turnLeft() {
  goesForward = false;
  motor1.setSpeed(MAX_SPEED);
  motor2.setSpeed(MAX_SPEED);
  motor3.setSpeed(MAX_SPEED);
  motor4.setSpeed(MAX_SPEED);

  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  delay(1000);
}
