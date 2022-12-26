const int LED = 13;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED, HIGH); // turns LED on
  delay(2); // wait 0.5 second
  digitalWrite(LED, LOW); // LED off
  delay(1); //wait 2 second

}
