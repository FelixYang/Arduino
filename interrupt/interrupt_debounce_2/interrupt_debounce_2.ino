
const int buttonInterrupt = 0;  // Button interrupt
const int buttonLedPin =  13;   // LED indicating the button state
const int switchLedPin = 12;    // LED indicating the switch state

volatile int buttonState = LOW; //initial button state

volatile boolean switchState = false; 

volatile long lastDebounceTime = 0;   // the last time the interrupt was triggered
long debounceDelay = 10;    // the debounce time; decrease if quick button presses are ignored

void setup() {
  pinMode(buttonLedPin, OUTPUT);
  pinMode(switchLedPin, OUTPUT);
  
  digitalWrite(buttonLedPin, LOW);
  
  attachInterrupt(buttonInterrupt, Rise, RISING);
}

void loop()
{
  
}

void Rise()
{
  long currentTime = millis();
  
  if ((currentTime - lastDebounceTime) > debounceDelay)
  {
    lastDebounceTime = currentTime;
    
    if (buttonState == LOW)
    {
      buttonState = HIGH;
      
      attachInterrupt(buttonInterrupt, Fall, FALLING);
    }
    
    digitalWrite(buttonLedPin, buttonState);
    
    Switch(buttonState);
  }
}

void Fall()
{
  long currentTime = millis();
  
  if ((currentTime - lastDebounceTime) > debounceDelay)
  {
    lastDebounceTime = currentTime;
    
    if (buttonState == HIGH)
    {
      buttonState = LOW;
      
      attachInterrupt(buttonInterrupt, Rise, RISING);
    }
    
    digitalWrite(buttonLedPin, buttonState);
    
    Switch(buttonState);
  }
}

void Switch(int state)
{
  if (state == HIGH)
  {
    switchState = !switchState;
  }
  
  if (switchState)
  {
    digitalWrite(switchLedPin, HIGH);
  }
  else
  {
    digitalWrite(switchLedPin, LOW);
  }
}

