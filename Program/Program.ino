#include <ResponsiveAnalogRead.h>
#include "ACS712.h"
ACS712 sensor(ACS712_20A, A0);
const int iPre=A1;
const int tPre=A2;
int greenLED=7;
int relay=9;
float I;
float noLoadCurrent;
unsigned int timeDelay;
unsigned long t;
unsigned long t1,t2=0;
bool relayFlag=0;
int ledState = LOW;

ResponsiveAnalogRead current(iPre, true);
ResponsiveAnalogRead Time(tPre, true);

void setup() 
{ 
  Serial.begin(9600);
  pinMode(greenLED,OUTPUT);
  pinMode(iPre,INPUT);
  pinMode(tPre,INPUT);
  pinMode(relay,OUTPUT);
  digitalWrite(greenLED,LOW);
  digitalWrite(relay,LOW);
  sensor.calibrate();
  intro();
  delay(1000);
  digitalWrite(relay,HIGH);

}

void loop() 
{
  current.update();
  Time.update();  

  I = sensor.getCurrentAC();
  //noLoadCurrent=map(current.getValue(),0,1024,0,100);
  noLoadCurrent=current.getValue()*0.01;
  timeDelay=map(Time.getValue(),0,1024,0,60000);
 
  Serial.print("Set_Time: ");
  Serial.print(timeDelay);
  Serial.print(" | Set_Current: ");
  Serial.print(noLoadCurrent);
  Serial.print(" | Read_Current: ");
  Serial.print(I);
  Serial.print(" | System_Time = ");
  Serial.println(t);
  
 

  if(I<=noLoadCurrent && relayFlag==0)
  {
    Blink();
    if(t-t1>=timeDelay)
    {
      t1=t;
      digitalWrite(relay,LOW);
      digitalWrite(greenLED,HIGH);
      relayFlag=1;
    }
  }
  else 
  {
    if(relayFlag==0)
    {
     digitalWrite(greenLED,LOW);
    }
  }
  if(relayFlag==1)
  {
    Serial.println("Relay OFF");
  }

  
t=millis(); 
}

void intro()
{
  for(int i=0;i<7;i++)
  {
    Serial.println(".");
    delay(80);
  }
  Serial.println("Designed By Anand");
  delay(100);
  Serial.println("TechnoSpark Services");
  delay(100);
  Serial.println("8086381799");
  delay(100);
  for(int i=0;i<7;i++)
  {
    Serial.println(".");
    delay(80);
  }
}
void Blink()
{
 
  if(t-t2>=400)
  { 
    if (ledState == LOW) 
    {
      ledState = HIGH;
    } 
    else 
    {
      ledState = LOW;
    }
    t2=t;
    digitalWrite(greenLED,ledState);
  }
}

