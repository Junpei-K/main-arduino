/* main_arduino.ino
 * MAIN Arduino の制御
 */

#include <Wire.h>
#include "main_define.h"
#include "subfunction.h"

void setup() {
  Wire.begin();
  pinMode(PIN_GUN, INPUT); // トリガー
  pinMode(PIN_SINDOU, OUTPUT); // 振動モータ
  digitalWrite(PIN_SINDOU, LOW); // 振動モータ停止

  /* モータ制御モジュールの初期設定 */
  Wire.beginTransmission(MOTOR_ADDRESS);
  Wire.write(START); /* スタート処理(モータの動作を開始させる指令を出す) */
  Wire.endTransmission();

  /* 的当たり判定関係の初期設定 */
  Wire.beginTransmission(TARGET_ADDRESS);
  Wire.write(START); /* スタート処理(全てのLEDを消灯させる指令を出す) */
  Wire.endTransmission();

  /* PC関係の初期設定 */
  Serial.begin(115200);
  Serial.write("s"); /* スタートの合図 */

  /* スコアの初期化 */
  score_reset();

  /* 銃関係の初期設定 */
  gun_reload();

  /* 当たり判定の初期化 */
  target_init();
}

void loop() {
  /* ローカル変数 */
  byte hit_num; // SLVからの当たり判定番号取得用
  char time_up; // PCからタイムアップ判定を受け取る用
  char bulletnum; //PCへ送る残り弾数
  char scorenum; //PCへ送るスコア
  int hit_flag; // 当たった判定がされていない的に当たったフラグ

Serial.println(digitalRead(PIN_GUN));

  /*銃のトリガーON・OFFにより場合わけ */
  if(digitalRead(PIN_GUN) == HIGH)
  {
    // トリガーONのとき
    // デバッグ用 /////////////////
    Serial.println("TRIGGER_ON");
    //////////////////////////////

    digitalWrite(PIN_SINDOU, HIGH);

    // 残り弾数処理
    gun_shoot();

    // 残り弾数の取得
    bulletnum = gun_getBulletInfo();

    // Unity PC にトリガーONを伝える
    Serial.write("h");
    delay(100);
    // 続けて残り弾数を送る　★なくても良い
    Serial.write(bulletnum);
    delay(50);

    /* 的の当たり判定情報の受取り */
    // 的管理Arduinoに要求
    Wire.requestFrom(TARGET_ADDRESS, 1);
    while(Wire.available()) {
      // 当たり判定のあった的の番号を受け取る
      hit_num = Wire.read();

      // 既に当たった的かどうか判定する
      hit_flag = target_hit(hit_num);

      // デバッグ用 ///////////////////
      Serial.print("TARGET Number:");
      Serial.println(hit_num);
      ////////////////////////////////
    }
    if (hit_flag == 1) {
      // 的に当たった判定をPCに送る
      Serial.write("p");
      delay(50);

      // 的動作Arduino に当たった的番号を通知
      Wire.beginTransmission(MOTOR_ADDRESS);
      Wire.write(hit_num);
      Wire.endTransmission();

      Serial.println(hit_num);
    }
  } else {
    // トリガーOFFのとき
    // 振動モータOFF
    digitalWrite(PIN_SINDOU, LOW);

    // デバッグ用 //////////////////
    Serial.println("TRIGGER_OFF");
    ///////////////////////////////
  }

  // 現在スコアの取得
  scorenum = score_getScore();

  // Unity PC にスコアを送信　★なくても良い
  Serial.write(scorenum);
  delay(50);

  /* ゲームの終了判定 */
  // Unity PC からタイムアップしたかどうかを受け取る
  time_up = Serial.read();
  // 残り弾数が0 または スコア満点 または タイムアップでゲーム終了
  if(gun_getBulletInfo() == 0 || score_getScore() == SCORE_PERFECT || time_up == '1') {
    // 停止処理
    finish();
    while(1){} /* ★再起動まで待機 */
  }

  // ループ全体のディレイ //
  delay(300);
  /////////////////////////
}

/* ゲームの停止処理 */
void finish()
{
  // 的動作Arduino にゲーム終了を伝える
  Wire.beginTransmission(MOTOR_ADDRESS);
  Wire.write(STOP);
  Wire.endTransmission();

  // 的管理Arduino にゲーム終了を伝える
  Wire.beginTransmission(TARGET_ADDRESS);
  Wire.write(STOP);
  Wire.endTransmission();

  // Unity PC にゲーム終了を伝える
  Serial.write("f");
  delay(50);
}
