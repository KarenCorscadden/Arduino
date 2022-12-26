// Turns on an LED while the button is pressed

const int LED = 13;
const int BUTTON = 7;

int val = 0; // used to store the state of the input pin

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  val = digitalRead(BUTTON); // read and store button state

  if (val == HIGH) {
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }
  

}
