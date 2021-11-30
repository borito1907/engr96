#include <SoftwareSerial.h>
#include <Wire.h>
#include <Servo.h>
#include <MPU6050.h>

//Motor Pins
const int motor1Power = A0;
const int motor2Power = A1;

// Motors
const int D1 = 10;
const int D2 = 11;
const int D3 = 12;
const int D4 = 13;

// Ultrasonic Sensor Variables

const int FLTrig = 32;
const int FLEcho = 33;
long FLDistance();

const int FRTrig = 36;
const int FREcho = 37;
long FRDistance();

const int ObjTrig = 34;
const int ObjEcho = 35;
long ObjDistance();

const int BTrig = 26;
const int BEcho = 27;
long BDistance();

const int RTrig = 24;
const int REcho = 25;
long RDistance();

const int LTrig = 22;
const int LEcho = 23;
long LDistance();

long BetterDistance(char sensor);

//Servo Pin

const int ServoPin = 8;
Servo mechServo; // Servo object declaration
int pos = 0; //position variable for Servo

// Reading input

char input;
char lastInput = ' ';


//Active Functions

void avoidRight();
void avoidLeft();
void forward();
void backward();
void left();
void right();

const float AVOIDANCE_DISTANCE = 20;
const float WALL_AVOID_DIST = 10;
const float AVOIDANCE_ANGLE = 30;
const float AVOIDANCE_DELAY = 750;
const float TURN_PRECISION = 1;
const float OUT_IN_THE_OPEN = 150;
void turnQuantity(float deltaYaw);

//State Setup
int state = 4;
void state1();
void state2();
void state3();
void state4();
void state5();

// Handle Bad Sensor Input



void setup() {
  Serial.begin(9600);
  
  // Define inputs and outputs
  pinMode(motor1Power, OUTPUT);
  pinMode(motor2Power, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);

  pinMode(FLTrig, OUTPUT);
  pinMode(FLEcho, INPUT);
  pinMode(FRTrig, OUTPUT);
  pinMode(FREcho, INPUT);
  pinMode(ObjTrig, OUTPUT);
  pinMode(ObjEcho, INPUT);
  pinMode(BTrig, OUTPUT);
  pinMode(BEcho, INPUT);
  pinMode(RTrig, OUTPUT);
  pinMode(REcho, INPUT);
  pinMode(LTrig, OUTPUT);
  pinMode(LEcho, INPUT);

  mechServo.attach(ServoPin); //Servo on pin 8
  mechOpen();
  // mechClose();
  
}

void loop() {
    // Serial.println(ObjDistance());
   
    mechClose();
    
    /*
    switch (state) {
    case 1: state1();  break;
    case 2: state2();  break;
    case 3: state3();  break;
    case 4: state4(); break;
    default: break;
    }
    */
    
}

/*
void state1() { // Navigate the straightaway
  // So the sensors rest
  delay(100);
  long FL = FLDistance();
  long FR = FRDistance();
  long R = RDistance();
  long L = LDistance();
  
  forward();
  // If both sensors sense an obstacle nearby
  if (FL < AVOIDANCE_DISTANCE && FR < AVOIDANCE_DISTANCE) {
    // If the left wall is further away than the right one
    if (L > R) {
      avoidLeft();
      // If the right wall is further away than the left one
    } else {
      avoidRight();
    }
    return;
  }
  // Obstacle on the left
  if (FL < AVOIDANCE_DISTANCE) {
    if (R < 20){
      backward();
      delay(300);
      avoidLeft();
    }
    else {
      avoidRight();
    }
    return;
  }
  // Obstacle on the right
  if (FR < AVOIDANCE_DISTANCE) {
    if (L < 20){
      backward();
      delay(300);
      avoidRight();
    }
    else {
      avoidLeft();
    }
    return;
  }
  if ((L + R > OUT_IN_THE_OPEN) && (FL > 50) && (FR > 50) && (millis() > 20000)){
    state++;
  }
  
  return;
}
*/

void state1(){
  delay(100);
  long FL = FLDistance();
  long FR = FRDistance();
  long R = RDistance();
  long L = LDistance();

  forward();
  if (FR < AVOIDANCE_DISTANCE){
    avoidLeft();
  }
  if (FL < AVOIDANCE_DISTANCE){
    avoidRight();
  }
  if ((L + R > 200) && (millis() > 22000)){
    state++;
  }
}

void state2() { // Angle Calibration
  turnQuantity(90);
  while ((FLDistance() - FRDistance()) > 3){
    right();
  }
  while ((FRDistance() - FLDistance()) > 3){
    left();
  }
  turnQuantity(-10);
  state++;
}

void state3(){ // Center Calibration
  while ((BDistance() - ((FLDistance() + FRDistance()) / 2)) > 1){
    backward();
  }
  while ((((FLDistance() + FRDistance()) / 2) - BDistance()) > 1){
    forward();
  }
  stop();
  state++;
}
/*
void state4(){ // Find the object
  delay(100);
  if (ObjDistance() > ((FLDistance() + FRDistance) / 2)){
    left();
  }
  
  if (ObjDistance() > 6 && FLDistance() > 6 && FRDistance() > 6){
    forward();
  }
  else {
    stop();
    mechClose();
    delay(200);
  }
}
*/
/*
void state5()
{

}
*/
void avoidLeft(){
  turnQuantity(-AVOIDANCE_ANGLE);
  forward();
  delay(AVOIDANCE_DELAY);
  stop();
  turnQuantity(AVOIDANCE_ANGLE);
}

void avoidRight(){
  turnQuantity(AVOIDANCE_ANGLE);
  forward();
  delay(AVOIDANCE_DELAY);
  stop();
  turnQuantity(-AVOIDANCE_ANGLE);
}

void turnQuantity(float deltaYaw) {
  if (deltaYaw > 0){
    right();
    delay(17 * abs(deltaYaw));
  }
  if (deltaYaw < 0){
    left();
    delay(17 * abs(deltaYaw));
  }
  stop();
  delay(500);
}

// Moves the motors in the forward direction
void forward() {
  Serial.println("Moving Forward");
  
  analogWrite(motor1Power, 255);
  analogWrite(motor2Power, 255);

  digitalWrite(D1, LOW);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, LOW);
  digitalWrite(D4, HIGH);
}

// Moves the motors in backward direction
void backward() {
  Serial.println("Moving Backward");
    
  analogWrite(motor1Power, 255);
  analogWrite(motor2Power, 255);

  digitalWrite(D1, HIGH);
  digitalWrite(D2, LOW);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, LOW);
}

void left() {
  analogWrite(motor1Power, 155);
  analogWrite(motor2Power, 155);

  digitalWrite(D1, LOW);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, LOW);
}

void right() {
  analogWrite(motor1Power, 155);
  analogWrite(motor2Power, 155);

  digitalWrite(D1, HIGH);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, HIGH);
}

void stop() {
  analogWrite(motor1Power, 0);
  analogWrite(motor2Power, 0);

  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
}

// Servo functions

void mechOpen() 
{           
  pos = 0;
  mechServo.write(pos);
}

void mechClose() 
{
  pos = 120;
  mechServo.write(pos);
}

// Ultrasonic sensor functions

long FLDistance()
{
  long duration;
  long cm;

  //Send a Pulse
  digitalWrite(FLTrig, LOW);
  delayMicroseconds(5);
  digitalWrite(FLTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(FLTrig, LOW);

  //Get Pulse
  duration = pulseIn(FLEcho, HIGH);

  // Convert the time into a distance
  cm = (duration / (2 * 29.1));
  return cm;
}

long FRDistance() 
{
  long duration;
  long cm;

  //Send a Pulse
  digitalWrite(FRTrig, LOW);
  delayMicroseconds(5);
  digitalWrite(FRTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(FRTrig, LOW);

  //Get Pulse
  duration = pulseIn(FREcho, HIGH);

  // Convert the time into a distance
  cm = (duration / (2 * 29.1));
  return cm;
}

long ObjDistance() {
  long duration;
  long cm;

  //Send a Pulse
  digitalWrite(ObjTrig, LOW);
  delayMicroseconds(5);
  digitalWrite(ObjTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(ObjTrig, LOW);

  //Get Pulse
  duration = pulseIn(ObjEcho, HIGH);

  // Convert the time into a distance
  cm = (duration / (2 * 29.1));
  return cm;
}

long BDistance() {
  long duration;
  long cm;

  //Send a Pulse
  digitalWrite(BTrig, LOW);
  delayMicroseconds(5);
  digitalWrite(BTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(BTrig, LOW);

  //Get Pulse
  duration = pulseIn(BEcho, HIGH);

  // Convert the time into a distance
  cm = (duration / (2 * 29.1));
  return cm;
}

long LDistance() {
  long duration;
  long cm;

  //Send a Pulse
  digitalWrite(LTrig, LOW);
  delayMicroseconds(5);
  digitalWrite(LTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(LTrig, LOW);

  //Get Pulse
  duration = pulseIn(LEcho, HIGH);

  // Convert the time into a distance
  cm = (duration / (2 * 29.1));
  return cm;
}

long RDistance() {
  long duration;
  long cm;

  //Send a Pulse
  digitalWrite(RTrig, LOW);
  delayMicroseconds(5);
  digitalWrite(RTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(RTrig, LOW);

  //Get Pulse
  duration = pulseIn(REcho, HIGH);

  // Convert the time into a distance
  cm = (duration / (2 * 29.1));
  return cm;
}
/*
long BetterDistance(int sensor){
  long dist[10];
  
  for (int i = 0; i < 10;i++){
    switch (sensor){
    case 1:
    dist[i] = FLDistance();
    return findMedian(dist,10);
    case 2:
    dist[i] = FRDistance();
    return findMedian(dist,10);
    default:
    break;
    }
  }
}

long findMedian(long arr[], int len){
  sort(arr, arr + len);
  return arr[len/2];
}
*/
