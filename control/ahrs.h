#ifndef __AHRS_H__
#define __AHRS_H__

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include "stm32f4xx.h"   

#define MPU6050_GYRO_SCALE	1000
#define MPU6050_ACC_SCALE	8
#define HALF_SIGNED16		32767

#define AHRS_EVENT_MPU6050	1
#define AHRS_EVENT_HMC5883	(1 << 2)
#define AHRS_EVENT_ADNS3080	(1 << 3)
#define AHRS_EVENT_SONAR	(1 << 4)
#define AHRS_EVENT_CARMERA	(1 << 5)
#define AHRS_EVENT_Update 	(1 << 7)
#define AHRS_EVENT_WRONG 	(1 << 15)

void ahrs_put_mpu6050(s16 * data);
void ahrs_update(void);
s16 MoveAve_SMA(volatile int16_t NewData, volatile int16_t *MoveAve_FIFO, u8 SampleNum);
s16 MoveAve_WMA(volatile int16_t NewData, volatile int16_t *MoveAve_FIFO, u8 SampleNum);
float Moving_Median(volatile float NewData, volatile float *MoveMid_FIFO, u8 SampleNum);
extern struct rt_event ahrs_event;
extern struct ahrs_t
{
	float acc_x;
	float acc_y;
	float acc_z;
	float g_x;
	float g_y;
	float g_z;
	float gryo_pitch;
	float gryo_roll;
	float gryo_yaw;
	float degree_pitch;
	float degree_roll;
	float degree_yaw;
	float height;
	float height_v;
	float height_acc;
	float height_acc_fix;
	int32_t x;
	int32_t y;
	float line_err;
	float angle_err;
	int32_t dx;
	int32_t dy;
	float vx;
	float time_span;
}ahrs;

typedef struct 
{
	rt_err_t mpu6050;
	rt_err_t hmc5883;
	rt_err_t sonar;
	rt_err_t adns3080;
	rt_err_t camera;
}ahrs_state_t;

extern ahrs_state_t ahrs_state;

typedef struct {
	float q0;
	float q1;
	float q2;
	float q3;
} Quaternion;

float toRad(float degree);
float rangeYaw(float yaw);
float diffYaw(float yaw1,float yaw2);
float low_pass(float ov,float nv,float hz,float dt);
extern int16_t mpu_acc_x,mpu_acc_y,mpu_acc_z;
extern int16_t mpu_gryo_pitch,mpu_gryo_roll,mpu_gryo_yaw;
extern float MPU6050_Diff[];
extern struct rt_semaphore angle_fix_sem;

#endif
