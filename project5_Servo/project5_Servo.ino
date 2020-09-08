#include <Servo.h>

Servo myServo;

int const potPin = A0;
const int buttonPin = 2;
int potVal;
int angle;
int dirr = 0; // 0 = right, 1 = left

int state = 0; // 0 = manual, 1 = auto

int curr_button = 0;
int prev_button = 0;

void setup() {
  myServo.attach(9);

  pinMode(2, INPUT);
  
  Serial.begin(9600);
}

void loop() {

  curr_button = digitalRead(buttonPin);
  if(curr_button == 1 && prev_button == 0){
    state = !state;
    Serial.print("In state: ");
    Serial.println(state);
  }
  prev_button = curr_button;

  
  switch(state){
    case 0:
    potVal = analogRead(potPin);
    
    angle = map(potVal, 0, 1023, 0, 179);
    break;
    case 1:
      if(dirr == 0){
        angle++;
        if(angle >= 178){
          dirr = 1;
        }
      }else if(dirr == 1){
        angle--;
        if(angle <= 1){
          dirr = 0;
        }
      }else{
        Serial.print("Error: angle is out of bounds, curr angle: ");
        Serial.println(angle);
      }
    break;
  }
  Serial.print("potVal: \t");
  Serial.print(potVal);
  Serial.print("\t| angle: ");
  Serial.println(angle);
  
  myServo.write(angle);
  delay(15);
}
