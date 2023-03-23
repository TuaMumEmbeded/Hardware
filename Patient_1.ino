//SENDER
#include <esp_now.h>
#include <WiFi.h>

const char* ssid = "Toey";
const char* password = "99999997";

//FLEX-SENSOR
const int flex1 = A3;
const int flex2 = A0;

//LED
const int red_led = 19;
const int yellow_led = 22;
const int green_led = 21;
const int violet_led = 23;

//ULTRASONIC
const int trigPin1 = 2;
const int echoPin1 = 15;
const int trigPin2 = 0;
const int echoPin2 = 4;
int duration1;
int duration2;

//BUZZER
const int buzzer = 14;

uint8_t broadcastAddress[] = {0x4C, 0x11, 0xAE, 0xD3, 0xED, 0x34};

String success;

typedef struct struct_message {
  int id;
  int blue_led;
  int green_led;
  int yellow_led;
  int violet_led;
  int red_led;
  int buzz;
} struct_message_send;

struct_message send_Data;

esp_now_peer_info_t peerInfo;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  if (status ==0){
    success = "Delivery Success :)";
  }
  else{
    success = "Delivery Fail :(";
  }
  Serial.println(">>>>>");
}

void setup() {
  Serial.begin(115200);

  //FLEX-SENSOR
  pinMode(flex1, INPUT);
  pinMode(flex2, INPUT);
  //LED
  pinMode(red_led, OUTPUT);
  pinMode(yellow_led, OUTPUT);
  pinMode(green_led, OUTPUT);
  pinMode(violet_led, OUTPUT);
  digitalWrite(red_led, LOW);
  digitalWrite(yellow_led, LOW);
  digitalWrite(green_led, LOW);
  digitalWrite(violet_led, LOW);
  //ULTRASONIC
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  //BUZZER
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, HIGH);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_send_cb(OnDataSent);

  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  
}

void loop() {

  send_Data.id = 1;

  //FLEX SENSOR
  Serial.println("data1 =");
  Serial.println(analogRead(flex1));
  Serial.println("data2 =");
  Serial.println(analogRead(flex2));
  delay(1000);
  if ((analogRead(flex1) < 1100) && (analogRead(flex2) < 800)){
    digitalWrite(violet_led, HIGH);
    send_Data.violet_led = 1;
  }else if ((analogRead(flex1) < 1100) && (analogRead(flex2) > 700)){
    digitalWrite(yellow_led, HIGH);
    send_Data.yellow_led = 1;
  }else if ((analogRead(flex1) > 1100) && (analogRead(flex2) < 700)){
    digitalWrite(green_led, HIGH);
    send_Data.green_led = 1;
  }else{
    digitalWrite(violet_led, LOW);
    digitalWrite(yellow_led, LOW);
    digitalWrite(green_led, LOW);
    send_Data.violet_led = 0;
    send_Data.yellow_led = 0;
    send_Data.green_led = 0;
  }

  //ULTRASONIC & BUZZER
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);

  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);

  if (((duration1 < 400) and (duration1 > 200)) or ((duration2 < 400) and (duration2 > 200))){
    digitalWrite(red_led, HIGH);
    send_Data.red_led = 1;
    digitalWrite(buzzer, LOW);
    send_Data.buzz = 0;
    delay(300);
  }else{
    digitalWrite(red_led, LOW);
    send_Data.red_led = 0;
    digitalWrite(buzzer, HIGH);
    send_Data.buzz = 1;
    delay(300);
  }

  Serial.println();
  Serial.print(">>>>> ");
  Serial.println("Send data");

  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &send_Data, sizeof(send_Data));
    
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
}
