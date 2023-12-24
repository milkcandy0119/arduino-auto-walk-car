#include <SoftwareSerial.h> // 引用「軟體序列埠」程式庫

#define OTP OUTPUT
#define INP INPUT
#define H HIGH
#define L LOW

// L = 左, R = 右
// F = 前, B = 後
// H-F L-B 
const int LB_I = 12; // 馬達 LB 的正反轉接腳
const int LB_E = 10; // 馬達 LB 的致能接腳

// H-B L-F
const int RB_E = 5; // 馬達 RB 的致能接腳 
const int RB_I = 4; // 馬達 RB 的正反轉接腳 

// H-F L-B
const int LF_I = 8; // 馬達 LF 的正反轉接腳 
const int LF_E = 9; // 馬達 LF 的致能接腳 

// H-B L-F
const int RF_E = 6; // 馬達 RF 的致能接腳 
const int RF_I = 7; // 馬達 RF 的正反轉接腳 

const int pin[] = {4, 5, 6, 7, 8, 9, 10, 12};

int speed = 130;

SoftwareSerial BT(3, 11); // 設定軟體序列埠(接收腳, 傳送腳)

void setup() {
  BT.begin(9600);
  Serial.begin(9600);
  for(int i=0;i<8;i++)  pinMode(pin[i], OTP);
  Serial.println("bot is ready");
}

void loop() {
  char command = '0';
  if(BT.available()){//如果藍牙有傳資料過來
    command = BT.read();    //把讀到的資料丟給i，這次是用char
    Serial.print("command: ");
    Serial.println(command);
  }

  switch(command){
    case 'm': // init
      speed = 100;
      break;
    
    case 'w': // 馬達轉向：前進
       forward();
       break;
    case 's': // 馬達轉向：後退
      backward();
      break;
    case 'a': // 馬達轉向：向左移動
      left();
      break;
    case 'd': // 馬達轉向：向左移動
      right();
      break;
    case 'n': // 馬達停止
      stop();
      break;
      
    case 'q':
      left_forward(); // 馬達轉向：向左前移動
      break;
    case 'z':
      left_backward(); // 馬達轉向：向左後移動
      break;
    case 'e':
      right_forward(); // 馬達轉向：向右前移動
      break;
    case 'c':
      right_backward(); // 馬達轉向：向右後移動
      break;

    case 'o': // 馬達轉向：左轉
      turn_left();
      break;
    case 'k': // 馬達轉向：右轉
      turn_right();
      break;

    case 'l': // 馬達加速
      speed = 255;
      break;
    case 'p': // 馬達減速
      speed = 130;
      break;
  }
}



/*=====基礎移動=====*/

void stop(){ // 馬達停止
  analogWrite(RF_E, 0);
  digitalWrite(RF_I, L); 
  analogWrite(LF_E, 0);
  digitalWrite(LF_I, L); 
  analogWrite(RB_E, 0);
  digitalWrite(RB_I, L); 
  analogWrite(LB_E, 0);
  digitalWrite(LB_I, L); 
}

void forward(){ // 馬達轉向：前進
  analogWrite(RF_E, speed); 
  digitalWrite(RF_I, L);

  analogWrite(LF_E, speed); 
  digitalWrite(LF_I, H);
  
  analogWrite(RB_E, speed); 
  digitalWrite(RB_I, L);

  analogWrite(LB_E, speed); 
  digitalWrite(LB_I, H);
}

void backward(){ // 馬達轉向：後退
  analogWrite(RF_E, speed); 
  digitalWrite(RF_I, H);

  analogWrite(LF_E, speed); 
  digitalWrite(LF_I, L);
  
  analogWrite(RB_E, speed); 
  digitalWrite(RB_I, H);

  analogWrite(LB_E, speed); 
  digitalWrite(LB_I, L);
}

void left(){ // 馬達轉向：向左移動
  analogWrite(RF_E, speed); 
  digitalWrite(RF_I, H);

  analogWrite(LF_E, speed); 
  digitalWrite(LF_I, H);
  
  analogWrite(RB_E, speed); 
  digitalWrite(RB_I, H);

  analogWrite(LB_E, speed); 
  digitalWrite(LB_I, H);
}

void right(){ // 馬達轉向：向右移動
  analogWrite(RF_E, speed); 
  digitalWrite(RF_I, L);

  analogWrite(LF_E, speed); 
  digitalWrite(LF_I, L);
  
  analogWrite(RB_E, speed); 
  digitalWrite(RB_I, L);

  analogWrite(LB_E, speed); 
  digitalWrite(LB_I, L);
}

/*=====斜向移動=====*/

void left_forward(){ // 馬達轉向：向左前移動
  analogWrite(RF_E, 0); 
  digitalWrite(RF_I, L);

  analogWrite(LF_E, speed); 
  digitalWrite(LF_I, H);
  
  analogWrite(RB_E, speed); 
  digitalWrite(RB_I, H);

  analogWrite(LB_E, 0); 
  digitalWrite(LB_I, L);
}

void left_backward(){ // 馬達轉向：向左後移動
  analogWrite(RF_E, 0); 
  digitalWrite(RF_I, L);

  analogWrite(LF_E, speed); 
  digitalWrite(LF_I, L);
  
  analogWrite(RB_E, speed); 
  digitalWrite(RB_I, L);

  analogWrite(LB_E, 0); 
  digitalWrite(LB_I, L);
}

void right_forward(){ // 馬達轉向：向右前移動
  analogWrite(RF_E, speed); 
  digitalWrite(RF_I, L);
  analogWrite(LF_E, 0); 
  digitalWrite(LF_I, L);
  
  analogWrite(RB_E, 0); 
  digitalWrite(RB_I, L);
  analogWrite(LB_E, speed); 
  digitalWrite(LB_I, L);
}

void right_backward(){ // 馬達轉向：向右後移動
  analogWrite(RF_E, speed); 
  digitalWrite(RF_I, H);
  analogWrite(LF_E, 0); 
  digitalWrite(LF_I, L);
  
  analogWrite(RB_E, 0); 
  digitalWrite(RB_I, L);
  analogWrite(LB_E, speed); 
  digitalWrite(LB_I, H);
}

/*=====轉向=====*/

void turn_right(){ // 馬達轉向：右轉
  analogWrite(RF_E, speed); 
  digitalWrite(RF_I, L);

  analogWrite(LF_E, speed); 
  digitalWrite(LF_I, L);
  
  analogWrite(RB_E, speed); 
  digitalWrite(RB_I, H);

  analogWrite(LB_E, speed); 
  digitalWrite(LB_I, H);
}

void turn_left(){ // 馬達轉向：左轉
  analogWrite(RF_E, speed); 
  digitalWrite(RF_I, H);

  analogWrite(LF_E, speed); 
  digitalWrite(LF_I, H);
  
  analogWrite(RB_E, speed); 
  digitalWrite(RB_I, L);

  analogWrite(LB_E, speed); 
  digitalWrite(LB_I, L);
}