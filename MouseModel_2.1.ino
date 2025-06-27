#include <AFMotor.h>
#include <NewPing.h>
#include <Servo.h>


#define TRIG_PIN A0
#define ECHO_PIN A1
#define SERVO_PIN 10


#define MAX_DISTANCE 200
#define SAFE_DISTANCE 40  // Start avoiding at 40cm
#define MIN_DISTANCE 15   // Emergency stop distance
#define SCAN_INTERVAL 200 // ms between scans


#define MOTOR_SPEED 180   // Base speed (0-255)
#define TURN_DURATION 600 // ms for 90° turn
#define REVERSE_DURATION 500 // ms for backing up


AF_DCMotor leftFront(1, MOTOR12_64KHZ);
AF_DCMotor leftRear(2, MOTOR12_64KHZ);
AF_DCMotor rightFront(3, MOTOR34_64KHZ);
AF_DCMotor rightRear(4, MOTOR34_64KHZ);

Servo headServo;
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);


unsigned long lastScanTime = 0;
int currentDistance = 0;
bool obstacleDetected = false;

void setup() {
  Serial.begin(9600);
  headServo.attach(SERVO_PIN);
  centerHead();
  stopMotors();
  delay(1000); 
  Serial.println("4WD Obstacle Avoidance Robot Ready");
}

void loop() {
  currentDistance = scanForward();
  
  if (currentDistance <= MIN_DISTANCE) {
    emergencyStop();
  } else if (currentDistance <= SAFE_DISTANCE) {
    avoidObstacle();
  } else {
    moveForward();
  }
  
  printSensorData();
}


void moveForward() {
  setLeftMotors(FORWARD, MOTOR_SPEED);
  setRightMotors(FORWARD, MOTOR_SPEED);
  obstacleDetected = false;
}

void stopMotors() {
  setLeftMotors(RELEASE, 0);
  setRightMotors(RELEASE, 0);
}

void emergencyStop() {
  stopMotors();
  delay(200);
  moveBackward();
  delay(REVERSE_DURATION);
  stopMotors();
  avoidObstacle();
}

void moveBackward() {
  setLeftMotors(BACKWARD, MOTOR_SPEED);
  setRightMotors(BACKWARD, MOTOR_SPEED);
}


void turnRight() {
  setLeftMotors(FORWARD, MOTOR_SPEED);
  setRightMotors(BACKWARD, MOTOR_SPEED);
  delay(TURN_DURATION);
  stopMotors();
}

void turnLeft() {
  setLeftMotors(BACKWARD, MOTOR_SPEED);
  setRightMotors(FORWARD, MOTOR_SPEED);
  delay(TURN_DURATION);
  stopMotors();
}

void setLeftMotors(uint8_t dir, int speed) {
  leftFront.setSpeed(speed);
  leftRear.setSpeed(speed);
  leftFront.run(dir);
  leftRear.run(dir);
}

void setRightMotors(uint8_t dir, int speed) {
  rightFront.setSpeed(speed);
  rightRear.setSpeed(speed);
  rightFront.run(dir);
  rightRear.run(dir);
}


void avoidObstacle() {
  stopMotors();
  
  int rightDist = scanRight();
  int leftDist = scanLeft();
  
  if (rightDist > leftDist && rightDist > SAFE_DISTANCE) {
    turnRight();
  } else if (leftDist > SAFE_DISTANCE) {
    turnLeft();
  } else {
    moveBackward();
    delay(REVERSE_DURATION * 2);
    avoidObstacle();
    return;
  }
  
  delay(200);
  moveForward();
}


int scanForward() {
  if (millis() - lastScanTime > SCAN_INTERVAL) {
    currentDistance = getFilteredDistance();
    lastScanTime = millis();
  }
  return currentDistance;
}

int scanRight() {
  headServo.write(45);
  delay(300);
  int distance = getFilteredDistance();
  centerHead();
  return distance;
}

int scanLeft() {
  headServo.write(135);
  delay(300);
  int distance = getFilteredDistance();
  centerHead();
  return distance;
}

int getFilteredDistance() {
  int distance = sonar.ping_cm();
  return (distance == 0) ? MAX_DISTANCE : distance;
}

void centerHead() {
  headServo.write(90);
  delay(200);
}


void printSensorData() {
  static unsigned long lastPrint = 0;
  if (millis() - lastPrint > 500) {
    Serial.print("Distance: ");
    Serial.print(currentDistance);
    Serial.print("cm | Action: ");
    Serial.println(obstacleDetected ? "Avoiding" : "Moving");
    lastPrint = millis();
  }
}
