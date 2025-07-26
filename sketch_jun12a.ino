int red=11;
int yel=9;
int grn=10;



void setup() {
 
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(9,OUTPUT);

}

void loop() {
  
  analogWrite(red,102);
  delay(500);
  analogWrite(red,0);

  analogWrite(red,200);
  delay(500);
  analogWrite(red,0);

  analogWrite(yel,102);
  delay(500);
  analogWrite(yel,0);

  analogWrite(grn,102);
  delay(500);
  analogWrite(grn,0);
  


}
