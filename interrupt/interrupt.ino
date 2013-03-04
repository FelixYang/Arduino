
int pInt = 0; //uno_digital pin 2; leonardo_digital pin 3
int pin = 13;
int ledOut = A0;
volatile int state = LOW;

void setup()
{
  Serial.begin(9600);
  pinMode(pin, OUTPUT);
  attachInterrupt(pInt, blink, CHANGE );  
}

void loop()
{

}

void blink()
{
  delayMicroseconds(500000);  //delay function that could using in interrupt
  state = !state;
  Serial.print(state);
  Serial.println("int occure!");
  digitalWrite(pin, state);
  digitalWrite(ledOut, state);
}
