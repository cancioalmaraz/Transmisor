#pragma once
#include<stdbool.h>
#include<math.h>
#include "stm32f7xx_hal.h"

typedef enum {

	SELF_TEST_X = 0x0D,
	SELF_TEST_Y,
	SELF_TEST_Z,
	SELF_TEST_A,
	SMPLRT_DIV = 0x19,
	CONFIG,
	GYRO_CONFIG,
	ACCEL_CONFIG,
	FIFO_EN = 0x23,
	I2C_MST_CTRL,
	I2C_SLV0_ADDR,
	I2C_SLV0_REG,
	I2C_SLV0_CTRL,
	I2C_SLV1_ADDR,
	I2C_SLV1_REG,
	I2C_SLV1_CTRL,
	I2C_SLV2_ADDR,
	I2C_SLV2_REG,
	I2C_SLV2_CTRL,
	I2C_SLV3_ADDR,
	I2C_SLV3_REG,
	I2C_SLV3_CTRL,
	I2C_SLV4_ADDR,
	I2C_SLV4_REG,
	I2C_SLV4_DO,
	I2C_SLV4_CTRL,
	I2C_SLV4_DI,
	I2C_MST_STATUS,
	INT_PIN_CFG,
	INT_ENABLE,
	INT_STATUS = 0x3A,
	ACCEL_XOUT_H,
	ACCEL_XOUT_L,
	ACCEL_YOUT_H,
	ACCEL_YOUT_L,
	ACCEL_ZOUT_H,
	ACCEL_ZOUT_L,
	TEMP_OUT_H,
	TEMP_OUT_L,
	GYRO_XOUT_H,
	GYRO_XOUT_L,
	GYRO_YOUT_H,
	GYRO_YOUT_L,
	GYRO_ZOUT_H,
	GYRO_ZOUT_L,
	EXT_SENS_DATA_00,
	EXT_SENS_DATA_01,
	EXT_SENS_DATA_02,
	EXT_SENS_DATA_03,
	EXT_SENS_DATA_04,
	EXT_SENS_DATA_05,
	EXT_SENS_DATA_06,
	EXT_SENS_DATA_07,
	EXT_SENS_DATA_08,
	EXT_SENS_DATA_09,
	EXT_SENS_DATA_10,
	EXT_SENS_DATA_11,
	EXT_SENS_DATA_12,
	EXT_SENS_DATA_13,
	EXT_SENS_DATA_14,
	EXT_SENS_DATA_15,
	EXT_SENS_DATA_16,
	EXT_SENS_DATA_17,
	EXT_SENS_DATA_18,
	EXT_SENS_DATA_19,
	EXT_SENS_DATA_20,
	EXT_SENS_DATA_21,
	EXT_SENS_DATA_22,
	EXT_SENS_DATA_23,
	I2C_SLV0_DO = 0x63,
	I2C_SLV1_DO,
	I2C_SLV2_DO,
	I2C_SLV3_DO,
	I2C_MST_DELAY_CTRL,
	SIGNAL_PATH_RESET,
	USER_CTRL = 0x6A,
	PWR_MGMT_1,
	PWR_MGMT_2,
	FIFO_COUNTH = 0x72,
	FIFO_COUNTL,
	FIFO_R_W,
	WHO_AM_I

} MPU_REGISTER;

typedef enum {

	FS_SEL_250,
	FS_SEL_500,
	FS_SEL_1000,
	FS_SEL_2000

} MPU_GYRO_RANGE;

typedef enum {

	AFS_SEL_2G,
	AFS_SEL_4G,
	AFS_SEL_8G,
	AFS_SEL_16G

} MPU_ACCEL_RANGE;

typedef enum {

	MPU_OK,
	MPU_ERROR

} MPU_RESULT;

typedef enum {

	CLK_INTERNAL,
	CLK_PLL_XGYRO,
	CLK_PLL_YGYRO,
	CLK_PLL_ZGYRO,
	CLK_PLL_EXT32K,
	CLK_PLL_EXT19M,
	CLK_PLL_KEEP_RESET = 0x07

} MPU_CLKSEL;

enum {
	Angle_Pitch,
	Angle_Roll,
	Angle_Yaw
};

typedef struct {

	uint8_t addres;
	uint32_t timeout;

	I2C_HandleTypeDef* i2c;

	MPU_GYRO_RANGE gyro_range;
	MPU_ACCEL_RANGE accel_range;
	MPU_CLKSEL clksel;

	int16_t offset_pitch;
	int16_t offset_roll;

} MPU_config;

typedef struct {

	MPU_config config;

} MPU_HandleTypeDef;

MPU_RESULT mpu_init(MPU_HandleTypeDef* dev, MPU_config* config);

MPU_RESULT mpu_sleep(MPU_HandleTypeDef* dev, bool state);

MPU_RESULT mpu_set_gyro_range(MPU_HandleTypeDef* dev, MPU_GYRO_RANGE range);

MPU_RESULT mpu_set_accel_range(MPU_HandleTypeDef* dev, MPU_ACCEL_RANGE range);

MPU_RESULT mpu_set_clksel(MPU_HandleTypeDef* dev, MPU_CLKSEL clk);

MPU_RESULT mpu_get_gyro(MPU_HandleTypeDef* dev, int16_t* x, int16_t *y, int16_t *z);

MPU_RESULT mpu_get_accel(MPU_HandleTypeDef* dev, int16_t* x, int16_t *y, int16_t *z);

void mpu_get_angles(MPU_HandleTypeDef* dev, float* lastAngs, float* angs, float dif);

int16_t mpu_get_gyro_xout(MPU_HandleTypeDef* dev);

int16_t mpu_get_gyro_yout(MPU_HandleTypeDef* dev);
