
const char NAME[] = "Karen";
const int LED[] = {2, 3, 4, 5, 6, 7, 8};
const int BUTTON = 10;

int val = 0; // state of input pin
int old_val = 0; // previous value of val
int state = 0; // state of LED (1 = on)
int letter = -1;

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i <= 6; i++) {
    pinMode(LED[i], OUTPUT);
  }
  pinMode(BUTTON, INPUT);
  //Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = digitalRead(BUTTON);
  if ((val == LOW) && (old_val == HIGH)){
    delay(10);
  }
  if ((val == HIGH) && (old_val == LOW)) {
    letter = letter + 1;
    letter %= 6;
    //Serial.println(letter);
    delay(10);
    int mask = 1; // create a mask with least significant bit set to 1
    for (int i = 0; i <= 6; i++) {
      //Serial.println(mask);
      state = mask & NAME[letter]; // extract mask position value of current letter to state
      //Serial.println(state);
      if (state != 0) {
        digitalWrite(LED[i], HIGH);
      } else {
        digitalWrite(LED[i], LOW);
      }
      mask = mask << 1;  // shift mask 1 bit left (more significant)
    }
  //Serial.println("End of Button Press");
  }

  old_val = val;

}
