/*
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means. See the LICENSE for more information.
 */

#include <DHT_U.h>
#include <DHT.h>
//#include <MQUnifiedsensor.h>

#define DHT_DATA 2
#define DHTType DHT22
#define MQ_ANALOG 0

void init_DHT(void);
void init_MQ(void);

int mq_read(void);
int get_air_quality(float);
int air_quality_warn(int);

float get_humid(void);
float get_temp(void);
