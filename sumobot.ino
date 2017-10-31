#include <Ultrasonic.h>
#include <Filter.h>

// Arduino Pro Micro - ATMega 32u4
#define ECHO 14
#define TRIG 15
#define BTN 6
#define rightWheelPin 3
#define leftWheelPin 5
#define leftEdgeSensor A3
#define rightEdgeSensor A4
#define EYES 12
#define BEEPER 10

bool button_pressed = false; //init button state
int attack_threshold = 30; //distance in centimeters
float edge_threshold = 3.0; // Edge detection voltage. Lower is white line detection.

Ultrasonic ultrasonic(ECHO, TRIG);
Moving_average ma(50,0); //sample rolling average of last 50 readings

// ------- PROGRAM SETUP -------- //
void setup() {
  Serial.begin(9600);

  // Pin Setup
  pinMode(BTN, INPUT_PULLUP);
  pinMode(leftEdgeSensor, INPUT);
  pinMode(rightEdgeSensor, INPUT);
  pinMode(EYES, OUTPUT);
  pinMode(BEEPER, OUTPUT);

  // Don't start anything until button is pressed
  while (button_pressed == false){
    int btn_state = digitalRead(BTN);
    if(btn_state == LOW){
      button_pressed = true;
    }
  }
  // Wait the regulated 3 seconds
  digitalWrite(BEEPER, "HIGH");
  delay(3000);
  digitalWrite(BEEPER, "LOW");
}

// ------- MAIN LOOP ------- //
void loop() {
  if( inRange() ){
    Serial.println("FULL FORWARD!");
    delay(15);
  } else {
    Serial.println("SPIN AROUND");
    delay(15);
  }

  digitalWrite(EYES, "HIGH");
  delay(500);
  digitalWrite(EYES, "LOW");
  delay(500);
}

/**
 * Object Detection
 */
bool inRange() {
  int distance_read = ultrasonic.distanceRead();
  int distance = ma.filter(distance_read);

  Serial.print(distance_read);
  Serial.print(" : ");
  Serial.print(distance);
  Serial.print(" : ");

  if( distance <= attack_threshold && distance != 0 ){
    return true;
  } else {
    return false;
  }
}

/**
 * Edge Detection
 */
bool detectEdge(pin) {
  // convert analog signal to voltage.
  int proximityADC = analogRead(pin);
  float proximityV = (float)proximityADC * 5.0 / 1023.0;
  
  if( proximityV <= edge_threshold){
    return true;
  } else {
    return false;
  }
}

/**
 * Move Robot Forward
 */
void forward(){

}

/**
 * Move Robot Left by degrees
 */
void left(deg){

}

/**
 * Move Robot Right by degrees
 */
void right(deg){

}

/**
 * Turn Around
 */
void turnAround(){

}