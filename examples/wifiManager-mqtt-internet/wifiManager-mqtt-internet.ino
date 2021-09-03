/*
    Control de NeoDigitos por MQTT usando WiFiManager.h
    para configurar WiFi, (broker y tópicos <- esto todavía no sirve) para suscribirse 
    por medio de un Captive Portal. Este Captive Portal se genera
    cada que no logra conectarse a su red wifi configurada previamente.

    Está planeado para suscribirse a un tópico personalizable para el 
    número y a otro tambien personalizable para el color a recibir.
    El formato que tomará es "Neodigito/Number/ESPXXXXXX"
    y también se suscribirá a "Neodigito/Number" en caso de 
    querer controlar más de un Neodigito a la vez.

    Basado en las librerías de NeoDígito y WiFiManager.
    Potenciado por Inventoteca y Xircuitos, Julio, 2021.

    ¡¡INSTALAR VERSIÓN 5.13 DE ArduinoJson.h!!
        
    Referencias:
    https://github.com/Inventoteca/NeoDigito/tree/main/examples/wifi-mqtt-internet
    https://github.com/CurlyWurly-1/ESP8266-WIFIMANAGER-MQTT

*/

#include <FS.h>                   //this needs to be first, or it all crashes and burns...

#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager
#include <ArduinoJson.h>          //https://github.com/bblanchon/ArduinoJson //¡¡INSTALAR VERSIÓN 5.13 DE ArduinoJson.h!!
#include <PubSubClient.h>
#include <NeoDigito.h>            //https://github.com/Inventoteca/NeoDigito

// Para configurar el cliente de mqtt
WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];

// Pin donde estará conectado el display
#define PIN 0           // Para el caso especifico del ESP8266 con batería, D3 - GPIO0
#define DIGITS 10        // Neodigitos conectados
#define PIXPERSEG 3     // Neopixels por segmento

NeoDigito display1 = NeoDigito(DIGITS, PIXPERSEG, PIN, NEO_GRB + NEO_KHZ800);

WiFiManager wifiManager;
//flag for saving data
bool shouldSaveConfig = true;
//define your DEFAULT values here, if there are different values in config.json, they are overwritten.
#define mqtt_server       "iot.inventoteca.com"
#define mqtt_port         "1883"
#define mqtt_user         "mqtt_user"
#define mqtt_pass         "mqtt_pass"
#define number_topic    "Number"
#define color_topic    "Color"

float temp = 0.0;
float hum = 0.0;
float diff = 1.0;
String ESP_ID = String(ESP.getChipId());
String NumberTopicWithESP_ID;
String ColorTopicWithESP_ID;
String NumberTopic;
String ColorTopic;
String literalementeNada = "";
//Porque la librería WM los quiere como arreglos de caracteres
char charColorTopicESP_ID[100];
char charNumberTopicESP_ID[100];
char charColorTopic[100];
char charNumberTopic[100];

void setup()
{
  display1.begin(); // Esta función llama Adafruit_NeoPixel.begin() para configurar;
  display1.setPixelColor(0x090000);
  Serial.begin(115200);

  // Para que el Captive Portal también pida esta info
  // id/name placeholder/prompt default length
  WiFiManagerParameter custom_mqtt_server("server", "MQTT Server", mqtt_server, 40);
  WiFiManagerParameter custom_mqtt_port("port", "MQTT Port", mqtt_port, 6);
  WiFiManagerParameter custom_number_topic("number", "Topico NeoNumber: Neodigito/ ... /ESPXXXX", number_topic, 40);
  WiFiManagerParameter custom_color_topic("color", "Topico NeoColor: Neodigito/ ... /ESPXXXX", color_topic, 40);
  //add all your parameters here
  wifiManager.addParameter(&custom_mqtt_server);
  wifiManager.addParameter(&custom_mqtt_port);
  wifiManager.addParameter(&custom_number_topic);
  wifiManager.addParameter(&custom_color_topic);

  // Reset Wifi settings for testing
  //wifiManager.resetSettings(); //<--COMENTAR DESPUÉS DE TESTEAR
  //clean FS for testing
  //SPIFFS.format(); //<--COMENTAR DESPUÉS DE TESTEAR

  //Revisa si ya hay config de parámetros extra guardada previamente
  checkSPIFFS();
  
  //Intenta conectarse a WiFi, si fracasa genera AP
  //y se queda en bucle esperando a la nueva configuración
  //wifiManager.autoConnect(); //Alternativamente: wifiManager.autoConnect("NombreAP_Aqui","password");
  wifiManager.autoConnect("Neodigito","12345678");
  
  //if you get here you have connected to the WiFi
  Serial.println("connected...yeey :)");

  //read updated parameters
  strcpy(mqtt_server, custom_mqtt_server.getValue());
  strcpy(mqtt_port, custom_mqtt_port.getValue());
  strcpy(number_topic, custom_number_topic.getValue());
  strcpy(color_topic, custom_color_topic.getValue());

  if (shouldSaveConfig) saveFS();

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  display1.print("Internet");
  display1.show();
  delay(500);
  display1.print(WiFi.localIP().toString());
  display1.show();
  delay(500);

  //Para poder controlar individualmente cada neodigito
  NumberTopicWithESP_ID = literalementeNada + "Neodigito/" + number_topic + "/ESP" + ESP_ID;
  ColorTopicWithESP_ID = literalementeNada + "Neodigito/" + color_topic + "/ESP" + ESP_ID;
  //Para poder controlar grupalmente los neodigitos
  NumberTopic = literalementeNada + "Neodigito/" + number_topic;
  ColorTopic = literalementeNada + "Neodigito/" + color_topic;
    
  NumberTopicWithESP_ID.toCharArray(charNumberTopicESP_ID, 100);
  ColorTopicWithESP_ID.toCharArray(charColorTopicESP_ID, 100);
  NumberTopic.toCharArray(charNumberTopic, 100);
  ColorTopic.toCharArray(charColorTopic, 100);
    
  Serial.print("Esperando mensajes en: ");
  Serial.println(charNumberTopicESP_ID);
  Serial.print("Y tambien en: ");
  Serial.println(charColorTopicESP_ID);
  
  int  mqtt_port_int;
  mqtt_port_int = atoi(mqtt_port);
  client.setServer(mqtt_server, mqtt_port_int);
  client.setCallback(callback);
}

void loop()
{

  if (!client.connected())
  {
    reconnect();
  }
  client.loop();

}



// -------------------------------------------- callback
// aqui se lee el mensaje letra por letra
void callback(char* topic, byte* payload, unsigned int length)
{
  String StrColor = "";
  String StrTopic = topic;
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.println("] ");

  
    if (StrTopic == charColorTopicESP_ID|| StrTopic == charColorTopic) 
  {
    for (int i = 0; i < length; i++)
    {
      StrColor += (char)payload[i];

    }
    display1.setPixelColor(StrColor.toInt());
    //display1.print(StrColor);
    display1.show();
    Serial.print(StrColor);
    StrColor = "";
  }

  else if (StrTopic == charNumberTopicESP_ID || StrTopic == charNumberTopic) 
  {
    display1.clear();
    for (int i = 0; i < length; i++)
    {
      Serial.print((char)payload[i]);
      StrColor += (char)payload[i];
      //display1.write((char)payload[i],i);
    }

    display1.print(StrColor);
    Serial.println();
    display1.show();
  }


}


// ----------------------------------------- reconect
void reconnect()
{
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str()))
    {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("neoAlive", charNumberTopicESP_ID);
      // ... and resubscribe
      client.subscribe(charNumberTopicESP_ID);
      client.subscribe(charColorTopicESP_ID);
      client.subscribe(charNumberTopic);
      client.subscribe(charColorTopic);
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void checkSPIFFS()
{
  //read configuration from FS json
  Serial.println("mounting FS...");

  if (SPIFFS.begin()) { //Revisa si existe configuración previa
    Serial.println("mounted file system");
    if (SPIFFS.exists("/config.json")) {
      //file exists, reading and loading
      Serial.println("reading config file");
      File configFile = SPIFFS.open("/config.json", "r");
      if (configFile) {
        Serial.println("opened config file");
        size_t size = configFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);

        configFile.readBytes(buf.get(), size);
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        json.printTo(Serial);
        if (json.success()) {
          Serial.println("\nparsed json");
          strcpy(mqtt_server, json["mqtt_server"]);
          strcpy(mqtt_port, json["mqtt_port"]);
          strcpy(number_topic, json["number_topic"]);
          strcpy(color_topic, json["color_topic"]);
        } else {
          Serial.println("failed to load json config");
        }
      }
    }
  } else {
    Serial.println("failed to mount FS");
  } //end read
}

void saveFS()
{
  //save the custom parameters to FS
  if (shouldSaveConfig) {
    Serial.println("saving config");
    DynamicJsonBuffer jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();
    json["mqtt_server"] = mqtt_server;
    json["mqtt_port"] = mqtt_port;
    json["number_topic"] = number_topic; //Sólo si tiene contraseña el broker MQTT
    json["color_topic"] = color_topic;

    File configFile = SPIFFS.open("/config.json", "w");
    if (!configFile) {
      Serial.println("Failed to open config file for writing");
    }

    json.printTo(Serial);
    json.printTo(configFile);
    configFile.close();
    //end save
  }
}