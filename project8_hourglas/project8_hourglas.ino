const int switchPin = 13;

unsigned long prev_time = 0;
int switchState = 0;
int prevSwitchState = 0;

int led = 3;
int blinking = 0;
boolean toogle = false;

int state = 0; // 0 = counting, 1 = done counting

long interval = 60000;
long short_interval = 1000;

void setup() {
  // put your setup code here, to run once:
  for(int i = led; i < 9; i++){
    pinMode(i, OUTPUT);
  }

  pinMode(switchPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentTime= millis();

  switch(state){
    case(0) :
      if(currentTime - prev_time > interval && led != 9){
        prev_time = currentTime;
        digitalWrite(led, HIGH);
        led++;
    
        if(led == 9){
          state = 1;
        }
      }
    break;
    case(1) :
      if(currentTime - prev_time > short_interval){
        prev_time = currentTime;
        if(blinking == 0){
//          digitalWrite(3, LOW);
//          digitalWrite(4, HIGH);
//          digitalWrite(5, LOW);
//          digitalWrite(6, HIGH);
//          digitalWrite(7, LOW);
//          digitalWrite(8, HIGH);
          toogle = true;
          for(int i = 3; i < 9; i++){
            digitalWrite(i, toogle);
            toogle = !toogle;
          }
          blinking = 1;
        }else{
//          digitalWrite(8, LOW);
//          digitalWrite(7, HIGH);
//          digitalWrite(6, LOW);
//          digitalWrite(5, HIGH);
//          digitalWrite(4, LOW);
//          digitalWrite(3, HIGH);
          toogle = false;
          for(int i = 3; i < 9; i++){
              digitalWrite(i, toogle);
              toogle = !toogle;
          }
          blinking = 0;
        }
      }
  }

  switchState = digitalRead(switchPin);
      
      if(switchState != prevSwitchState){
        for(int i = led; i > 2; i--){
          digitalWrite(i, LOW);
        }
    
        led = 3;
        state = 0;
        prev_time = currentTime;
      }
      prevSwitchState = switchState;
}
