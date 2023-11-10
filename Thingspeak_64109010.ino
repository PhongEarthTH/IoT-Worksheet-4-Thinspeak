#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

float tem;
float hum;
DHT dhtsen(D4,DHT11);

const char*  writeKey = "D01JRS8M37U7IM7O";
unsigned long channelID = 2338170;

WiFiClient client;

void init_wifi(String ssid, String password) {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial. print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup(){
  Serial.begin(9600);
  init_wifi("Galaxy A71 96DE","25452002");
  dhtsen.begin();
  tem = 0;
  hum = 0;
  ThingSpeak.begin(client);
}

void getSensor(){
  hum = (dhtsen.readHumidity());
  tem = (dhtsen.readTemperature());
  ThingSpeak.setField(1, hum);
  ThingSpeak.setField(2, tem);
}

void loop(){
  getSensor();
  int x = ThingSpeak.writeFields(channelID, writeKey);
  if(x == 200) {
    Serial.println("sent humidity and temperature to ThingSpeak");
  } else {
    Serial.println("Problem sending to ThingSpeak");
  }
  delay(20000);
}