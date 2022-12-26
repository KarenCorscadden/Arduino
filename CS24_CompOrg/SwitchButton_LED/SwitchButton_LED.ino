const int LED = 13;
const int BUTTON = 10;

int val = 0; // state of input pin
int old_val = 0; // previous value of val
int state = 0; // state of LED (1 = on)

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  val = digitalRead(BUTTON);

  if ((val == HIGH) && (old_val == LOW)) {
    state = 1 - state;
    delay(10);
  }
  
  old_val = val;

  if (state == 1) {
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }

}
