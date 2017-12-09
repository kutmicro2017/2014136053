#include <Adafruit_NeoPixel.h>
#define Button_A 2  // 터치센서
#define Piezo 4
#include <Servo.h> 

#define PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800);

Servo servo;
int servoPin = 9;
int angle = 0;

char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
 int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };

int tempo = 300;
int lenght[2] = {15, 26};
char notes[2][80] = { "ccggaag ffeeddc ggffeed ggffeed ccggaag ffeeddc ",
                   "eeeeeeegcde fffffeeeeddedg  " };
int beats[2][80] = { { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 }, 
                  { 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2} };
int next = 0;
volatile bool state1 = false;
volatile bool state2 = false;
volatile bool endstate = false;
float pressTime = 0;
float touch = 0;

void tTof() {
  state1 = true;
  state2 = true;
  while(digitalRead(Button_A)==HIGH)
 {
   delay(100);
   //pressTime = pulseIn(3,HIGH);
   pressTime++;
   Serial.print("pressTime : "); Serial.println(pressTime);
   Serial.print("B4_digitalRead(5) : "); Serial.println(digitalRead(5));
 }
 touch  = pressTime;
 pressTime = 0;
 Serial.println(touch);
}
void playTone(int tone, int duration) {
 for (long i = 0; i < duration * 1000L; i += tone * 2) {

   
     
   digitalWrite(Piezo, HIGH);
   delayMicroseconds(tone);
   digitalWrite(Piezo, LOW);
   delayMicroseconds(tone);
 }
}
void playNote(char note, int duration) {
 
 for (int i = 0; i < 8; i++) {
   if (names[i] == note) {
     colorWipe(i);
     playTone(tones[i], duration);
   }
 }
}

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(25); // 밝기조절
  
  servo.attach(servoPin);
  pinMode(Button_A, INPUT);
  Serial.begin(9600);
  pinMode(Piezo, OUTPUT);
  attachInterrupt(0, tTof, RISING);
}
void loop() {
 if(state1 == true) {
  while(true) {
    state2 = false;
   
   for (int i = 0; i < lenght[next]; i++) {
    
   if (notes[next][i] == ' ') {
    if(angle > 170)
    angle = 0;
    angle += 30;
      servo.write(angle);
     delay(beats[next][i] * tempo);
   } else {
     
     playNote(notes[next][i], beats[next][i] * tempo);
   }
   if(touch < 30 && touch >= 0 && state2 == true) {
    state2 = false;
    next++;
    if(next == 2)
     next = 0;
     i = 0;
     continue;
   }
   else if(touch > 30 && state2 == true) {
    endstate = true;
    state2 = false;
    state1 = false;
    next = 0;
    for(uint16_t i = 0; i < 16; i++)
      strip.setPixelColor(i, false);
      strip.show();
    break;
   }
   if(angle > 170)
    angle = 0;
   angle += 30;
   servo.write(angle);
   delay(tempo / 2);
   }
    if(endstate == true)
    break;
   next++;
   if(next == 2)
     next = 0;
 }
 }



 
}






void colorWipe(int num) {
 if(num == 0) {
  for(uint16_t i = 0; i < 16; i++)
      strip.setPixelColor(i, false);
    for(uint16_t i = 0; i < 2; i++) {
      strip.setPixelColor(i, strip.Color(255 - i * 7,0,0));
      strip.show();
    }
  }
  else if(num == 1) {
    for(uint16_t i = 0; i < 16; i++)
      strip.setPixelColor(i, false);
    for(uint16_t i = 0; i < 4; i++) {
      strip.setPixelColor(i, strip.Color(255 - i * 7,0,0));
      strip.show();
    }
  }
  else if(num == 2) {
    for(uint16_t i = 0; i < 16; i++)
      strip.setPixelColor(i, false);
    for(uint16_t i = 0; i < 6; i++) {
      if(i < 4)
      strip.setPixelColor(i, strip.Color(255 - i * 7,0,0));
      else
      strip.setPixelColor(i, strip.Color(255,94 - i * 2,0));
      strip.show();
    }
  }
  else if(num == 3) {
    for(uint16_t i = 0; i < 16; i++)
      strip.setPixelColor(i, false);
    for(uint16_t i = 0; i < 8; i++) {
      if(i < 4)
      strip.setPixelColor(i, strip.Color(255 - i * 7,0,0));
      else
      strip.setPixelColor(i, strip.Color(255 - i * 4,165 - i * 9,0));
      strip.show();
    }
  }
  else if(num == 4) {
    for(uint16_t i = 0; i < 16; i++)
      strip.setPixelColor(i, false);
    for(uint16_t i = 0; i < 10; i++) {
      if(i < 4)
      strip.setPixelColor(i, strip.Color(255 - i * 7,0,0));
      else if( i < 8)
      strip.setPixelColor(i, strip.Color(255 - i * 4,165 - i * 9,0));
      else
      strip.setPixelColor(i, strip.Color(0,255 - i * 9,127 - i * 5));
      strip.show();
    }
  }
  else if(num == 5) {
    for(uint16_t i = 0; i < 16; i++)
      strip.setPixelColor(i, false);
    for(uint16_t i = 0; i < 12; i++) {
       if(i < 4)
      strip.setPixelColor(i, strip.Color(255 - i * 7,0,0));
      else if( i < 8)
      strip.setPixelColor(i, strip.Color(255 - i * 4,165 - i * 9,0));
      else
      strip.setPixelColor(i, strip.Color(0,255 - i * 9,127 - i * 5));
      strip.show();
    }
  }
  else if(num == 6) {
    for(uint16_t i = 0; i < 16; i++)
      strip.setPixelColor(i, false);
    for(uint16_t i = 0; i < 14; i++) {
      if(i < 4)
      strip.setPixelColor(i, strip.Color(255 - i * 7,0,0));
      else if( i < 8)
      strip.setPixelColor(i, strip.Color(255 - i * 4,165 - i * 9,0));
      else if(i < 12)
      strip.setPixelColor(i, strip.Color(0,255 - i * 9,127 - i * 5));
      else
      strip.setPixelColor(i, strip.Color(175 - i * 4,238 - i * 9,238 - i * 3));
      strip.show();
    }
  }
  else if(num == 7) {
    
    for(uint16_t i = 0; i < 16; i++)
      strip.setPixelColor(i, false);
    for(uint16_t i = 0; i < 16; i++) {
      if(i < 4)
      strip.setPixelColor(i, strip.Color(255 - i * 7,0,0));
      else if( i < 8)
      strip.setPixelColor(i, strip.Color(255 - i * 4,165 - i * 9,0));
      else if(i < 12)
      strip.setPixelColor(i, strip.Color(0,255 - i * 9,127 - i * 5));
      else
      strip.setPixelColor(i, strip.Color(175 - i * 4,238 - i * 9,238 - i * 3));
      strip.show();
    }
  }
}
