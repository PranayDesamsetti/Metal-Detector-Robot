
const byte npulse = 12; // number of pulses to charge the capacitor before each measurement
 
const byte pin_pulse = A1; // sends pulses to charge the capacitor (can be a digital pin)
const byte pin_cap  = A2; // measures the capacitor charge
const byte pin_LED = 6; // LED that turns on when metal is detected

#include <AFMotor.h>
#include <Servo.h>

#define trig_Pin 6
#define echo_Pin 5
#define MAX_SPEED 150 // sets speed of DC  motors
#define MAX_SPEED_OFFSET 20


AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);
Servo myservo;

boolean goesForward = false;
int distance = 100;
int speedSet = 0;
int Time = 0;

void setup() {
  pinMode(pin_pulse, OUTPUT);
  digitalWrite(pin_pulse, LOW);
  pinMode(pin_cap, INPUT);
  pinMode(pin_LED, OUTPUT);
  digitalWrite(pin_LED, LOW);
  Serial.begin(9600);
  myservo.attach(9);
  myservo.write(95);
  pinMode(trig_Pin, OUTPUT);
  pinMode(echo_Pin, INPUT);
  delay(2000);
}
 
const int nmeas = 256; //measurements to take
long int sumsum = 0; //running sum of 64 sums
long int skip = 0; //number of skipped sums
long int diff = 0;      //difference between sum and avgsum
long int flash_period = 0; //period (in ms)
long unsigned int prev_flash = 0; //time stamp of previous flash
 
void loop() {
 
  int minval = 2000;
  int maxval = 0;
 
  //perform measurement
  long unsigned int sum = 0;
  for (int imeas = 0; imeas < nmeas + 2; imeas++) {
    //reset the capacitor
    pinMode(pin_cap, OUTPUT);
    digitalWrite(pin_cap, LOW);
    delayMicroseconds(20);
    pinMode(pin_cap, INPUT);
    //apply pulses
    for (int ipulse = 0; ipulse < npulse; ipulse++) {
      digitalWrite(pin_pulse, HIGH); //takes 3.5 microseconds
      delayMicroseconds(3);
      digitalWrite(pin_pulse, LOW); //takes 3.5 microseconds
      delayMicroseconds(3);
    }
    //read the charge on the capacitor
    int val = analogRead(pin_cap); //takes 13x8=104 microseconds
    minval = min(val, minval);
    maxval = max(val, maxval);
    sum += val;
 
    //determine if LEDs should be on or off
    long unsigned int timestamp = millis();
    byte ledstat = 0;
    if (timestamp < prev_flash +12) {
      if (diff > 0)ledstat = 1;
      if (diff < 0)ledstat = 2;
    }
    if (timestamp > prev_flash + flash_period) {
      if (diff > 0)ledstat = 1;
      if (diff < 0)ledstat = 2;
      prev_flash = timestamp;
    }
    if (flash_period > 1000)ledstat = 0;
 
    //switch the LEDs to this setting
    if (ledstat == 0) {
      digitalWrite(pin_LED, LOW);
    }
    if (ledstat == 1) {
      digitalWrite(pin_LED, LOW);
    }
    if (ledstat == 2) {
      digitalWrite(pin_LED, HIGH);
    }
 
  }
 
  //subtract minimum and maximum value to remove spikes
  sum -= minval; sum -= maxval;
 
  //process
  if (sumsum == 0) sumsum = sum << 6; //set sumsum to expected value
  long int avgsum = (sumsum + 32) >> 6;
  diff = sum - avgsum;
  if (abs(diff)<avgsum >> 10) {   //adjust for small changes
    sumsum = sumsum + sum - avgsum;
    skip = 0;
  } else {
    skip++;
  }
  if (skip > 64) {  // break off in case of prolonged skipping
    sumsum = sum << 6;
    skip = 0;
  }
 
  // one permille change = 2 ticks/s
  if (diff == 0) flash_period = 1000000;
  else flash_period = avgsum / (2 * abs(diff));


  //

  myservo.write(95);

   
  distance = obstacle();
  Serial.println(distance);
  int distanceR = 0;
  int distanceL =  0;
  delay(40);

  if (distance <= 15)
  { 
    moveStop();
    delay(100);
    moveBackward();
    delay(300);
    moveStop();
    delay(200);
    distanceR = lookRight();
    delay(200);
    distanceL = lookLeft();
    delay(200);

    if (distanceR > distanceL)
    {
      turnRight();
      moveStop();
    }else if (distanceR < distanceL)
    {
      turnLeft();
      moveStop();
    }
  }
  else
  {
    goesForward = true;
    moveForward();
  }

}

int obstacle()
{
  digitalWrite(trig_Pin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trig_Pin, LOW);
  Time = pulseIn(echo_Pin, HIGH);
  distance = (Time / 29.1) / 2;
  if (distance < 0)
    distance = 0;
  if (distance > 200)
    distance = 200;
  return distance;
}

int lookRight()
{
  myservo.write(0);
  delay(500);
  distance = obstacle();
  delay(200);
  myservo.write(95);
  return distance;
}

int lookLeft()
{
  myservo.write(185);
  delay(500);
  distance = obstacle();
  delay(200);
  myservo.write(95);
  return distance;
}

void moveStop() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  Serial.println(" Stop ");
}

void moveForward() {

  if (goesForward)
  {
    goesForward = true;
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
    Serial.println(" Forward ");
    for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 5) // slowly bring the speed up to avoid loading down the batteries too quickly
    {
      motor1.setSpeed(speedSet);
      motor2.setSpeed(speedSet);
      motor3.setSpeed(speedSet);
      motor4.setSpeed(speedSet);
      delay(5);
    }
  }
}

void moveBackward() {
  goesForward = false;
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  Serial.println(" Backward ");
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 5) // slowly bring the speed up to avoid loading down the batteries too quickly
  {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    motor3.setSpeed(speedSet);
    motor4.setSpeed(speedSet);
    delay(5);
  }
}

void turnRight() {
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  delay(2000);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  Serial.println(" Turn Right ");
}

void turnLeft() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  delay(2000);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  Serial.println(" Turn Left ");
}
