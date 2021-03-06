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
	// set the LCD address to 0x27 (SDA: A4, SCL: A5)
	LiquidCrystal_I2C lcd(0x27, LCD_ROWS, LCD_COLS);
#else
	#include <LiquidCrystal.h>
	LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
#endif

int char_count = 0; // Keep track of the number of special chars
int led_state = LOW; // Keep track of the default-LED state

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

void select_line(int l) {
	lcd.setCursor(0, l);
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

void println_lcd(String s) {
	if (s.length() > LCD_COLS) {
		lcd.print(s.substring(0, LCD_COLS - 1));
	} else {
		lcd.print(s);
		for (int i = s.length(); i < LCD_COLS; i++) {
			lcd.print(" ");
		}
	}
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
 * Places a blinking cursor at the current cursor locale in the LCD.
 * Removes the cursor if false.
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
 * Moves the cursor to the given locale in the LCD and then places a
 * blinking cursor there.
 */
void blink_cursor(int row, int col) {
	if (row > LCD_ROWS || col > LCD_COLS)
		return;
	lcd.setCursor(row, col);
	lcd.cursor();
	lcd.blink();
}

/*
 * Scrolls the printed text from the given offset in the given direction
 * with the given delay between each character being scrolled
 */
void scroll_text(int offset, int dir, int ms) {
	for (int i = 0; i < offset; i++) {
		if (dir)
			lcd.scrollDisplayLeft();
		else
			lcd.scrollDisplayRight();
		delay(ms);
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
