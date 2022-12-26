int latch=9;  //74HC595  pin 9 STCP
int clock=10; //74HC595  pin 10 SHCP
int data=8;   //74HC595  pin 8 DS
int right=11; //right digit ground of display
int left=12; //left digit ground of display
unsigned short mtime=0;
int counter;

unsigned char table[]=
{0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c
,0x39,0x5e,0x79,0x71,0x00};

void setup() {
  pinMode(latch,OUTPUT);
  pinMode(clock,OUTPUT);
  pinMode(data,OUTPUT);
  pinMode(right,OUTPUT);
  pinMode(left,OUTPUT);
  digitalWrite(right, HIGH);
  digitalWrite(left, HIGH);
}
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
void Blink(unsigned int d)
{
  digitalWrite(latch,LOW);
  shiftOut(data,clock,MSBFIRST,table[0]);
  digitalWrite(latch,HIGH);
  digitalWrite(right, LOW);
  digitalWrite(left, LOW);
  delay(d);
  digitalWrite(right, HIGH);
  digitalWrite(left, HIGH);
}
void loop() {
  counter = 10000 - millis();
  if (counter < 0){
    counter = 0;
    Blink(500);
    delay(500);
  } else {
    Display(counter/1000, (counter%1000)/100);
    delay(5);
  }
  
}
