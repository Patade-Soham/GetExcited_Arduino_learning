int in1 = 6;
int in2 = 7;
int in3 = 10;
int in4 = 11;
int ena = 5;
int enb = 9;
char Command;

void setup() {
  Serial.begin(9600);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);
  Serial.println("Enter command: f (forward), b (backward), s (stop)");
}

void loop() {
  if (Serial.available() > 0) {
    Command = Serial.read();

    if (Command == 'f') {
      // Forward
      digitalWrite(in1, HIGH);
      digitalWrite(in4, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      analogWrite(ena, 255);
      analogWrite(enb, 255);
      delay(3000);
    }
    else if (Command == 'b') {
      // Backward
      digitalWrite(in1, LOW);
      digitalWrite(in4, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, HIGH);
      analogWrite(ena, 255);
      analogWrite(enb, 255);
      delay(3000);
    }
    else if (Command == 's') {
      // Stop
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
      analogWrite(ena, 0);
      analogWrite(enb, 0);
      delay(2000);
    }
    else {
      Serial.println("Invalid Choice");
    }
  }
}
