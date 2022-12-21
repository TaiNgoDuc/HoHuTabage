#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Arduino_JSON.h>
#include <ESP8266WiFiMulti.h>
// #include <Servo.h>

// int hong_ngoai = D6;

const int trig = D6;     // chân trig của HC-SR04
const int echo = D5;     // chân echo của HC-SR04

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
  pinMode(trig, OUTPUT);
  pinMode(echo,INPUT);
}

void loop() {

  unsigned long duration; // biến đo thời gian
  int distance;           // biến lưu khoảng cách
  bool debug = false;

  WiFiClient client;
  HTTPClient http;

  String postData = "";

  // int sensorValue = digitalRead(trig);

  Serial.print("Gia tri cam bien:");

  digitalWrite(trig,0);   // tắt chân trig
  delay(2000);
  digitalWrite(trig,1);   // phát xung từ chân trig
  delay(5000);   // xung có độ dài 5 microSeconds
  digitalWrite(trig,0);   // tắt chân trig
    
  /* Tính toán thời gian */
  // Đo độ rộng xung HIGH ở chân echo. 
  duration = pulseIn(echo,HIGH);  
  // Tính khoảng cách đến vật.
  distance = int(duration/2/29.412);


  Serial.println(digitalRead(echo)); 
  if (0 < distance <= 10) {
    postData = "status=10%";
    delay(1000);
  } else if (10 < distance <= 20) {
    postData = "status=20%";
    delay(1000);
  } else if (10 < distance <= 20) {
    postData = "status=20%";
    delay(1000);
  } else if (20 < distance <= 30) {
    postData = "status=30%";
    delay(1000);
  } else if (30 < distance <= 40) {
    postData = "status=40%";
    delay(1000);
  } else if (50 < distance <= 60) {
    postData = "status=50%";
    delay(1000);
  }

  //round distance to the nearest 10
  distance = distance - (distance % 10);
  if (debug) {
    postData = "status=" + String(distance) + "cm";
  }

  Serial.println(postData);
  Serial.print(distance);
  Serial.println("cm");
  delay(200);

  http.begin(client, serverName);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpCode = http.POST(postData);

  http.end();
  delay(10000);
}