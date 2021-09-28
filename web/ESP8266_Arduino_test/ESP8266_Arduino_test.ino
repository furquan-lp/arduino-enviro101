#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>

SoftwareSerial s(D6, D5);
WiFiServer server(80);

int data[] = { 0, 0, 0 };
const char* ssid = "asus";
const char* password = "9939593102";

void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  s.begin(9600);
  Serial.begin(9600);

  delay(10);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop() {
  digitalWrite(13, LOW);
  s.write("s");
  if (s.available() >= 3) {
    for (int i = 0; i < 3; i++) {
      data[i] = s.read();
    }
  }

  int h = 84;
  int t = 29;
  int env = 13;

  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");

  client.println("<h2><b>IoT Project for Environment Analysis</b></h2>");
  client.println("<h3><i>Electrofusion</i> Team <u>Silicon Stomp</u></h3>");
  client.println("<i>Presented by</i>: Syed Furquan (Leader)");
  client.println("<br>And Sandesh, Prem, Sahil & Subham");
  client.println("<br>");
  client.println("<br><b><u>Temperature</b></u>: ");
  client.print(t);
  client.print(" degrees");
  client.println("<br><b><u>Humidity</u></b>: ");
  client.print(h);
  client.print("%");
  client.println("<br><b><u>Environment Quality</u></b>: ");
  client.print(getEnviroQuality(env));
  client.println("</html>");

  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
}

String getEnviroQuality(int mp) {
  if (mp <= 5) {
    return "Healthy";
  } else if (mp > 5 && mp <= 10) {
    return "Under normal levels";
  } else if (mp > 10 && mp <= 25) {
    return "Above normal levels";
  } else if (mp > 25 && mp <= 50) {
    return "Unsafe";
  } else if (mp > 50) {
    return "<b>HAZARDOUS<b>";
  } else {
    return "UNKNOWN";
  }
}
