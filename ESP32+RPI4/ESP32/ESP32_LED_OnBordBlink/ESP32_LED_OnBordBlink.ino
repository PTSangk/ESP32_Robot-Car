/*
  Blink
  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/

#define ledPin 21

// the setup function runs once when you press reset or power the board
void setup(void) {
  pinMode(ledPin, OUTPUT);
}
void loop() {
  digitalWrite(ledPin, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                 // wait for a second
  digitalWrite(ledPin, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);
}
