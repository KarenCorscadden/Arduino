// CS24 Program that uses a 4 digit 7 segment display
// and a rotary encoder to set and display a countdown
// timer.
// file: Lab2.ino, Fall 2022, (c) Karen Corscadden

int latch=9;  //74HC595  pin 9 STCP
int clock=10; //74HC595  pin 10 SHCP
int data=8;   //74HC595  pin 8 DS
int right=11; //right digit ground of display
int left=12; //left digit ground of display
int val=0; //state of button
int old_val=0; //previous state of button
boolean do_button=false;
long counter;
volatile boolean TurnDetected=false;  // need volatile for Interrupts
volatile boolean rotationdirection;  // CW or CCW rotation
const int PinCLK=2;   // Generating interrupts using CLK signal
const int PinDT=3;    // Reading DT signal
const int PinSW=4;    // Reading Push Button switch
enum state {
  set_time,
  countdown,
  zero_time
};

state s=set_time;
unsigned short max_time=25;
unsigned long cd_time;
unsigned char table[]=
{0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c
,0x39,0x5e,0x79,0x71,0x00};

// Interrupt routine runs if CLK goes from HIGH to LOW
void isr ()  {
  delay(10);  // delay for Debouncing
  TurnDetected = true;
  if (digitalRead(PinCLK))
    rotationdirection= digitalRead(PinDT);
  else
    rotationdirection= !digitalRead(PinDT);
}

void setup() {
  pinMode(latch,OUTPUT);
  pinMode(clock,OUTPUT);
  pinMode(data,OUTPUT);
  pinMode(right,OUTPUT);
  pinMode(left,OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  digitalWrite(right, HIGH);
  digitalWrite(left, HIGH);
  pinMode(PinCLK,INPUT);
  pinMode(PinDT,INPUT);  
  pinMode(PinSW,INPUT_PULLUP);
  attachInterrupt (0,isr,FALLING); // interrupt 0 always connected to pin 2 on Arduino UNO
  cd_time=millis();
}

// outputs 2 characters to the display, msb is the more
// significant digit and lsb is the least significant
// digit.
void Display(unsigned char msb, unsigned char lsb)
{
  digitalWrite(latch,LOW);
  shiftOut(data,clock,MSBFIRST,table[lsb]);
  digitalWrite(latch,HIGH);
  digitalWrite(right, LOW);
  delay(5);
  digitalWrite(right, HIGH);
  digitalWrite(latch,LOW);
  shiftOut(data,clock,MSBFIRST,table[msb]);
  digitalWrite(latch,HIGH);
  digitalWrite(left, LOW);
  delay(5);
  digitalWrite(left, HIGH);
}

// first checks the button press state to determine if a 
// button press needs to be handled and then implements
// the countdown timer behavior as a finite state machine
// (via a switch block) with 3 states: set_time, countdown,
// and zero_time. Finishes with a bit more logic to handle
// the button press.
void loop() {
  val = !digitalRead(PinSW);
  if ((val == LOW) && (old_val == HIGH)) {
    delay(10);
  }
  if ((val == HIGH) && (old_val == LOW)) {
    do_button = true;
  }
  digitalWrite(13, val); //lighting the LED for debugging purposes
  switch(s) {
    case set_time:
      if (do_button) {
        s = countdown;
        cd_time = millis();
        do_button = false;
        break;
      }
      Display(max_time/10, max_time%10);
      if (TurnDetected) {
        TurnDetected = false;
        if (rotationdirection) {
          if (max_time < 99) {
            max_time++;
          }
        } else {
          if (max_time > 0) {
            max_time--;
          }
        }
      }
      break;
    case countdown:
      counter = (max_time * 100) - (millis() - cd_time);
      if (counter < 0){
        s = zero_time;
        break;
      }
      Display(counter/1000, (counter%1000)/100);
      if (do_button) {
        do_button = false;
        s = set_time;
        break;
      }
      if (TurnDetected){
        s = set_time;
        max_time = counter/100;
        TurnDetected = false;
        break;
      }
      delay(5);
      break;
    case zero_time:
      if (millis()%1000 < 500) {
        Display(0,0);
      }
      if (do_button) {
        do_button = false;
        s = set_time;
        break;
      }
      if (TurnDetected){
        s = set_time;
        max_time = 0;
        TurnDetected = false;
        break;
      }
      break;
  }
  old_val = val;
}
