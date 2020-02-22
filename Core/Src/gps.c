#include "gps.h"

static double convertDegMinToDecDeg (float degMin){
  double min = 0.0;
  double decDeg = 0.0;

  min = fmod((double)degMin, 100.0);

  degMin = (int) ( degMin / 100 );
  decDeg = degMin + ( min / 60 );

  return decDeg;
}

void gps_init(gps* dev, gps_config* config){
	
	dev->config = *config;

	dev->i = 0;
	dev->lastTime = 0;

	HAL_UART_Receive_IT(dev->config.uart, dev->pData, 1);

}

void gps_process(gps* dev){

	if( ((HAL_GetTick()-dev->lastTime) > 10) && (dev->i > 0) ){

		char* string;

		memset(&dev->data, 0, sizeof(dev->data));
		
		string = strstr(dev->buffer, "$GPRMC,");

		if (string != NULL){

			sscanf(string, "$GPRMC,%2d%2d%2d.%2d,%c,%f,%c,%f,%c,%*f,,%2d%2d%2d,", &dev->data.hour, &dev->data.min, &dev->data.sec, &dev->data.msec,
															      &dev->data.status,
															      &dev->data.latitud, &dev->data.ns, &dev->data.longitud, &dev->data.ew,
																  &dev->data.day, &dev->data.month, &dev->data.year);

		}

		string = strstr(dev->buffer, "$GPVTG,");

		if (string != NULL){

			sscanf(string, "$GPVTG,,%*c,,%*c,%*f,%*c,%f", &dev->data.velocity);

		}

		string = strstr(dev->buffer, "$GPGGA,");

		if (string != NULL){

			sscanf(string, "$GPGGA,%*f,%*f,%*c,%*f,%*c,%*c,%*d,%*f,%f", &dev->data.altitude);

		}

		string = strstr(dev->buffer, "$GPGSV,");

		if (string != NULL){

			sscanf(string, "$GPGSV,%*d,%*d,%d", &dev->data.satellites);

		}

		if (dev->data.hour < fabs(dev->config.gtm)){
			dev->data.hour += (24 + dev->config.gtm);
		}
		else{
			dev->data.hour += dev->config.gtm;
		}
		dev->data.year += 2000;

		dev->data.latitudDec = convertDegMinToDecDeg(dev->data.latitud);
		dev->data.longitudDec = convertDegMinToDecDeg(dev->data.longitud);

		if (dev->data.ns == 'S'){
			dev->data.latitud *= -1;
			dev->data.latitudDec *= -1;
		}

		if (dev->data.ew == 'W'){
			dev->data.longitud *= -1;
			dev->data.longitudDec *= -1;
		}

		
		memset(dev->buffer, 0, sizeof(dev->buffer));

		dev->i = 0;

		HAL_UART_Receive_IT(dev->config.uart, dev->pData, 1);

	}
}

void gps_callBack(gps* dev){

	dev->lastTime = HAL_GetTick();

	dev->buffer[dev->i] = dev->pData[0];

	dev->i++;

	HAL_UART_Receive_IT(dev->config.uart, dev->pData, 1);

}
