int relaisPin = 16;
void setup() {
  // put your setup code here, to run once:
  pinMode(relaisPin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(500);
  digitalWrite(relaisPin, HIGH);
  delay(1000);
  digitalWrite(relaisPin, LOW);
}
