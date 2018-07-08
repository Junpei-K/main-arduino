#ifndef _MAIN_DEFINE_H_
#define _MAIN_DEFINE_H_

/* I2CのSLVアドレス */
#define TARGET_ADDRESS 8  // 的管理Arduino のSLVアドレス
#define MOTOR_ADDRESS 9   // 的動作Arduino のSLVアドレス

/* ピン番号 */
#define PIN_GUN 1   // トリガーのピン番号
#define PIN_SINDOU 2  // 振動モータのピン番号

/* SLVへの信号 */
#define START 101
#define STOP 103

/* トリガー状況 */
#define TRIGGER_OFF 0
#define TRIGGER_ON  1

#endif /* _MAIN_DEFINE_H_ */
