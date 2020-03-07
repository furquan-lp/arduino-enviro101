//#include <Arduino.h>
//#include <Wire.h>

#include "display.h"
#include "sensors.h"

// Globals:
int pass = 0, mq_vals = 0;
const int load_time = 5; // in seconds

// The special symbols

byte char_S[] = {
  B01111,
  B10000,
  B10000,
  B01110,
  B00001,
  B11110,
  B00000,
  B11111
};

byte char_I[] = {
  B01110,
  B00100,
  B00100,
  B00100,
  B00100,
  B01110,
  B00000,
  B11111
};

byte char_L[] = {
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B11111,
  B00000,
  B11111
};

byte char_C[] = {
  B01110,
  B10001,
  B10000,
  B10000,
  B10001,
  B01110,
  B00000,
  B11111
};

byte char_O[] = {
  B01110,
  B10001,
  B10001,
  B10001,
  B10001,
  B01110,
  B00000,
  B11111
};

byte char_N[] = {
  B10001,
  B11001,
  B10101,
  B10101,
  B10011,
  B10001,
  B00000,
  B11111
};

// The 'hourglass' wait symbol
byte char_ext[] = {
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
	//Serial.begin(9600);
	init_led();
	toggle_led();
	init_DHT();
	//init_MQ();
	init_lcd();
	printlcd("Please wait...");
	print_spc_char(char_ext, 15, 0);
	print_at("Loading Sensors", 1);
	delay(load_time * 1000); // load time for the sensors
	toggle_led();
	print_welcome();
	delay(2500);
	print_credits();
	delay(1000);
	clear_lcd();

	/*print_credits();
	delay(2500);
	clear_lcd();
	print_welcome();
	delay(2500);
	clear_lcd();
	print_spc_char(char_ext, 19, 3);*/
}

void loop() {
	//if (pass == 0)
	//	printlcd("-- Begin --");
	//pass++;
	//print_at("Running: ", 1);
	//printlcd(pass);
	select_line(0);
	display_temp();
	printlcd(" & ");
	display_humid();
	select_line(1);
	display_air(mq_read());
	blink_led(50);
	delay(1500);
}

// Enviro-specific display functions

void print_air_quality(int q) {
	switch (q) {
		case 0:
			printlcd("HEALTHY");
			break;
		case 1:
			printlcd("NORMAL ");
			break;
		case 2:
			printlcd("POOR   ");
			break;
		case 3:
			printlcd("UNSAFE ");
			break;
		case 4:
			printlcd("HAZARD ");
			break;
		case -1:
			printlcd("UNKNOWN");
			break;
		default:
			printlcd("ERROR  ");
			break;
	}
}

String get_warn_str(int warn) {
	switch (warn) {
		case 0:
			return "Gases within limits ";
		case 1:
			return "Gases outside limits";
		case -1:
			return "SENSOR ERROR!";
		default:
			return "PROGRAM FAULT";
	}
}

void display_temp() {
	printlcd((int) get_temp());
	printlcd((char) 223);
	printlcd("C");
}

void display_humid() {
	printlcd((int) get_humid());
	printlcd("% Humid");
}

void display_air(int mq) {
	printlcd("Air: "); // DEBUG
	//print_air_quality(get_air_quality(mq_read()));
	printlcd(mq_read());
	printlcd("ppm");
	//print_at(get_warn_str(mq), 3);
}

void print_silicon() {
	print_spc_char(char_S, 0, 0);
	print_spc_char(char_I, 1, 0);
	print_spc_char(char_L, 2, 0);
	print_spc_char(char_I, 3, 0);
	print_spc_char(char_C, 4, 0);
	print_spc_char(char_O, 5, 0);
	print_spc_char(char_N, 6, 0);
}

void print_credits() {
	print_home("");
	print_silicon();
	printlcd(" *Stomp* ");
	for (int i = 0; i < 2; i++) {
		print_at("Sahil, {SYED},  ", 1);
		delay(1000);
		print_at(" Sandesh, Prem, ", 1);
		delay(1000);
		print_at(" Subham & Saurav", 1);
		delay(1000);
	}
	print_at("Sahil, {SYED},  ", 1);
}

void print_welcome() {
	print_at("-TESSERACT 2020-", 0);
	print_at("[ Air-Analysis ]", 1);
}
