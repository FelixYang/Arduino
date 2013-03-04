//

#include <SerialCommand.h>

#define arduinoLED 13 

SerialCommand scmd;
/*
char* cmd_list[] = {
    "PWM"
};

char* callback_funcs[] ={
    set_pwm
};
*/
void setup(){
    pinMode(3, OUTPUT);
    Serial.begin(9600);
    int i;
    // for (i=0; i++; i<sizeof(cmd_list))
    // {
        // scmd.addCommand(cmd_list[i], callback_funcs[i]);
        // scmd.addCommand("PWM", set_pwm);
    // }
  scmd.addCommand("ON",LED_on);       // Turns LED on
  scmd.addCommand("OFF",LED_off);        // Turns LED off
  scmd.addCommand("PWM", set_pwm);
}

void loop(){
    scmd.readSerial();
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

void set_pwm()
{ char *arg1, *arg2;
  arg1 = scmd.next();
  arg2 = scmd.next();
  Serial.print(arg1);
  Serial.println(arg2);
  
  if (arg1 != NULL) {
    int pin, duty;

    pin = atoi(arg1);
    if (pin == 3 || pin == 5 || pin == 6 || pin == 9 || pin == 10 || pin == 11)
    {
        duty = atoi(arg2);
        analogWrite(pin, duty);
    }
    else
    {
        Serial.println("wrong pwm pin select!");
    }
  }
}