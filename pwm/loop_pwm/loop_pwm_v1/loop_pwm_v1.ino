//

#include <SerialCommand.h>

#define pin 4 
#define arduinoLED 13

const int INIT_FRQ = 50;
const int INIT_DUTY = 50;

const int PIN0_INT = 3;
const int PIN1_INT = 3;
const int PIN2_INT = 1;
const int PIN3_INT = 0;

int frq= 50;
int duty= 50;
int t[2];

SerialCommand scmd;

void setup(){
    pinMode(4, OUTPUT);
  
    attachInterrupt(PIN0_INT, pin0_int, LOW);
    attachInterrupt(PIN1_INT, pin1_int, LOW);
    attachInterrupt(PIN2_INT, pin2_int, LOW);
    attachInterrupt(PIN3_INT, pin3_int, LOW);
    
    Serial.begin(9600);
    scmd.addCommand("ON",LED_on);       // Turns LED on
    scmd.addCommand("OFF",LED_off);        // Turns LED off
}

void loop(){
    scmd.readSerial();
    digitalWrite(pin, HIGH);
    delay(t[0]);
    digitalWrite(pin, LOW);
    delay(t[1]);
}

void pin0_int()
{
    frq += 5;
    set_pwm(frq, duty);
}

void pin1_int()
{
    duty += 5;
    set_pwm(frq, duty);
}

void pin2_int()
{
    frq = INIT_FRQ;
    set_pwm(frq, duty);
}
void pin3_int()
{
    duty = INIT_DUTY;
    set_pwm(frq, duty);
}

void set_pwm(int f, int d)
{
   int t_h, t_l;

   t_h = d * 10 / f;
   t_l = (100-d) * 10 / f;
   t[0] = t_h;
   t[1] = t_l; 
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