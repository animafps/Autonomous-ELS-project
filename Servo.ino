#include <Servo.h>
int trigPin = 12;  // defines the pins and speeds to begin and make defult not reverse                
int echoPin = 13; 
long duration;
int cm;

int enablePin = 3;
int in1Pin = 7;
int in2Pin = 8;
int speed = 2000;
bool reverse = false;

int enablePin2 = ;
int in3Pin = 4;
int in4Pin = 2;
int speed2 = 2000;
bool reverse2 = false;

Servo myservo;
int pos = 0;


void setup() {
  Serial.begin (9600); // This defines the inputs and outputs of the pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  pinMode(in1Pin, OUTPUT); // defines outputs for the motor driver
  pinMode(in2Pin, OUTPUT);
  
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  setMotor1(speed2, reverse2); // starts the bot moving
  setMotor1(speed, reverse);
}

void loop() {
  for (pos = 30; pos <= 140; pos += 10) {  // moves the servo motor between 30-140 degrees in 10 degree intervals
    myservo.write(pos); 
    delay(80); // allows time for the servo to reach its destination
    getDistance(); // checks and gets the distace every 10 degrees
    isWall(); // checks for wall and moves acordingly every 10 degrees 
  }
  for (pos = 150; pos >= 40; pos -= 10) {  // does the same as above but for the range of 150 to 40 degrees
    myservo.write(pos);
    getDistance();
    isWall();
    delay(80); 
  }
}

void getDistance() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW); // sends a pulse of sound
    duration = pulseIn(echoPin, HIGH); // difines the duration as the difference of input and output
    cm = (duration/2) / 29.1;  // does some math to calculated the distace from the speed of sound
    Serial.print(cm); 
    Serial.print("cm    ");
    Serial.print(pos);
    Serial.println("Degree"); // prints the distace and the postion that is at every 10 degrees
};

void isWall() {
if (cm < 10)  // checks if there is a object that is less than 10cm away 
{
  if ((pos <= 70) && (pos >= 30))
  {
    Serial.println("wall left");
    speed = 2000;
    setMotor1(speed, reverse);
    speed2 = 400;
    setMotor2(speed2, reverse2);  // if its on the left side using tank controls it steers to the right
  }
  else
  if ((pos <= 150) && (pos >= 110))
  {
    Serial.println("wall right");
    speed = 400;
    setMotor1(speed, reverse);
    speed2 = 2000;
    setMotro2(speed2, reverse2); // if its on the right side using tank controls it steers to the left
  }
  else
  if ((pos <= 80) && (pos <= 100))
  {
    Serial.println("wall infront");
    speed = 0;
    setMotor1(speed, reverse);
    speed2 = 0;
    setMotor2(speed2, reverse2); // if wall infront it stops moving (need to make it move backwards and move out of the way)
  }
}
  else
  speed = 2000;
  setMotor1(speed, reverse);
  speed2 = 2000;
  setMotor2(speed2, reverse2); // if no wall it keeps going forward
}

void setMotor1(int speed, boolean reverse)  // defines the function on how to control the motor speed and direction
{
  analogWrite(enablePin, speed);
  digitalWrite(in1Pin, ! reverse);
  digitalWrite(in2Pin, reverse);
}
void setMotor2(int speed2, boolean reverse2)
{
  analogWrite(enablePin2, speed2);
  digitalWrite(in3Pin, ! reverse2);
  digitalWrite(in4Pin, reverse2);
}
  
