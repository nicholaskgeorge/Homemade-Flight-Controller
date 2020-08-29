int up = 10;
int upb = 0;
int down = 9;
int downb = 0;
int val = 0;

void setup() {
  Serial.begin(9600);
  pinMode(up, INPUT);
  pinMode(down, INPUT);
}

void loop() {
  if (Serial.available() > 0) {
    val = Serial.read();
    Serial.println(val);
  }
  delay(100);
  upb = digitalRead(up);
  downb = digitalRead(down);
  if (upb == HIGH){
    Serial.print('a');
  }
  if (downb == HIGH){
    Serial.print('b');
  }
  
}
