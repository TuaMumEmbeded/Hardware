#include "pitches.h"
#include <DebouncedSwitch.h>
#include <esp_now.h>
#include <WiFi.h>

const char* ssid = "Toey";
const char* password = "99999997";

TaskHandle_t TaskPiano;
TaskHandle_t CSong;

//switch
int but1 = 2;
int but2 = 4;
int but3 = 17;
int but4 = 18;
int but5 = 21;
int but6 = 23;
int but7 = 12;
int but8 = 32;

//LED
int led1 = 13;
int led2 = 0;
int led3 = 16;
int led4 = 5;
int led5 = 19;
int led6 = 22;
int led7 = 33;
int led8 = 15;

//song
int song1 = 14;
int song2 = 27;
int song3 = 26;

const int BUZZER = 25;
const int TONE_PWM_CHANNEL = 0; 


//debouncesw
DebouncedSwitch b1(but1);
DebouncedSwitch b2(but2);
DebouncedSwitch b3(but3);
DebouncedSwitch b4(but4);
DebouncedSwitch b5(but5);
DebouncedSwitch b6(but6);
DebouncedSwitch b7(but7);
DebouncedSwitch b8(but8);

//debounceSong
DebouncedSwitch s1(song1);
DebouncedSwitch s2(song2);
DebouncedSwitch s3(song3);

//----------------------------------------
uint8_t broadcastAddress[] = {0x4C, 0x11, 0xAE, 0xD3, 0xED, 0x34};

String success;

typedef struct struct_message {
  int id;
  int red_led;
  int yellow_led;
  int green_led;
  int violet_led;
  int buzz;
} struct_message_send;

struct_message send_Data;

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


void setup()
{
  Serial.begin(115200);
  pinMode(song1, INPUT_PULLUP);
  pinMode(song2, INPUT_PULLUP);
  pinMode(song3, INPUT_PULLUP);
  pinMode(but1, INPUT_PULLUP);
  pinMode(but2, INPUT_PULLUP);
  pinMode(but3, INPUT_PULLUP);
  pinMode(but4, INPUT_PULLUP);
  pinMode(but5, INPUT_PULLUP);
  pinMode(but6, INPUT_PULLUP);
  pinMode(but7, INPUT_PULLUP);
  pinMode(but8, INPUT_PULLUP);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(led7, OUTPUT);
  pinMode(led8, OUTPUT);
  ledcAttachPin(BUZZER, TONE_PWM_CHANNEL);

  xTaskCreatePinnedToCore(ChooseSong, "CSong", 10000, NULL, 1, &CSong, 0);
  xTaskCreatePinnedToCore(piano, "TaskPiano", 10000, NULL, 1, &TaskPiano, 1);

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

void loop()
{ 
  b1.update();
  b2.update();
  b3.update();
  b4.update();
  b5.update();
  b6.update();
  b7.update();
  b8.update();

  s1.update();
  s2.update();
  s3.update();
  
  send_Data.id = 3;
  if (b1.isDown() or b2.isDown() or b3.isDown() or b4.isDown() or b5.isDown() or b6.isDown() or b7.isDown() or b8.isDown()){
    send_Data.red_led = 1;
  }else{
    send_Data.red_led = 0;
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

void piano(void *unused){
  for (;;){
    if (b1.isDown()){
    ledcWriteNote(TONE_PWM_CHANNEL, NOTE_C, 5);
    delay(50);
    }
    else {
      ledcWriteTone(TONE_PWM_CHANNEL, 0);
    }
    
    if (b2.isDown()){
      ledcWriteNote(TONE_PWM_CHANNEL, NOTE_D, 5);
      delay(50);
    }
    else {
      ledcWriteTone(TONE_PWM_CHANNEL, 0);
    }  

    if (b3.isDown()){
      ledcWriteNote(TONE_PWM_CHANNEL, NOTE_E, 5);
      delay(50);
    }
    else {
      ledcWriteTone(TONE_PWM_CHANNEL, 0);
    }

    if (b4.isDown()){
      ledcWriteNote(TONE_PWM_CHANNEL, NOTE_F, 5);
      delay(50);
    }
    else {
      ledcWriteTone(TONE_PWM_CHANNEL, 0);
    }

    if (b5.isDown()){
      ledcWriteNote(TONE_PWM_CHANNEL, NOTE_G, 5);
      delay(50);
    }
    else {
      ledcWriteTone(TONE_PWM_CHANNEL, 0);
    }

    if (b6.isDown()){
      ledcWriteNote(TONE_PWM_CHANNEL, NOTE_A, 5);
      delay(50);
    }
    else {
      ledcWriteTone(TONE_PWM_CHANNEL, 0);
    }

    if (b7.isDown()){
      ledcWriteNote(TONE_PWM_CHANNEL, NOTE_B, 5);
      delay(50);
    }
    else {
      ledcWriteTone(TONE_PWM_CHANNEL, 0);
    }

    if (b8.isDown()){
      ledcWriteNote(TONE_PWM_CHANNEL, NOTE_C, 6);
      delay(50);
    }
    else {
      ledcWriteTone(TONE_PWM_CHANNEL, 0);
    }
  }
}

void ChooseSong(void *unused){
  for(;;) {
    if (s1.isDown()){  
      //Jingle Bell    
      delay(500);
      
      //start
      digitalWrite(led3, HIGH);
      delay(250);
      digitalWrite(led3, LOW);
      delay(250);

      digitalWrite(led3, HIGH);
      delay(250);
      digitalWrite(led3, LOW);
      delay(250);

      digitalWrite(led3, HIGH);
      delay(500);
      digitalWrite(led3, LOW);
      delay(250);

      digitalWrite(led3, HIGH);
      delay(250);
      digitalWrite(led3, LOW);
      delay(250);

      digitalWrite(led3, HIGH);
      delay(250);
      digitalWrite(led3, LOW);
      delay(250);

      digitalWrite(led3, HIGH);
      delay(500);
      digitalWrite(led3, LOW);
      delay(250);

      digitalWrite(led3, HIGH);
      delay(250);
      digitalWrite(led3, LOW);
      delay(250);

      digitalWrite(led5, HIGH);
      delay(250);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led1, HIGH);
      delay(500);
      digitalWrite(led1, LOW);
      delay(250);

      digitalWrite(led2, HIGH);
      delay(250);
      digitalWrite(led2, LOW);
      delay(250);

      digitalWrite(led3, HIGH);
      delay(750);
      digitalWrite(led3, LOW);
      delay(500);

      //   
      digitalWrite(led4, HIGH);
      delay(250);
      digitalWrite(led4, LOW);
      delay(250);

      digitalWrite(led4, HIGH);
      delay(250);
      digitalWrite(led4, LOW);
      delay(250);

      digitalWrite(led4, HIGH);
      delay(500);
      digitalWrite(led4, LOW);
      delay(250);

      digitalWrite(led4, HIGH);
      delay(250);
      digitalWrite(led4, LOW);
      delay(250);

      digitalWrite(led3, HIGH);
      delay(250);
      digitalWrite(led3, LOW);
      delay(250);

      digitalWrite(led3, HIGH);
      delay(500);
      digitalWrite(led3, LOW);
      delay(250);

      //
      digitalWrite(led2, HIGH);
      delay(250);
      digitalWrite(led2, LOW);
      delay(250);

      digitalWrite(led2, HIGH);
      delay(250);
      digitalWrite(led2, LOW);
      delay(250);

      digitalWrite(led2, HIGH);
      delay(250);
      digitalWrite(led2, LOW);
      delay(250);

      digitalWrite(led3, HIGH);
      delay(250);
      digitalWrite(led3, LOW);
      delay(250);

      digitalWrite(led2, HIGH);
      delay(500);
      digitalWrite(led2, LOW);
      delay(250);

      digitalWrite(led5, HIGH);
      delay(500);
      digitalWrite(led5, LOW);
      delay(250); 

      // 
      digitalWrite(led3, HIGH);
      delay(250);
      digitalWrite(led3, LOW);
      delay(250);

      digitalWrite(led3, HIGH);
      delay(250);
      digitalWrite(led3, LOW);
      delay(250);

      digitalWrite(led3, HIGH);
      delay(500);
      digitalWrite(led3, LOW);
      delay(250);

      digitalWrite(led3, HIGH);
      delay(250);
      digitalWrite(led3, LOW);
      delay(250);

      digitalWrite(led3, HIGH);
      delay(250);
      digitalWrite(led3, LOW);
      delay(250);

      digitalWrite(led3, HIGH);
      delay(500);
      digitalWrite(led3, LOW);
      delay(250);

      digitalWrite(led3, HIGH);
      delay(250);
      digitalWrite(led3, LOW);
      delay(250);

      digitalWrite(led5, HIGH);
      delay(250);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led1, HIGH);
      delay(500);
      digitalWrite(led1, LOW);
      delay(250);

      digitalWrite(led2, HIGH);
      delay(250);
      digitalWrite(led2, LOW);
      delay(250);

      digitalWrite(led3, HIGH);
      delay(750);
      digitalWrite(led3, LOW);
      delay(500);

      //   
      digitalWrite(led4, HIGH);
      delay(250);
      digitalWrite(led4, LOW);
      delay(250);

      digitalWrite(led4, HIGH);
      delay(250);
      digitalWrite(led4, LOW);
      delay(250);

      digitalWrite(led4, HIGH);
      delay(500);
      digitalWrite(led4, LOW);
      delay(250);

      digitalWrite(led4, HIGH);
      delay(250);
      digitalWrite(led4, LOW);
      delay(250);

      digitalWrite(led3, HIGH);
      delay(250);
      digitalWrite(led3, LOW);
      delay(250);

      digitalWrite(led3, HIGH);
      delay(500);
      digitalWrite(led3, LOW);
      delay(250);

      //
      digitalWrite(led5, HIGH);
      delay(250);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led5, HIGH);
      delay(250);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led4, HIGH);
      delay(250);
      digitalWrite(led4, LOW);
      delay(250);

      digitalWrite(led2, HIGH);
      delay(250);
      digitalWrite(led2, LOW);
      delay(250);

      digitalWrite(led1, HIGH);
      delay(750);
      digitalWrite(led1, LOW);
      delay(250);
    }   
    else if (s2.isDown()){
      //London Bridge
      delay(500);

      //start
      //
      digitalWrite(led5, HIGH);
      delay(500);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led6, HIGH);
      delay(125);
      digitalWrite(led6, LOW);
      delay(250);

      digitalWrite(led5, HIGH);
      delay(250);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led4, HIGH);
      delay(250);
      digitalWrite(led4, LOW);
      delay(250);

      digitalWrite(led3, HIGH);
      delay(250);
      digitalWrite(led3, LOW);
      delay(250);

      digitalWrite(led4, HIGH);
      delay(250);
      digitalWrite(led4, LOW);
      delay(250);

      digitalWrite(led5, HIGH);
      delay(500);
      digitalWrite(led5, LOW);
      delay(250);

      //
      digitalWrite(led2, HIGH);
      delay(250);
      digitalWrite(led2, LOW);
      delay(250);

      digitalWrite(led3, HIGH);
      delay(250);
      digitalWrite(led3, LOW);
      delay(250);

      digitalWrite(led4, HIGH);
      delay(500);
      digitalWrite(led4, LOW);
      delay(250);

      digitalWrite(led3, HIGH);
      delay(250);
      digitalWrite(led3, LOW);
      delay(250);

      digitalWrite(led4, HIGH);
      delay(250);
      digitalWrite(led4, LOW);
      delay(250);

      digitalWrite(led5, HIGH);
      delay(500);
      digitalWrite(led5, LOW);
      delay(250);

      //
      digitalWrite(led5, HIGH);
      delay(500);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led6, HIGH);
      delay(125);
      digitalWrite(led6, LOW);
      delay(250);

      digitalWrite(led5, HIGH);
      delay(250);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led4, HIGH);
      delay(250);
      digitalWrite(led4, LOW);
      delay(250);

      digitalWrite(led3, HIGH);
      delay(250);
      digitalWrite(led3, LOW);
      delay(250);

      digitalWrite(led4, HIGH);
      delay(250);
      digitalWrite(led4, LOW);
      delay(250);

      digitalWrite(led5, HIGH);
      delay(500);
      digitalWrite(led5, LOW);
      delay(250);

      //
      digitalWrite(led2, HIGH);
      delay(500);
      digitalWrite(led2, LOW);
      delay(250);

      digitalWrite(led5, HIGH);
      delay(500);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led3, HIGH);
      delay(250);
      digitalWrite(led3, LOW);
      delay(250);

      digitalWrite(led1, HIGH);
      delay(250);
      digitalWrite(led1, LOW);
      delay(750);

      //verse2
      digitalWrite(led5, HIGH);
      delay(500);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led6, HIGH);
      delay(125);
      digitalWrite(led6, LOW);
      delay(250);

      digitalWrite(led5, HIGH);
      delay(250);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led4, HIGH);
      delay(250);
      digitalWrite(led4, LOW);
      delay(250);

      digitalWrite(led3, HIGH);
      delay(125);
      digitalWrite(led3, LOW);
      delay(125);

      digitalWrite(led3, HIGH);
      delay(125);
      digitalWrite(led3, LOW);
      delay(125);

      digitalWrite(led4, HIGH);
      delay(250);
      digitalWrite(led4, LOW);
      delay(250);

      digitalWrite(led5, HIGH);
      delay(500);
      digitalWrite(led5, LOW);
      delay(250);

      //
      digitalWrite(led2, HIGH);
      delay(125);
      digitalWrite(led2, LOW);
      delay(125);

      digitalWrite(led2, HIGH);
      delay(125);
      digitalWrite(led2, LOW);
      delay(125);

      digitalWrite(led3, HIGH);
      delay(250);
      digitalWrite(led3, LOW);
      delay(250);

      digitalWrite(led4, HIGH);
      delay(500);
      digitalWrite(led4, LOW);
      delay(250);

      digitalWrite(led3, HIGH);
      delay(125);
      digitalWrite(led3, LOW);
      delay(125);

      digitalWrite(led3, HIGH);
      delay(125);
      digitalWrite(led3, LOW);
      delay(125);

      digitalWrite(led4, HIGH);
      delay(250);
      digitalWrite(led4, LOW);
      delay(250);

      digitalWrite(led5, HIGH);
      delay(500);
      digitalWrite(led5, LOW);
      delay(250);

      //
      digitalWrite(led5, HIGH);
      delay(500);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led6, HIGH);
      delay(125);
      digitalWrite(led6, LOW);
      delay(250);

      digitalWrite(led5, HIGH);
      delay(250);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led4, HIGH);
      delay(250);
      digitalWrite(led4, LOW);
      delay(250);

      digitalWrite(led3, HIGH);
      delay(125);
      digitalWrite(led3, LOW);
      delay(125);

      digitalWrite(led3, HIGH);
      delay(125);
      digitalWrite(led3, LOW);
      delay(125);

      digitalWrite(led4, HIGH);
      delay(250);
      digitalWrite(led4, LOW);
      delay(250);

      digitalWrite(led5, HIGH);
      delay(500);
      digitalWrite(led5, LOW);
      delay(250);

      //
      digitalWrite(led2, HIGH);
      delay(500);
      digitalWrite(led2, LOW);
      delay(250);

      digitalWrite(led5, HIGH);
      delay(500);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led3, HIGH);
      delay(250);
      digitalWrite(led3, LOW);
      delay(250);

      digitalWrite(led1, HIGH);
      delay(250);
      digitalWrite(led1, LOW);
      delay(250);

      digitalWrite(led1, HIGH);
      delay(500);
      digitalWrite(led1, LOW);
      delay(500);
    }
    else if (s3.isDown()){
      //All Of Me
      delay(500);
      
      //start
      digitalWrite(led5, HIGH);
      delay(1250);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led3, HIGH);
      delay(250);
      digitalWrite(led3, LOW);
      delay(250);

      digitalWrite(led6, HIGH);
      delay(500);
      digitalWrite(led6, LOW);
      delay(250);

      digitalWrite(led3, HIGH);
      delay(500);
      digitalWrite(led3, LOW);
      delay(250);

      digitalWrite(led2, HIGH);
      delay(1250);
      digitalWrite(led2, LOW);
      delay(250);

      digitalWrite(led1, HIGH);
      delay(250);
      digitalWrite(led1, LOW);
      delay(250);

      digitalWrite(led3, HIGH);
      delay(500);
      digitalWrite(led3, LOW);
      delay(250);

      //
      digitalWrite(led3, HIGH);
      delay(250);
      digitalWrite(led3, LOW);
      delay(250);

      digitalWrite(led3, HIGH);
      delay(500);
      digitalWrite(led3, LOW);
      delay(250);

      digitalWrite(led2, HIGH);
      delay(250);
      digitalWrite(led2, LOW);
      delay(250);

      digitalWrite(led2, HIGH);
      delay(250);
      digitalWrite(led2, LOW);
      delay(250);
      
      digitalWrite(led2, HIGH);
      delay(250);
      digitalWrite(led2, LOW);
      delay(125);

      digitalWrite(led1, HIGH);
      delay(125);
      digitalWrite(led1, LOW);
      delay(125);

      digitalWrite(led2, HIGH);
      delay(250);
      digitalWrite(led2, LOW);
      delay(750);

      //
      digitalWrite(led3, HIGH);
      delay(250);
      digitalWrite(led3, LOW);
      delay(250);

      digitalWrite(led3, HIGH);
      delay(500);
      digitalWrite(led3, LOW);
      delay(250);

      digitalWrite(led2, HIGH);
      delay(250);
      digitalWrite(led2, LOW);
      delay(250);

      digitalWrite(led2, HIGH);
      delay(250);
      digitalWrite(led2, LOW);
      delay(250);
      
      digitalWrite(led2, HIGH);
      delay(250);
      digitalWrite(led2, LOW);
      delay(125);

      digitalWrite(led1, HIGH);
      delay(125);
      digitalWrite(led1, LOW);
      delay(125);

      digitalWrite(led2, HIGH);
      delay(250);
      digitalWrite(led2, LOW);
      delay(750);

      //verse2
      digitalWrite(led3, HIGH);
      delay(250);
      digitalWrite(led3, LOW);
      delay(125);

      digitalWrite(led3, HIGH);
      delay(250);
      digitalWrite(led3, LOW);
      delay(125);

      digitalWrite(led5, HIGH);
      delay(250);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led5, HIGH);
      delay(1250);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led3, HIGH);
      delay(250);
      digitalWrite(led3, LOW);
      delay(250);

      digitalWrite(led6, HIGH);
      delay(500);
      digitalWrite(led6, LOW);
      delay(250);

      digitalWrite(led8, HIGH);
      delay(125);
      digitalWrite(led8, LOW);
      delay(125);

      digitalWrite(led7, HIGH);
      delay(125);
      digitalWrite(led7, LOW);
      delay(500);

      digitalWrite(led6, HIGH);
      delay(750);
      digitalWrite(led6, LOW);
      delay(500);

      digitalWrite(led5, HIGH);
      delay(250);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led3, HIGH);
      delay(500);
      digitalWrite(led3, LOW);
      delay(250);

      //
      digitalWrite(led3, HIGH);
      delay(250);
      digitalWrite(led3, LOW);
      delay(250);

      digitalWrite(led3, HIGH);
      delay(500);
      digitalWrite(led3, LOW);
      delay(250);

      digitalWrite(led2, HIGH);
      delay(250);
      digitalWrite(led2, LOW);
      delay(250);

      digitalWrite(led2, HIGH);
      delay(250);
      digitalWrite(led2, LOW);
      delay(250);
      
      digitalWrite(led2, HIGH);
      delay(250);
      digitalWrite(led2, LOW);
      delay(125);

      digitalWrite(led1, HIGH);
      delay(125);
      digitalWrite(led1, LOW);
      delay(125);

      digitalWrite(led2, HIGH);
      delay(250);
      digitalWrite(led2, LOW);
      delay(750);

      //
      digitalWrite(led3, HIGH);
      delay(250);
      digitalWrite(led3, LOW);
      delay(250);

      digitalWrite(led3, HIGH);
      delay(500);
      digitalWrite(led3, LOW);
      delay(250);

      digitalWrite(led2, HIGH);
      delay(250);
      digitalWrite(led2, LOW);
      delay(250);

      digitalWrite(led2, HIGH);
      delay(250);
      digitalWrite(led2, LOW);
      delay(250);
      
      digitalWrite(led2, HIGH);
      delay(250);
      digitalWrite(led2, LOW);
      delay(125);

      digitalWrite(led1, HIGH);
      delay(125);
      digitalWrite(led1, LOW);
      delay(125);

      digitalWrite(led2, HIGH);
      delay(250);
      digitalWrite(led2, LOW);
      delay(750);

      //peak
      digitalWrite(led3, HIGH);
      delay(125);
      digitalWrite(led3, LOW);
      delay(125);

      digitalWrite(led3, HIGH);
      delay(125);
      digitalWrite(led3, LOW);
      delay(125);

      digitalWrite(led4, HIGH);
      delay(125);
      digitalWrite(led4, LOW);
      delay(125);

      digitalWrite(led5, HIGH);
      delay(125);
      digitalWrite(led5, LOW);
      delay(125);

      digitalWrite(led8, HIGH);
      delay(750);
      digitalWrite(led8, LOW);
      delay(250);

      digitalWrite(led7, HIGH);
      delay(750);
      digitalWrite(led7, LOW);
      delay(250);

      digitalWrite(led6, HIGH);
      delay(750);
      digitalWrite(led6, LOW);
      delay(250);

      digitalWrite(led5, HIGH);
      delay(500);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led3, HIGH);
      delay(250);
      digitalWrite(led3, LOW);
      delay(125);

      digitalWrite(led3, HIGH);
      delay(500);
      digitalWrite(led3, LOW);
      delay(2000);

      //
      digitalWrite(led3, HIGH);
      delay(125);
      digitalWrite(led3, LOW);
      delay(125);

      digitalWrite(led3, HIGH);
      delay(125);
      digitalWrite(led3, LOW);
      delay(125);

      digitalWrite(led4, HIGH);
      delay(125);
      digitalWrite(led4, LOW);
      delay(125);

      digitalWrite(led5, HIGH);
      delay(125);
      digitalWrite(led5, LOW);
      delay(125);

      digitalWrite(led8, HIGH);
      delay(750);
      digitalWrite(led8, LOW);
      delay(250);

      digitalWrite(led7, HIGH);
      delay(750);
      digitalWrite(led7, LOW);
      delay(250);

      digitalWrite(led6, HIGH);
      delay(750);
      digitalWrite(led6, LOW);
      delay(250);

      digitalWrite(led5, HIGH);
      delay(500);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led3, HIGH);
      delay(250);
      digitalWrite(led3, LOW);
      delay(125);

      digitalWrite(led3, HIGH);
      delay(500);
      digitalWrite(led3, LOW);
      delay(750);

      digitalWrite(led3, HIGH);
      delay(125);
      digitalWrite(led3, LOW);
      delay(250);

      digitalWrite(led2, HIGH);
      delay(500);
      digitalWrite(led2, LOW);
      delay(750);

      digitalWrite(led2, HIGH);
      delay(125);
      digitalWrite(led2, LOW);
      delay(250);

      digitalWrite(led1, HIGH);
      delay(500);
      digitalWrite(led1, LOW);
      delay(250);
    }
  }
}
