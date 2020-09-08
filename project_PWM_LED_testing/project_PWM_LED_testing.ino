const int greenLEDPin = 9;
const int blueLEDPin = 10;
const int redLEDPin = 11;
const int buttonPin = 2;

int redValue = 0;
int blueValue = 0;
int greenValue = 0;

int state = 0; // 0 = red, 1 = green, 2 = blue, 3 = white

int curr_button = 0;
int prev_button = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Begin communication at 9600 bps

  pinMode(greenLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);

  pinMode(2, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Read the push button
  curr_button = digitalRead(buttonPin);

  // Edge detection on the push button
  if(curr_button == 1 && prev_button == 0){
    state++;
    if(state >= 4){
      state = 0;
    }
    Serial.print("In state: ");
    Serial.println(state);
  }
  prev_button = curr_button;
  delay(10);
  if(state == 0){
    redValue++;
    greenValue = 0;
    blueValue = 0;
    if(redValue >= 256){
      redValue = 0;
    }
  }else if(state == 1){
    redValue = 0;
    greenValue = 255;
    blueValue = 0;
  }else if(state == 2){
    redValue = 0;
    greenValue = 0;
    blueValue = 255;
  }else if(state == 3){
    redValue = 255;
    greenValue = 255;
    blueValue = 255;
  }else{
    redValue = 0;
    greenValue = 0;
    blueValue = 0;
  }

  analogWrite(redLEDPin, redValue);
  analogWrite(greenLEDPin, greenValue);
  analogWrite(blueLEDPin, blueValue);
}
