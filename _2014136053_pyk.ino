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
int delaytime = 10000; //40초
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


//------------맨처음, 상 신호등만 초록색 ----------------  
digitalWrite(Le_R, HIGH);
digitalWrite(Ri_R, HIGH);
digitalWrite(Do_R, HIGH);
digitalWrite(Up_R, LOW);
digitalWrite(Up_G, HIGH);
delay(delaytime); //40초 동안 유지
//------------------------------------------------------.
digitalWrite(Up_G, LOW); // 상 신호등 초록색 꺼짐

// -------------초록색 -> 빨간색 될때 ------------------------
Yellow(Up_Y);
// --------------------------------------------------------
// ---------------------하 신호등 빨간불이 초록불로 바뀜------------------------
digitalWrite(Up_R, HIGH); 
digitalWrite(Do_R, LOW);
digitalWrite(Do_G, HIGH); 
// ------------------------------------------------------------------------------

for(int count=0; count<1000;count++) { // 앞으로 10초동안 반복
 if(state == false) { //스위치가 눌렸으면
    delay(1000); //3초 대기
    digitalWrite(Do_G, LOW); // 하 신호등 초록불을 꺼준다
    Yellow(Do_Y); // 하 신호등 노란불 점멸
    digitalWrite(Do_R, HIGH); // 하 신호등 빨간불을 켠다
    state = true; // 상태를 처음의 ture 로 바꿔줌
 }
 if(count == (delaytime/1000)) break;
 delay(1000); // 무조건 적으로 10초 기다릴것
}


if(digitalRead(Do_G) == HIGH) { //스위치가 눌리지 않았을 경우 진행
    digitalWrite(Do_G, LOW);  // 하 초록불 꺼짐
    Yellow(Do_Y); // 하 노란불 점멸
    digitalWrite(Do_R, HIGH); // 하 빨간불 켜짐
}



digitalWrite(Do_R, HIGH);  // 하 빨간불 켜져있음
digitalWrite(Le_R, LOW); // 좌 빨간불 꺼짐
digitalWrite(Le_G, HIGH); // 좌 신호등 초록불만 켜짐
delay(delaytime); //40초간 유지
digitalWrite(Le_G, LOW); //좌 초록불 꺼짐
Yellow(Le_Y); //좌 노란불 점멸
digitalWrite(Le_R, HIGH); // 좌 빨간불 켜짐


digitalWrite(Ri_R, LOW); // 우 빨간불 꺼짐
digitalWrite(Ri_G, HIGH);  // 우 초록불 켜짐
delay(delaytime); 
digitalWrite(Ri_G, LOW); // 우 초록불 꺼짐
Yellow(Ri_Y); // 우 노란불 점멸
digitalWrite(Ri_G, LOW); // 우 초록불 꺼짐
digitalWrite(Ri_R, HIGH); // 우 빨간불 켜짐

}











//----------------------------------함수들--------------------------------
void Botton(){ //스위치가 눌렸을 때 실행되는 함수
 if(digitalRead(Do_G) == HIGH) state = false; //스위치가 눌리면 state의 값을 바꿔준다
}




void Yellow(const int LED) {  //yellow신호 점멸
   for(int i =0; i < 10; i++) {
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    delay(500);
   }
}

//----------------------------------------------------------------------------
