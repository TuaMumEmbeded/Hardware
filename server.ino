#include <esp_now.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "Toey";
const char* password = "99999997";
char jsonOutput[128];

String success;

typedef struct struct_message_forsend {
  int id[2];
  bool blue_led[2];
  bool green_led[2];
  bool yellow_led[2];
  bool violet_led[2];
  bool red_led[2];
};  

struct_message_forsend receive_Data;

char jsonOutput1[128];
char jsonOutput2[128];

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&receive_Data, incomingData, sizeof(receive_Data));

  const size_t CAPACITY = JSON_OBJECT_SIZE(5);
  StaticJsonDocument<CAPACITY> doc1;
  StaticJsonDocument<CAPACITY> doc2;

  JsonObject object1 = doc1.to<JsonObject>();
  JsonObject object2 = doc2.to<JsonObject>();

  object1["Emergency"] = receive_Data.violet_led[0];
  object1["Bed"] = receive_Data.red_led[0];
  object1["Restroom"] = receive_Data.yellow_led[0];
  object1["Hungry"] = receive_Data.green_led[0];
  object1["Game"] = receive_Data.blue_led[0];


  object2["Emergency"] = receive_Data.violet_led[1];
  object2["Bed"] = receive_Data.red_led[1];
  object2["Restroom"] = receive_Data.yellow_led[1];
  object2["Hungry"] = receive_Data.green_led[1];
  object2["Game"] = receive_Data.blue_led[1];
  
  serializeJson(doc1, jsonOutput1);
  serializeJson(doc2, jsonOutput2);
  
  Serial.println();
  Serial.println("<<<<< Receive Data:");
  Serial.print("ID: ");
  Serial.println(receive_Data.id[0]);
  Serial.print("Blue: ");
  Serial.println(receive_Data.blue_led[0]);
  Serial.print("Green: ");
  Serial.println(receive_Data.green_led[0]);
  Serial.print("Yellow: ");
  Serial.println(receive_Data.yellow_led[0]);
  Serial.print("Violet: ");
  Serial.println(receive_Data.violet_led[0]);
  Serial.print("Red: ");
  Serial.println(receive_Data.red_led[0]);
  Serial.println("<<<<<");

}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  WiFi.mode(WIFI_STA);
  Serial.print("Connecting to WiFi");

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

  esp_now_register_recv_cb(OnDataRecv);
  
}

void loop() {
  if (WiFi.status() == WL_CONNECTED){
    HTTPClient client1;
    HTTPClient client2;
    client1.begin("http://first-herokuapp.herokuapp.com/sensor/patient/2");
    client1.addHeader("Content-Type", "application/json");

    client2.begin("http://first-herokuapp.herokuapp.com/sensor/patient/3");
    client2.addHeader("Content-Type", "application/json");

    int httpCode1 = client1.PUT(jsonOutput1);
    int httpCode2 = client2.PUT(jsonOutput2);

    if (httpCode1 > 0){
      String payload = client1.getString();
      Serial.println("\nStatuscode: " + String(httpCode1));
      Serial.println(payload);

      client1.end();

    }else{
      Serial.println("Error on HTTP request");
    }
  }else{
    Serial.println("Connection lost");
  }
  delay(500);
}