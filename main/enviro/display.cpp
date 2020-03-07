/*
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means. See the LICENSE for more information.
 */

#include "display.h"
#ifdef LCD_I2C
	#include <LiquidCrystal_I2C.h>
	// set the LCD address to 0x27 for a 16 chars and 2 line display
	LiquidCrystal_I2C lcd(0x27, 16, 2);
#else
	#include <LiquidCrystal.h>
	LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
#endif

int char_count = 0; // Keep track of the number of special chars
int led_state = LOW; // Keep track of the default LED state

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

void init_lcd() {
#ifdef LCD_I2C
	lcd.init();
	lcd.backlight();
#else
	lcd.begin(LCD_ROWS, LCD_COLS);
#endif
	lcd.setCursor(0, 0);
	lcd.noDisplay();
	delay(100);
	lcd.display();
}

void clear_lcd() {
	lcd.clear();
}

void printlcd(String s) {
	lcd.print(s);
}

void printlcd(int n) {
	lcd.print(n);
}

void printlcd(float f) {
	lcd.print(f);
}

void printlcd(char c) {
	lcd.print(c);
}

void printlcd(String s[]) {
	lcd.home();
	for (int i = 0; i < 4; i++) {
		lcd.setCursor(0, i);
		lcd.print(s[i]);
	}
}

void print_home(String s) {
	lcd.home();
	lcd.print(s);
}

void print_at(String s, int line) {
	if (line > LCD_COLS)
		return;
	lcd.home();
    lcd.setCursor(0, line);
    lcd.print(s);
}

void print_at(String s, int row, int col) {
	if (row > LCD_ROWS || col > LCD_COLS)
		return;
	lcd.home();
    lcd.setCursor(row, col);
    lcd.print(s);
}

/*
 * Places a blinking cursor at the current cursor locale in the LCD
 */
void blink_cursor(bool b) {
	if (b) {
		lcd.cursor();
		lcd.blink();
	} else {
		lcd.noBlink();
		lcd.noCursor();
	}
}

/*
 * Prints a special character on the 20x4 at the given row and column.
 * Please note that only a limited amount of special characters are
 * allowed and this function does not check for those.
 */
void print_spc_char(byte character[], int localeR, int localeC) {
  lcd.createChar(char_count, character);
  lcd.setCursor(localeR, localeC);
  lcd.write(byte(char_count));
  char_count++;
}

// Enviro-specific display functions

void print_silicon() {
	print_spc_char(char_S, 6, 0);
	print_spc_char(char_I, 7, 0);
	print_spc_char(char_L, 8, 0);
	print_spc_char(char_I, 9, 0);
	print_spc_char(char_C, 10, 0);
	print_spc_char(char_O, 11, 0);
	print_spc_char(char_N, 12, 0);
}

void print_air_quality(int q) {
	switch (q) {
		case 0:
			lcd.print("HEALTHY");
			break;
		case 1:
			lcd.print("NORMAL");
			break;
		case 2:
			lcd.print("POOR");
			break;
		case 3:
			lcd.print("UNSAFE");
			break;
		case 4:
			lcd.print("HAZARD");
			break;
		case -1:
			lcd.print("UNKNOWN");
			break;
		default:
			lcd.print("ERROR");
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

// LED-control functions

void init_led() {
	pinMode(LED, OUTPUT);
}

void init_led(int pin) {
	pinMode(pin, OUTPUT);
}

void toggle_led() {
	if (led_state == LOW) {
		digitalWrite(LED, HIGH);
		led_state = HIGH;
	} else {
		digitalWrite(LED, LOW);
		led_state = LOW;
	}
}

void toggle_led(bool n) {
	if (n) {
		digitalWrite(LED, HIGH);
		led_state = HIGH;
	} else {
		digitalWrite(LED, LOW);
		led_state = LOW;
	}
}

void toggle_led(bool n, int pin) {
	if (n)
		digitalWrite(pin, HIGH);
	else
		digitalWrite(pin, LOW);
}

void blink_led(int ms) {
	led_state = HIGH;
	digitalWrite(LED, HIGH);
	delay(ms / 2);
	digitalWrite(LED, LOW);
	led_state = LOW;
	delay(ms / 2);
}

void blink_led(int ms, int pin) {
	digitalWrite(pin, HIGH);
	delay(ms / 2);
	digitalWrite(pin, LOW);
	delay(ms / 2);
}
