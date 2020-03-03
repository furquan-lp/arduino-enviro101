//#include <Arduino.h>
//#include <Wire.h>

#include "display.h"
#include "sensors.h"

void setup() {
	Serial.begin(9600);
	init_led();
}

void loop() {
	Serial.print("MQ135: ");
	Serial.println(mq_read());
	blink_led(1000);
}
