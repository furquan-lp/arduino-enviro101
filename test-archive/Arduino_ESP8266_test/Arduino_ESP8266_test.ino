#include <SoftwareSerial.h>

SoftwareSerial s(5,6);

int data[] = { 20, 21, 13 };

void setup() {
  s.begin(9600);
}
 
void loop() {
  // Check if ESP8266 is responding
  if(s.available() >= 3) {
    for (int i = 0; i < 3; i++) {
      s.write(data[i]);
    }
  }
}
