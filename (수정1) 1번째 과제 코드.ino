#define Up_R 25 //상 신호등
#define Up_Y 26
#define Up_G 27
#define Do_R 4 //하 신호등
#define Do_Y 5
#define Do_G 6
#define Le_R 7 // 좌 신호등
#define Le_Y 8
#define Le_G 9
#define Ri_R 22 // 우 신호등
#define Ri_Y 23
#define Ri_G 24 
#define Button_A 2 // 스위치
int delaytime = 40000; //40초
volatile bool state = true; //스위치 변수, 누를 시 false

void setup() {  // OUTPUT 세팅
  pinMode(Up_R, OUTPUT);
  pinMode(Up_G, OUTPUT);
  pinMode(Up_Y, OUTPUT);
  pinMode(Do_R, OUTPUT);
  pinMode(Do_G, OUTPUT);
  pinMode(Do_Y, OUTPUT);
  pinMode(Le_R, OUTPUT);
  pinMode(Le_G, OUTPUT);
  pinMode(Le_Y, OUTPUT);
  pinMode(Ri_R, OUTPUT);
  pinMode(Ri_G, OUTPUT);
  pinMode(Ri_Y, OUTPUT);
  pinMode(Button_A, INPUT_PULLUP); //기본값 HIGH input과는 다르게 프로세서 내부 저항을 사용
  attachInterrupt(0,Botton, FALLING); // 인터럽트 0 은 핀 2에 상호작용 따라서 스위치를 2번에 달것
}

void loop() {
// -----------------------------------------------------
//순서는 상-하-좌-우
// -----------------------------------------------------


//------------맨처음, 상 하 신호등만 초록색 ----------------  
digitalWrite(Le_R, HIGH);
digitalWrite(Ri_R, HIGH);
digitalWrite(Do_R, LOW);
digitalWrite(Up_R, LOW);
digitalWrite(Up_G, HIGH);
digitalWrite(Do_G, HIGH); 
for(int count=0;count<40;count++){ //40초간 초록불 유지
  if(state == false){ //스위치가 눌리면
    delay(1000); //1초 후
    digitalWrite(Up_G, LOW);
    digitalWrite(Do_G, LOW);
    Yellow(Up_Y, Do_Y);
    digitalWrite(Up_R, HIGH);
    digitalWrite(Do_R, HIGH); //점멸 후 빨간색
    digitalWrite(Le_G, HIGH);
    digitalWrite(Ri_G, HIGH);
    digitalWrite(Le_R, LOW);
    digitalWrite(Ri_R, LOW);
    delay(5000);
    digitalWrite(Le_G, LOW);
    digitalWrite(Ri_G, LOW);
    Yellow(Le_Y, Ri_Y);
    state = true;
    if(count>=15){ //15초 이상이 지난 후 누르면 for문 빠져나옴 40 - 25
      break; 
    }
    else{ //25초 이하라면 다시 상하 켜줌
      digitalWrite(Up_R, LOW);
      digitalWrite(Do_R, LOW);
      digitalWrite(Up_G, HIGH);
      digitalWrite(Do_G, HIGH);
      digitalWrite(Le_G, LOW);
      digitalWrite(Ri_G, LOW);
      digitalWrite(Le_R, HIGH);
      digitalWrite(Ri_R, HIGH);
      count = count + 25; //25 초가 지난만큼 추가 Yellow 2 +  초록불5초=25
    }
  }
  delay(1000);
}
digitalWrite(Up_R, LOW);
digitalWrite(Do_R, LOW);
digitalWrite(Up_G, LOW);
digitalWrite(Do_G, LOW);
Yellow(Up_Y, Do_Y);
digitalWrite(Up_R, HIGH);
digitalWrite(Do_R, HIGH);
digitalWrite(Le_R, LOW);
digitalWrite(Ri_R, LOW);
digitalWrite(Le_G, HIGH);
digitalWrite(Ri_G, HIGH);
delay(delaytime); //40초간 좌우 초록불 온
Yellow(Ri_Y, Le_Y);
digitalWrite(Le_G, LOW);
digitalWrite(Ri_G, LOW);
}











//----------------------------------함수들--------------------------------
void Botton(){ //스위치가 눌렸을 때 실행되는 함수
 if(digitalRead(Do_G) == HIGH && digitalRead(Up_G) == HIGH) state = false; //스위치가 눌리면 state의 값을 바꿔준다
}




void Yellow(const int LED1, const int LED2) {  //yellow신호 점멸
   for(int i =0; i < 10; i++) {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    delay(500);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    delay(500);
   }
}

//----------------------------------------------------------------------------
