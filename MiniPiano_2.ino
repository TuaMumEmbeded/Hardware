#include "pitches.h"
#include <DebouncedSwitch.h>
#include <esp_now.h>
#include <WiFi.h>

const char* ssid = "Toey";
const char* password = "99999997";

TaskHandle_t TaskPiano;
TaskHandle_t CSong;

//switch
int but1 = 19;
int but2 = 21;
int but3 = 22;
int but4 = 23;
int but5 = 12;
int but6 = 13;
int but7 = 32;
int but8 = 33;

//LED
int led1 = 15;
int led2 = 2;
int led3 = 0;
int led4 = 4;
int led5 = 16;
int led6 = 17;
int led7 = 5;
int led8 = 18;


//song
int song1 = 25;
int song2 = 26;
int song3 = 27;

const int BUZZER = 14;
const int TONE_PWM_CHANNEL = 0; 

int notes[] = {
  NOTE_C3, NOTE_D3, NOTE_E3, NOTE_F3, NOTE_G3, NOTE_A3, NOTE_B3, NOTE_C4
};

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
  // pinMode(BUZZER, OUTPUT);
  ledcAttachPin(BUZZER, TONE_PWM_CHANNEL);
  Serial.begin(115200);

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
  
  send_Data.id = 4;
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
      //Twinkle     
      delay(500);
      
      //start
      //     
      digitalWrite(led1, HIGH);
      delay(500);
      digitalWrite(led1, LOW);
      delay(500);

      digitalWrite(led1, HIGH);
      delay(500);
      digitalWrite(led1, LOW);
      delay(500);
      
      digitalWrite(led5, HIGH);
      delay(500);
      digitalWrite(led5, LOW);
      delay(500);

      digitalWrite(led5, HIGH);
      delay(500);
      digitalWrite(led5, LOW);
      delay(500);

      digitalWrite(led6, HIGH);
      delay(500);
      digitalWrite(led6, LOW);
      delay(500);

      digitalWrite(led6, HIGH);
      delay(500);
      digitalWrite(led6, LOW);
      delay(500);

      digitalWrite(led5, HIGH);
      delay(1000);
      digitalWrite(led5, LOW);
      delay(500);

      digitalWrite(led4, HIGH);
      delay(500);
      digitalWrite(led4, LOW);
      delay(500);

      digitalWrite(led4, HIGH);
      delay(500);
      digitalWrite(led4, LOW);
      delay(500);

      digitalWrite(led3, HIGH);
      delay(500);
      digitalWrite(led3, LOW);
      delay(500);

      digitalWrite(led3, HIGH);
      delay(500);
      digitalWrite(led3, LOW);
      delay(500);

      digitalWrite(led2, HIGH);
      delay(500);
      digitalWrite(led2, LOW);
      delay(500);

      digitalWrite(led2, HIGH);
      delay(500);
      digitalWrite(led2, LOW);
      delay(500);

      digitalWrite(led1, HIGH);
      delay(1000);
      digitalWrite(led1, LOW);
      delay(500);

      // 
      digitalWrite(led5, HIGH);
      delay(500);
      digitalWrite(led5, LOW);
      delay(500);

      digitalWrite(led5, HIGH);
      delay(500);
      digitalWrite(led5, LOW);
      delay(500);

      digitalWrite(led4, HIGH);
      delay(500);
      digitalWrite(led4, LOW);
      delay(500);

      digitalWrite(led4, HIGH);
      delay(500);
      digitalWrite(led4, LOW);
      delay(500);

      digitalWrite(led3, HIGH);
      delay(500);
      digitalWrite(led3, LOW);
      delay(500);

      digitalWrite(led3, HIGH);
      delay(500);
      digitalWrite(led3, LOW);
      delay(500);

      digitalWrite(led2, HIGH);
      delay(1000);
      digitalWrite(led2, LOW);
      delay(500);

      // 
      digitalWrite(led5, HIGH);
      delay(500);
      digitalWrite(led5, LOW);
      delay(500);

      digitalWrite(led5, HIGH);
      delay(500);
      digitalWrite(led5, LOW);
      delay(500);

      digitalWrite(led4, HIGH);
      delay(500);
      digitalWrite(led4, LOW);
      delay(500);

      digitalWrite(led4, HIGH);
      delay(500);
      digitalWrite(led4, LOW);
      delay(500);

      digitalWrite(led3, HIGH);
      delay(500);
      digitalWrite(led3, LOW);
      delay(500);

      digitalWrite(led3, HIGH);
      delay(500);
      digitalWrite(led3, LOW);
      delay(500);

      digitalWrite(led2, HIGH);
      delay(1000);
      digitalWrite(led2, LOW);
      delay(500); 

      //
      digitalWrite(led1, HIGH);
      delay(500);
      digitalWrite(led1, LOW);
      delay(500);

      digitalWrite(led1, HIGH);
      delay(500);
      digitalWrite(led1, LOW);
      delay(500);
      
      digitalWrite(led5, HIGH);
      delay(500);
      digitalWrite(led5, LOW);
      delay(500);

      digitalWrite(led5, HIGH);
      delay(500);
      digitalWrite(led5, LOW);
      delay(500);

      digitalWrite(led6, HIGH);
      delay(500);
      digitalWrite(led6, LOW);
      delay(500);

      digitalWrite(led6, HIGH);
      delay(500);
      digitalWrite(led6, LOW);
      delay(500);

      digitalWrite(led5, HIGH);
      delay(1000);
      digitalWrite(led5, LOW);
      delay(500);

      digitalWrite(led4, HIGH);
      delay(500);
      digitalWrite(led4, LOW);
      delay(500);

      digitalWrite(led4, HIGH);
      delay(500);
      digitalWrite(led4, LOW);
      delay(500);

      digitalWrite(led3, HIGH);
      delay(500);
      digitalWrite(led3, LOW);
      delay(500);

      digitalWrite(led3, HIGH);
      delay(500);
      digitalWrite(led3, LOW);
      delay(500);

      digitalWrite(led2, HIGH);
      delay(500);
      digitalWrite(led2, LOW);
      delay(500);

      digitalWrite(led2, HIGH);
      delay(500);
      digitalWrite(led2, LOW);
      delay(500);

      digitalWrite(led1, HIGH);
      delay(1000);
      digitalWrite(led1, LOW);
      delay(500);    
    }   
    else if (s2.isDown()){
      //Joy to the world     
      delay(500);
      
      //start
      //     
      digitalWrite(led8, HIGH);
      delay(500);
      digitalWrite(led8, LOW);
      delay(500);

      digitalWrite(led7, HIGH);
      delay(500);
      digitalWrite(led7, LOW);
      delay(250);
      
      digitalWrite(led6, HIGH);
      delay(250);
      digitalWrite(led6, LOW);
      delay(250);

      digitalWrite(led5, HIGH);
      delay(500);
      digitalWrite(led5, LOW);
      delay(500);

      digitalWrite(led4, HIGH);
      delay(250);
      digitalWrite(led4, LOW);
      delay(250);

      digitalWrite(led3, HIGH);
      delay(500);
      digitalWrite(led3, LOW);
      delay(500);

      digitalWrite(led2, HIGH);
      delay(500);
      digitalWrite(led2, LOW);
      delay(500);

      digitalWrite(led1, HIGH);
      delay(500);
      digitalWrite(led1, LOW);
      delay(750);

      //
      digitalWrite(led5, HIGH);
      delay(250);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led6, HIGH);
      delay(500);
      digitalWrite(led6, LOW);
      delay(500);
      
      digitalWrite(led6, HIGH);
      delay(250);
      digitalWrite(led6, LOW);
      delay(250);

      digitalWrite(led7, HIGH);
      delay(500);
      digitalWrite(led7, LOW);
      delay(500);

      digitalWrite(led7, HIGH);
      delay(250);
      digitalWrite(led7, LOW);
      delay(250);

      digitalWrite(led8, HIGH);
      delay(500);
      digitalWrite(led8, LOW);
      delay(500);

      //
      digitalWrite(led8, HIGH);
      delay(250);
      digitalWrite(led8, LOW);
      delay(250);

      digitalWrite(led8, HIGH);
      delay(500);
      digitalWrite(led8, LOW);
      delay(125);
      
      digitalWrite(led7, HIGH);
      delay(250);
      digitalWrite(led7, LOW);
      delay(250);

      digitalWrite(led6, HIGH);
      delay(500);
      digitalWrite(led6, LOW);
      delay(125);

      digitalWrite(led5, HIGH);
      delay(250);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led5, HIGH);
      delay(500);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led4, HIGH);
      delay(250);
      digitalWrite(led4, LOW);
      delay(250);

      digitalWrite(led3, HIGH);
      delay(250);
      digitalWrite(led3, LOW);
      delay(125);

      //
      digitalWrite(led8, HIGH);
      delay(250);
      digitalWrite(led8, LOW);
      delay(250);

      digitalWrite(led8, HIGH);
      delay(500);
      digitalWrite(led8, LOW);
      delay(125);
      
      digitalWrite(led7, HIGH);
      delay(250);
      digitalWrite(led7, LOW);
      delay(250);

      digitalWrite(led6, HIGH);
      delay(500);
      digitalWrite(led6, LOW);
      delay(125);

      digitalWrite(led5, HIGH);
      delay(250);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led5, HIGH);
      delay(500);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led4, HIGH);
      delay(250);
      digitalWrite(led4, LOW);
      delay(250);

      digitalWrite(led3, HIGH);
      delay(250);
      digitalWrite(led3, LOW);
      delay(125);

      digitalWrite(led3, HIGH);
      delay(250);
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
      delay(250);
      digitalWrite(led3, LOW);
      delay(250);

      digitalWrite(led3, HIGH);
      delay(250);
      digitalWrite(led3, LOW);
      delay(125);

      digitalWrite(led4, HIGH);
      delay(250);
      digitalWrite(led4, LOW);
      delay(125);

      digitalWrite(led5, HIGH);
      delay(500);
      digitalWrite(led5, LOW);
      delay(500);

      //
      digitalWrite(led4, HIGH);
      delay(250);
      digitalWrite(led4, LOW);
      delay(125);

      digitalWrite(led3, HIGH);
      delay(250);
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

      digitalWrite(led2, HIGH);
      delay(250);
      digitalWrite(led2, LOW);
      delay(125);

      digitalWrite(led3, HIGH);
      delay(250);
      digitalWrite(led3, LOW);
      delay(125);

      digitalWrite(led4, HIGH);
      delay(500);
      digitalWrite(led4, LOW);
      delay(500);

      //
      digitalWrite(led3, HIGH);
      delay(250);
      digitalWrite(led3, LOW);
      delay(125);

      digitalWrite(led2, HIGH);
      delay(250);
      digitalWrite(led2, LOW);
      delay(125);
      
      digitalWrite(led1, HIGH);
      delay(250);
      digitalWrite(led1, LOW);
      delay(250);

      digitalWrite(led8, HIGH);
      delay(500);
      digitalWrite(led8, LOW);
      delay(125);

      digitalWrite(led6, HIGH);
      delay(250);
      digitalWrite(led6, LOW);
      delay(125);

      digitalWrite(led5, HIGH);
      delay(250);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led4, HIGH);
      delay(250);
      digitalWrite(led4, LOW);
      delay(125);

      digitalWrite(led3, HIGH);
      delay(250);
      digitalWrite(led3, LOW);
      delay(125);

      digitalWrite(led4, HIGH);
      delay(250);
      digitalWrite(led4, LOW);
      delay(125);

      digitalWrite(led3, HIGH);
      delay(500);
      digitalWrite(led3, LOW);
      delay(500);

      digitalWrite(led2, HIGH);
      delay(500);
      digitalWrite(led2, LOW);
      delay(500);

      digitalWrite(led1, HIGH);
      delay(500);
      digitalWrite(led1, LOW);
      delay(500);

      //verse2
      //     
      digitalWrite(led8, HIGH);
      delay(500);
      digitalWrite(led8, LOW);
      delay(500);

      digitalWrite(led7, HIGH);
      delay(500);
      digitalWrite(led7, LOW);
      delay(250);
      
      digitalWrite(led6, HIGH);
      delay(250);
      digitalWrite(led6, LOW);
      delay(250);

      digitalWrite(led5, HIGH);
      delay(500);
      digitalWrite(led5, LOW);
      delay(500);

      digitalWrite(led4, HIGH);
      delay(250);
      digitalWrite(led4, LOW);
      delay(250);

      digitalWrite(led3, HIGH);
      delay(500);
      digitalWrite(led3, LOW);
      delay(500);

      digitalWrite(led2, HIGH);
      delay(500);
      digitalWrite(led2, LOW);
      delay(500);

      digitalWrite(led1, HIGH);
      delay(500);
      digitalWrite(led1, LOW);
      delay(750);

      //
      digitalWrite(led5, HIGH);
      delay(250);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led6, HIGH);
      delay(500);
      digitalWrite(led6, LOW);
      delay(500);
      
      digitalWrite(led6, HIGH);
      delay(250);
      digitalWrite(led6, LOW);
      delay(250);

      digitalWrite(led7, HIGH);
      delay(500);
      digitalWrite(led7, LOW);
      delay(500);

      digitalWrite(led7, HIGH);
      delay(250);
      digitalWrite(led7, LOW);
      delay(250);

      digitalWrite(led8, HIGH);
      delay(500);
      digitalWrite(led8, LOW);
      delay(500);

      //
      digitalWrite(led8, HIGH);
      delay(250);
      digitalWrite(led8, LOW);
      delay(250);

      digitalWrite(led8, HIGH);
      delay(500);
      digitalWrite(led8, LOW);
      delay(125);
      
      digitalWrite(led7, HIGH);
      delay(250);
      digitalWrite(led7, LOW);
      delay(250);

      digitalWrite(led6, HIGH);
      delay(500);
      digitalWrite(led6, LOW);
      delay(125);

      digitalWrite(led5, HIGH);
      delay(250);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led5, HIGH);
      delay(500);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led4, HIGH);
      delay(250);
      digitalWrite(led4, LOW);
      delay(250);

      digitalWrite(led3, HIGH);
      delay(250);
      digitalWrite(led3, LOW);
      delay(125);

      //
      digitalWrite(led8, HIGH);
      delay(250);
      digitalWrite(led8, LOW);
      delay(250);

      digitalWrite(led8, HIGH);
      delay(500);
      digitalWrite(led8, LOW);
      delay(125);
      
      digitalWrite(led7, HIGH);
      delay(250);
      digitalWrite(led7, LOW);
      delay(250);

      digitalWrite(led6, HIGH);
      delay(500);
      digitalWrite(led6, LOW);
      delay(125);

      digitalWrite(led5, HIGH);
      delay(250);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led5, HIGH);
      delay(500);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led4, HIGH);
      delay(250);
      digitalWrite(led4, LOW);
      delay(250);

      digitalWrite(led3, HIGH);
      delay(250);
      digitalWrite(led3, LOW);
      delay(125);

      digitalWrite(led3, HIGH);
      delay(250);
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
      delay(250);
      digitalWrite(led3, LOW);
      delay(250);

      digitalWrite(led3, HIGH);
      delay(250);
      digitalWrite(led3, LOW);
      delay(125);

      digitalWrite(led4, HIGH);
      delay(250);
      digitalWrite(led4, LOW);
      delay(125);

      digitalWrite(led5, HIGH);
      delay(500);
      digitalWrite(led5, LOW);
      delay(500);

      //
      digitalWrite(led4, HIGH);
      delay(250);
      digitalWrite(led4, LOW);
      delay(125);

      digitalWrite(led3, HIGH);
      delay(250);
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

      digitalWrite(led2, HIGH);
      delay(250);
      digitalWrite(led2, LOW);
      delay(125);

      digitalWrite(led3, HIGH);
      delay(250);
      digitalWrite(led3, LOW);
      delay(125);

      digitalWrite(led4, HIGH);
      delay(500);
      digitalWrite(led4, LOW);
      delay(500);

      //
      digitalWrite(led3, HIGH);
      delay(250);
      digitalWrite(led3, LOW);
      delay(125);

      digitalWrite(led2, HIGH);
      delay(250);
      digitalWrite(led2, LOW);
      delay(125);
      
      digitalWrite(led1, HIGH);
      delay(250);
      digitalWrite(led1, LOW);
      delay(250);

      digitalWrite(led8, HIGH);
      delay(500);
      digitalWrite(led8, LOW);
      delay(125);

      digitalWrite(led6, HIGH);
      delay(250);
      digitalWrite(led6, LOW);
      delay(125);

      digitalWrite(led5, HIGH);
      delay(250);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led4, HIGH);
      delay(250);
      digitalWrite(led4, LOW);
      delay(125);

      digitalWrite(led3, HIGH);
      delay(250);
      digitalWrite(led3, LOW);
      delay(125);

      digitalWrite(led4, HIGH);
      delay(250);
      digitalWrite(led4, LOW);
      delay(125);

      digitalWrite(led3, HIGH);
      delay(500);
      digitalWrite(led3, LOW);
      delay(500);

      digitalWrite(led2, HIGH);
      delay(500);
      digitalWrite(led2, LOW);
      delay(500);

      digitalWrite(led1, HIGH);
      delay(500);
      digitalWrite(led1, LOW);
      delay(500);
    } 
    else if (s3.isDown()){
      //Red     
      delay(500);
      
      //start
      digitalWrite(led5, HIGH);
      delay(125);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led6, HIGH);
      delay(125);
      digitalWrite(led6, LOW);
      delay(250);
      
      digitalWrite(led5, HIGH);
      delay(125);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led4, HIGH);
      delay(125);
      digitalWrite(led4, LOW);
      delay(250);

      digitalWrite(led4, HIGH);
      delay(250);
      digitalWrite(led4, LOW);
      delay(250);

      digitalWrite(led4, HIGH);
      delay(125);
      digitalWrite(led4, LOW);
      delay(250);

      digitalWrite(led2, HIGH);
      delay(125);
      digitalWrite(led2, LOW);
      delay(250);

      digitalWrite(led4, HIGH);
      delay(125);
      digitalWrite(led4, LOW);
      delay(250);

      digitalWrite(led6, HIGH);
      delay(125);
      digitalWrite(led6, LOW);
      delay(250);

      digitalWrite(led4, HIGH);
      delay(125);
      digitalWrite(led4, LOW);
      delay(500);

      digitalWrite(led1, HIGH);
      delay(250);
      digitalWrite(led1, LOW);
      delay(500);

      //
      digitalWrite(led5, HIGH);
      delay(125);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led6, HIGH);
      delay(125);
      digitalWrite(led6, LOW);
      delay(250);
      
      digitalWrite(led5, HIGH);
      delay(125);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led4, HIGH);
      delay(125);
      digitalWrite(led4, LOW);
      delay(250);

      digitalWrite(led5, HIGH);
      delay(250);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led5, HIGH);
      delay(250);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led5, HIGH);
      delay(250);
      digitalWrite(led5, LOW);
      delay(125);

      digitalWrite(led1, HIGH);
      delay(125);
      digitalWrite(led1, LOW);
      delay(250);

      digitalWrite(led6, HIGH);
      delay(125);
      digitalWrite(led6, LOW);
      delay(250);

      digitalWrite(led5, HIGH);
      delay(500);
      digitalWrite(led5, LOW);
      delay(500);

      //
      digitalWrite(led5, HIGH);
      delay(125);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led6, HIGH);
      delay(125);
      digitalWrite(led6, LOW);
      delay(250);
      
      digitalWrite(led5, HIGH);
      delay(125);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led4, HIGH);
      delay(125);
      digitalWrite(led4, LOW);
      delay(250);

      digitalWrite(led4, HIGH);
      delay(250);
      digitalWrite(led4, LOW);
      delay(250);

      digitalWrite(led2, HIGH);
      delay(125);
      digitalWrite(led2, LOW);
      delay(250);

      digitalWrite(led4, HIGH);
      delay(500);
      digitalWrite(led4, LOW);
      delay(125);

      digitalWrite(led4, HIGH);
      delay(500);
      digitalWrite(led4, LOW);
      delay(125);

      digitalWrite(led4, HIGH);
      delay(500);
      digitalWrite(led4, LOW);
      delay(125);

      digitalWrite(led4, HIGH);
      delay(500);
      digitalWrite(led4, LOW);
      delay(125);

      digitalWrite(led4, HIGH);
      delay(500);
      digitalWrite(led4, LOW);
      delay(250);

      digitalWrite(led5, HIGH);
      delay(1500);
      digitalWrite(led5, LOW);
      delay(500);

      //
      digitalWrite(led6, HIGH);
      delay(125);
      digitalWrite(led6, LOW);
      delay(250);

      digitalWrite(led6, HIGH);
      delay(125);
      digitalWrite(led6, LOW);
      delay(250);

      digitalWrite(led5, HIGH);
      delay(125);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led4, HIGH);
      delay(125);
      digitalWrite(led4, LOW);
      delay(250);

      digitalWrite(led4, HIGH);
      delay(500);
      digitalWrite(led4, LOW);
      delay(250);

      //
      digitalWrite(led4, HIGH);
      delay(125);
      digitalWrite(led4, LOW);
      delay(250);
      
      digitalWrite(led4, HIGH);
      delay(125);
      digitalWrite(led4, LOW);
      delay(250);

      digitalWrite(led4, HIGH);
      delay(125);
      digitalWrite(led4, LOW);
      delay(250);
      
      digitalWrite(led4, HIGH);
      delay(500);
      digitalWrite(led4, LOW);
      delay(250);

      digitalWrite(led4, HIGH);
      delay(125);
      digitalWrite(led4, LOW);
      delay(250);
      
      digitalWrite(led4, HIGH);
      delay(125);
      digitalWrite(led4, LOW);
      delay(250);

      digitalWrite(led4, HIGH);
      delay(125);
      digitalWrite(led4, LOW);
      delay(250);
      
      digitalWrite(led4, HIGH);
      delay(500);
      digitalWrite(led4, LOW);
      delay(500);

      digitalWrite(led5, HIGH);
      delay(125);
      digitalWrite(led5, LOW);
      delay(250);
      
      digitalWrite(led5, HIGH);
      delay(125);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led5, HIGH);
      delay(125);
      digitalWrite(led5, LOW);
      delay(250);
      
      digitalWrite(led5, HIGH);
      delay(500);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led5, HIGH);
      delay(125);
      digitalWrite(led5, LOW);
      delay(250);
      
      digitalWrite(led5, HIGH);
      delay(125);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led5, HIGH);
      delay(125);
      digitalWrite(led5, LOW);
      delay(250);
      
      digitalWrite(led5, HIGH);
      delay(500);
      digitalWrite(led5, LOW);
      delay(250);

      //verse2
      digitalWrite(led5, HIGH);
      delay(125);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led6, HIGH);
      delay(125);
      digitalWrite(led6, LOW);
      delay(250);
      
      digitalWrite(led5, HIGH);
      delay(125);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led4, HIGH);
      delay(125);
      digitalWrite(led4, LOW);
      delay(250);

      digitalWrite(led4, HIGH);
      delay(250);
      digitalWrite(led4, LOW);
      delay(250);

      digitalWrite(led4, HIGH);
      delay(125);
      digitalWrite(led4, LOW);
      delay(250);

      digitalWrite(led2, HIGH);
      delay(125);
      digitalWrite(led2, LOW);
      delay(250);

      digitalWrite(led4, HIGH);
      delay(125);
      digitalWrite(led4, LOW);
      delay(250);

      digitalWrite(led6, HIGH);
      delay(125);
      digitalWrite(led6, LOW);
      delay(250);

      digitalWrite(led4, HIGH);
      delay(125);
      digitalWrite(led4, LOW);
      delay(500);

      digitalWrite(led1, HIGH);
      delay(250);
      digitalWrite(led1, LOW);
      delay(500);

      //
      digitalWrite(led5, HIGH);
      delay(125);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led6, HIGH);
      delay(125);
      digitalWrite(led6, LOW);
      delay(250);
      
      digitalWrite(led5, HIGH);
      delay(125);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led4, HIGH);
      delay(125);
      digitalWrite(led4, LOW);
      delay(250);

      digitalWrite(led5, HIGH);
      delay(250);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led5, HIGH);
      delay(250);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led5, HIGH);
      delay(250);
      digitalWrite(led5, LOW);
      delay(125);

      digitalWrite(led1, HIGH);
      delay(125);
      digitalWrite(led1, LOW);
      delay(250);

      digitalWrite(led6, HIGH);
      delay(125);
      digitalWrite(led6, LOW);
      delay(250);

      digitalWrite(led5, HIGH);
      delay(500);
      digitalWrite(led5, LOW);
      delay(500);

      //
      digitalWrite(led5, HIGH);
      delay(125);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led6, HIGH);
      delay(125);
      digitalWrite(led6, LOW);
      delay(250);
      
      digitalWrite(led5, HIGH);
      delay(125);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led4, HIGH);
      delay(125);
      digitalWrite(led4, LOW);
      delay(250);

      digitalWrite(led4, HIGH);
      delay(250);
      digitalWrite(led4, LOW);
      delay(250);

      digitalWrite(led2, HIGH);
      delay(125);
      digitalWrite(led2, LOW);
      delay(250);

      digitalWrite(led4, HIGH);
      delay(500);
      digitalWrite(led4, LOW);
      delay(125);

      digitalWrite(led4, HIGH);
      delay(500);
      digitalWrite(led4, LOW);
      delay(125);

      digitalWrite(led4, HIGH);
      delay(500);
      digitalWrite(led4, LOW);
      delay(125);

      digitalWrite(led4, HIGH);
      delay(500);
      digitalWrite(led4, LOW);
      delay(125);

      digitalWrite(led4, HIGH);
      delay(500);
      digitalWrite(led4, LOW);
      delay(250);

      digitalWrite(led5, HIGH);
      delay(1500);
      digitalWrite(led5, LOW);
      delay(500);

      //
      digitalWrite(led6, HIGH);
      delay(125);
      digitalWrite(led6, LOW);
      delay(250);

      digitalWrite(led6, HIGH);
      delay(125);
      digitalWrite(led6, LOW);
      delay(250);

      digitalWrite(led5, HIGH);
      delay(125);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led4, HIGH);
      delay(125);
      digitalWrite(led4, LOW);
      delay(250);

      digitalWrite(led4, HIGH);
      delay(500);
      digitalWrite(led4, LOW);
      delay(250);

      //
      digitalWrite(led4, HIGH);
      delay(125);
      digitalWrite(led4, LOW);
      delay(250);
      
      digitalWrite(led4, HIGH);
      delay(125);
      digitalWrite(led4, LOW);
      delay(250);

      digitalWrite(led4, HIGH);
      delay(125);
      digitalWrite(led4, LOW);
      delay(250);
      
      digitalWrite(led4, HIGH);
      delay(500);
      digitalWrite(led4, LOW);
      delay(250);

      digitalWrite(led4, HIGH);
      delay(125);
      digitalWrite(led4, LOW);
      delay(250);
      
      digitalWrite(led4, HIGH);
      delay(125);
      digitalWrite(led4, LOW);
      delay(250);

      digitalWrite(led4, HIGH);
      delay(125);
      digitalWrite(led4, LOW);
      delay(250);
      
      digitalWrite(led4, HIGH);
      delay(500);
      digitalWrite(led4, LOW);
      delay(500);

      digitalWrite(led5, HIGH);
      delay(125);
      digitalWrite(led5, LOW);
      delay(250);
      
      digitalWrite(led5, HIGH);
      delay(125);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led5, HIGH);
      delay(125);
      digitalWrite(led5, LOW);
      delay(250);
      
      digitalWrite(led5, HIGH);
      delay(500);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led5, HIGH);
      delay(125);
      digitalWrite(led5, LOW);
      delay(250);
      
      digitalWrite(led5, HIGH);
      delay(125);
      digitalWrite(led5, LOW);
      delay(250);

      digitalWrite(led5, HIGH);
      delay(125);
      digitalWrite(led5, LOW);
      delay(250);
      
      digitalWrite(led5, HIGH);
      delay(500);
      digitalWrite(led5, LOW);
      delay(500);

      //peak
      digitalWrite(led4, HIGH);
      delay(125);
      digitalWrite(led4, LOW);
      delay(250);
      
      digitalWrite(led8, HIGH);
      delay(125);
      digitalWrite(led8, LOW);
      delay(250);

      digitalWrite(led5, HIGH);
      delay(125);
      digitalWrite(led5, LOW);
      delay(250);
      
      digitalWrite(led6, HIGH);
      delay(1750);
      digitalWrite(led6, LOW);
      delay(500);

      digitalWrite(led5, HIGH);
      delay(125);
      digitalWrite(led5, LOW);
      delay(250);
      
      digitalWrite(led4, HIGH);
      delay(125);
      digitalWrite(led4, LOW);
      delay(250);

      digitalWrite(led5, HIGH);
      delay(1500);
      digitalWrite(led5, LOW);
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
      delay(250);
      digitalWrite(led3, LOW);
      delay(250);

      digitalWrite(led2, HIGH);
      delay(500);
      digitalWrite(led2, LOW);
      delay(250);
    }   
  }
}