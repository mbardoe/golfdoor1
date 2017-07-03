/*
 Golf Party in a box that when it senses a ball in the box
 the lid of the box comes down. 
 
 There parts for this project are:
 photoresistor
 3 yellow LED's
 1 red LED
 1 green LED
 2 mini Servo motors
 2 220 ohm resistor
 1 megaohm resistor
 1 push button
 10k ohm resistor
 
 The circuit has the photo resistor with the 1 mega ohm resistor
 The yellow lights are wired in parallel with no resistor.
 The red and green lights are wired to the arduino pins and a 220 ohm resistor to ground
 The push button has a 10k ohm resistor to ground and a listening pin on the arduino.
 
 The goal of this code is to set up the level of the light in the box. If your readings 
 are too high use a smaller resistor.
 
 Then once the baseline for the photoresistor readings is found the box goes into wait mode.
 
 When the button is pressed the inside lights turn on. There is a delay to make sure the 
 photoresistor comes up to full power. Then the green light comes on to show that it is ready.
 
 When the ball comes in, it sets off the door. The green light goes off, and we return to wait
 mode. When the button is pressed the user has 5 seconds to retrieve the ball and reset. Then
 the green light comes on, and we are ready again.
 
 Matthew K. Bardoe 7/2/17
 
 
 This example code is part of the public domain 
 */

// include the servo library
#include <Servo.h>
int sensorValue; // where we register the photoresistor
Servo myServoRight;  // create a servo object 
Servo myServoLeft;  // another servo for the door
const int redLED = 3; // red not ready light
const int greenLED = 4; // green ready light
const int button = 2; //button for the indicator that we are ready to go.
const int boxLED = 5; // LED's that light up the box.
int buttonState = 0;  // initial button state
int boxReady = 0;  // is the box ready? 0=no; 1 = yes.
int sensorLow = 1023; // callibrate the sensor. Start it off as high as possible.

void setup() {
  //Serial.begin(9600);
  //Set pinModes.
  pinMode(button, INPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(boxLED, OUTPUT);
  //turn on light in the box to warm up photoresistor
  digitalWrite(boxLED, HIGH);
  //initialize servos
  myServoRight.attach(9); // attaches the servo on pin 9 to the servo object 
  myServoLeft.attach(10);
  myServoRight.write(60);
  myServoLeft.write(60);
  // wait for photoresistor to warm up
  delay(100);

  // calibrate for the first five seconds after program runs
  while (millis() < 5000) {

    sensorValue = analogRead(A0);
    //    Serial.print(sensorLow);
    //    Serial.print(" ");
    //    Serial.println(sensorValue);
    //    
    // record the minimum sensor value
    if (sensorValue < sensorLow) {
      sensorLow = sensorValue;
    }
    // don't need a lot of readings
    delay(100);
  }
  // set lights indicate we are in waiting mode
  digitalWrite(redLED, HIGH);
  digitalWrite(boxLED,LOW);
  digitalWrite(greenLED,LOW);


}

void loop() {

  if (boxReady == 0){
    // box isn't ready right now
    //Serial.println("box not ready");
    // listen for button
    buttonState = digitalRead(button);
    if (buttonState == 1){
      // box is ready
      boxReady = 1;
      //change lights
      digitalWrite(boxLED,HIGH);
      digitalWrite(redLED,LOW);
      delay(500);

      // open door
      myServoRight.write(60);
      myServoLeft.write(60);
      // wait for photo resistor to warm up and player to retrieve ball
      delay(5000);
      // indicate we are ready
      digitalWrite(greenLED,HIGH);
    }
  }
  else
  {
    // test value of photoresistor
    sensorValue = analogRead(A0);
    //    Serial.print("Sensor value: ");
    //    Serial.print(sensorLow);
    //    Serial.println(sensorValue);
    // if photoresistor has dropped close door
    if (sensorValue < sensorLow-8){
      //close door
      myServoRight.write(130);
      myServoLeft.write(130);
      // box is no longer ready
      boxReady = 0;
      // reset lights
      digitalWrite(greenLED,LOW);
      digitalWrite(redLED,HIGH);
      digitalWrite(boxLED,LOW);
      // give a time for lights to light
      delay(100);
    }

    // slow down a little
    delay(20);
  }
}



