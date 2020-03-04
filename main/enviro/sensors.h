#include <DHT_U.h>
#include <DHT.h>
//#include <MQUnifiedsensor.h>

#define DHT_DATA 2
#define DHTType DHT22
#define MQ_ANALOG 0

int mq_read(void);
int get_air_quality(float);
int air_quality_warn(int);

float get_humid(void);
float get_temp(void);
