#include "pitches.h"
#include <DebouncedSwitch.h>

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

int notes[] = {
  NOTE_C3, NOTE_D3, NOTE_E3, NOTE_F3, NOTE_G3, NOTE_A3, NOTE_B3, NOTE_C4
};

DebouncedSwitch b1(but1);
DebouncedSwitch b2(but2);
DebouncedSwitch b3(but3);
DebouncedSwitch b4(but4);
DebouncedSwitch b5(but5);
DebouncedSwitch b6(but6);
DebouncedSwitch b7(but7);
DebouncedSwitch b8(but8);
DebouncedSwitch s1(song1);

void setup()
{
  pinMode(song1, INPUT);
  pinMode(song2, INPUT);
  pinMode(song3, INPUT);
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
  Serial.begin(9600);
}

void loop()
{
  // ledcWriteTone(TONE_PWM_CHANNEL, NOTE_C5);
  // digitalWrite(led1, HIGH);
  // delay(500);
  // ledcWriteTone(TONE_PWM_CHANNEL, 0);
  // digitalWrite(led1, LOW);
  // delay(500);

  // ledcWriteTone(TONE_PWM_CHANNEL, NOTE_C5);
  // digitalWrite(led2, HIGH);
  // delay(500);
  // ledcWriteTone(TONE_PWM_CHANNEL, 0);
  // digitalWrite(led2, LOW);
  // delay(500);
  
  // ledcWriteTone(TONE_PWM_CHANNEL, NOTE_G5);
  // digitalWrite(led3, HIGH);
  // delay(500);
  // ledcWriteTone(TONE_PWM_CHANNEL, 0);
  // digitalWrite(led3, LOW);
  // delay(500);

  // ledcWriteTone(TONE_PWM_CHANNEL, NOTE_G5);
  // digitalWrite(led4, HIGH);
  // delay(500);
  // ledcWriteTone(TONE_PWM_CHANNEL, 0);
  // digitalWrite(led4, LOW);
  // delay(500);

  // ledcWriteTone(TONE_PWM_CHANNEL, NOTE_A5);
  // digitalWrite(led5, HIGH);
  // delay(500);
  // ledcWriteTone(TONE_PWM_CHANNEL, 0);
  // digitalWrite(led5, LOW);
  // delay(500);

  // ledcWriteTone(TONE_PWM_CHANNEL, NOTE_A5);
  // digitalWrite(led6, HIGH);
  // delay(500);
  // ledcWriteTone(TONE_PWM_CHANNEL, 0);
  // digitalWrite(led6, LOW);
  // delay(500);

  // ledcWriteTone(TONE_PWM_CHANNEL, NOTE_G5);
  // digitalWrite(led7, HIGH);
  // delay(500);
  // ledcWriteTone(TONE_PWM_CHANNEL, 0);
  // digitalWrite(led7, LOW);
  // delay(1000);

  // ledcWriteTone(TONE_PWM_CHANNEL, NOTE_F5);
  // digitalWrite(led8, HIGH);
  // delay(500);
  // ledcWriteTone(TONE_PWM_CHANNEL, 0);
  // digitalWrite(led8, LOW);
  // delay(500);

  // ledcWriteTone(TONE_PWM_CHANNEL, NOTE_F5);
  // digitalWrite(led3, HIGH);
  // delay(500);
  // ledcWriteTone(TONE_PWM_CHANNEL, 0);
  // digitalWrite(led3, LOW);
  // delay(500);

  // ledcWriteTone(TONE_PWM_CHANNEL, NOTE_E5);
  // digitalWrite(led4, HIGH);
  // delay(500);
  // ledcWriteTone(TONE_PWM_CHANNEL, 0);
  // digitalWrite(led4, LOW);
  // delay(500);

  // ledcWriteTone(TONE_PWM_CHANNEL, NOTE_E5);
  // digitalWrite(led5, HIGH);
  // delay(500);
  // ledcWriteTone(TONE_PWM_CHANNEL, 0);
  // digitalWrite(led5, LOW);
  // delay(500);

  // ledcWriteTone(TONE_PWM_CHANNEL, NOTE_D5);
  // digitalWrite(led6, HIGH);
  // delay(500);
  // ledcWriteTone(TONE_PWM_CHANNEL, 0);
  // digitalWrite(led6, LOW);
  // delay(500);

  // ledcWriteTone(TONE_PWM_CHANNEL, NOTE_D5);
  // digitalWrite(led7, HIGH);
  // delay(500);
  // ledcWriteTone(TONE_PWM_CHANNEL, 0);
  // digitalWrite(led7, LOW);
  // delay(500);

  // ledcWriteTone(TONE_PWM_CHANNEL, NOTE_C5);
  // digitalWrite(led8, HIGH);
  // delay(500);
  // ledcWriteTone(TONE_PWM_CHANNEL, 0);
  // digitalWrite(led8, LOW);
  // delay(500);
  
  b1.update();
  b2.update();
  b3.update();
  b4.update();
  b5.update();
  b6.update();
  b7.update();
  b8.update();
  s1.update();

  // if (s1.isDown()){
  // digitalWrite(led1, HIGH);
  // delay(1000);
  // digitalWrite(led2, HIGH);
  // delay(1000);
  // digitalWrite(led3, HIGH);
  // delay(1000);
  // digitalWrite(led4, HIGH);
  // delay(1000);
  // digitalWrite(led5, HIGH);
  // delay(1000);
  // digitalWrite(led6, HIGH);
  // delay(1000);
  // digitalWrite(led7, HIGH);
  // delay(1000);
  // digitalWrite(led8, HIGH);
  // delay(1000);
  // digitalWrite(led1, LOW);
  // delay(1000);
  // digitalWrite(led2, LOW);
  // delay(1000);
  // digitalWrite(led3, LOW);
  // delay(1000);
  // digitalWrite(led4, LOW);
  // delay(1000);
  // digitalWrite(led5, LOW);
  // delay(1000);
  // digitalWrite(led6, LOW);
  // delay(1000);
  // digitalWrite(led7, LOW);
  // delay(1000);
  // digitalWrite(led8, LOW);
  // delay(1000);

  // }
  
  if (b1.isDown()){
    ledcWriteNote(TONE_PWM_CHANNEL, NOTE_C, 5);
    digitalWrite(led1, HIGH);
    // ledcWriteTone(TONE_PWM_CHANNEL, NOTE_C5);
    delay(50);
  }
  else {
    ledcWriteTone(TONE_PWM_CHANNEL, 0);
    digitalWrite(led1, LOW);
  }
  
  if (b2.isDown()){
    ledcWriteNote(TONE_PWM_CHANNEL, NOTE_D, 5);
    digitalWrite(led2, HIGH);
    // ledcWriteTone(TONE_PWM_CHANNEL, NOTE_C5);
    delay(50);
  }
  else {
    ledcWriteTone(TONE_PWM_CHANNEL, 0);
    digitalWrite(led2, LOW);
  }  

  if (b3.isDown()){
    digitalWrite(led3, HIGH);
    ledcWriteNote(TONE_PWM_CHANNEL, NOTE_E, 5);
    delay(50);
  }
  else {
    digitalWrite(led3, LOW);
    ledcWriteTone(TONE_PWM_CHANNEL, 0);
  }

  if (b4.isDown()){
    digitalWrite(led4, HIGH);
    // ledcWriteTone(TONE_PWM_CHANNEL, NOTE_C5);
    ledcWriteNote(TONE_PWM_CHANNEL, NOTE_F, 5);
    delay(50);
  }
  else {
    digitalWrite(led4, LOW);
    ledcWriteTone(TONE_PWM_CHANNEL, 0);
  }

  if (b5.isDown()){
    digitalWrite(led5, HIGH);
    // ledcWriteTone(TONE_PWM_CHANNEL, NOTE_G5);
    ledcWriteNote(TONE_PWM_CHANNEL, NOTE_G, 5);
    delay(50);
  }
  else {
    digitalWrite(led5, LOW);
    ledcWriteTone(TONE_PWM_CHANNEL, 0);
  }

  if (b6.isDown()){
    digitalWrite(led6, HIGH);
    // ledcWriteTone(TONE_PWM_CHANNEL, NOTE_A5);
    ledcWriteNote(TONE_PWM_CHANNEL, NOTE_A, 5);
    delay(50);
  }
  else {
    digitalWrite(led6, LOW);
    ledcWriteTone(TONE_PWM_CHANNEL, 0);
  }

  if (b7.isDown()){
    digitalWrite(led7, HIGH);
    // ledcWriteTone(TONE_PWM_CHANNEL, NOTE_C5);
    ledcWriteNote(TONE_PWM_CHANNEL, NOTE_B, 5);
    delay(50);
  }
  else {
    digitalWrite(led7, LOW);
    ledcWriteTone(TONE_PWM_CHANNEL, 0);
  }

  if (b8.isDown()){
    digitalWrite(led8, HIGH);
    // ledcWriteTone(TONE_PWM_CHANNEL, NOTE_C5);
    ledcWriteNote(TONE_PWM_CHANNEL, NOTE_C, 6);
    delay(50);
  }
  else {
    digitalWrite(led8, LOW);
    ledcWriteTone(TONE_PWM_CHANNEL, 0);
  }
}