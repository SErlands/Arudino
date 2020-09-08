
#include <SPI.h>
 //MOSI: pin 11 don't use for anything
 //MISO: pin 12 to Q7 of last register
 //SCK:  pin 13 to CP
 // PL:  pin 2
 byte shift_1, shift_2;
 
void setup(){
  Serial.begin(9600);
  SPI.setClockDivider(SPI_CLOCK_DIV128);
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);
  SPI.begin();
  
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
}


void loop(){
  digitalWrite(2, LOW);
  delay(1);
  digitalWrite(2,HIGH);
  shift_2 = SPI.transfer(0x00);
  shift_1 = SPI.transfer(0x00);
  Serial.print("Register 1 = ");
  Serial.println(shift_1,BIN);
  Serial.print("Register 2 = ");
  Serial.println(shift_2,BIN);  
  delay(1000);
}
