/*
 * Title: Shooting_Star_Main
 * 
 * Description:
 *      - This sketch was created for controling a WS2812B LED light strip (or similar) using the FastLED library. 
 *      
 * Author: Electriangle
 *      - Channel: https://www.youtube.com/@Electriangle
 *      - Shooting Star LED Animation Video: https://www.youtube.com/watch?v=tcjGnPcd1oU
 *      
 * License: MIT License
 *      - Copyright (c) 2022 Electriangle
 *
 * Date Created: 11/30/2022
 * Last Updated: 11/30/2022
*/

#include "FastLED.h"
#include <Arduino.h>

struct Button{
  const uint8_t PIN;
  uint32_t  numberKeyPresses;
  bool pressed;
};

Button button1 = {D4, 0, false};
Button button2 = {9, 0, false};

#define NUM_LEDS  30    // Enter the total number of LEDs on the strip
#define LEDPIN    D3      // The pin connected to Din to control the LEDs
#define BTNPIN    7


CRGB leds[NUM_LEDS];
static int buttonState = 0;
static int cnt = 0;

void ARDUINO_ISR_ATTR isr(void* arg){
  Button* s = static_cast<Button*>(arg);
  s->numberKeyPresses = s->numberKeyPresses+1>=7? 0: s->numberKeyPresses +=1;
  s->pressed = true;
  detachInterrupt(button1.PIN);
}

void ARDUINO_ISR_ATTR isr() {
  button2.numberKeyPresses =  button2.numberKeyPresses+1>=7? 0:button2.numberKeyPresses +=1;
  button2.pressed = true;
  detachInterrupt(button2.PIN);
}

void setup() {
  Serial.begin(115200);
  // initialize the pushbutton pin as an input:
  pinMode(button1.PIN, INPUT_PULLDOWN);
  attachInterruptArg(button1.PIN, isr, &button1, RISING);
  pinMode(button2.PIN, INPUT_PULLDOWN);
  attachInterrupt(button2.PIN, isr, RISING);

  FastLED.addLeds<WS2812B, LEDPIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 1500);    // Set power limit of LED strip to 5V, 1500mA
  FastLED.clear();                                    // Initialize all LEDs to "OFF"

}

void loop() {

  if(button1.pressed){
    Serial.printf("Button 1 has been pressed %u times\n", button1.numberKeyPresses);
    button1.pressed = false;
    attachInterruptArg(button1.PIN, isr, &button1, RISING);
  }
    if(button2.pressed){
    Serial.printf("Button 2 has been pressed %u times\n", button2.numberKeyPresses);
    button2.pressed = false;
    attachInterrupt(button2.PIN, isr, RISING);
  }
    switch(button2.numberKeyPresses)
    {
      case 0:
       // shootingStarAnimation(255, 255, 255, random(10, 60), random(5, 100), random(2000, 8000), 1); //Right
       shootingStarAnimation(255, 255, 255, 30, 15, 1000, 1);
        break;
      case 1:
        shootingStarAnimation(255, 255, 255, 30,15, 1000, -1);//Left
     //   Fire(0, 50, 100, 10, 0);
        break;
      case 2://
        fadeAnimation(255, 255,255);//Bat low
   //     fadeAnimation(random(0,255), random(0,255),random(0,255));
        break;
      case 3: //Over heating
        Fire(30, 150, 50);//candle
        break;
      case 4:
        knightRider(255, 255, 255, 10, 10, 50);//backward
       // knightRider(0, 255, 0, 5, 10, 50);
       // knightRider(0, 0, 255, 5, 10, 50);
        break;
      case 5:
         shootingStarAnimation(255, 255, 255, 30, random(5, 100), random(2000, 8000), 1); //Charging
   //     rainbowCycle(50);
        break;
      case 6:
      TwinklePixels(255, 255, 10, 50, 50);//Brake
     //   TwinklePixels(random(256), 255, 20, 50, 50);
        break;
      default:
        break;
    }
 //   Serial.println(buttonState);
    Serial.printf("bt1:%d\n",button1.numberKeyPresses);
    Serial.printf("bt2:%d\n",button2.numberKeyPresses);
  // Try changing the arguments. Uncomment this line of code to try out a fully randomized animation example:
  //  shootingStarAnimation(random(0, 255), random(0, 255), random(0, 255), random(10, 60), random(5, 40), random(2000, 8000), 1);
}
