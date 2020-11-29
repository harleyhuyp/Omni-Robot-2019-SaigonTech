/* Finished 2019 - For Omni Pathfinder Robot - Arduino Mega 2560*/
#include <STTODRobot.h>
STTODRobot myOmni = STTODRobot();
#define NOTE_C8  4186
unsigned int i,u,v;       //temporary counting variables
unsigned int IN1 = 22;      unsigned int EN1 = 5;
unsigned int IN2 = 23;      unsigned int EN2 = 6;
unsigned int IN3 = 24;      unsigned int EN3 = 7;
unsigned int IN4 = 25;
unsigned int IN5 = 26;      unsigned int buzzer = 13;
unsigned int IN6 = 27;

int A[16] ={A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15};
const int trig=12;
const int echo=13;
int sensorValue[16];      
int maxSensorVal[16];           
int minSensorVal[16];
byte ontheline;
const int left=90;
const int right=270;
const int forward=0;
const int backward=180;
unsigned long duration;
int distance;

void tornado(unsigned char vel,unsigned int duration)
{
      digitalWrite(IN1,HIGH);               //rotating            cuphap: tornado(toc do quay);
      digitalWrite(IN2,LOW);
      analogWrite (EN1,vel);

      digitalWrite(IN3,HIGH);
      digitalWrite(IN4,LOW);
      analogWrite (EN2,vel);

      digitalWrite(IN5,HIGH);
      digitalWrite(IN6,LOW);
      analogWrite (EN3,vel); delay(2000);
      digitalWrite(IN1,LOW);
      digitalWrite(IN2,LOW);
      analogWrite (EN1,0);
      digitalWrite(IN3,LOW);
      digitalWrite(IN4,LOW);
      analogWrite (EN2,0);
      digitalWrite(IN5,LOW);
      digitalWrite(IN6,LOW);
      analogWrite (EN3,0);
}
void minustornado(unsigned char vel,unsigned int duration)
{
      digitalWrite(IN2,HIGH);               //rotating            cu phap: tornado(toc do quay);
      digitalWrite(IN1,LOW);
      analogWrite (EN1,vel);

      digitalWrite(IN4,HIGH);
      digitalWrite(IN3,LOW);
      analogWrite (EN2,vel);

      digitalWrite(IN6,HIGH);
      digitalWrite(IN5,LOW);
      analogWrite (EN3,vel); delay(duration);
      digitalWrite(IN1,LOW); digitalWrite(IN2,LOW); analogWrite (EN1,0);
      digitalWrite(IN3,LOW); digitalWrite(IN4,LOW); analogWrite (EN2,0);
      digitalWrite(IN5,LOW); digitalWrite(IN6,LOW); analogWrite (EN3,0);
}
void motortest()
  {
      digitalWrite(IN1,HIGH);
      digitalWrite(IN2,LOW);
      analogWrite (EN1,210);   delay(2000); stops(1000);
      digitalWrite(IN1,LOW);
      digitalWrite(IN2,HIGH);
      analogWrite (EN1,210);   delay(2000);
      stops(1000);
      digitalWrite(IN3,HIGH);
      digitalWrite(IN4,LOW);
      analogWrite (EN2,210);   delay(2000); stops(1000);
      digitalWrite(IN3,LOW);
      digitalWrite(IN4,HIGH);
      analogWrite (EN2,210);   delay(2000);
      stops(1000);
      digitalWrite(IN5,HIGH);
      digitalWrite(IN6,LOW);
      analogWrite (EN3,210);   delay(2000); stops(1000);
      digitalWrite(IN5,LOW);
      digitalWrite(IN6,HIGH);
      analogWrite (EN3,210);   delay(2000);
      stops(1000);
  }
void stops(unsigned int duration)
  {
      digitalWrite(IN1,LOW);
      digitalWrite(IN2,LOW);
      analogWrite (EN1,0);
      digitalWrite(IN3,LOW);
      digitalWrite(IN4,LOW);
      analogWrite (EN2,0);
      digitalWrite(IN5,LOW);
      digitalWrite(IN6,LOW);
      analogWrite (EN3,0);    delay(duration);
  }
void sound(unsigned int times)
  {
    unsigned int y;
    for (y=1;y<=times;y++)
      {tone (53,NOTE_C8,200); delay(200);
      noTone(53); delay(200); }
  }
void getout()
{
  sound(3); stops(10000);
}
/* NOTE:
 *    FUNCTION: ledsignal('duration');  : turn on led in 'duration' second(s)
 *              tornado('vel');         : make Omni spin in 'vel' speed
 *              sound(times)            : buzzer
 *
 *              stops(duration);         : Omni stops in "duration" miliseconds
 *              getdistance();           :get distance from distance sensor
 *              currentstatus();         :ontheline = currentstatus:
count how many sensors are on the line
 *              motortest();             :test motor
 *              myOmni.move_omni  (angle,velocity);   :run the given angle
 */
byte getdistance()
{
     digitalWrite(trig,0);
     delayMicroseconds(2);
     digitalWrite(trig,1);
     delayMicroseconds(5);
     digitalWrite(trig,0);
     duration= pulseIn(echo,HIGH);
     distance=int(duration/2/29.412);
     return distance;
}
int currentstatus()
{
  for (i=0;i<=15;i++)
      {
        sensorValue[i] = analogRead(A[i]);
        if ((sensorValue[i]< minSensorVal[i]) || (sensorValue[i] >
maxSensorVal[i]))
        {
          sensorValue[i] = constrain(sensorValue[i], 0, 1023);
        }
        sensorValue[i] = map(sensorValue[i], minSensorVal[i],
maxSensorVal[i], 0, 1023);
      }           //CALIBRATE
   ontheline=0;
   for (i=0;i<=15;i++)
    {
      if (sensorValue[i]>500) {ontheline++;}
    }
    return ontheline;
}
void setup()
{
  Serial.begin(9600);
  myOmni.init (IN1,IN2,EN1,IN3,IN4,EN2,IN5,IN6,EN3);

  pinMode(IN1,OUTPUT);          pinMode(EN1,OUTPUT);
  pinMode(IN2,OUTPUT);          pinMode(EN2,OUTPUT);
  pinMode(IN3,OUTPUT);          pinMode(EN3,OUTPUT);
  pinMode(IN4,OUTPUT);          pinMode(trig,OUTPUT);
  pinMode(IN5,OUTPUT);          pinMode(echo,INPUT);
  pinMode(IN6,OUTPUT);
  sound(2);
  for (i=0;i<=15;i++)
    {
      pinMode(A[i],INPUT);
      minSensorVal[i]=1024;
      maxSensorVal[i]=0;
    }

  while (millis()<=3000)
    {
      myOmni.rotate_omni (true,140);
      for (v=0;v<=15;v++)
      {
        sensorValue[v] = analogRead (A[v]);
        if (sensorValue[v] < minSensorVal[v]) {minSensorVal[v] =
sensorValue[v];}
        if (sensorValue[v] > maxSensorVal[v]) {maxSensorVal[v] =
sensorValue[v];}
      }
      v=0;
    }             //calibrating
   stops(4000);
   tornado(200,2000);      stops(2000);
   minustornado(200,2000); stops(2000);
   motortest();
   stops(2000);
}
void loop()
{
     distance=1000; u=millis();
     while (distance>30)
      {
        myOmni.move_omni  (0,150);
        getdistance();
      }
      u=millis()-u;
      myOmni.move_omni  (180,120); delay(u-2000); sound(1); stops(2000);
}
