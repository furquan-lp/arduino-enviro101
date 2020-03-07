#include "sensors.h"

DHT dht = DHT(DHT_DATA, DHTType);

int analog_pin = 0;

//MQ135 gasSensor = MQ135(ANALOGPIN);
//MQUnifiedsensor MQ135(pin, type);

void init_DHT() {
	dht.begin();
}

void init_MQ() {
	analog_pin = MQ_ANALOG;
}

int mq_read() {
	return analogRead(analog_pin);
}

/*
 * 0  Healthy
 * 1  Normal
 * 2  Poor (Moderate)
 * 3  Unsafe
 * 4  Hazard
 * -1 Unknown
 */
int get_air_quality(float mp) {
	if (mp <= 280.0)
		return 0;
	else if (mp > 280.0 && mp <= 360.0)
		return 1;
	else if (mp > 360.0 && mp <= 420.0)
		return 2;
	else if (mp > 420.0 && mp <= 480.0)
		return 3;
	else if (mp > 480.0)
		return 4;
	else
		return -1;
}

int air_quality_warn(int air_q) {
	switch (air_q) {
		case 3:
			return 1;
		case 4:
			return 2;
		default:
			return 0;
	}
}

float get_humid() {
	return dht.readHumidity();
}

float get_temp() {
	return dht.readTemperature();
}
