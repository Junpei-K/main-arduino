#ifndef _MOTOR_DEFINE_H_
#define _MOTOR_DEFINE_H_

#define SLAVE_ADDRESS 9 // 的動作Arduino のSLVアドレス

/* 的動作Arduino のステータス */
#define WAIT 100
#define START 101 // MAINと合わせる
#define RUNNING 102
#define STOP 103 // MAINと合わせる

/* サーボのピン番号 */
#define SERVO1 9
#define SERVO2 10
#define SERVO3 11

/* 観覧車用モータ情報 */
#define IN1 5
#define IN2 6
int VR_PIN = A0;
int VR_VALUE;
int PWM_VALUE;
int STATUS;

/* パカパカの的番号 */
#define TARGET1 13
#define TARGET2 14
#define TARGET3 15

#endif /* _MOTOR_DEFINE_H_ */
