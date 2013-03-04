//Software debouncing in Interrupt, by Delphiño K.M.

int ledOut = 13;
volatile int state = LOW;
long debouncing_time = 15; //Debouncing Time in Milliseconds
volatile unsigned long last_micros;



void setup() {
  pinMode(ledOut, OUTPUT); //
  attachInterrupt(0, debounceInterrupt, RISING);
  Serial.begin(9600);
}

void loop() {
}

void debounceInterrupt() {
  if((long)(micros() - last_micros) >= debouncing_time * 1000) {
    Interrupt();
    last_micros = micros();
  }
}

void Interrupt() {
  //Do Something
  state = !state;
  digitalWrite(ledOut, state);
  Serial.print(state);
  Serial.println(" ;");
}
