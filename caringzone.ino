#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//LED-1
const int led1 = 13;
const int led2 = 12;
const int led3 = 14;
const int led4 = 27;

//BUZZER
const int buzzer = 26;

//LED-1
const int led5 = 25;
const int led6 = 33;
const int led7 = 32;
const int led8 = 15;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(led7, OUTPUT);
  pinMode(led8, OUTPUT);
  pinMode(buzzer, OUTPUT);
  
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  delay(2000);
  display.clearDisplay();
  display.setTextSize(2.5);
  display.setTextColor(WHITE);
  // display.println("Hello, World!");
  // display.display();
}

void loop() {

  digitalWrite(led1, HIGH);
  digitalWrite(buzzer, LOW);
  display.setCursor(10, 10);
  display.println("1: DANGER");
  display.setCursor(10, 40);
  display.println("2:");
  display.display();
  delay(500);
  digitalWrite(led1, LOW);
  digitalWrite(buzzer, HIGH);
  display.clearDisplay();
  display.display();
  delay(500);
  digitalWrite(led2, HIGH);
  digitalWrite(buzzer, LOW);
  display.setCursor(10, 10);
  display.println("1: TIOLET");
  display.setCursor(10, 40);
  display.println("2:");
  display.display();
  delay(500);
  digitalWrite(led2, LOW);
  digitalWrite(buzzer, HIGH);
  display.clearDisplay();
  display.display();
  delay(500);
  digitalWrite(led3, HIGH);
  digitalWrite(buzzer, LOW);
  display.setCursor(10, 10);
  display.println("1: HUNGRY");
  display.setCursor(10, 40);
  display.println("2:");
  display.display();
  delay(500);
  digitalWrite(led3, LOW);
  digitalWrite(buzzer, HIGH);
  display.clearDisplay();
  display.display();
  delay(500);
  digitalWrite(led4, HIGH);
  digitalWrite(buzzer, LOW);
  display.setCursor(10, 10);
  display.println("1: GAMING");
  display.setCursor(10, 40);
  display.println("2:");
  display.display();
  delay(500);
  digitalWrite(led4, LOW);
  digitalWrite(buzzer, HIGH);
  display.clearDisplay();
  display.display();
  delay(500);
  digitalWrite(led5, HIGH);
  digitalWrite(buzzer, LOW);
  display.setCursor(10, 10);
  display.println("1:");
  display.setCursor(10, 40);
  display.println("2: DANGER");
  display.display();
  delay(500);
  digitalWrite(led5, LOW);
  digitalWrite(buzzer, HIGH);
  display.clearDisplay();
  display.display();
  delay(500);
  digitalWrite(led6, HIGH);
  digitalWrite(buzzer, LOW);
  display.setCursor(10, 10);
  display.println("1:");
  display.setCursor(10, 40);
  display.println("2: TIOLET");
  display.display();
  delay(500);
  digitalWrite(led6, LOW);
  digitalWrite(buzzer, HIGH);
  display.clearDisplay();
  display.display();
  delay(500);
  digitalWrite(led7, HIGH);
  digitalWrite(buzzer, LOW);
  display.setCursor(10, 10);
  display.println("1:");
  display.setCursor(10, 40);
  display.println("2: HUNGRY");
  display.display();
  delay(500);
  digitalWrite(led7, LOW);
  digitalWrite(buzzer, HIGH);
  display.clearDisplay();
  display.display();
  delay(500);
  digitalWrite(led8, HIGH);
  digitalWrite(buzzer, LOW);
  display.setCursor(10, 10);
  display.println("1:");
  display.setCursor(10, 40);
  display.println("2: GAMING");
  display.display();
  delay(500);
  digitalWrite(led8, LOW);
  digitalWrite(buzzer, HIGH);
  display.clearDisplay();
  display.display();
  delay(500);
}
