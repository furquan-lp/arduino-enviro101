#include "sensors.h"

DHT dht = DHT(DHT_DATA, DHTType);
//MQ135 gasSensor = MQ135(ANALOGPIN);
//MQUnifiedsensor MQ135(pin, type);

int mq_read() {
	return analogRead(MQ_ANALOG);
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
	if (mp <= 250.0)
		return 0;
	else if (mp > 250.0 && mp <= 340.0)
		return 1;
	else if (mp > 340.0 && mp <= 400.0)
		return 2;
	else if (mp > 400.0 && mp <= 450.0)
		return 3;
	else if (mp > 450.0)
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

float humidity() {
	return dht.readHumidity();
}

float temperature() {
	return dht.readTemperature();
}
