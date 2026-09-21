#include <Arduino.h>
#define Enc_SW 4
#define Enc_DT 3
#define Enc_CLK 2

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


Enc_lastClockState = digitalRead(Enc_CLK);
}

void loop() {
  // put your main code here, to run repeatedly:

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
    
  }

  Enc_lastClockState = Enc_clockState;

  Serial.println(Enc_Counter);

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

      Serial.print(minutesLeft);
      Serial.print(" : ");
      Serial.println(secondsLeft);
      Serial.println("YAYAYYAY WE DID IT!");
    }
    



  }



}
