/* subfunction.ino
 *  MAINで使うsub関数の定義
 */

#include "subfunction.h"

/* 内部変数 */
static unsigned char target_array[TARGET_MAX]; /* 的の当たり判定状況管理用配列 */
static char bullet; /* 残り弾薬数 */
static char score; /* スコア */


/* 当たり判定処理関数 */
/* スコアの加算も行う */
int target_hit(byte target_num)
{
  int hit_f = 0; // 既に当たった判定がされていないとき、1
  /* 既に当たった判定がされている的だった場合、無視する */
  if(target_array[target_num] != ON) {
    target_array[target_num] = ON;
    score += SCORE_MIN_UNIT;
    hit_f = 1;
  }

  return hit_f;
}

/* 射撃処理 */
void gun_shoot(void)
{
  // 残り弾数をマイナス
  bullet--;
}

/* リロード処理 */
void gun_reload(void)
{
  bullet = BULLET_MAX;
}

/* 残り弾数のgetter */
char gun_getBulletInfo(void)
{
  return bullet;
}


/* スコアリセット */
void score_reset(void)
{
  score = 0;
}

/* スコアのgetter */
char score_getScore(void)
{
  return score;
}

/* 当たり判定配列初期化 */
void target_init(void) {
  for(int i = 0; i < TARGET_MAX; i++) {
      target_array[i] = OFF;
  }
}
