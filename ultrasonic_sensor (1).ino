#define echoPin 13 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 12 //attach pin D3 Arduino to pin Trig of HC-SR04
int relaisPin = 14;

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT  
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  pinMode(relaisPin,OUTPUT);
}
void loop() {
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(500); // geef data ongeveer elke 500 ms
  
  if (distance>20) {
    
    // opendraaien
    digitalWrite(relaisPin, HIGH);
    delay(1000);
    digitalWrite(relaisPin, LOW);
    // 5s vullen
    delay(5000);
    // dichtdraaien
    digitalWrite(relaisPin, HIGH);
    delay(1000);
    digitalWrite(relaisPin, LOW);
  }
  else {
    digitalWrite(relaisPin, LOW);
  }
}
