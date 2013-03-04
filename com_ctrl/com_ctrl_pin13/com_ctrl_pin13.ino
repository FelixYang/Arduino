
int ledPin = 13;
char command;

void setup()
{
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop ()
{
  command = Serial.read();
  if (command == 'H')
   {
      digitalWrite(ledPin, HIGH);
   }
   if (command == 'L')
   {
      digitalWrite(ledPin, LOW);
   }
}