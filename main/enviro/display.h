#include <LiquidCrystal.h>
#include <Arduino.h>
#include <Wire.h>

#define LED LED_BUILTIN
#define LCD_ROWS 24
#define LCD_COLS 4

void init_lcd(void);
void clear_lcd(void);
void printlcd(String);
void print_at(String, int);
void print_at(String, int, int);

void print_spc_char(byte character[], int localeR, int localeC);
void print_air_quality(int);
void print_air_warn(int);

void init_led(void);
void toggle_led(void);
void toggle_led(int);
void blink_led(int);
