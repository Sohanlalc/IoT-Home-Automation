#include <ESP8266WiFi.h>
#include<FirebaseArduino.h>
#include <DHT.h>
#define FIREBASE_HOST "demoauto-3cc97.firebaseio.com"                     //Your Firebase Project URL goes here without "http:" , "\" and "/"
#define FIREBASE_AUTH "VpN7KYwScall4NDnaBbdDPej33lYpu4xVlwIouYd"       //Your Firebase Database Secret goes here
#define WIFI_SSID "mine"
                                          //your WiFi SSID for which yout NodeMCU connects
#define WIFI_PASSWORD "12gh34gh"                                      //Password of your wifi network 

#define Relay1 2 //D4

#define Enable 12 //D6
#define Input1  13//D7
#define Input2  15//D8

#define DHTTYPE DHT11
#define DHTPIN  14 //D5

#define smoke A0 //A0
#define buzzer 10 // SD3

DHT dht(DHTPIN, DHTTYPE ,11);
float humidity, temp; 
int smokeval=0;

int th=700;
int rel1;
int fan;

void setup() 
{
  pinMode(smoke,INPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(Enable,OUTPUT);
  digitalWrite(Enable,LOW);
   pinMode(Input1,OUTPUT);
    pinMode(Input2,OUTPUT);
    
 pinMode(Relay1,OUTPUT);
 digitalWrite(Relay1,LOW);
  Serial.begin(115200);  
  
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status()!=WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  dht.begin();
  
  Serial.println();
  Serial.print("connected:");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
   Firebase.setInt("LED",0);                     
 
    
  
}
void firebasereconnect()
{
  Serial.println("Trying to reconnect");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  }

void loop() 
{
  delay(1000);
  if (Firebase.failed())
      {
      Serial.print("setting number failed:");
      Serial.println(Firebase.error());
      firebasereconnect();
      return;
      }

   //Smoke Sensor data
   
  int smokeval=analogRead(smoke);
   Firebase.setInt("Smoke",smokeval);
  if(smokeval > th)
  {
    digitalWrite(buzzer,HIGH);
  
  }
  else
  {
    digitalWrite(buzzer,LOW);
  
  }
  
    //DHT11 Data 

   temp = dht.readTemperature();
    Firebase.setFloat("Temperature",temp);
  
 humidity = dht.readHumidity();
  Firebase.setFloat("Humidity",humidity);
  //LIght control
  rel1=Firebase.getString("LED").toInt(); 
  
  
  if(rel1==1)                                                            
     {
      digitalWrite(Relay1,LOW);
      Serial.println("Relay 1 ON");
      Firebase.setString("Status","LIGHT-ON");
      
    }
 if(rel1==0)                                                     
    {                                      
      digitalWrite(Relay1,HIGH);
      Serial.println("Relay 1 OFF");
       Firebase.setString("Status","LIGHT-OFF");
      
    }

    //Fan Control

   fan=Firebase.getString("FAN").toInt(); 
  
  
  if(fan==1)                                                            
     {
      digitalWrite(Enable,HIGH);
       digitalWrite(Input1,LOW);
        digitalWrite(Input2,HIGH);
     
      Firebase.setString("Status","FAN-ON");
      
    }
 if(fan==0)                                                     
    {                                      
      digitalWrite(Enable,LOW);
       digitalWrite(Input1,LOW);
        digitalWrite(Input2,LOW);
     
     
      Firebase.setString("Status","FAN-OFF");
      
    }




}
