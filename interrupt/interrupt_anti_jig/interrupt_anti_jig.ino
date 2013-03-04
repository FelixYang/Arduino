
/*
http://www.davidorlo.com/articles/arduino/arduino-%E2%80%93-interrupt-tutorial-with-led-switch
Advanced Blink with an Interrupt Sketch
By: David M. Orlo
www.DaviedOrlo.com
*/
byte SWITCHPIN=2; //Set Pin 2 as Switch
byte LEDPIN=13; //Set Pin 6 as LED
byte brightness; //Create a Integer variable named brightness
byte delayedoff; //Create a Integer variable named delayedoff
byte delayedon; //Create a Integer variable named delayedon
//If you want to go higher than 255 you must change from "byte" to "int"
volatile boolean trigger=LOW; //This is our interrupt connected to the button switch
 
void setup(){
  attachInterrupt(0, interrupttrigger, LOW); //Interrupt 0 is Digital Pin 2
  //When the Input goes from High to Low it will trigger a function called crazyLED
  pinMode(LEDPIN, OUTPUT); //Set Pin 6 as Output
}
 
void loop(){
  delay(200); //Wait a moment to help debounce the switch
  if (trigger==1){ //Check to see if the interrupt was triggered
    crazyLED();} //Enter our LED blinking function
  else{ //If the button was pressed again
    analogWrite(LEDPIN, 0);} //Turn the LED off
}
 
void crazyLED(){
  delay(200); //Wait a moment to help debounce the switch
  while(trigger == HIGH){ //Will run this loop until the interrupt value changes
    brightness = random(1, 254); //Generates a random number from 1-254 and assigns it to the variable named brightness
    delayedoff = random(1, 125); //A random amount of time the LED is turned off
    delayedon = random(1, 250); //A random amount of time the LED is turned on
    analogWrite(LEDPIN, brightness); //Uses the random number we generated to write the value to our LED
    delay(delayedon); //random delay on time
    analogWrite(LEDPIN, 0); //We turn the LED off for a blinking effect
    delay(delayedoff);} //Random delay off time
}
 
void interrupttrigger(){ //When the switch is pressed (Interrupt is triggered) the arduino enters this function
  if (trigger ==LOW){ //Checks to see what the last value was (high or low)
    trigger=HIGH;} //If its low it is now set to high
  else{
    trigger=LOW;} //If its high it is now set to low
}
