#include "mpu6050.h"

//-----------------------Functions read and write registers-------------------

static uint16_t mpu_read_register(MPU_HandleTypeDef* dev, MPU_REGISTER reg){

	uint8_t buffer[1];
	buffer[0] = reg;
	HAL_I2C_Master_Transmit(dev->config.i2c, (dev->config.addres)<<1, buffer, 1, dev->config.timeout);
	HAL_I2C_Master_Receive(dev->config.i2c, (dev->config.addres)<<1, buffer, 1, dev->config.timeout);
	return buffer[0];

}

static MPU_RESULT mpu_write_register(MPU_HandleTypeDef* dev, MPU_REGISTER reg, uint8_t data){

	uint8_t buffer[2];
	buffer[0] = reg;
	buffer[1] = data;
	if (HAL_I2C_Master_Transmit(dev->config.i2c, (dev->config.addres)<<1, buffer, 2, dev->config.timeout)==HAL_OK){
		return MPU_OK;
	}
	else{
		return MPU_ERROR;
	}

}

//----------------------------------------------------------------------------

MPU_RESULT mpu_init(MPU_HandleTypeDef* dev, MPU_config* config){
	dev->config = *config;
	if (HAL_I2C_IsDeviceReady(dev->config.i2c, dev->config.addres<<1, 10, dev->config.timeout)==HAL_OK){
		mpu_set_clksel(dev, dev->config.clksel);
		mpu_set_gyro_range(dev, dev->config.gyro_range);
		mpu_set_accel_range(dev, dev->config.accel_range);
		mpu_sleep(dev, false);
		return MPU_OK;
	}
	return MPU_ERROR;
}

MPU_RESULT mpu_sleep(MPU_HandleTypeDef* dev, bool state){
	uint8_t value = mpu_read_register(dev, PWR_MGMT_1);
	if (state){
		value |= (1<<6);
	}
	else{
		value &= ~(1<<6);
	}
	return mpu_write_register(dev, PWR_MGMT_1, value);
}

MPU_RESULT mpu_set_gyro_range(MPU_HandleTypeDef* dev, MPU_GYRO_RANGE range){
	uint8_t value = mpu_read_register(dev, GYRO_CONFIG);
	value &= ~(0x03<<3);
	value |= (range<<3);
	return mpu_write_register(dev, GYRO_CONFIG, value);
}

MPU_RESULT mpu_set_accel_range(MPU_HandleTypeDef* dev, MPU_ACCEL_RANGE range){
	uint8_t value = mpu_read_register(dev, ACCEL_CONFIG);
	value &= ~(0x03<<3);
	value |= (range<<3);
	return mpu_write_register(dev, ACCEL_CONFIG, value);
}

MPU_RESULT mpu_set_clksel(MPU_HandleTypeDef* dev, MPU_CLKSEL clk){
	uint8_t value = mpu_read_register(dev, PWR_MGMT_1);
	value &= ~(0x07);
	value |= (clk);
	return mpu_write_register(dev, PWR_MGMT_1, value);
}

MPU_RESULT mpu_get_gyro(MPU_HandleTypeDef* dev, int16_t* x, int16_t *y, int16_t *z){
	uint8_t buffer[6];
	buffer[0] = GYRO_XOUT_H;
	HAL_I2C_Master_Transmit(dev->config.i2c, (dev->config.addres)<<1, buffer, 1, dev->config.timeout);
	HAL_I2C_Master_Receive(dev->config.i2c, (dev->config.addres)<<1, buffer, 6, dev->config.timeout);
	*x = (((int16_t)buffer[0])<<8) | buffer[1];
	*y = (((int16_t)buffer[2])<<8) | buffer[3];
	*z = (((int16_t)buffer[4])<<8) | buffer[5];
	return MPU_OK;
}

MPU_RESULT mpu_get_accel(MPU_HandleTypeDef* dev, int16_t* x, int16_t *y, int16_t *z){
	uint8_t buffer[6];
	buffer[0] = ACCEL_XOUT_H;
	HAL_I2C_Master_Transmit(dev->config.i2c, (dev->config.addres)<<1, buffer, 1, dev->config.timeout);
	HAL_I2C_Master_Receive(dev->config.i2c, (dev->config.addres)<<1, buffer, 6, dev->config.timeout);
	*x = (((int16_t)buffer[0])<<8) | buffer[1];
	*y = (((int16_t)buffer[2])<<8) | buffer[3];
	*z = (((int16_t)buffer[4])<<8) | buffer[5];
	return MPU_OK;
}

void mpu_get_angles(MPU_HandleTypeDef* dev, float* lastAngs, float* angs, float dif){
	int16_t ax, ay, az, gx, gy, gz;
	float ang_p, ang_r;
	for (uint8_t i = 0; i < 3; i++){
		lastAngs[i] = angs[i];
	}
	mpu_get_accel(dev, &ax, &ay, &az);
	mpu_get_gyro(dev, &gx, &gy, &gz);
	ang_p = (-1*(atan(ax/sqrt( pow(az,2) + pow(ay,2) ))*(180.0/3.141592)) - dev->config.offset_pitch);
	ang_r = (-1*(atan(ay/sqrt( pow(az,2) + pow(ax,2) ))*(180.0/3.141592)) - dev->config.offset_roll);
	*angs++ = 0.98*( *lastAngs++ + gx*dif ) + 0.02*ang_p;	//Filter Complement
	*angs++ = 0.98*( *lastAngs++ + gy*dif ) + 0.02*ang_r;	//Filter Complement
	*angs = *lastAngs + ((float)gy/131.0)*dif;
}

int16_t mpu_get_gyro_xout(MPU_HandleTypeDef* dev){
	return (mpu_read_register(dev, GYRO_XOUT_H)<<8) | mpu_read_register(dev, GYRO_XOUT_L);
}

int16_t mpu_get_gyro_yout(MPU_HandleTypeDef* dev){
	return (mpu_read_register(dev, GYRO_YOUT_H)<<8) | mpu_read_register(dev, GYRO_YOUT_L);
}


