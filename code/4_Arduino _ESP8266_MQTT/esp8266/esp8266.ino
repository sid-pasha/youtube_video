#include <ESP8266WiFi.h>            //https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi
#include <WiFiClient.h>
#include <PubSubClient.h>           //https://github.com/Imroy/pubsubclient


const char *ssid = ""; // Имя роутера
const char *password = ""; // Пароль роутера

String mqtt_server = ""; // Имя сервера MQTT
int mqtt_port = ; // Порт для подключения к серверу MQTT
String mqtt_user = ""; // Логин для подключения к серверу MQTT
String mqtt_pass = ""; // Пароль для подключения к серверу MQTT
String device_name = "";//имя  device_name
String group= "";//Группа group
 
String top1,top2,top3,top4; //адресное пространство MQTT 
int mqtt_data_status;

String A; 

  WiFiClient mqtttestclient; 
  PubSubClient mqttclient(mqtttestclient);
  


void callback(const MQTT::Publish& pub){
     String payload = pub.payload_string();
}

void setup(void) {
     Serial.begin(9600);
     
     top3 += "/home/"+group+ "/"+device_name+"/";//уровень устройства
     top2 += "/home/"+group+"/";//уровень комнаты     
     top1 += "/home/";//уровень дома   

     Serial.print("Connecting to ");
     Serial.println(ssid);
     WiFi.begin(ssid, password);
     while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
           }
     Serial.println("");
     Serial.println("WiFi connected");
     Serial.println("IP address: ");
     Serial.println(WiFi.localIP());
     mqtt_connect();
}

void loop(void) {
     if (mqttclient.connected()){
         mqttclient.loop();
        }

     if(Serial.available()){    
        String Var="";  
        while (!Serial.available()) delay(20); 
                delay(400); 
                while (Serial.available())  
                       Var = Var + (char)(Serial.read());
                       A=Var.substring(Var.indexOf("Aa")+2,Var.indexOf("aA")); 

                       String   test;
                                test += "{\"status\":\""; 
                                test +=A; 
                                test += "\",\"smooth_change\":\"1\"}"; 
                       mqttclient.publish("/home/room1/led1/BN-SZ01/leds",test); 
        }
}  
    
  
 
