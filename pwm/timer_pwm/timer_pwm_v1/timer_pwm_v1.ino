//2013-2-27
//using CmdMessenger to control pwm setting change.
//注意：因为Leonardo中的PWM pin和timer间的对应，与UNO不同。setPwmFrequency不能起作用，
//所以该例程在Leonardo上无法运行。
#include <SerialCommand.h>

#define arduinoLED 13   // Arduino LED on board

SerialCommand SCmd;   // The demo SerialCommand object

void setup()
{  
  pinMode(arduinoLED,OUTPUT);      // Configure the onboard LED for output
  digitalWrite(arduinoLED,LOW);    // default to LED off

  Serial.begin(9600); 

  // Setup callbacks for SerialCommand commands 
  SCmd.addCommand("ON",LED_on);       // Turns LED on
  SCmd.addCommand("OFF",LED_off);        // Turns LED off
  SCmd.addCommand("LED",LED_ctrl);        // 
  SCmd.addCommand("P",process_command);  // Converts two arguments to integers and echos them back 
  SCmd.addCommand("PWM", setPwmFrequency);
  
  SCmd.addDefaultHandler(unrecognized);  // Handler for command that isn't matched  (says "What?") 
  Serial.println("Ready");  

}

void loop()
{  
  SCmd.readSerial();     // We don't do much, just process serial commands
}


void LED_on()
{
  Serial.println("LED on"); 
  digitalWrite(arduinoLED,HIGH);  
}

void LED_off()
{
  Serial.println("LED off"); 
  digitalWrite(arduinoLED,LOW);
}

void LED_ctrl()
{
  char *arg1, *arg2;
  int arg1_i, arg2_i;
  arg1 = SCmd.next();    // Get the next argument from the SerialCommand object buffer
  arg2 = SCmd.next();
  arg1_i = atoi(arg1);
  arg2_i = atoi(arg2);
  switch (arg1_i)
  {
    case NULL:     // As long as it existed, take it
        Serial.print("please input parameters! "); 
        break;
    case 1:
        digitalWrite(arduinoLED,LOW);
        Serial.print(arg2);
        Serial.print("OFF");
        break;
    case 9:
        digitalWrite(arduinoLED,HIGH);
        Serial.print(arg2);
        Serial.print("ON");
        break;
    default:
        Serial.print("Wrong param: ");
        Serial.print(arg1);
        Serial.println(";");
        break;
   }
}


void process_command()    
{
  int aNumber;  
  char *arg; 

  Serial.println("We're in process_command"); 
  arg = SCmd.next(); 
  if (arg != NULL) 
  {
    aNumber=atoi(arg);    // Converts a char string to an integer
    Serial.print("First argument was: "); 
    Serial.println(aNumber); 
  } 
  else {
    Serial.println("No arguments"); 
  }

  arg = SCmd.next(); 
  if (arg != NULL) 
  {
    aNumber=atol(arg); 
    Serial.print("Second argument was: "); 
    Serial.println(aNumber); 
  } 
  else {
    Serial.println("No second argument"); 
  }

}

void setPwmFrequency() 
{
  char *arg1, *arg2;
  int pin, divisor;
  
  arg1 = SCmd.next(); 
  arg2 = SCmd.next();
  pin = atoi(arg1);
  divisor = atoi(arg2);
  
  byte mode;
  if(pin == 5 || pin == 6 || pin == 9 || pin == 10) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    if(pin == 5 || pin == 6) {
      TCCR0B = TCCR0B & 0b11111000 | mode;
    } else {
      TCCR1B = TCCR1B & 0b11111000 | mode;
    }
  } else if(pin == 3 || pin == 11) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 32: mode = 0x03; break;
      case 64: mode = 0x04; break;
      case 128: mode = 0x05; break;
      case 256: mode = 0x06; break;
      case 1024: mode = 0x7; break;
      default: return;
    }
    // TCCR2B = TCCR2B & 0b11111000 | mode;
  }
  Serial.print(pin);
  Serial.print(divisor);
  Serial.println("Setting pwm!");
}

// This gets set as the default handler, and gets called when no other command matches. 
void unrecognized()
{
  Serial.println("What?"); 
}

