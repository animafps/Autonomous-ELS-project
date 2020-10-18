#include <Servo.h>
#include <AFMotor.h>

Servo myservo;
int pos = 90; // Defaults the servo position to 90 degrees
AF_DCMotor motor1(4); // Left Motor
AF_DCMotor motor2(2); // Right Motor

int trigPin = 12;  // Define pins for Ultrasonic sensor             
int echoPin = 13; 
long duration;
int cm;
int Distanceleft;
int Distanceright;

void setup() 
{ 
  Serial.begin (9600); // This defines the inputs and outputs of the pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  motor1.setSpeed(255); //Normal speed 200
  motor2.setSpeed(255);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  delay(5000);
}

void loop() 
{
  myservo.write(50);
  delay(400);
  getDistance();
  logic();
  myservo.write(90);
  delay(400);
  getDistance();
  logic();
  myservo.write(130);
  delay(400);
  getDistance();
  logic();
  myservo.write(90);
  delay(400);
  getDistance();
  logic();
}

void getDistance() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW); // sends a pulse of sound
    duration = pulseIn(echoPin, HIGH); // difines the duration as the difference of input and output
    cm = (duration/2) / 29.1;  // does some math to calculated the distace from the speed of sound
};

void getDistanceLeft() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW); // sends a pulse of sound
    duration = pulseIn(echoPin, HIGH); // difines the duration as the difference of input and output
    Distanceleft = (duration/2) / 29.1;  // does some math to calculated the distace from the speed of sound
};

void getDistanceRight() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW); // sends a pulse of sound
    duration = pulseIn(echoPin, HIGH); // difines the duration as the difference of input and output
    Distanceright = (duration/2) / 29.1;  // does some math to calculated the distace from the speed of sound
};

void logic()
{
  if(cm < 35)
  {
    Serial.println("Wall");
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    delay(500);
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    myservo.write(10);
    delay(400);
    getDistanceRight();
    delay(400);
    myservo.write(170);
    delay(400);
    getDistanceLeft();
    delay(400);
    myservo.write(90);
    if(Distanceright > Distanceleft)
    {
      Serial.println("Wall left");
      motor1.run(FORWARD);
      motor2.run(BACKWARD);
      delay(300);
    }  
    if(Distanceleft > Distanceright)
    {
      Serial.println("Wall right");
      motor1.run(BACKWARD);
      motor2.run(FORWARD);
      delay(300);  
    }
    if((Distanceright < 5) && (Distanceleft < 5) | (Distanceleft = Distanceright))
    {
      Serial.println("Wall Close");
      motor1.run(FORWARD);
      motor2.run(BACKWARD);
      delay(140);  
    }
    else
    {
      motor1.run(FORWARD);
      motor2.run(FORWARD);
    }
    
  } 
}