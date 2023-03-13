#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>

const char* ssid = "Toey";
const char* password = "99999997";

//LED-1
const int blue1 = 13;
const int green1 = 12;
const int yellow1 = 14;
const int violet1 = 27;
const int red1 = 2;

//BUZZER
const int buzzer1 = 4;
const int buzzer2 = 16;

//LED-2
const int blue2 = 25;
const int green2 = 33;
const int yellow2 = 32;
const int violet2 = 15;
const int red2 = 0;

uint8_t broadcastAddress[] = {0x3C, 0x61, 0x05, 0x03, 0x41, 0xA0};

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

struct_message receive_Data;

struct_message board1;
struct_message board2;
struct_message board3;
struct_message board4;
struct_message boardsStruct[4] = {board1, board2, board3, board4};

typedef struct struct_message_forsend {
  int id[2];
  bool blue_led[2];
  bool green_led[2];
  bool yellow_led[2];
  bool violet_led[2];
  bool red_led[2];
};

struct_message_forsend send_Data;

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

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&receive_Data, incomingData, sizeof(receive_Data));
  Serial.println();
  // Serial.println("<<<<< Receive Data:");
  boardsStruct[receive_Data.id-1].blue_led = receive_Data.blue_led;
  boardsStruct[receive_Data.id-1].green_led = receive_Data.green_led;
  boardsStruct[receive_Data.id-1].yellow_led = receive_Data.yellow_led;
  boardsStruct[receive_Data.id-1].violet_led = receive_Data.violet_led;
  boardsStruct[receive_Data.id-1].red_led = receive_Data.red_led;
  boardsStruct[receive_Data.id-1].buzz = receive_Data.buzz;

  digitalWrite(red1, boardsStruct[0].red_led);
  digitalWrite(yellow1, boardsStruct[0].yellow_led);
  digitalWrite(green1, boardsStruct[0].green_led);
  digitalWrite(violet1, boardsStruct[0].violet_led);
  digitalWrite(blue1, boardsStruct[2].blue_led);
  digitalWrite(buzzer1, boardsStruct[0].buzz);
  digitalWrite(red2, boardsStruct[1].red_led);
  digitalWrite(yellow2, boardsStruct[1].yellow_led);
  digitalWrite(green2, boardsStruct[1].green_led);
  digitalWrite(violet2, boardsStruct[1].violet_led);
  digitalWrite(blue2, boardsStruct[3].blue_led);
  digitalWrite(buzzer2, boardsStruct[1].buzz);
}

void setup() {
  Serial.begin(115200);

  pinMode(blue1, OUTPUT);
  pinMode(green1, OUTPUT);
  pinMode(yellow1, OUTPUT);
  pinMode(violet1, OUTPUT);
  pinMode(red1, OUTPUT);
  pinMode(blue2, OUTPUT);
  pinMode(green2, OUTPUT);
  pinMode(yellow2, OUTPUT);
  pinMode(violet2, OUTPUT);
  pinMode(red2, OUTPUT);
  pinMode(buzzer1, OUTPUT);
  pinMode(buzzer2, OUTPUT);

  digitalWrite(blue1, LOW);
  digitalWrite(green1, LOW);
  digitalWrite(yellow1, LOW);
  digitalWrite(violet1, LOW);
  digitalWrite(blue2, LOW);
  digitalWrite(green2, LOW);
  digitalWrite(yellow2, LOW);
  digitalWrite(violet2, LOW);
  digitalWrite(buzzer1, HIGH);
  digitalWrite(buzzer2, HIGH);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }

  Serial.println("\nConnected to the WiFi network");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_send_cb(OnDataSent);
  
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 6;  
  peerInfo.encrypt = false;
  
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  send_Data.id[0] = 1;
  send_Data.blue_led[0] = boardsStruct[2].blue_led;
  send_Data.green_led[0] = boardsStruct[0].green_led;
  send_Data.yellow_led[0] = boardsStruct[0].yellow_led;
  send_Data.violet_led[0] = boardsStruct[0].violet_led;
  send_Data.red_led[0] = boardsStruct[0].red_led;
  send_Data.id[1] = 2;
  send_Data.blue_led[1] = boardsStruct[3].blue_led;
  send_Data.green_led[1] = boardsStruct[1].green_led;
  send_Data.yellow_led[1] = boardsStruct[1].yellow_led;
  send_Data.violet_led[1] = boardsStruct[1].violet_led;
  send_Data.red_led[1] = boardsStruct[1].red_led;
  
  delay(500);
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