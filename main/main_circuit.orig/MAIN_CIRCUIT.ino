// include the libraries:
#include <LiquidCrystal.h>
#include <DHT_U.h>
#include <DHT.h>
#include <MQ135.h>


// Definitions
#define dataPin 2
#define DHTType DHT22

// Global variables
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
//const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
const int ANALOGPIN=0;
int charCount = 0, loop_run = 0;

// Global references
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
DHT dht = DHT(dataPin, DHTType);
MQ135 gasSensor = MQ135(ANALOGPIN);

// Character variables
byte charS[] = {
  B01111,
  B10000,
  B10000,
  B01110,
  B00001,
  B11110,
  B00000,
  B11111
};

byte charI[] = {
  B01110,
  B00100,
  B00100,
  B00100,
  B00100,
  B01110,
  B00000,
  B11111
};

byte charL[] = {
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B11111,
  B00000,
  B11111
};

byte charC[] = {
  B01110,
  B10001,
  B10000,
  B10000,
  B10001,
  B01110,
  B00000,
  B11111
};

byte charO[] = {
  B01110,
  B10001,
  B10001,
  B10001,
  B10001,
  B01110,
  B00000,
  B11111
};

byte charN[] = {
  B10001,
  B11001,
  B10101,
  B10101,
  B10011,
  B10001,
  B00000,
  B11111
};

byte charPlug[] = {
  B00000,
  B01010,
  B01010,
  B11111,
  B10001,
  B01110,
  B00100,
  B00000
};


// Main functions

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  dht.begin();
  // set up the LCD's number of columns and rows:
  lcd.begin(20, 4);
  
  printWelcomeScreen();
  delay(2500);
  lcd.clear();
  printCredits();
  delay(2000);
  digitalWrite(LED_BUILTIN, HIGH); 
  lcd.clear();
  printSpecialChar(charPlug, 19, 3);
}

void loop() {
  int loadTime = 1;
  if (loop_run == 0) {
    lcd.home();
    lcd.print("Initializing Sensors");
    lcd.setCursor(0, 1);
    lcd.print("Please wait...");
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
  delay(2000);
  loop_run++;
  digitalWrite(LED_BUILTIN, HIGH);
  
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float rzero = gasSensor.getRZero();
  float ppm = gasSensor.getPPM();
  
  lcd.home();
  lcd.print("Temperature: ");
  lcd.print(t);
  lcd.print((char) 223);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(h);
  lcd.print("%");

  int warn = 0;
  lcd.setCursor(0, 2);
  lcd.print("Air Quality: ");
  if (loop_run < loadTime) {
    lcd.print("WAITING");
  } else {
    warn = showAirStr(ppm);
  }

  lcd.setCursor(0, 3);
  if (loop_run < loadTime) {
    lcd.print("SENSOR LOADING...");
    return;
  }
  
  if (warn == 0) {
    lcd.print("Gases within limits ");
  } else if (warn == 1) {
    lcd.print("Gases outside limits");
  } else if (warn == 2) {
    lcd.print("WARNING TOXIC LEVELS");
  } else if (warn == -1) {
    lcd.print("SENSOR ERROR!");
    lcd.print(ppm);
  }
  Serial.println(ppm);
}

// Print functions

void printSpecialChar(byte character[], int localeR, int localeC) {
  lcd.createChar(charCount, character);
  lcd.setCursor(localeR, localeC);
  lcd.write(byte(charCount));
  charCount++;
}

// @return
//   0 Levels within health limits
//   1 Toxic concenteration levels
//   -1 Unknown level detected
int showAirStr(float mp) {
  Serial.println(mp);
  if (mp < 5.00) {
    lcd.print("HEALTHY");
  } else if (mp > 5.00 && mp < 10.00) {
    lcd.print("NORMAL ");
  } else if (mp > 10.00 && mp < 25.00) {
    lcd.print("STUFFED");
  } else if (mp > 25.00 && mp < 50.00) {
    lcd.print("UNSAFE ");
    return 1;
  } else if (mp > 50.00) {
    lcd.print("HAZARD ");
    return 2;
  } else {
    lcd.print("UNKNOWN");
    return -1;
  }
  return 0;
}

void printWelcomeScreen() {
  lcd.home();
  lcd.print("      WELCOME!      ");
  lcd.setCursor(0, 1);
  lcd.print("  IoT Project for   ");
  lcd.setCursor(0, 2);
  lcd.print("Enviornment and Air ");
  lcd.setCursor(0, 3);
  lcd.print("  Quality Analysis  ");
}

void printCredits() {
  lcd.home();
  printSpcTeamName();
  lcd.setCursor(0, 1);
  lcd.print("Syed, Sandesh, Prem,");
  lcd.setCursor(0, 2);
  lcd.print("Sahil and Subham ");
  lcd.setCursor(0, 3);
  lcd.print("      PRESENT      ");
}

void printSpcTeamName() {
  lcd.home();
  lcd.print("*Team ");
  printSpecialChar(charS, 6, 0);
  printSpecialChar(charI, 7, 0);
  printSpecialChar(charL, 8, 0);
  printSpecialChar(charI, 9, 0);
  printSpecialChar(charC, 10, 0);
  printSpecialChar(charO, 11, 0);
  printSpecialChar(charN, 12, 0);
  lcd.print(" Stomp*");
}

void printLCDInfo(LiquidCrystal l, byte row, byte col, byte rs, byte en, byte d4, byte d5,
  byte d6, byte d7) {
  l.home();
  l.print("LCD ");
  l.print(row);
  l.print("x");
  l.print(col);
  l.print(" on DIGITAL");
  
  l.setCursor(0, 1);
  l.print("RS ");
  l.print(rs);
  l.print(" EN ");
  l.print(en);
  l.print(" D4 ");
  l.print(d4);
  l.print(" D5 ");
  l.print(d5);

  l.setCursor(0, 2);
  l.print("D6 ");
  l.print(d6);
  l.print(" D7 ");
  l.print(d7);
}
