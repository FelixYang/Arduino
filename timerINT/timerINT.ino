#include <MsTimer2.h>

void setup() 
{
  pinMode(13, OUTPUT);
  MsTimer2::set(500, flash); // 500ms period
  MsTimer2::start();
}

void loop() 
{   }

void flash() {
  static boolean output = HIGH;
  
  digitalWrite(13, output);
  output = !output;
}