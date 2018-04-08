/* main.ino 
 * 概要：制御のメインモジュール
 * 処理：モータ制御モジュールとの通信
 *      的の当たり判定周りの制御モジュールとの通信
 *      銃の残り段数管理、音声処理等の制御
 *      ランキング表示,音声出力等用PCとの通信
 */

#include <Wire.h>
#include "define.h"
#include "subfunction.h"

void setup() {
  Wire.begin();
    
  /* モータ制御モジュールの初期設定 */
  Wire.beginTransmission(MOTOR_ADDRESS);
  Wire.write(START); /* スタート処理(モータの動作を開始させる指令を出す) */
  Wire.endTransmission();

  /* 的当たり判定関係の初期設定 */
  Wire.beginTransmission(TARGET_ADDRESS);
  Wire.write(START); /* スタート処理(全てのLEDを消灯させる指令を出す) */
  Wire.endTransmission();

  /* 銃関係の初期設定 */
  gun_reload();

  /* PC関係の初期設定 */
  Serial.begin(9600);
  Serial.print("s"); /* スタートの合図 */

  /* スコアの初期化 */
  score_reset();
}

/*
 * ★loopで行う処理：
 * ・的の当たり判定情報の受け取り
 * ・銃のトリガーが引かれた情報の受取り
 * ・PCへ送る情報のまとめ
 * ・PCへの情報の送信
 * ・終了判定の確認
 */
void loop() {
  /* 的の当たり判定情報の受取り */
  Wire.requestFrom(TARGET_ADDRESS, 1);
  target_hit(Wire.read());
  
  /*銃のトリガー情報の受取り */ 
  if(digitalRead(PIN_GUN) == HIGH)
  {
    gun_shoot();
    Serial.print("g"); /* 射撃音声出力の要請 */
    Serial.print(gun_getBulletInfo(), DEC); /* 残り弾数の送信 */
  }

  Serial.print(score_getScore(), DEC); /*スコアの送信 */
  
  /* ★ゲームの終了判定 */
  if(gun_getBulletInfo() == 0 || score_getScore() == SCORE_PERFECT /* || タイムアップ */  ) {
    finish();
    while(1); /* ★再起動まで待機 */
  }
}

/* ゲームの停止処理 */
void finish()
{
  Wire.beginTransmission(MOTOR_ADDRESS);
  Wire.write(STOP); /* ストップ処理(モータの動作を停止させる指令を出す) */
  Wire.endTransmission();

  /* ★ゲーム終了後にLEDは点灯しっぱなし？ */
  
  Serial.print("f"); /* 終了の合図 */
}

