#include <SoftwareSerial.h>
 
#define DEBUG true
 
SoftwareSerial esp8266(10,11); // make RX Arduino line is pin 2, make TX Arduino line is pin 3.
                             // This means that you need to connect the TX line from the esp to the Arduino's pin 2
                             // and the RX line from the esp to the Arduino's pin 3
  const String on PROGMEM="ON";
  const String off PROGMEM="OFF";
  
  const String webpage1 PROGMEM= "<!DOCTYPE html><html><body><h1>LED 13 is "; 
  const String webpage2 PROGMEM= "OFF";
  String webpage12= webpage1+webpage2;
  const String webpage3 PROGMEM= "</h1><form action = "" method = 'post'><input type='submit' name='13' value='Toggle13' /></form>";
  
  const String webpage4 PROGMEM= "<h1>LED 3 is "; 
  const String webpage5 PROGMEM= "OFF";
  String webpage45= webpage4+webpage5;
  const String webpage6 PROGMEM= "</h1><form action = "" method = 'post'><input type='submit' name='03' value='Toggle03' /></form>";                       
  
  const String webpage11 PROGMEM= "<h1>LED 4 is "; 
  const String webpage22 PROGMEM= "OFF";
  String webpage1122= webpage11+webpage22;
 const String webpage33 PROGMEM= "</h1><form action = "" method = 'post'><input type='submit' name='04' value='Toggle04' /></form>";
  
  const String webpage44 PROGMEM= "<h1>LED 5 is "; 
  const String webpage55 PROGMEM= "OFF";
  String webpage4455= webpage44+webpage55;
  const String webpage66 PROGMEM= "</h1><form action = "" method = 'post'><input type='submit' name='05' value='Toggle05' /></form>";

// DO NOT USE PIN 10 AND 11.. SINCE THEY ARE THE RX AND TX FOR ESP8266
  
  const String webpage41 PROGMEM= "<h1>LED 6 is "; 
  const String webpage51 PROGMEM= "OFF";
  String webpage4151= webpage41+webpage51;
  const String webpage61 PROGMEM= "</h1><form action = "" method = 'post'><input type='submit' name='06' value='Toggle06' /></form></body></html>";     
void setup()
{
  Serial.begin(9600);
  esp8266.begin(9600); // your esp's baud rate might be different
  
 
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
  pinMode(3,OUTPUT);
  digitalWrite(3,LOW);
   pinMode(4,OUTPUT);
  digitalWrite(4,LOW);
  pinMode(5,OUTPUT);
  digitalWrite(5,LOW);
  pinMode(6,OUTPUT);
  digitalWrite(6,LOW);
  sendData("AT+RST\r\n",2000,DEBUG); // reset module
  sendData("AT+CWMODE=2\r\n",1000,DEBUG); // configure as access point
  sendData("AT+CIFSR\r\n",1000,DEBUG); // get ip address
  sendData("AT+CIPMUX=1\r\n",1000,DEBUG); // configure for multiple connections
  sendData("AT+CIPSERVER=1,80\r\n",1000,DEBUG); // turn on server on port 80
}
 
void loop()
{ int i,ledno1,ledno2,ledno;
  char dump,ch;
  
  
  
  if(esp8266.available()) // check if the esp is sending a message 
  {
    if(esp8266.find("+IPD,"))
    {
     delay(1000);
 
     int connectionId = esp8266.read()-48; // subtract 48 because the read() function returns 
                                           // the ASCII decimal value and 0 (the first decimal number) starts at 48
     for(i=0;i<10;i++)
     { dump=esp8266.read();
     }
    
     
     if(esp8266.read()=='m')
     { for(i=0;i<6;i++)
       { 
          dump=esp8266.read();
       }
       ledno1=esp8266.read()-48;
       ledno2=esp8266.read()-48;
       ledno=(ledno1*10)+(ledno2*1);
       int ledval;
       ledval=!digitalRead(ledno);
       digitalWrite(ledno,ledval);
       
       if(ledno==13)                        //Since LED is present at pin 13 on the arduino board (to check if the project is working)
       {     if(ledval==0)
             {
                webpage12=webpage1+off;
             }
             else if(ledval==1)
             {
                webpage12=webpage1+on;
             }
       }
       else if(ledno==3)
       {     if(ledval==0)
             {
                webpage45=webpage4+off;
             }
             else if(ledval==1)
             {
                webpage45=webpage4+on;
             }
       }
       else if(ledno==4)
       {     if(ledval==0)
             {
                webpage1122=webpage11+off;
             }
             else if(ledval==1)
             {
                webpage1122=webpage11+on;
             }
       }
       else if(ledno==5)
       {     if(ledval==0)
             {
                webpage4455=webpage44+off;
             }
             else if(ledval==1)
             {
                webpage4455=webpage44+on;
             }
       }
       else if(ledno==6)
       {     if(ledval==0)
             {
                webpage4151=webpage41+off;
             }
             else if(ledval==1)
             {
                webpage4151=webpage41+on;
             }
       }
       
     }
     sendData("AT+CIFSR\r\n",1000,DEBUG);
     String webpage = webpage12+webpage3;
     String cipSend = "AT+CIPSEND=";
     cipSend += connectionId;
     cipSend += ",";
     cipSend +=webpage.length();
     cipSend +="\r\n";
     sendData(cipSend,1000,DEBUG);
     sendData(webpage,1000,DEBUG);
     
     String webpagea = webpage45+webpage6;
     String cipSenda = "AT+CIPSEND=";
     cipSenda += connectionId;
     cipSenda += ",";
     cipSenda +=webpagea.length();
     cipSenda +="\r\n";
     sendData(cipSenda,1000,DEBUG);
     sendData(webpagea,1000,DEBUG);

     String webpageb = webpage1122+webpage33;
     String cipSendb = "AT+CIPSEND=";
     cipSendb += connectionId;
     cipSendb += ",";
     cipSendb +=webpageb.length();
     cipSendb +="\r\n";
     sendData(cipSendb,1000,DEBUG);
     sendData(webpageb,1000,DEBUG);

     String webpagec = webpage4455+webpage66;
     String cipSendc = "AT+CIPSEND=";
     cipSendc += connectionId;
     cipSendc += ",";
     cipSendc +=webpagec.length();
     cipSendc +="\r\n";
     sendData(cipSendc,1000,DEBUG);
     sendData(webpagec,1000,DEBUG);

     String webpaged = webpage4151+webpage61;
     String cipSendd = "AT+CIPSEND=";
     cipSendd += connectionId;
     cipSendd += ",";
     cipSendd +=webpaged.length();
     cipSendd +="\r\n";
     sendData(cipSendd,1000,DEBUG);
     sendData(webpaged,1000,DEBUG);

     String closeCommand = "AT+CIPCLOSE="; 
     closeCommand+=connectionId; // append connection id
     closeCommand+="\r\n";
     
     sendData(closeCommand,3000,DEBUG);
    }
  }
}
 
 
String sendData(String command, const int timeout, boolean debug)
{
    String response = "";
    
    esp8266.print(command); // send the read character to the esp8266
    
    long int time = millis();
    
    while( (time+timeout) > millis())
    {
      while(esp8266.available())
      {
        
        // The esp has data so display its output to the serial window 
        char c = esp8266.read(); // read the next character.
        response+=c;
      }  
    }
    
    if(debug)
    {
      Serial.print(response);
    }
    
    return response;
}

