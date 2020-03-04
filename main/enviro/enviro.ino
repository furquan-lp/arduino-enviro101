//#include <Arduino.h>
//#include <Wire.h>

#include "display.h"
#include "sensors.h"

int pass = 0, mq_vals = 0;

// The 'hourglass' wait symbol
byte charExtra[] = {
  B11111,
  B10001,
  B01010,
  B00100,
  B01010,
  B10001,
  B10001,
  B11111
};

void setup() {
	Serial.begin(9600);
	init_led();
	init_led(12);
}

void loop() {
	if (pass == 0)
		Serial.println("\t-- Begin --");
	pass++;
	if (pass % 60 == 0) {
		Serial.print("\nAverage after 60000ms: ");
		Serial.print(mq_vals / 60);
		Serial.println("");
		blink_led(2000, 12);
		mq_vals = 0;
	}
	Serial.print("MQ135: ");
	Serial.print(mq_read());
	Serial.print("; Pass: ");
	Serial.println(pass);
	mq_vals += mq_read();
	blink_led(1000);
}

void display_temp() {
	print_at("Temperature: ", 0);
	printlcd(get_temp());
	printlcd((char) 223);
	printlcd("C");
}

void display_humid() {
	print_at("Humidity: ", 1);
	printlcd(get_humid());
	printlcd("%");
}

void display_air(int mq) {
	print_at("Air Quality: ", 2);
	print_air_quality(mq);
	print_at(get_warn_str(mq), 3);
}

void print_credits() {
	print_home("_Team");
	print_silicon();
	print_home(" Stomp_");
	print_at("Sahil {SYED} Sandesh", 1);
	print_at("Prem Subham & Saurav", 2);
	print_at("    -*PRESENT*-     ", 3);
}

void print_welcome() {
	String lines[] = {
		" -/TESSERACT 2020\- ",
		"   Air Quality &    ",
		"Environment Analysis",
		"      \MODEL/       "
	};
	printlcd(lines);
}
