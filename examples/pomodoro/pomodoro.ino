/* NeoDigito example code: Pomodoro

  

  Created by Inventoteca 

  https://github.com/Inventoteca/NeoDigito

  This example code is in the public domain.
  Remember that you must have installed Adafruit_NeoPixel library.
*/

#include <NeoDigito.h>

#define PIN         2   // Pin where the display will be attached
#define DIGITS      2   // Number of NeoDigitos connected
#define PIXPERSEG   3   // NeoPixels per segment,3 for BIG version, 2 for MEDIO
const int buttonPin = 4;
// Specified the number of displays and the number of neopixels per segment, for more info about the argumets check documentation
NeoDigito display1 = NeoDigito(DIGITS, PIXPERSEG, PIN);

int cycle = 0;
int state = 3;  // counter for the number of button presses
int buttonState = 0;        // current state of the button
int lastButtonState = 0;    // previous state of the button
int millis_timer = 1000;
long millis_prev = 0;
int current_time = 0;
long color = Cian;

void setup()
{
  display1.begin();                          // This fuction calls Adafruit_NeoPixel.begin() to configure.
  display1.print("Hi");                      // It prints the value.
  display1.updateColor(Rainbow);            // Color specified by name RED, WHITE, YELLOW, etc or 32bit, or 8bit numbers (R, G, B).
  display1.show();                          // Lights up the pixels.
  //delay(3000);
  display1.clear();                         // It erase the text in the whole display.
  display1.show();
  display1.setColor(Cian);
  display1.print(25);                      // It prints the value.
  display1.updateColor(Red);            // Color specified by name RED, WHITE, YELLOW, etc or 32bit, or 8bit numbers (R, G, B).
  display1.show();                          // Lights up the pixels.
  //delay(3000);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  Serial.begin(115200);
  Serial.println("Pomodoro");
  millis_prev = millis();

}

void loop()
{
  if (digitalRead(buttonPin) == LOW)
  {
    // if the current state is HIGH then the button went from off to on:
    state++;
    Serial.print("cycle: ");
    Serial.println(cycle);
    Serial.print("state: ");
    Serial.println(state);

    while (digitalRead(buttonPin) == LOW)
    {
      delay(50);
    }
    current_time = 0;
    millis_prev = millis();





  }

  switch (state)
  {
    case 0:
          display1.print(25);                      // It prints the value.
      display1.updateColor(Red);            // Color specified by name RED, WHITE, YELLOW, etc or 32bit, or 8bit numbers (R, G, B).
      display1.show();
    case 1:
      timer1(1);
      break;
    case 2:
      timer1(1);
      break;
    case 3:
      timer1(1);
      break;

    default:
    state=0;
      break;
  }
  //millis_prev = millis();
}



void timer1(int timer_1)
{
  //
  if ((millis() - millis_prev) > millis_timer)
  {
    millis_prev = millis();
    digitalWrite(13, !(digitalRead(13)));

    if (state == 1)
    {
      if (color == 65535)
        color = 16448;
      else
        color = 65535;
    }
    if (state == 2)
    {
      if (color == 16716947)
        color = 8391215;
      else
        color = 16716947;
    }




    Serial.println(current_time);

    display1.clear();
    if (((timer_1 * 60) - current_time) / 60 < 10)                    // Less than 10 so place space or zero
      display1.print(" ");
    display1.print(((timer_1 * 60) - current_time) / 60);
    display1.updateColor(color);            // Color specified by name RED, WHITE, YELLOW, etc or 32bit, or 8bit numbers (R, G, B).
    display1.show();


    if (current_time >= (timer_1 * 60)) //time out
    {
      if (state == 1)
      {
        cycle++;
        state = 3;
      }
      if (state == 3)
      {
        cycle = 0;
        state = 1;
      }
      state++;
      current_time = 0;
      //millis_prev = millis();
      Serial.println(millis());
      Serial.println(millis_prev);
    }
    else
    {
      current_time++;
    }
  }
}
