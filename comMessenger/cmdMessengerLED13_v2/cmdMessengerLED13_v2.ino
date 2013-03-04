
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
  SCmd.addCommand("HELLO",SayHello);     // Echos the string argument back
  SCmd.addCommand("P",process_command);  // Converts two arguments to integers and echos them back 
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
  char *arg, *arg2_a;
  int arg_i, arg2;
  arg = SCmd.next();    // Get the next argument from the SerialCommand object buffer
  arg_i = atoi(arg);
  arg2_a = SCmd.next();
  arg2 = atoi(arg2_a);
  switch (arg_i)
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
        Serial.print(arg);
        Serial.println(";");
        break;
   }
}

void SayHello()
{
  char *arg;  
  arg = SCmd.next();    // Get the next argument from the SerialCommand object buffer
  if (arg != NULL)      // As long as it existed, take it
  {
    Serial.print("Hello "); 
    Serial.println(arg); 
  } 
  else {
    Serial.println("Hello, whoever you are"); 
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

// This gets set as the default handler, and gets called when no other command matches. 
void unrecognized()
{
  Serial.println("What?"); 
}

