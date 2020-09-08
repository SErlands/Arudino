int sensorValue;
int sensorLow = 1023;
int sensorHigh = 0;

const int ledPin = 13;
const int setupLED = 2;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(setupLED, OUTPUT);
  
  digitalWrite(ledPin, HIGH);
  digitalWrite(setupLED, HIGH);
  while(millis() < 5000){
    sensorValue = analogRead(A0);
    if(sensorValue > sensorHigh){
      sensorHigh = sensorValue;
    }
    if(sensorValue < sensorLow){
      sensorLow = sensorValue;
    }
  }
  digitalWrite(setupLED, LOW);
  digitalWrite(ledPin, LOW);
}

void loop() {
  sensorValue = analogRead(A0);
  int pitch = map(sensorValue, sensorLow, sensorHigh, 50, 4000);
  tone(8, pitch, 20);
  delay(10);
}
