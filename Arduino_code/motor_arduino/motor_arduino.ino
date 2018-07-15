/* motor_arduino.ino
 * 的動作Arduino の制御
 */

#include <Wire.h>
#include <Servo.h>
#include "motor_define.h"

/* サーボ宣言 */
Servo servo1, servo2, servo3;

unsigned char status; // ステータス
byte b; // Wire.read用

void setup() {
  Serial.begin(9600);
  // Wire定義
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(slv_receive);

  // サーボ設定
  servo1.attach(SERVO1);
  servo2.attach(SERVO2);
  servo3.attach(SERVO3);

  // 初期状態の設定
  status = WAIT;
}

void loop() {
  if(status != WAIT && status != START && status != STOP){
    status = RUNNING;
  }
  if(status == WAIT) {
    // 待機状態

    // MASTER からSTARTが送られたらステータスがSTARTに遷移
    if(b == START) {
      status = START;
    }
  } else if(status == START) {
    // ゲーム開始時状態

    // パカパカをあける
    servo1.write(0);
    servo2.write(0);
    servo3.write(0);
    delay(1000);

    // ゲーム中状態に遷移
    status = RUNNING;

  } else if(status == RUNNING) {
    // ゲーム中状態

    /* 当たった的がパカパカなら対応するサーボを動かす */
    if(b == TARGET1) {
      servo1.write(90);
    }
    if(b == TARGET2) {
      servo2.write(90);
    }
    if(b == TARGET3) {
      servo3.write(90);
    }

    /* 観覧車を動かす */
    READ_VR();
    PWM_SYORI();
    delay(50);

    /* モグラを動かす */
    PWM_SYORI_MOGURA();
    delay(50);

    // MASTERからSTOPが送られたら終了状態に遷移
    if(b == STOP) {
      status = STOP;
    }
  } else if(status == STOP) {
    // 終了処理
  } else {
    // ここにはこない
  }
}

/* 観覧車モータ用処理１ */
void READ_VR(void) {
  VR_VALUE =analogRead(VR_PIN);
  if((VR_VALUE >= 500) && (VR_VALUE <= 523)) {
    STATUS = 0;
    PWM_VALUE = 0;
  }
  if(VR_VALUE <= 499) {
    STATUS = 1;
    PWM_VALUE = (500 - VR_VALUE)/2;
  }
  if(VR_VALUE >= 524) {
    STATUS = 2;
    PWM_VALUE = (VR_VALUE - 523)/2;
  }
}

/* 観覧車モータ用処理２ */
void PWM_SYORI(void) {
  if(STATUS == 0) {
    analogWrite(IN1, 0);
    analogWrite(IN2, 0);
  }
  if(STATUS == 1) {
    analogWrite(IN1, 255);
    analogWrite(IN2, PWM_VALUE);
  }
  if(STATUS == 2) {
    analogWrite(IN1, 0);
    analogWrite(IN2, PWM_VALUE);
  }
}

/* モグラ用モータ処理 */
void PWM_SYORI_MOGURA(void) {
  analogWrite(IN3, 255);
  analogWrite(IN4, 255);
}

/*MASTERから情報が送られたときの割り込み関数 */
void slv_receive() {
  // 変数bに送られた情報を格納する
  while (Wire.available()) {
    status = Wire.read();
  }

  // デバッグ用 ///////
  Serial.print("Info from MASTER:");
  Serial.println(status);
  ////////////////////
}
