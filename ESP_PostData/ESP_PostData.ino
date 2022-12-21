#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Arduino_JSON.h>
#include <ESP8266WiFiMulti.h>
// #include <Servo.h>

// int hong_ngoai = D6;

const int trig1 = D6;     // chân trig của HC-SR04
const int echo1 = D5;     // chân echo của HC-SR04
const int trig2 = D7;     // chân trig của HC-SR04
const int echo2 = D4;     // chân echo của HC-SR04

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
  pinMode(trig1, OUTPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo1,INPUT);
  pinMode(echo2,INPUT);
}

void loop() {

  unsigned long duration1; // biến đo thời gian
  int distance1;           // biến lưu khoảng cách
  unsigned long duration2; // biến đo thời gian
  int distance2;           // biến lưu khoảng cách
  int distance;            // bien luu khoang cach trung binh cua 2 sensor

  WiFiClient client;
  HTTPClient http;

  String postData = "";

  // int sensorValue = digitalRead(trig);

  Serial.print("Gia tri cam bien:");

  //Day la gia tri cua ultrasonic
  digitalWrite(trig1,0);   // tắt chân trig
  digitalWrite(trig2,0);   // tắt chân trig
  delay(2000);
  digitalWrite(trig1,1);   // phát xung từ chân trig
  digitalWrite(trig2,1);   // phát xung từ chân trig
  delay(5000);   // xung có độ dài 5 microSeconds
  digitalWrite(trig1,0);   // tắt chân trig
  digitalWrite(trig2,0);   // tắt chân trig

  
    
  /* Tính toán thời gian cua sensor */
  // Đo độ rộng xung HIGH ở chân echo. 
  duration1 = pulseIn(echo1,HIGH);  
  duration2 = pulseIn(echo2,HIGH); 
  // Tính khoảng cách đến vật.
  distance1 = int(duration1/2/29.412);
  distance2 = int(duration2/2/29.412);

  /* Tinh khoang cach trung binh cua 2 sensor */
  distance = int(( distance1 + distance2) / 2);


  Serial.println(digitalRead(echo1)); 
  Serial.println(digitalRead(echo2));
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
