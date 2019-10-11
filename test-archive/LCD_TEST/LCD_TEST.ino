/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
  
byte charHeart[] = {
  B00000,
  B01010,
  B10101,
  B10001,
  B10001,
  B01010,
  B00100,
  B00000
};

byte charDick[] = {
  B00100,
  B01010,
  B01010,
  B01010,
  B01010,
  B10001,
  B10001,
  B01110
};

byte charT[] = {
  B11111,
  B10101,
  B00100,
  B00100,
  B00100,
  B00100,
  B00000,
  B11111
};

byte charE[] = {
  B11111,
  B10001,
  B10000,
  B11100,
  B10001,
  B11111,
  B00000,
  B11111
};


void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(20, 4);
  lcd.print(" Team Silicon Stomp");
}

void loop() {
  lcd.createChar(0, charHeart);
  lcd.createChar(1, charDick);
  
  lcd.setCursor(3, 1);
  lcd.write(byte(0));
  lcd.setCursor(4, 1);
  lcd.print("IoT Project");
  lcd.setCursor(15, 1);
  lcd.write(byte(0));
  lcd.setCursor(4, 1);

  lcd.setCursor(0, 2);
  lcd.print("Prem chutiya");
  lcd.setCursor(0, 3);
  lcd.print("muh me le bc ");
  lcd.setCursor(12, 3);
  lcd.write(byte(1));
}
