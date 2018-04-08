#ifndef _SUBFUNCTION_H_
#define _SUBFUNCTION_H_


/* 定数 */
#define OFF (0) /* LED OFF */
#define ON (1) /* LED ON */
#define TARGET_MAX (8) /* 的の最大数 */
#define BULLET_MAX (20) /* 最大装填数 */
#define SCORE_MIN_UNIT (100) /* スコアの最小単位 */
#define SCORE_PERFECT (SCORE_MIN_UNIT*TARGET_MAX) /* パーフェクトスコア */

/* 関数 */
extern void target_hit(unsigned char); /* 当たり判定処理関数 */
extern void gun_shoot(void); /* 射撃処理 */
extern void gun_reload(void); /* リロード処理 */
extern unsigned char gun_getBulletInfo(void); /* bullet値のgetter */
extern void score_reset(void); /* スコアリセット */
extern unsigned char score_getScore(void); /* スコアのgetter */

#endif /* _SUBFUNCTION_H_ */
