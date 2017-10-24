#include <Ultrasonic.h>
#include <Filter.h>

// Arduino Pro Micro - ATMega 32u4
#define ECHO 14
#define TRIG 15
#define BTN 6
#define rightWheelPin 3
#define leftWheelPin 5

bool button_pressed = false; //init button state
int attack_threshold = 30; //distance in centimeters

Ultrasonic ultrasonic(ECHO, TRIG);
Moving_average ma(50,0); //sample rolling average of last 50 readings

// ------- PROGRAM SETUP -------- //
void setup() {
  Serial.begin(9600);
  pinMode(BTN, INPUT_PULLUP);

  // Don't start anything until button is pressed
  while (button_pressed == false){
    int btn_state = digitalRead(BTN);
    if(btn_state == LOW){
      button_pressed = true;
    }
  }
  // Wait the regulated 3 seconds
  delay(3000);
}

// ------- MAIN LOOP ------- //
void loop() {
  if( inRange() ){
    fullForward();
    Serial.println("FULL FORWARD!");
    delay(15);
  } else {
    spinAround();
    Serial.println("SPIN AROUND");
    delay(15);
  }
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

void fullForward(){
  Serial.print("GOOOooOOOoOOOoOOOOOOOo!!");
  digitalWrite(rightWheelPin, HIGH);
  digitalWrite(leftWheelPin, HIGH);
}

void spinAround(){
  Serial.print("TUUUUUUUuuUUUUuUUURnnnnnNNNnnn!!");
  digitalWrite(rightWheelPin, HIGH);
}
