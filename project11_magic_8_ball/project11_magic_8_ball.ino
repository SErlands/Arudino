#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int leds[] = {8,9,10};

const int switchPin = 6;
int switchState = 0;
int prevSwitchState = 0;
int reply, prev_reply;
int state = 0;

unsigned long prev_time = 0;
long led_time = 1000;
long reset_time = 5000;
long scroll_time = 750;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  pinMode(switchPin, INPUT);
  

  pinMode(leds[0], OUTPUT);
  pinMode(leds[1], OUTPUT);
  pinMode(leds[2], OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentTime= millis();
  switchState = digitalRead(switchPin);

  switch(state){
    case 0: //  Wating for action
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Drink chooser 3000x");
      lcd.setCursor(0,1);
      lcd.print("   Press the button to decide!");
      state = 1;
      prev_time = currentTime;
      break;
    case 1: // Wait for button press
      if(currentTime - prev_time > scroll_time){
        lcd.scrollDisplayLeft();
        prev_time = currentTime;
      }     
      if(switchState == 1 && prevSwitchState == 0){
        state = 2;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Calculating...");
        lcd.setCursor(0,1);
        lcd.print("");
        prev_time = currentTime;
      }
      break;
    case 2: // Calculating shinadigans
      digitalWrite(leds[0], HIGH);
      if(currentTime - prev_time > led_time*3){
        state = 3;
        print_drink();
        prev_time = currentTime;
      }else if(currentTime - prev_time > led_time*2){
        digitalWrite(leds[2], HIGH);
      }else if(currentTime - prev_time > led_time*1){
        digitalWrite(leds[1], HIGH);
      }
      break;
      
    case 3: // Wait for reset
      
        if(currentTime - prev_time > reset_time){
          state = 0;
          digitalWrite(leds[0], LOW);
          digitalWrite(leds[1], LOW);
          digitalWrite(leds[2], LOW);
          prev_time = currentTime;
        }else if(switchState == 1 && prevSwitchState == 0){
          state = 0;
          digitalWrite(leds[0], LOW);
          digitalWrite(leds[1], LOW);
          digitalWrite(leds[2], LOW);
          prev_time = currentTime;
        }
        break;
    }
  
  prevSwitchState = switchState;
}

void print_drink(){
  reply = random(8);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("You should drink");
  lcd.setCursor(0,1);
  switch(reply){
    case 0:
      lcd.print("a beer");
      break;
    case 1:
      lcd.print("a cider");
      break;
    case 2:
      lcd.print("a shot of Raki");
      break;
    case 3:
      lcd.print("a long drink");
      break;
    case 4:
      lcd.print("a shot of vodka");
      break;
    case 5:
      lcd.print("water, yes water");
      break;
    case 6:
      lcd.print("a shot fireball");
      break;
    case 7:
      lcd.print("a shot sourz");
      break;
    }
}
