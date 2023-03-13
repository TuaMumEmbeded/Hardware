//SENDER
#include <esp_now.h>
#include <WiFi.h>
//----------------------------------------
const char* ssid = "Toey";
const char* password = "99999997";
//----------------------------------------Defines PIN Button and PIN LED.
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

int send_val_1;

//----------------------------------------

uint8_t broadcastAddress[] = {0x4C, 0x11, 0xAE, 0xD3, 0xED, 0x34}; //--> REPLACE WITH THE MAC Address of your receiver.(B)

// int LED_State_Send1 = 0; //--> Variable to hold the data to be transmitted to control the LEDs on the paired ESP32.
// int LED_State_Send2 = 0;
// int LED_State_Send3 = 0;
// int BUZZ_State_Send = 0;

// int LED_State_Receive; //--> Variable to receive data to control the LEDs on the ESP32 running this code.

String success; //--> Variable to store if sending data was successful

//----------------------------------------Structure example to send data
//Must match the receiver structure
typedef struct struct_message {
  int id;
  int blue_led;
  int green_led;
  int yellow_led;
  int violet_led;
  int red_led;
  int buzz;
} struct_message_send;

struct_message send_Data; // Create a struct_message to send data.

esp_now_peer_info_t peerInfo;

// struct_message receive_Data; // Create a struct_message to receive data.
//----------------------------------------

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ Callback when data is sent
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
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ Callback when data is received
// void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
//   memcpy(&receive_Data, incomingData, sizeof(receive_Data));
//   Serial.println();
//   Serial.println("<<<<< Receive Data:");
//   Serial.print("Bytes received: ");
//   Serial.println(len);
//   LED_State_Receive = receive_Data.red_led;
//   Serial.print("Receive Data: ");
//   Serial.println(LED_State_Receive);
//   Serial.println("<<<<<");

//   digitalWrite(LED_Pin, );
// }
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ VOID SETUP
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
  
  WiFi.mode(WIFI_STA); //--> Set device as a Wi-Fi Station
  WiFi.begin(ssid, password);

  //----------------------------------------Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  //----------------------------------------
  
  //----------------------------------------Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  //----------------------------------------
  
  //----------------------------------------Register peer
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  //----------------------------------------
  
  //----------------------------------------Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  //----------------------------------------
  
  // esp_now_register_recv_cb(OnDataRecv); //--> Register for a callback function that will be called when data is received
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void loop() {

  // send_val_1 = random(0, 255);
  // send_Data.red_led = 100;
  // delay(3000);
  send_Data.id = 2;

  //FLEX SENSOR
  Serial.println("data1 =");
  Serial.println(analogRead(flex1));
  Serial.println("data2 =");
  Serial.println(analogRead(flex2));
  delay(1000);
  if ((analogRead(flex1) < 600) && (analogRead(flex2) < 600)){
    digitalWrite(violet_led, HIGH);
    send_Data.violet_led = 1;
    // delay(2000);
    // digitalWrite(red_led, LOW);
    // send_Data.red_led = 0;
  }else if ((analogRead(flex1) < 500) && (analogRead(flex2) > 800)){
    digitalWrite(yellow_led, HIGH);
    send_Data.yellow_led = 1;
    // delay(2000);
    // digitalWrite(yellow_led, LOW);
    // send_Data.yellow_led = 0;
  }else if ((analogRead(flex1) > 800) && (analogRead(flex2) < 600)){
    digitalWrite(green_led, HIGH);
    send_Data.green_led = 1;
    // delay(2000);
    // digitalWrite(green_led, LOW);
    // send_Data.green_led = 0;
  }else{
    digitalWrite(violet_led, LOW);
    digitalWrite(yellow_led, LOW);
    digitalWrite(green_led, LOW);
    send_Data.violet_led = 0;
    send_Data.yellow_led = 0;
    send_Data.green_led = 0;
  }

  // //ULTRASONIC & BUZZER
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
  // Serial.println(duration1);

  if (((duration1 < 1000) and (duration1 > 200)) or ((duration2 < 1000) and (duration2 > 200))){
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

  //----------------------------------------When the button is pressed it will send data to control the LED on the ESP32 Target.

  Serial.println();
  Serial.print(">>>>> ");
  Serial.println("Send data");

  //----------------------------------------Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &send_Data, sizeof(send_Data));
    
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  //----------------------------------------

  //----------------------------------------Wait for the button to be released. Release the button first to send the next data.
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<