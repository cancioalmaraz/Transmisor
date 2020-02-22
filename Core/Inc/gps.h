#pragma once

#include<string.h>
#include<stdio.h>
#include<math.h>
#include "stm32f7xx_hal.h"

typedef struct {

	UART_HandleTypeDef* uart;
	int8_t gtm;

} gps_config;

typedef struct {

	int day, month, year, hour, min, sec, msec, satellites;
	char status, ns, ew;
	float latitud, longitud, velocity, altitude;
	double latitudDec, longitudDec;

} gps_data;

typedef struct {
	
	gps_config config;
	gps_data   data;
	char buffer[600];
	int i, lastTime;
	uint8_t pData[1];

} gps;

void gps_init(gps* dev, gps_config* config);

void gps_process(gps* dev);

void gps_callBack(gps* dev);
