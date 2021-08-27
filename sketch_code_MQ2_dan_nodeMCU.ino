//Asyoni elektronik

#include <MQ2.h>
#include <ESP8266WiFi.h>

int pinAout = A0;
int lpg_gas, co_gas, smoke_gas;

MQ2 mq2(pinAout);
String apiKey = "9OIMT8UHI5OTVECW";           // Masukan Write API key kamu dari ThingSpeak
const char* ssid =  "Asyoni elektronik";     // Masukan nama wifi kamu
const char* pass =  "12345678";             // Masukan Password wifi kamu
const char* server = "api.thingspeak.com";
WiFiClient client;


void setup() {
  
Serial.begin(115200);

  mq2.begin();
       delay(10);
      
 
       Serial.println("Connecting to ");
       Serial.println(ssid);
 
 
       WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(100);
            Serial.print("*");
     }
      Serial.println("");
      Serial.println("***WiFi Terhubung***");
 


  
}
 
void loop() {
  
  

if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
      {  
       String sendData = apiKey+"&field1="+String(lpg_gas)+"&field2="+String(co_gas)+"&field3="+String(smoke_gas)+"\r\n\r\n"; 
       
       //Serial.println(sendData);

       client.print("POST /update HTTP/1.1\n");
       client.print("Host: api.thingspeak.com\n"); 
       client.print("Connection: close\n");
       client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
       client.print("Content-Type: application/x-www-form-urlencoded\n");
       client.print("Content-Length: ");
       client.print(sendData.length());
       client.print("\n\n");
       client.print(sendData);
       
  float* values= mq2.read(false); //jika diset "false" tidak akan dimunculkan di serial monitor
  lpg_gas = mq2.readLPG();
  co_gas = mq2.readCO();
  smoke_gas = mq2.readSmoke();

   
     
  Serial.print("LPG:"); 
  Serial.print(lpg_gas);
  Serial.print(" CO:");
  Serial.print(co_gas);
  Serial.print("SMOKE:"); 
  Serial.println(smoke_gas);
  
  Serial.println("%. Menghubungkan ke Thingspeak.");


   }
      
      
      client.stop();
      Serial.println("Mengirim data....");
      
      //delay(2000); // Delay ini akan mempengaruhi pengiriman data ke Thingspeak setiap 2000 milidetik atau = 2 detik sekali. Bisa dirubah sesuai dengan kebutuhan.
}
