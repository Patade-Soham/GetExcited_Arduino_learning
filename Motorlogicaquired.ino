int ena = 6;
int in1=12;
int in2=11;
int enb = 3;
int in3=10;
int in4=9;
char command;


void setup() {
  Serial.begin(9600);
  pinMode(ena,OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(enb,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  

}

void loop() {
  Serial.println('which command do you want to give');
  command=Serial.read();
  if (command=='f'){
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    digitalWrite(in4,LOW);
    digitalWrite(in3,HIGH);
    analogWrite(ena,200);
    analogWrite(enb,200);
    delay(3000);
  }
  else if (command=='s'){
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
    digitalWrite(in3,LOW);
    digitalWrite(in4,LOW);
    delay(2000);
    }
  else if (command=='b'){


    digitalWrite(in2,HIGH);
    digitalWrite(in1,LOW);
    digitalWrite(in4,HIGH);
    digitalWrite(in3,LOW);
    delay(3000);
  }
  else if(command=='r'){
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    digitalWrite(in4,LOW);
    digitalWrite(in3,LOW);
    analogWrite(ena,200);
    analogWrite(enb,200);
    delay(500);

  }
  else if(command=='l'){
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
    digitalWrite(in4,LOW);
    digitalWrite(in3,HIGH);
    analogWrite(ena,200);
    analogWrite(enb,200);
    delay(500);
  }
  else {
    Serial.println('Invalid Choice');
  }



  

}
