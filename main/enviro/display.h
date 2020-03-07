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
void print_home(String);
void print_at(String, int);
void print_at(String, int, int);
void blink_cursor(bool);
void blink_cursor(int, int);
void scroll_text(int, int, int);

void print_spc_char(byte character[], int localeR, int localeC);
void print_silicon(void);
void print_air_quality(int);
String get_warn_str(int);

void init_led(void);
void init_led(int);
void toggle_led(void);
void toggle_led(bool);
void toggle_led(bool, int);
void blink_led(int);
void blink_led(int, int);
