#include <Arduino.h>

// initialize pushbutton
int pushButton = 12;
int led = 11;
int isClickedPushButton = 0;

byte lastButtonState;

void setup()
{
  pinMode(pushButton, INPUT);
  pinMode(led, OUTPUT);
  lastButtonState = digitalRead(pushButton);
}

void handlePushButtonWithDebounce(int buttonPin, void (*instruction)())
{
  // digital push button input
  int pushButtonDigitalInput = digitalRead(buttonPin);

  // when push button get input run this block
  if (pushButtonDigitalInput != lastButtonState)
  {
    lastButtonState = pushButtonDigitalInput;
    if (pushButtonDigitalInput == 1)
    {
      instruction();
    };
  }
  delay(5);
}

void handleLedLogic()
{
  if (isClickedPushButton == 0)
  {
    digitalWrite(led, 1);
    isClickedPushButton = 1;
  }
  else
  {
    digitalWrite(led, 0);
    isClickedPushButton = 0;
  };
}

void loop()
{
  handlePushButtonWithDebounce(pushButton, &handleLedLogic);
}