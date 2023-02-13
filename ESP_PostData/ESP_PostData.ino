#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Arduino_JSON.h>
#include <ESP8266WiFiMulti.h>
#include <ESP_Mail_Client.h>


#define trig1     5   // pin TRIG to D1
#define echo1     4   // pin ECHO to D2
#define trig2     14   // pin TRIG to D5
#define echo2     12   // pin ECHO to D6

#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 465

/* The sign in credentials */
#define AUTHOR_EMAIL "vanhoanbh1510@gmail.com"
#define AUTHOR_PASSWORD "fshszhrlxydvpsti"

/* Recipient's email*/
#define RECIPIENT_EMAIL "hoangvanhoan1510@gmail.com"

/* The SMTP Session object used for Email sending */
SMTPSession smtp;

// Servo myservo;
ESP8266WiFiMulti WiFiMulti;

const char* ssid = "We Are One";    // Co dung thi nho doi ten wifi nhe cac nguoi anh em
const char* password = "12444nam";   // pass luon nhe cac ban

// Your IP address or domain name with URL path
const char* serverName = "http://hohutasmartgarbage.atwebpages.com/updateData.php";

// Update interval time set to 5 seconds
const long interval = 5000;
unsigned long previousMillis = 0;
int currentTime = 3600000;
int pauseTime = 3600000;

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

void sendEmail() {

  // sent mail function
  /* Declare the session config data */
  ESP_Mail_Session session;

  /* Set the session config */
  session.server.host_name = SMTP_HOST;
  session.server.port = SMTP_PORT;
  session.login.email = AUTHOR_EMAIL;
  session.login.password = AUTHOR_PASSWORD;
  session.login.user_domain = "";

  /* Declare the message class */
  SMTP_Message message;

  /* Set the message headers */
  message.sender.name = "ESP";
  message.sender.email = AUTHOR_EMAIL;
  message.subject = "GARBAGE LEVEL NOTIFICATION";
  message.addRecipient("HoHuTa", RECIPIENT_EMAIL);

  /*Send HTML message*/
  String htmlMsg = "Dear User, </p> <br> <p>Please be advised that our trash bin is currently overflowing and needs to be addressed immediately. Please empty your garbage.</p><p>Best Regards,</p><p>Dev Team.";
  message.html.content = htmlMsg.c_str();
  message.html.content = htmlMsg.c_str();
  message.text.charSet = "us-ascii";
  message.html.transfer_encoding = Content_Transfer_Encoding::enc_7bit;

  /*
  //Send raw text message
  String textMsg = "Hello World! - Sent from ESP board";
  message.text.content = textMsg.c_str();
  message.text.charSet = "us-ascii";
  message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;
  
  message.priority = esp_mail_smtp_priority::esp_mail_smtp_priority_low;
  message.response.notify = esp_mail_smtp_notify_success | esp_mail_smtp_notify_failure | esp_mail_smtp_notify_delay;*/

  /* Set the custom message header */
  //message.addHeader("Message-ID: <abcde.fghij@gmail.com>");

  /* Connect to server with the session config */
  if (!smtp.connect(&session))
    return;

  /* Start sending Email and close the session */
  if (!MailClient.sendMail(&smtp, &message))
    Serial.println("Error sending Email, " + smtp.errorReason());

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
  // digitalWrite(trig2,1);   // phát xung từ chân trig
  delay(5000);   // xung có độ dài 5 microSeconds
  digitalWrite(trig1,0);   // tắt chân trig
  // digitalWrite(trig2,0);   // tắt chân trig
  
    
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

  //check if distance is less than 4cm
  currentTime = currentTime + interval;
  if (distance <= 2) {
    
    if (currentTime >= pauseTime) {
      currentTime = 0;
      // Serial.println("testmail: zzzzz");
      sendEmail();
    }
  }
}
