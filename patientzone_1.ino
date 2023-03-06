//FLEX-SENSOR
const int flex1 = A17;
const int flex2 = A19;

//LED
const int red_led = 23;
const int yellow_led = 22;
const int green_led = 21;

//ULTRASONIC
const int trigPin1 = 2;
const int echoPin1 = 15;
const int trigPin2 = 0;
const int echoPin2 = 4;
int duration1;
int duration2;

//BUZZER
const int buzzer = 14;

void setup() {
  Serial.begin(9600);
  //FLEX-SENSOR
  pinMode(flex1, INPUT);
  pinMode(flex2, INPUT);
  //LED
  pinMode(red_led, OUTPUT);
  pinMode(yellow_led, OUTPUT);
  pinMode(green_led, OUTPUT);
  digitalWrite(red_led, LOW);
  digitalWrite(yellow_led, LOW);
  digitalWrite(green_led, LOW);
  //ULTRASONIC
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  //BUZZER
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, HIGH);
}

void loop() {
  //FLEX SENSOR
  Serial.println("data1 =");
  Serial.println(analogRead(flex1));
  Serial.println("data2 =");
  Serial.println(analogRead(flex2));
  delay(1000);
  if ((analogRead(flex1) < 1100) && (analogRead(flex2) < 800)){
    digitalWrite(red_led, HIGH);
    delay(2000);
    digitalWrite(red_led, LOW);
  }else if ((analogRead(flex1) < 1100) && (analogRead(flex2) > 700)){
    digitalWrite(yellow_led, HIGH);
    delay(2000);
    digitalWrite(yellow_led, LOW);
  }else if ((analogRead(flex1) > 1100) && (analogRead(flex2) < 700)){
    digitalWrite(green_led, HIGH);
    delay(2000);
    digitalWrite(green_led, LOW);
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
  // Serial.println(duration1);

  if (((duration1 < 1000) and (duration1 > 200)) or ((duration2 < 1000) and (duration2 > 200))){
    digitalWrite(red_led, HIGH);
    digitalWrite(buzzer, LOW);
    delay(300);
    digitalWrite(red_led, LOW);
    digitalWrite(buzzer, HIGH);
    delay(300);
    digitalWrite(red_led, HIGH);
    digitalWrite(buzzer, LOW);
    delay(300);
    digitalWrite(red_led, LOW);
    digitalWrite(buzzer, HIGH);
    delay(300);
    digitalWrite(red_led, HIGH);
    digitalWrite(buzzer, LOW);
    delay(300);
    digitalWrite(red_led, LOW);
    digitalWrite(buzzer, HIGH);
    delay(300);
    digitalWrite(red_led, HIGH);
    digitalWrite(buzzer, LOW);
    delay(300);
    digitalWrite(red_led, LOW);
    digitalWrite(buzzer, HIGH);
    delay(300);
    digitalWrite(red_led, HIGH);
    digitalWrite(buzzer, LOW);
    delay(300);
    digitalWrite(red_led, LOW);
    digitalWrite(buzzer, HIGH);
    delay(300);
  }
}