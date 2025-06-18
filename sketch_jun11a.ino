int ledpin=11;
int ledpin1 =13;
int ledpin2=12;
int i ;
int ans;
void setup() {
  pinMode(ledpin, OUTPUT);
  pinMode(ledpin1, OUTPUT);
  pinMode(ledpin2, OUTPUT);

 
  Serial.begin(9600);
  Serial.println("How many times led should blink");
  while (Serial.available()==0){}
  ans=Serial.parseInt();

}

void loop() {
  for(i=0;i<ans;i++){
  Serial.print("red");
  Serial.println(i);
  digitalWrite(ledpin, HIGH);
  delay(500);
  digitalWrite(ledpin, LOW);
  delay(500);
  }
  for(i=0;i<ans-1;i++){
  Serial.print("yellow");
  Serial.println(i);
  digitalWrite(ledpin1, HIGH);
  delay(500);
  digitalWrite(ledpin1, LOW);
  delay(500);
  }
for(i=0;i<ans-2;i++){
  Serial.print("green");
  Serial.println(i);
  
  digitalWrite(ledpin2, HIGH);
  delay(500);
  digitalWrite(ledpin2, LOW);
  delay(500);
  
 }


}
