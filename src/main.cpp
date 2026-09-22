#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define Enc_SW 4
#define Enc_DT 3
#define Enc_CLK 2

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


int Enc_Counter = 1;
int Enc_clockState = 0;
int Enc_lastClockState = 0;
unsigned long Enc_lastPress = 0;
unsigned long Duration = 0;
unsigned long TargetTime = 0;
unsigned long currentTime = 0;
unsigned long timeLeft = 0;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
delay(1500);
Serial.println("hello world");

pinMode(Enc_DT, INPUT);
pinMode(Enc_CLK, INPUT);
pinMode(Enc_SW, INPUT_PULLUP);

display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
display.clearDisplay();
display.setTextSize(5);
display.setTextColor(WHITE);
display.setCursor(40, 20);



Enc_lastClockState = digitalRead(Enc_CLK);
}

void loop() {
  // put your main code here, to run repeatedly:
  bool counterUpdate = false;

  Enc_clockState = digitalRead(Enc_CLK);
  if (Enc_clockState != Enc_lastClockState){
    if (digitalRead(Enc_DT) != Enc_clockState){
      if(Enc_Counter > 59){
        Enc_Counter = 1;
      }else {
        Enc_Counter++;
      }
      
    }else{
      if (Enc_Counter < 2){
        Enc_Counter = 60;
      }else{
        Enc_Counter--;
      }
      
    }
    counterUpdate = true;
  }

  Enc_lastClockState = Enc_clockState;

  //Serial.println(Enc_Counter);
  if (counterUpdate) {
    display.setCursor(40, 20);
    display.println(Enc_Counter);
    display.display();
    //delay(10);
    display.clearDisplay();
  }


  int Enc_butState = digitalRead(Enc_SW);
  if (Enc_butState == LOW){
    if (millis() - Enc_lastPress > 200){
      Serial.println("Button pressed!");
    }
    Enc_lastPress = millis();

    Duration = Enc_Counter * 60000;
    TargetTime = millis() + Duration;
   

    while (millis() <= TargetTime){
      currentTime = millis();
      timeLeft = TargetTime - currentTime;
      int intTimeLeft = 0;
      intTimeLeft = timeLeft/1000;
      int minutesLeft = 0;
      int secondsLeft = 0;

      minutesLeft = intTimeLeft/60;
      secondsLeft = intTimeLeft%60;

      display.setTextSize(2);

      display.setCursor(20, 20);
      //Serial.print(minutesLeft);
      display.print(minutesLeft);
      //display.display();
      //Serial.print(" : ");
      display.print(" : ");
      //display.display();
      //Serial.println(secondsLeft);
      display.println(secondsLeft);
      display.display();
      //delay(100);
      display.clearDisplay();
    }
    



  }



}
