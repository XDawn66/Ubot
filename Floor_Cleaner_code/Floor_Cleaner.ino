#include <Servo.h>
//#include "IR.h"
#include "IRremote.h"

const int trigPin1 = 6;
const int echoPin1 = 5;
const int trigPin2 = 12;
const int echoPin2 = 11;
const int trigPin3 = 10;
const int echoPin3 = 9;
int irpin =4;

int distanceleft;
int distancefront;
int distanceright;
int currentstate = 0;
int on = 0;
int auto_mode = 1; //auto by defalut

IRrecv IR(13); //create the instance of 'IR'


void setup() {
  pinMode(trigPin1, OUTPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(trigPin3, OUTPUT);// Sets the trigPin as an Output
  pinMode(echoPin1, INPUT); // Sets the echoPin as an Input
  pinMode(echoPin2, INPUT);
  pinMode(echoPin3, INPUT);
  pinMode(irpin, INPUT);
  Serial.begin(9600);
  IR.enableIRIn();
  
}

void loop() {
  int duration1,duration2,duration3;
   digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distanceleft = duration1 * 0.034 / 2;
  Serial.print("Distance1: ");
  Serial.println(distanceleft);
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distancefront = duration2 * 0.034 / 2;
  Serial.print("Distance2: ");
  Serial.println(distancefront);
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  duration3 = pulseIn(echoPin3, HIGH);
  distanceright = duration3 * 0.034 / 2;
  Serial.print("Distance3: ");
  Serial.println(distanceright);
  int s = digitalRead(irpin);
  Serial.println(s);
  if(IR.decodedIRData.decodedRawData == 0xFFA25D)
  {
     on = 0;
  }
   if(IR.decodedIRData.decodedRawData == 0xFF02FD) //if the pause button is pressed
  {
     on = 1;
  }
  if(IR.decodedIRData.decodedRawData == 0xFF02FD) //if the pause button is pressed
  {
     on = 1;
  }
  if(IR.decodedIRData.decodedRawData == 0xFF6897) //if the pause button is pressed
  {
     auto_mode = 1;
  }
  if(IR.decodedIRData.decodedRawData == 0xFF30CF) //if the 0 button is pressed
  {
     auto_mode = 0; //manul mode
  }
  if(IR.decodedIRData.decodedRawData == 0xFF30CF) //if the vol+ button is pressed
  {
     digitalWrite(2, LOW);
    digitalWrite(1, HIGH);
    digitalWrite(0, LOW);
    digitalWrite(3, HIGH);
    delay(1000);
  }
  if(IR.decodedIRData.decodedRawData == 0xFF30CF) //if the vol- button is pressed
  {
     digitalWrite(2, HIGH);
    digitalWrite(1, LOW);
    digitalWrite(0, HIGH);
    digitalWrite(3,LOW);
  }
  if(IR.decodedIRData.decodedRawData == 0xFF30CF) //if the left button is pressed
  {
     digitalWrite(2, HIGH);
    digitalWrite(1, LOW);
    digitalWrite(0, LOW);
    digitalWrite(3, HIGH);
    delay(100);
  }
  if(IR.decodedIRData.decodedRawData == 0xFF30CF) //if the right button is pressed
  {
     digitalWrite(2, LOW);
    digitalWrite(1, HIGH);
    digitalWrite(0, HIGH);
    digitalWrite(3, LOW);
  }
  if(IR.decodedIRData.decodedRawData == 0xFF18E7) //if the 2 button is pressed
  {
  }
 
 if(on && auto_mode)
 { 
  if(s==HIGH) //move backward when ir sensor is far from ground
  { 
    digitalWrite(1, LOW);
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    delay(1000);
    currentstate=1;
    }
  if ((currentstate==0)&&(s==LOW)&&(distanceleft <= 15 && distancefront > 15 && distanceright <= 15) || (currentstate==0)&&(s==LOW)&&(distanceleft > 15 && distancefront > 15 && distanceright > 15))
  {
    digitalWrite(1, HIGH); 
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    digitalWrite(4,LOW);
    
  }
  //make left turn
  if ((currentstate==1)&&(s==LOW)||(s==LOW)&&(distanceleft <= 15 && distancefront <= 15 && distanceright > 15)||(s==LOW)&&(distanceleft <= 15 && distancefront <= 15 && distanceright > 15)||(s==LOW)&& (distanceleft <= 15 && distancefront > 15 && distanceright > 15)||(distanceleft <= 15 && distancefront > 15 && distanceright > 15))
  {
    digitalWrite(1, HIGH);
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    delay(100);
    currentstate=0;
  }
  //make right turn
  if ((s==LOW)&&(distanceleft > 15 && distancefront <= 15 && distanceright <= 15) ||(s==LOW)&& (distanceleft > 15 && distancefront > 15 && distanceright <= 15) ||(s==LOW)&& (distanceleft > 15 && distancefront <= 15 && distanceright > 15) )
  {
    digitalWrite(1, LOW);
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
  }
 }
}
