#ifndef _MOTOR_DEFINE_H_
#define _MOTOR_DEFINE_H_

#define SLAVE_ADDRESS 9 // �I����Arduino ��SLV�A�h���X

/* �I����Arduino �̃X�e�[�^�X */
#define WAIT 100
#define START 101 // MAIN�ƍ��킹��
#define RUNNING 102
#define STOP 103 // MAIN�ƍ��킹��

/* �T�[�{�̃s���ԍ� */
#define SERVO1 9
#define SERVO2 10
#define SERVO3 11

/* �ϗ��ԗp���[�^��� */
#define IN1 5
#define IN2 6
int VR_PIN = A0;
int VR_VALUE;
int PWM_VALUE;
int STATUS;

/* �p�J�p�J�̓I�ԍ� */
#define TARGET1 13
#define TARGET2 14
#define TARGET3 15

#endif /* _MOTOR_DEFINE_H_ */
