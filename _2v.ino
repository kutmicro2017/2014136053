#define UpDown_R 4 //상하 신호등
#define UpDown_Y 5
#define UpDown_G 6
#define LeftRight_R 7 // 좌우 신호등
#define LeftRight_Y 8
#define LeftRight_G 9
#define Button_A 2 // 스위치
int delaytime = 40000; //40초
volatile bool state = true; //스위치 변수, 누를 시 false


int walkSignNumber[10][8][4] = {

  { //0
    { 0, 1, 1, 0 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 0, 1, 1, 0 }
  },

  { //1
    { 0, 0, 1, 0 },
    { 0, 1, 1, 0 },
    { 1, 1, 1, 0 },
    { 0, 1, 1, 0 },
    { 0, 1, 1, 0 },
    { 0, 1, 1, 0 },
    { 0, 1, 1, 0 },
    { 1, 1, 1, 1 }
  },

  { //2
    { 0, 1, 1, 0 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 0, 0, 0, 1 },
    { 0, 0, 1, 0 },
    { 0, 1, 0, 0 },
    { 1, 0, 0, 0 },
    { 1, 1, 1, 1 }
  },

  { //3
    { 0, 1, 1, 0 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 0, 0, 0, 1 },
    { 0, 1, 1, 1 },
    { 0, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 0, 1, 1, 0 }
  },

  { //4
    { 0, 0, 1, 0 },
    { 0, 1, 1, 0 },
    { 1, 0, 1, 0 },
    { 1, 1, 1, 1 },
    { 0, 0, 1, 0 },
    { 0, 0, 1, 0 },
    { 0, 0, 1, 0 },
    { 0, 0, 1, 0 }
  },

  { //5
    { 1, 1, 1, 1 },
    { 1, 0, 0, 0 },
    { 1, 0, 0, 0 },
    { 1, 1, 1, 0 },
    { 0, 0, 0, 1 },
    { 0, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 0, 1, 1, 0 }
  },

  { //6
    { 0, 1, 1, 1 },
    { 1, 0, 0, 0 },
    { 1, 0, 0, 0 },
    { 1, 1, 1, 0 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 0, 1, 1, 0 }
  },

  { //7
    { 1, 1, 1, 1 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 0, 0, 0, 1 },
    { 0, 0, 1, 0 },
    { 0, 1, 0, 0 },
    { 0, 1, 0, 0 },
    { 0, 1, 0, 0 }
  },

  { //8
    { 0, 1, 1, 0 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 0, 1, 1, 0 },
    { 0, 1, 1, 0 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 0, 1, 1, 0 }
  },

  { //9
    { 0, 1, 1, 0 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 0, 1, 1, 1 },
    { 0, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 0, 1, 1, 0 }
  }
};

int signImage[2][8][8] = {
  { //stop
    { 0, 0, 0, 1, 1, 0, 0, 0},
    { 0, 0, 1, 0, 0, 1, 0, 0},
    { 0, 0, 0, 1, 1, 0, 0, 0},
    { 0, 0, 1, 1, 1, 1, 0, 0},
    { 0, 1, 0, 1, 1, 0, 1, 0},
    { 0, 0, 0, 1, 1, 0, 0, 0},
    { 0, 0, 1, 0, 0, 1, 0, 0},
    { 0, 0, 1, 0, 0, 1, 0, 0}
  },

  { //go
    { 0, 0, 0, 1, 1, 0, 0, 0},
    { 0, 0, 1, 0, 0, 1, 0, 0},
    { 0, 0, 0, 1, 1, 0, 0, 0},
    { 1, 0, 1, 1, 1, 1, 1, 0},
    { 0, 1, 0, 1, 1, 0, 0, 1},
    { 0, 0, 1, 0, 0, 1, 0, 0},
    { 0, 1, 0, 0, 0, 0, 1, 0},
    { 0, 0, 1, 0, 0, 0, 0, 1}
  }

};


int walkPedMatrixCol[] = { 40, 42, 44, 46, 48, 5, 4, 3  };
int walkPedMatrixRow[] = { 41, 43, 45, 47, 49, 14, 15, 16 }; //숫자 나타내는 도트매트릭스

int drowSignalCol[] = { 22, 24, 26, 28, 30, 32, 34, 36 };
int drowSignalRow[] = { 23, 25, 27, 29, 31, 33, 35, 37 }; //아이콘 나타내는 도트매트릭스
//보행자 신호등은 상하 신호등이 빨간색일 때만 다운카운트

//col에 0v row에 5v가 들어가야 켜짐




void setup() {  // OUTPUT 세팅


  pinMode(UpDown_R, OUTPUT);
  pinMode(UpDown_G, OUTPUT);
  pinMode(UpDown_Y, OUTPUT);
  pinMode(LeftRight_R, OUTPUT);
  pinMode(LeftRight_G, OUTPUT);
  pinMode(LeftRight_Y, OUTPUT);
  pinMode(Button_A, INPUT_PULLUP); //기본값 HIGH input과는 다르게 프로세서 내부 저항을 사용
  attachInterrupt(0,Botton, FALLING); // 인터럽트 0 은 핀 2에 상호작용 따라서 스위치를 2번에 달것
}

void loop() {
// -----------------------------------------------------
//순서는 상-하-좌-우
// -----------------------------------------------------


//------------맨처음, 상 하 신호등만 초록색 ----------------  
digitalWrite(LeftRight_R, HIGH);
digitalWrite(UpDown_R, LOW);
digitalWrite(UpDown_G, HIGH);
for(int count=0;count<40;count++){ //40초간 초록불 유지
  if(state == false){ //스위치가 눌리면
    delay(1000); //1초 후
    digitalWrite(UpDown_G, LOW);
    Yellow(UpDown_Y);
    digitalWrite(UpDown_R, HIGH);
    digitalWrite(LeftRight_R, LOW);
    digitalWrite(LeftRight_G, HIGH);
    delay(5000);
    digitalWrite(LeftRight_G, LOW);
    Yellow(LeftRight_Y);
    state = true;
    if(count>=25){ //25초 이상이 지난 후 누르면 for문 빠져나옴
      break; 
    }
    else{ //25초 이하라면 다시 상하 켜줌
      digitalWrite(UpDown_R, LOW);
      digitalWrite(UpDown_G, HIGH);
      digitalWrite(LeftRight_G, LOW);
      digitalWrite(LeftRight_R, HIGH);
      count = count + 15; //15초가 지난만큼 추가
    }
  }
  delay(1000);
}
digitalWrite(UpDown_R, LOW);
digitalWrite(UpDown_G, LOW);
Yellow(UpDown_Y);
digitalWrite(UpDown_R, HIGH);
digitalWrite(LeftRight_R, LOW);
digitalWrite(LeftRight_G, HIGH);
delay(delaytime); //40초간 좌우 초록불 온
digitalWrite(LeftRight_G, LOW);
Yellow(LeftRight_Y);
}











//----------------------------------함수들--------------------------------
void Botton(){ //스위치가 눌렸을 때 실행되는 함수
 if(digitalRead(UpDown_G) == HIGH) state = false; //스위치가 눌리면 state의 값을 바꿔준다
}


void YellowBlink(int pin) {
  unsigned long startTime, endTime;
  startTime = endTime = millis();
  while (endTime - startTime <= YellowBlinkTime) {
    printNumMatrix(delaytime / 1000);
    printSignalMatrix(0);
    unsigned long blinkStart, blinkEnd;
    blinkStart = blinkEnd = millis();
    while (blinkEnd - blinkStart < 500) {
      printNumMatrix(delaytime / 1000);
      printSignalMatrix(0);
      digitalWrite(pin, HIGH);
      blinkEnd = millis();
    }
    blinkStart = blinkEnd = millis();
    while (blinkEnd - blinkStart < 500) {
      printNumMatrix(delaytime / 1000);
      printSignalMatrix(0);
      digitalWrite(pin, LOW);
      blinkEnd = millis();
    }
    endTime = millis();
  }
}
void Yellow(const int LED) {  //yellow신호 점멸
   printNumMatrix(delaytime / 1000);
   printSignalMatrix(0);
   for(int i =0; i < 250; i++) {
    digitalWrite(LED, HIGH);
    printNumMatrix(delaytime / 1000);
    printSignalMatrix(0);
    delay(10);
   }
 
   for(int i =0; i<250; i++){
    delay(10);
    digitalWrite(LED, LOW);
    printNumMatrix(delaytime / 1000);
    printSignalMatrix(0);
    
   }
}

void printSignalMatrix(int num) { //정지(0)인지 통행 가능(1)인지 아이콘 출력
  for (int r = 0; r < 8; r++) {
    CleanSignalMatrix();
    digitalWrite(drowSignalRow[r], HIGH);
    for (int c = 0; c < 8; ++c) {
      if (signImage[num][r][c]) digitalWrite(drowSignalCol[c], LOW);
    }
    delay(1);
    CleanSignalMatrix();
  }
}



void CleanMatrix() { //도트를 모두 끈다
  for (int i = 0; i < 8; i++) {
    digitalWrite(walkPedMatrixRow[i], LOW);
    digitalWrite(walkPedMatrixCol[i], HIGH);
  }
}

void CleanSignalMatrix() {//도트를 모두 끈다
  for (int i = 0; i < 8; i++) {
    digitalWrite(drowSignalRow[i], LOW);
    digitalWrite(drowSignalCol[i], HIGH);
  }
}

void printNumMatrix(int num) { //남은 시간 출력
  for (int r = 0; r < 8; r++) {
    CleanMatrix();
    digitalWrite(walkPedMatrixRow[r], HIGH);
    for (int c = 0; c < 4; ++c) { //10의 자리
      if (walkSignNumber[num / 10][r][c]) digitalWrite(walkPedMatrixCol[c], LOW);
    }
    for (int c = 0; c < 4; ++c) { //1의 자리
      if (walkSignNumber[num % 10][r][c]) digitalWrite(walkPedMatrixCol[c + 4], LOW);
    }
    delay(1); //시간지연을 조금이라도 줘야 도트가 깨끗하게 보임
    CleanMatrix();
  }
}









//----------------------------------------------------------------------------

