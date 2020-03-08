/*
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means. See the LICENSE for more information.
 */

#include <Arduino.h>
#include <Wire.h>

#define LED LED_BUILTIN
#define LCD_ROWS 16
#define LCD_COLS 2
#define LCD_I2C

void init_lcd(void);
void clear_lcd(void);
void select_line(int);
void printlcd(String);
void printlcd(int);
void printlcd(float);
void printlcd(char);
void printlcd(String*);
void println_lcd(String);
void print_spc_char(byte*, int, int);
void print_at(String, int);
void print_at(String, int, int);
void blink_cursor(bool);
void blink_cursor(int, int);
void scroll_text(int, int, int);

void init_led(void);
void init_led(int);
void toggle_led(void);
void toggle_led(bool);
void toggle_led(bool, int);
void blink_led(int);
void blink_led(int, int);
