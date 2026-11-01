#define BLYNK_PRINT Serial
// Replace placeholders locally. Never publish real credentials.
#define BLYNK_TEMPLATE_ID "YOUR_BLYNK_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "YOUR_BLYNK_TEMPLATE_NAME"
#define BLYNK_AUTH_TOKEN "YOUR_BLYNK_AUTH_TOKEN"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char ssid[] = "YOUR_WIFI_SSID";
char pass[] = "YOUR_WIFI_PASSWORD";

#define PIR D5
#define RELAY D1
#define LEDPIN D7
#define LDR D6
#define MQ A0
#define DHTPIN D4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
bool manualMode = false;
bool relayState = false;

String getAQILevel(int gasValue) {
  if (gasValue < 200) return "GOOD";
  else if (gasValue < 400) return "MODERATE";
  else if (gasValue < 700) return "POOR";
  else return "HAZARDOUS";
}

BLYNK_WRITE(V4) {
  relayState = (param.asInt() == 1);
  manualMode = true;
  digitalWrite(RELAY, relayState ? LOW : HIGH);
}

BLYNK_WRITE(V6) {
  if (param.asInt() == 1) manualMode = false;
}

void sendData() {
  int motion = digitalRead(PIR);
  int ldrValue = digitalRead(LDR); // LOW = dark, HIGH = light
  int gasValue = analogRead(MQ);
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    Serial.println("DHT ERROR");
    return;
  }

  String aqi = getAQILevel(gasValue);
  Blynk.virtualWrite(V0, temp);
  Blynk.virtualWrite(V1, hum);
  Blynk.virtualWrite(V2, motion);
  Blynk.virtualWrite(V3, aqi);
  Blynk.virtualWrite(V5, gasValue);

  if (!manualMode) {
    relayState = (motion == HIGH && temp > 25);
    digitalWrite(RELAY, relayState ? LOW : HIGH);
  }
  Blynk.virtualWrite(V4, relayState);

  digitalWrite(LEDPIN, ldrValue == LOW ? LOW : HIGH);

  Serial.print("Motion: "); Serial.print(motion);
  Serial.print(" | Temp: "); Serial.print(temp);
  Serial.print(" | Hum: "); Serial.print(hum);
  Serial.print(" | LDR: "); Serial.print(ldrValue);
  Serial.print(" | Gas: "); Serial.print(gasValue);
  Serial.print(" | AQI: "); Serial.println(aqi);
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  pinMode(PIR, INPUT);
  pinMode(RELAY, OUTPUT);
  pinMode(LEDPIN, OUTPUT);
  pinMode(LDR, INPUT);
  digitalWrite(RELAY, HIGH);
  digitalWrite(LEDPIN, HIGH);
  dht.begin();
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(2000L, sendData);
}

void loop() {
  Blynk.run();
  timer.run();
}
