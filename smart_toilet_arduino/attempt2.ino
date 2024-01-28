#include <Servo.h>

#define TRIG_PIN 10
#define ECHO_PIN 11
#define SERVO_PIN 9
#define GAS_SENSOR_PIN A0  
#define GREEN_LED_PIN 13
#define RED_LED_PIN 12
#define GAS_LED_PIN 8  

#define RELAY_PIN 7
#define BUTTON_PIN 2

Servo doorServo;
long duration, distance;
int gasValue;
bool doorOpen = false;


const int GAS_THRESHOLD = 300;

void setup() {
  doorServo.attach(SERVO_PIN);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(GAS_SENSOR_PIN, INPUT);  
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GAS_LED_PIN, OUTPUT);  
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP); 

  digitalWrite(GREEN_LED_PIN, HIGH);
  digitalWrite(RED_LED_PIN, HIGH);
  digitalWrite(GAS_LED_PIN, HIGH);  

  Serial.begin(9600);
}

void loop() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration * 0.034) / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  
  if (digitalRead(GREEN_LED_PIN) == HIGH && !doorOpen && distance < 4) {
    
    doorServo.write(180);
    doorOpen = true;

    
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, HIGH);

    
    delay(5000);

    
    doorServo.write(0);
    doorOpen = false;
  } else if (!doorOpen && distance < 4) {
    
    digitalWrite(RED_LED_PIN, LOW);
  }

  
  gasValue = analogRead(GAS_SENSOR_PIN);

  Serial.print("Gas Value: ");
  Serial.println(gasValue);

  
  if (gasValue > GAS_THRESHOLD) {
    
    digitalWrite(GAS_LED_PIN, LOW);
  } else {
    
    digitalWrite(GAS_LED_PIN, HIGH);
  }

  
  if (digitalRead(BUTTON_PIN) == LOW) {
    
    digitalWrite(RELAY_PIN, HIGH);


    delay(5000);
    doorServo.write(180);
    doorOpen = true;

    
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(RED_LED_PIN, HIGH);

    
    delay(5000);

    
    doorServo.write(0);
    doorOpen = false;

    
    digitalWrite(RELAY_PIN, LOW);
  }

  delay(100); 
}
