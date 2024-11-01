#include <Arduino.h>
#include <Stepper.h>
#define STEPS 2048 // the number of steps in one revolution of your motor (28BYJ - 48 )

Stepper stepper(STEPS, 7, 9, 8, 10);

// initialize pushbutton
int pushButton = 12;
int led = 11;
int redIndicator = 6;
int isClickedPushButton = 0;

byte lastButtonState;

void setup()
{
  pinMode(pushButton, INPUT);
  pinMode(led, OUTPUT);
  pinMode(redIndicator, OUTPUT);
  stepper.setSpeed(6); // 1rpm
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
    isClickedPushButton = 1;
  }
  else
  {
    isClickedPushButton = 0;
  };
}

void handleSteperMotorLogic()
{
  if (isClickedPushButton == 1)
  {
    digitalWrite(redIndicator, 0);
    digitalWrite(led, 1);
    stepper.step(2048);
    delay(1000);
    stepper.step(-2048);
    delay(1000);
    digitalWrite(led, 0);
    digitalWrite(redIndicator, 0);
    isClickedPushButton = !isClickedPushButton;
     
  }
  else
  {
    stepper.step(0);
  }
}

void handleDebouncePushbuttonAction()
{
  handleLedLogic();
  handleSteperMotorLogic();
}

void loop()
{
  digitalWrite(redIndicator, 1);
  handlePushButtonWithDebounce(pushButton, &handleDebouncePushbuttonAction);   
}