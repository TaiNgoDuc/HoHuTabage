#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Arduino_JSON.h>
#include <ESP8266WiFiMulti.h>


#define trig1     5   // pin TRIG to D1
#define echo1     4   // pin ECHO to D2
#define trig2     14   // pin TRIG to D5
#define echo2     12   // pin ECHO to D6

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
  pinMode(echo1, INPUT);

  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
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

  Serial.println("Gia tri cam bien:");

  //Day la gia tri cua ultrasonic 1
  digitalWrite(trig1,0);   // tắt chân trig
  
  delay(2000);
  digitalWrite(trig1,1);   // phát xung từ chân trig
  digitalWrite(trig2,1);   // phát xung từ chân trig
  delay(5000);   // xung có độ dài 5 microSeconds
  digitalWrite(trig1,0);   // tắt chân trig
  digitalWrite(trig2,0);   // tắt chân trig
  
    
  /* Tính toán thời gian cua sensor */
  // Đo độ rộng xung HIGH ở chân echo. 
  duration1 = pulseIn(echo1,HIGH);   
  // Tính khoảng cách đến vật.
  distance1 = int(duration1/2/29.412);


  // Day la gia tri cua ultrasonic 2
  digitalWrite(trig2,0);   // tắt chân trig
  delay(2000);
  digitalWrite(trig2,1);   // phát xung từ chân trig
  delay(5000);   // xung có độ dài 5 microSeconds
  digitalWrite(trig2,0);   // tắt chân trig

    /* Tính toán thời gian cua sensor */
  // Đo độ rộng xung HIGH ở chân echo.  
  duration2 = pulseIn(echo2,HIGH); 
  // Tính khoảng cách đến vật.
  distance2 = int(duration2/2/29.412);



  /* Tinh khoang cach trung binh cua 2 sensor */
  distance = int(( distance1 + distance2) / 2);



  // Serial.println(digitalRead(echo1)); 
  // Serial.println(digitalRead(echo2));

  //round distance to the nearest 10
  // distance = distance - (distance % 10);
  postData = "status=" + String(distance) + "cm";
  delay(1000);


  Serial.println(postData);
  Serial.println(duration1);
  Serial.println(duration2);
  Serial.println(distance1);
  Serial.println(distance2);
  Serial.print(distance);
  Serial.println("cm");
  delay(200);

  http.begin(client, serverName);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpCode = http.POST(postData);

  http.end();
  delay(10000);
}
