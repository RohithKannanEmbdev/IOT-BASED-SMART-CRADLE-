Code.c

#include<LiquidCrystal.h>
LiquidCrystal Lcd(13,12,11,10,9,8);

#include "DHT.h"
#define DHTPIN A3
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);


#define ldr A1
#define sound A2
#define rain A0
#define fan 5
#define motor 7
#define light 6
#define alarm 4

int h, t,ldrvalue,rainvalue,soundvalue;
void setup( ) 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16,2);  
  lcd.setCursor(0,0);
  lcd.print("BABY MONITORING");
  delay(3000);
  lcd.clear();
 
  pinMode(ldr,INPUT);
  pinMode(sound,INPUT);
  pinMode(rain,INPUT);
  pinMode(fan,OUTPUT);
  pinMode(motor,OUTPUT);
  pinMode(light,OUTPUT);
  pinMode(alaram,OUTPUT);
digitalWrite(light,HIGH);
digitalWrite(fan,HIGH);
digitalWrite(motor,HIGH);
digitalWrite(alaram,LOW);
  dht.begin();

}

void loop() 
{ 


    t = dht.readTemperature();
    lcd.setCursor(0,0);lcd.print("T:");
    if(t <= 9){lcd.print("0");lcd.print(t);}
    else if(t <= 99){lcd.print(t);}

  if(t>=35){digitalWrite(fan,LOW); }
  else{digitalWrite(fan,HIGH);}


    h = dht.readHumidity();
    lcd.setCursor(6,0);lcd.print("H:");
    if(h <= 9){lcd.print("0");lcd.print(h);}
    else if(h <= 99){lcd.print(h);}


    ldrvalue=analogRead(ldr);
   
    ldrvalue=map(ldrvalue,100,400,0,100);
     Serial.print("ldr : ");
    Serial.println(ldrvalue);
    lcd.setCursor(11,0);lcd.print("L:");
    if(ldrvalue <= 0){ldrvalue=0;}
   else if(ldrvalue>=100){ldrvalue=100;}
    if(ldrvalue <= 9){lcd.print("00");lcd.print(ldrvalue);}
    else if(ldrvalue <= 99){lcd.print("0");lcd.print(ldrvalue);}
    else if(ldrvalue <= 999){lcd.print(ldrvalue);}
    if(ldrvalue>=90){digitalWrite(light,LOW);Serial.print("l");}
    else{digitalWrite(light,HIGH);}
    
  rainvalue=analogRead(rain);
     Serial.print("rainvalue : ");
    Serial.println(rainvalue);
  rainvalue=map(rainvalue,0,1023,100,0);
    lcd.setCursor(0,1);lcd.print("W:");
    
     if(rainvalue <= 9){lcd.print("0");lcd.print(rainvalue);}
    else if(rainvalue <= 99){lcd.print(rainvalue);}
    if(rainvalue!=0&&rainvalue >=5){digitalWrite(alaram,HIGH);}
     else{digitalWrite(alaram,LOW);}
     

soundvalue=analogRead(sound);
          Serial.print("sound : ");
    Serial.println(soundvalue);
    soundvalue=map(soundvalue,0,1023,0,100);
    lcd.setCursor(6,1);lcd.print("S:");
    if(soundvalue <= 0){soundvalue=0;}
   else if(soundvalue>=100){soundvalue=100;}
     if(soundvalue <= 9){lcd.print("00");lcd.print(soundvalue);}
    else if(soundvalue <= 99){lcd.print("0");lcd.print(soundvalue);}
    else if(soundvalue <= 999){lcd.print(soundvalue);}
   if(soundvalue>=25){digitalWrite(motor,LOW); delay(5000);}
   else{digitalWrite(motor,HIGH);
}
   
      delay(500);
      senddata();
}



void send data()
{
      Serial.print('*');
    
    if(t <= 9){Serial.print("00");Serial.print(t);}
    else if(t <= 99){Serial.print("0");Serial.print(t);}
    else if(t <= 999){Serial.print(t);}

    if(h <= 9){Serial.print("00");Serial.print(h);}
    else if(h <= 99){Serial.print("0");Serial.print(h);}
    else if(h <= 999){Serial.print(h);}

  
   if(ldrvalue <= 9){Serial.print("00");Serial.print(ldrvalue);}
    else if(ldrvalue <= 99){Serial.print("0");Serial.print(ldrvalue);}
    else if(ldrvalue <= 999){Serial.print(ldrvalue);}

   if(rainvalue <= 9){Serial.print("00");Serial.print(rainvalue);}
    else if(rainvalue <= 99){Serial.print("0");Serial.print(rainvalue);}
    else if(rainvalue <= 999){Serial.print(rainvalue);}

    if(soundvalue <= 9){Serial.print("00");Serial.print(soundvalue);}
    else if(soundvalue <= 99){Serial.print("0");Serial.print(soundvalue);}
    else if(soundvalue <= 999){Serial.print(soundvalue);}
  
}



SENSOR FOR BLYNK APPLICATION:

IOT................

//E-725 babymonitoringiot
//babymonitoringiot@gmail.com
//Info@2022
#define BLYNK_PRINT Serial    
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "uo67Igck3LKBW8cmwM3EzRnaFHR_97br";

// Your Wi-Fi credentials.
// Set password to "" for open networks.
char ssid[] = "IOT";
char pass[] = "123456789";

unsigned int m=0,act=0,val,val1,val2,val3,val4,val5;

String inputString = ""; 
unsigned char a[200];

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);    
}

void loop()
{
   while(Serial.available())
    {
        char data;
        data=Serial.read();
  
        a[m]=data;
          if(a[0] == '*')
          {
            if(m<=15)
            {m++;}
          }

}
      if(m > 1)
      {
        val1 = (a[1]-0x30)*100 + (a[2]-0x30)*10  + (a[3] - 0x30);
        val2 = (a[4]-0x30)*100 + (a[5]-0x30)*10  + (a[6] - 0x30);
        val3 = (a[7]-0x30)*100 + (a[8]-0x30)*10  + (a[9] - 0x30);
        val4 = (a[10]-0x30)*100 + (a[11]-0x30)*10  + (a[12] - 0x30);
        val5 = (a[13]-0x30)*100 + (a[14]-0x30)*10  + (a[15] - 0x30);
       
        m=0;
      }
    
      
      delay(100);
      
        Blynk.virtualWrite(V1,val1);
     if(val1 >= 35){Blynk.notify("TEMPERATURE HIGH,DC FAN ON");}
    
    delay(100);
    Blynk.virtualWrite(V2,val2);
    delay(100);
    Blynk.virtualWrite(V3,val3);
    if(val3>=90){Blynk.notify("LDR LOW,LIGHT ON");}
    delay(100);
    Blynk.virtualWrite(V4,val4);
    if(val4!=0&&val4>=5){Blynk.notify("WATER HIGH,BUZZER ON");}
    delay(100);
    Blynk.virtualWrite(V5,val5);
    if(val5>=25){Blynk.notify("SOUND HIGH,DC MOTOR ON");}
    delay(100);
      Blynk.run();
      delay(100);
  }
