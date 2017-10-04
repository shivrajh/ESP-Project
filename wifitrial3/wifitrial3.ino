#include <SoftwareSerial.h>
 
#define DEBUG true
 
SoftwareSerial esp8266(2,3); // make RX Arduino line is pin 2, make TX Arduino line is pin 3.
                             // This means that you need to connect the TX line from the esp to the Arduino's pin 2
                             // and the RX line from the esp to the Arduino's pin 3
void setup()
{
  Serial.begin(9600);
  esp8266.begin(9600); // your esp's baud rate might be different
  
 
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
  pinMode(12,OUTPUT);
  digitalWrite(12,LOW);
  sendData("AT+RST\r\n",2000,DEBUG); // reset module
  sendData("AT+CWMODE=2\r\n",1000,DEBUG); // configure as access point
  sendData("AT+CIFSR\r\n",1000,DEBUG); // get ip address
  sendData("AT+CIPMUX=1\r\n",1000,DEBUG); // configure for multiple connections
  sendData("AT+CIPSERVER=1,80\r\n",1000,DEBUG); // turn on server on port 80
}
 
void loop()
{ int i,ledno1,ledno2,ledno;
  char dump,ch;
  String identify;
  String on="ON";
  String off="OFF";
  String webpage1 = "<!DOCTYPE html><html><body><h1>LED 13 is "; 
  String webpage2 = "OFF";
  String webpage12= webpage1+webpage2;
  String webpage3 = "</h1><form action = "" method = 'post'><input type='submit' name='13' value='Toggle LED' /></form>";
  String webpage4 = "<h2>LED 12 is "; 
  String webpage5 = "OFF";
  String webpage45= webpage4+webpage5;
  String webpage6 = "</h2><form action = "" method = 'post'><input type='submit' name='12' value='Toggle12' /></form></body></html>";
  
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
     /*for(i=0;i<7;i++)
     { ch=esp8266.read();
       identify+=ch;
     }*/
     
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
       
       if(ledno==13)
       {     if(ledval==0)
             {
                webpage12=webpage1+off;
             }
             else if(ledval==1)
             {
                webpage12=webpage1+on;
             }
       }
       else if(ledno==12)
       {     if(ledval==0)
             {
                webpage45=webpage4+off;
             }
             else if(ledval==1)
             {
                webpage45=webpage4+on;
             }
       }
       
     }  
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

