

char command; 

int ena = 6;
int in1 = 12;
int in2 = 11;
int enb = 3;
int in3 = 10;
int in4 = 9;

void setup() {
  Serial.begin(9600); 
  
  pinMode(ena, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop() {
  
  if (Serial.available()) {
    command = Serial.read();

    switch (command) {
      case 'F': 
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
        analogWrite(ena, 200); 
        analogWrite(enb, 200);
        break;

      case 'B': 
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
        analogWrite(ena, 200);
        analogWrite(enb, 200);
        break;

      case 'L': 
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
        analogWrite(ena, 200);
        analogWrite(enb, 200);
        break;

      case 'R': 
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
        analogWrite(ena, 200);
        analogWrite(enb, 200);
        break;

      case 'S': 
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, LOW);
        analogWrite(ena, 0);
        analogWrite(enb, 0);
        break;
    }
  }
}
