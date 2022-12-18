#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Arduino_JSON.h>
#include <ESP8266WiFiMulti.h>
// #include <Servo.h>

int hong_ngoai = D6;

// Servo myservo;
ESP8266WiFiMulti WiFiMulti;

const char* ssid = "Kid";    // Co dung thi nho doi ten wifi nhe cac nguoi anh em
const char* password = "taingoduc0406";   // pass luon nhe cac ban

// Your IP address or domain name with URL path
const char* serverName = "http://hohutasmartgarbage.atwebpages.com/updateData.php";

// Update interval time set to 5 seconds
const long interval = 5000;
unsigned long previousMillis = 0;

void setup() {
  Serial.begin(57600);
  WiFi.mode(WIFI_STA);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
  pinMode(hong_ngoai, INPUT);
}

void loop() {
  WiFiClient client;
  HTTPClient http;

  String postData = "";

  int sensorValue = digitalRead(hong_ngoai);

  Serial.print("Gia tri cam bien:");
  Serial.println(digitalRead(hong_ngoai));  //Nếu sensor = 1 thì không phát hiện vật cản, nếu sensor = 0 thì phát hiện vật cản.
  if (sensorValue == 0) {
    postData = "status=Yes";
    delay(1000);
  } else {
    postData = "status=No";
  }

  Serial.println(postData);

  http.begin(client, serverName);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpCode = http.POST(postData);

  http.end();
  delay(10000);
}