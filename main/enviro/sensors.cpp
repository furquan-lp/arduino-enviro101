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
 * 2  Stuffed (Moderate)
 * 3  Unsafe
 * 4  Hazard
 * -1 Unknown
 */
int get_air_quality(float mp) {
	return 0;
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
