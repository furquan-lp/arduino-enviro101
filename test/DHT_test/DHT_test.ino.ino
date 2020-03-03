#include <DHT_U.h>
#include <DHT.h>

#define dataPin 2
#define DHTType DHT22

DHT dht = DHT(dataPin, DHTType);

void setup() {
  Serial.begin(9600);
  dht.begin();
  
}

void loop() {
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("%; ");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println("*C");
}
