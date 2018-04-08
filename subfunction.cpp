/* subfunction.cpp
 *  サブ関数の定義
 */

#include "subfunction.h"

/* 内部変数 */
static unsigned char target_array[TARGET_MAX] = {OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF}; /* 的の当たり判定状況管理用配列 */
static unsigned char bullet; /* 残り弾薬数 */
static unsigned char score; /* スコア */


/* 当たり判定処理関数 */
/* スコアの加算も行う */
void target_hit(unsigned char target_num)
{
  target_array[target_num] = ON;
  score += SCORE_MIN_UNIT;
}

/* 射撃処理 */
void gun_shoot(void)
{
  bullet--;
}

/* リロード処理 */
void gun_reload(void)
{
  bullet = BULLET_MAX;
}

/* 残り弾数のgetter */
unsigned char gun_getBulletInfo(void)
{
  return bullet;
}


/* スコアリセット */
void score_reset(void)
{
  score = 0;
}

/* スコアのgetter */
unsigned char score_getScore(void)
{
  return score;
}

