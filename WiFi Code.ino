
#include <ESP8266WiFi.h>
//#include <ESP8266WebServer.h>

const char* host = "api.thingspeak.com"; // ThingSpeak domain    
const int httpPort = 80;
String ApiKey = "3HGHAE16COXBZPWW";
String path = "/update?key=" + ApiKey + "&field1=";   
//String path2 = "&field2=";
  
const char* ssid = "AndroidAP";
const char* pass = "87654321";
//char temperatureString[6],bpmString[6];
int b;
char cmd_arr1[100];
int cmd_count1;
int i;
//*******************************************************************************
void setup()
{
  Serial.begin(9600);
  Serial.println("");
  pinMode(5,OUTPUT);digitalWrite(5,LOW);
  WiFi.begin(ssid, pass);
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  digitalWrite(5,HIGH);
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Serial.println("- succesfully connected");
  Serial.println("- starting client");
}
//*******************************************************************************

void serial_get_command()
{
  char inchar=0;
  if(Serial.available() > 0)
  {
    inchar = Serial.read();    
    if(inchar == '<')
    {
      cmd_count1=0;
      while(inchar != '>' && cmd_count1<15)
      {
        if(Serial.available() > 0)
        {
          inchar = Serial.read();
          cmd_arr1[cmd_count1++] = inchar;
        }        
      }
      if(inchar == '>')
      {
        if(cmd_arr1[0]=='P')
        {
          cmd_arr1[0]='0';
          b = atoi(cmd_arr1);
          Serial.print("BPM: ");
          Serial.println(b);
         }
         else if(cmd_arr1[0]=='U')
         {
          cmd_arr1[0]='0';
          Serial.println("Uploading");
          send_data();
          
         }
         else
         {
          
         }
       }
    }
  }
}

//*******************************************************************************
void send_data()
{
  for(i=0;i<=3;i++){digitalWrite(5,LOW);delay(200);digitalWrite(5,HIGH);delay(200);}
  WiFiClient client;
  if (!client.connect(host, httpPort))return; 
  client.print(String("GET ") + path + b + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: keep-alive\r\n\r\n");        
                      
  for(i=0;i<=3;i++){digitalWrite(5,LOW);delay(50);digitalWrite(5,HIGH);delay(50);}
  client.stop();
}
//*******************************************************************************
void loop() 
{
 serial_get_command();
}
//*******************************************************************************
