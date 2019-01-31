//Project 1
// Created By: Sarah Watts and Nick Straub-Deck 
//Function: When you press the button a timer will start, 
//once that time reaches 5 hours it will emit a buzzing noise

#include <Wire.h> // Library for the clock
  long timer; //Variable for the time
  const int inputPin = 7; //Button pin
  const int outputPin = 8; // Speaker pin
  int buttonState = 0; //State of button

 //Variable types found here: https://www.arduino.cc/reference/en/#functions
  bool timerState; // State of the timer function
  bool buzzerState; // State of the buzzer function. 

void setup() {
  // put your setup code here, to run once:
  //found at this link: http://docs.macetech.com/doku.php/chronodot_v2.0
  Wire.begin();
  Serial.begin(9600);
  Wire.beginTransmission(0x68); // address DS3231
  Wire.write(0x0E); // select register
  Wire.write(0b00011100); // write register bitmap, bit 7 is /EOSC
  Wire.endTransmission();

 //  Setting input put and output pin for the button and the buzzer
 pinMode(inputPin, INPUT);
 pinMode(outputPin, OUTPUT); 
}

boolean Timer() {
  ///Things go in here
  //Also found at the following link:  http://docs.macetech.com/doku.php/chronodot_v2.0
  Wire.beginTransmission(0x68); // 0x68 is DS3231 device address
  Wire.write((byte)0); // start at register 0
  Wire.endTransmission();
  Wire.requestFrom(0x68, 3); // request three bytes (seconds, minutes, hours)
  int currentSeconds = 0;
  int currentHours = 0;
  int stopTime;
  int seconds = 0;
  int hours = 0;
  for(int i; i < 1; i++)
  { 
    seconds = Wire.read(); // get seconds
    hours = Wire.read();   // get hours
    currentSeconds = (((seconds & 0b11110000)>>4)*10 + (seconds & 0b00001111)); // convert BCD to decimal
    currentHours = (((hours & 0b00100000)>>5)*20 + ((hours & 0b00010000)>>4)*10 + (hours & 0b00001111)); // convert BCD to decimal (assume 24 hour mode)
    stopTime = currentSeconds + 30;
    Serial.println("This is current Hours: "); Serial.println(currentHours); 
    Serial.println("This is current seconds: "); Serial.println(currentSeconds);
    Serial.println("This is stopTime: "); Serial.println(stopTime); 
  }
  while (currentSeconds < stopTime){
    buttonState = digitalRead(inputPin);
    while (buttonState == LOW) {
      buttonState = digitalRead(inputPin);
      seconds = Wire.read();
      hours = Wire.read();
      currentSeconds = (((seconds & 0b11110000)>>4)*10 + (seconds & 0b00001111)); 
      currentHours = (((hours & 0b00100000)>>5)*20 + ((hours & 0b00010000)>>4)*10 + (hours & 0b00001111)); 
      if (currentSeconds == stopTime || currentSeconds > stopTime); //Trying to figure out the syntax for an or http://forum.arduino.cc/index.php?topic=43582.0
          return true; //Didn't realize true was lower case syntax, man: https://forum.arduino.cc/index.php?topic=401274.0
      if (buttonState == HIGH);
          return false;
      
    }
 
        
  }
  
  
 
  delay(1000);
}


bool Buzzer() {
  ///Things go in here too 
}

void loop() {
 //Commented out to test the clock
 //Also edited from code at the following link: https://www.arduino.cc/en/tutorial/button
 //buttonState = digitalRead(inputPin); 
 //if(buttonState == HIGH) {
    // tone(8, 196, 8);
// }
// else if (buttonState == LOW){
    // noTone(8);
// }
//}
   timerState = Timer();
}

 