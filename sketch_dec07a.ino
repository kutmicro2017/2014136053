#include <Adafruit_NeoPixel.h> // RGB 컬러 픽셀 헤더 파일 
#define Button_A 2  // 터치센서 
#define Piezo 4 // 피에조 부저
#include <Servo.h>  // 모터 헤더 파일

#define PIN 6 // RGB 컬러픽셀 링
Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800); // 컬러픽셀 객체 생성

Servo servo; // 모터 객체 생성
#define servoPin  9 // 모터 
int angle = 0; // 초기 

char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' }; // 계이름
 int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 }; // 계이름에 맞춘 피에조부조 헤르츠

int tempo = 300; 
int lenght[3] = {15, 26, 47}; // 곡들의 길이
char notes[3][80] = { "cdefgabCbagfedc  " , // 도레미파 솔라시도
                   "eeeeeeegcde fffffeeeeddedg  ", // 징글벨
                   "ccggaag ffeeddc ggffeed ggffeed ccggaag ffeeddc "}; // 작은별 
int beats[3][80] = {{ 1, 1, 1, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1} ,  // 도레미파솔라시도 템포
                  { 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2}, // 징글벨 템포
                   { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 4, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 }}; // 작은별 템포
int next = 0; // 곡 재생 순서
volatile bool state1 = false; // 전원 on
volatile bool state2 = false; // 버튼 입력 
volatile bool endstate = false; // 전원 off
float pressTime = 0; // 누르는 시간 
float touch = 0; // 누르는 시간 저장 값 

void tTof() { // 인터럽트 함수 touch가 얼마나 됐는지 계산 해줌
  state1 = true; 
  state2 = true;
  while(digitalRead(Button_A)==HIGH)  // 터치센서 눌렸을 때
 {
   delay(100);  // 약 0.1초
   //pressTime = pulseIn(3,HIGH) 
   pressTime++; // 약 presstime 10에 1초  
 //  Serial.print("pressTime : "); Serial.println(pressTime); 
//   Serial.print("B4_digitalRead(5) : "); Serial.println(digitalRead(5));
 }
 touch  = pressTime; // 저장 
 pressTime = 0; // 초기화
 //Serial.println(touch);
}
void playTone(int tone, int duration) { // 피에조 부조 실행
 for (long i = 0; i < duration * 1000L; i += tone * 2) {

   digitalWrite(Piezo, HIGH); 
   delayMicroseconds(tone); 
   digitalWrite(Piezo, LOW); 
   delayMicroseconds(tone);
 }
}
void playNote(char note, int duration) { // led 함수 실행 , 피에조 부조 실행 함수 실행
 
 for (int i = 0; i < 8; i++) {
   if (names[i] == note) {
     colorWipe(i);
     playTone(tones[i], duration);
   }
 }
}

void setup() {
  strip.begin(); // 초기화
  strip.show(); // led  
  strip.setBrightness(25); // 밝기조절
  
  servo.attach(servoPin); // servo 객체에 지정된 핀 설정
  
  pinMode(Button_A, INPUT); // touch 센서 
  //Serial.begin(9600);
  pinMode(Piezo, OUTPUT); // 피에조 부조
  attachInterrupt(0, tTof, RISING); // 인터럽트 설정
}
void loop() {
 if(state1 == true) { // state1 이 on 되면 true가 되므로 if문 사용
  while(true) { 
    state2 = false; // on상태에서 버튼 값들을 받아야 되므로 false로 만들어줌
   
   for (int i = 0; i < lenght[next]; i++) { // main loop
    
   if (notes[next][i] == ' ') { // 공백일 시 
     delay(beats[next][i] * tempo);  // 비트를 템포 수 만큼 딜레이
   } else { // 공백이 아닐 시 함수로 실행
     
     playNote(notes[next][i], beats[next][i] * tempo); 
   }
   if(touch < 30 && touch >= 0 && state2 == true) { // 다음곡 재생
    state2 = false; // 버튼 눌린 상태이므로 다시 false로 바꿔줌
    next++; // 곡 다음곡으로 변경
    if(next == 3)  // 마지막 곡일 시 
     next = 0; // 처음 곡
     i = 0; 
     continue; // 다시 for문의 처음으로
   }
   else if(touch > 30 && state2 == true) { // 전원 off 
    endstate = true; // while구문 끔
    state2 = false; // 버튼 안눌린 값으로 초기화
    state1 = false; // 버튼 안눌린 값으로 초기화
    next = 0; // 처음 곡으로
    for(uint16_t i = 0; i < 16; i++) 
      strip.setPixelColor(i, false); // led를 다 꺼줌
      strip.show(); // 적용
    break;
   }
//   for(uint16_t i = 0; i < 16; i++) 눌렸을때 깜빡이게 하려면 추가
//      strip.setPixelColor(i, false);
//    strip.show();
   if(angle > 170) // 각도가 170도 이상일 시
    angle = 0; // 0으로 바꾸어줌
   angle += 30; // 30도 증가
   servo.write(angle); //각 적용
   delay(tempo / 2); // 잠시 쉬는 타임
   }
    if(endstate == true) { //아예 끄는 거
    endstate = false; 
    break;
    }
   next++; // 다 돌았을 때 다음 곡 재생
   if(next == 3) // 마지막 곡이면
     next = 0; // 처음곡으로
 }
 }



 
}





// 이퀄라이져 함수
void colorWipe(int num) {
 if(num == 0) {
  for(uint16_t i = 0; i < 16; i++)
      strip.setPixelColor(i, false);
    for(uint16_t i = 0; i < 2; i++) {
      strip.setPixelColor(i, strip.Color(0,255,0));
      strip.show();
    }
  }
  else if(num == 1) {
    for(uint16_t i = 0; i < 16; i++)
      strip.setPixelColor(i, false);
    for(uint16_t i = 0; i < 4; i++) {
      if(i<2)
      strip.setPixelColor(i, strip.Color(0,255,0));
      else
      strip.setPixelColor(i, strip.Color(255 - i * 7,0,0));
      strip.show();
    }
  }
  else if(num == 2) {
    for(uint16_t i = 0; i < 16; i++)
      strip.setPixelColor(i, false);
    for(uint16_t i = 0; i < 6; i++) {
      if(i<2)
      strip.setPixelColor(i, strip.Color(0,255,0));
      else if(i < 4)
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
      if(i<2)
      strip.setPixelColor(i, strip.Color(0,255,0));
      else if(i < 4)
      strip.setPixelColor(i, strip.Color(255 - i * 7,0,0));
      else if(i<6)
      strip.setPixelColor(i,strip.Color(125,31,3));
      else
      strip.setPixelColor(i, strip.Color(255 - i * 4,165 - i * 9,0));
      strip.show();
    }
  }
  else if(num == 4) {
    for(uint16_t i = 0; i < 16; i++)
      strip.setPixelColor(i, false);
    for(uint16_t i = 0; i < 10; i++) {
      if(i<2)
      strip.setPixelColor(i, strip.Color(0,255,0));
      else if(i < 4)
      strip.setPixelColor(i, strip.Color(255 - i * 7,0,0));
      else if(i<6)
      strip.setPixelColor(i,strip.Color(125,31,3));
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
      if(i<2)
      strip.setPixelColor(i, strip.Color(0,255,0));
      else if(i < 4)
      strip.setPixelColor(i, strip.Color(255 - i * 7,0,0));
      else if(i<6)
      strip.setPixelColor(i,strip.Color(125,31,3));
      else if( i < 8)
      strip.setPixelColor(i, strip.Color(255 - i * 4,165 - i * 9,0));
      else if(i<10)
      strip.setPixelColor(i, strip.Color(0,255 - i * 9,127 - i * 5));
      else 
      strip.setPixelColor(i,strip.Color(0,0,255));
      strip.show();
    }
  }
  else if(num == 6) {
    for(uint16_t i = 0; i < 16; i++)
      strip.setPixelColor(i, false);
    for(uint16_t i = 0; i < 14; i++) {
      if(i<2)
      strip.setPixelColor(i, strip.Color(0,255,0));
      else if(i < 4)
      strip.setPixelColor(i, strip.Color(255 - i * 7,0,0));
      else if(i<6)
      strip.setPixelColor(i,strip.Color(125,31,3));
      else if( i < 8)
      strip.setPixelColor(i, strip.Color(255 - i * 4,165 - i * 9,0));
      else if(i<10)
      strip.setPixelColor(i, strip.Color(0,255 - i * 9,127 - i * 5));
      else if(1<12)
      strip.setPixelColor(i,strip.Color(0,0,255));
      else
      strip.setPixelColor(i, strip.Color(175 - i * 4,238 - i * 9,238 - i * 3));
      strip.show();
    }
  }
  else if(num == 7) {
    
    for(uint16_t i = 0; i < 16; i++)
      strip.setPixelColor(i, false);
    for(uint16_t i = 0; i < 16; i++) {
     if(i<2)
      strip.setPixelColor(i, strip.Color(0,255,0));
      else if(i < 4)
      strip.setPixelColor(i, strip.Color(255 - i * 7,0,0));
      else if(i<6)
      strip.setPixelColor(i,strip.Color(125,31,3));
      else if( i < 8)
      strip.setPixelColor(i, strip.Color(255 - i * 4,165 - i * 9,0));
      else if(i<10)
      strip.setPixelColor(i, strip.Color(0,255 - i * 9,127 - i * 5));
      else if(1<12)
      strip.setPixelColor(i,strip.Color(0,0,255));
      else if(i<14)
      strip.setPixelColor(i, strip.Color(175 - i * 4,238 - i * 9,238 - i * 3));
      else
      strip.setPixelColor(i, strip.Color(0,0,0));
      strip.show();
    }
  }
}
