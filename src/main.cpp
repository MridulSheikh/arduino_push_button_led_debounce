#include <Arduino.h>

// initialize pushbutton
int pushButton = 12;
int led = 11;
int isClickedPushButton = 0;

byte lastButtonState;

unsigned long lasTimeButtonStateChange = millis();

void setup()
{
  pinMode(pushButton, INPUT);
  pinMode(led, OUTPUT);
  lastButtonState = digitalRead(pushButton);
}

void loop()
{
  // digital push button input
  int pushButtonDigitalInput = digitalRead(pushButton);

  // when push button get input run this block
  if (pushButtonDigitalInput != lastButtonState)
  {
    lasTimeButtonStateChange = millis();
    lastButtonState = pushButtonDigitalInput;
    if (pushButtonDigitalInput == 0)
    {
      if (isClickedPushButton == 0)
      {
        isClickedPushButton = 1;
      }
      else
      {
        isClickedPushButton = 0;
      };
    };
  }

  // conditional led output
  if (isClickedPushButton == 1)
  {
    digitalWrite(led, 1);
  }
  else
  {
    digitalWrite(led, 0);
  };
}