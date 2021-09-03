/*
    Control de NeoDigitos por MQTT usando WiFiManager.h
    para configurar por medio de un Captive Portal.

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
#include <ArduinoJson.h>          //https://github.com/bblanchon/ArduinoJson <- Versión 5.13
#include <PubSubClient.h>
#include <NeoDigito.h>            //https://github.com/Inventoteca/NeoDigito

//flag for saving data
bool shouldSaveConfig = true;

//define your default values here, if there are different values in config.json, they are overwritten.
//char mqtt_server[40];
#define mqtt_server       "iot.inventoteca.com"
#define mqtt_port         "1883"
#define mqtt_user         "mqtt_user"
#define mqtt_pass         "mqtt_pass"
#define number_topic    "Neodigito/Number"
#define color_topic    "Neodigito/Color"

// Para NeoDigitos
#define PIN 0           // Pin donde se conectará el NeoDisplay
#define DIGITS 10        // Neodigitos conectados
#define PIXPERSEG 3     // Neopixels por segmento
NeoDigito display1 = NeoDigito(DIGITS, PIXPERSEG, PIN, NEO_GRB + NEO_KHZ800);

WiFiClient espClient;
PubSubClient client(espClient);
WiFiManager wifiManager;
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];

float temp = 0.0;
float hum = 0.0;
float diff = 1.0;
String ESP_ID = String(ESP.getChipId());
String NumberTopicWithESP_ID;
String ColorTopicWithESP_ID;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  //Neodigitos
  display1.begin();
  display1.setPixelColor(0x090000);
  display1.print("A");
  display1.show();
  Serial.println("NeoDisplay iniciando.");
  delay(3000);

  //clean FS for testing
  //SPIFFS.format(); //<--COMENTAR DESPUÉS DE TESTEAR
  checkSPIFFS();
 

  // Para que el Captive Portal también pida esta info
  // id/name placeholder/prompt default length
  WiFiManagerParameter custom_mqtt_server("server", "MQTT Server", mqtt_server, 40);
  WiFiManagerParameter custom_mqtt_port("port", "MQTT Port", mqtt_port, 6);
  WiFiManagerParameter custom_number_topic("number", "Topico NeoColor: ESPXXXX/", number_topic, 40); 
  WiFiManagerParameter custom_color_topic("color", "Topico NeoColor: ESPXXXX/", color_topic, 40);

  // Reset Wifi settings for testing
  //wifiManager.resetSettings(); //<--COMENTAR DESPUÉS DE TESTEAR


  //set static ip
  //  wifiManager.setSTAStaticIPConfig(IPAddress(10,0,1,99), IPAddress(10,0,1,1), IPAddress(255,255,255,0));

  //add all your parameters here
  wifiManager.addParameter(&custom_mqtt_server);
  wifiManager.addParameter(&custom_mqtt_port);
  wifiManager.addParameter(&custom_number_topic);
  wifiManager.addParameter(&custom_color_topic);


  //Intenta conectarse a WiFi, si fracasa genera AP
  //y se queda en bucle esperando a la nueva configuración
  wifiManager.autoConnect();

  //if you get here you have connected to the WiFi
  Serial.println("connected...yeey :)");

  //read updated parameters
  strcpy(mqtt_server, custom_mqtt_server.getValue());
  strcpy(mqtt_port, custom_mqtt_port.getValue());
  strcpy(number_topic, custom_number_topic.getValue()); 
  strcpy(color_topic, custom_color_topic.getValue());

  if (shouldSaveConfig) saveFS();
  
  Serial.println("Local ip: ");
  Serial.println(WiFi.localIP());
  display1.print("Internet");
  display1.show();
  delay(500);
  display1.print(WiFi.localIP().toString());
  display1.show();
  delay(500);

  const uint16_t mqtt_port_x = 1883; //<-----------------------------------CORREGIR
  client.setServer(mqtt_server, mqtt_port_x);
  client.setCallback(callback);


  NumberTopicWithESP_ID = "ESP" + ESP_ID + "/" + number_topic;
  ColorTopicWithESP_ID = "ESP" + ESP_ID + "/" + color_topic;
  Serial.print("Esperando mensajes en: ");
  Serial.println(NumberTopicWithESP_ID);
  Serial.print("Y tambien en: ");
  Serial.println(ColorTopicWithESP_ID);

  char topic[100];

  float newTemp = 10;
  float newHum = 20;
  hum = newHum;

//  Serial.print("Publicando cosas a: ");
//  snprintf(topic, sizeof(topic), "ESP%s/%s", ESP_ID, number_topic);
//  Serial.println(topic);
//  client.publish(topic, String(hum).c_str(), true);
}

//-----------------------------------------LOOP()---------------------------
void loop() {
  //Para MQTT
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 3000) { //Cada segundo
    lastMsg = now;
    char topic[100];
    char payload[100];
    float newTemp = 10;
    float newHum = 20;
    hum = newHum;

    Serial.print("Publicando cosas a: ");
    snprintf(topic, sizeof(topic), "ESP%s/%s", ESP_ID, number_topic);
    Serial.println(topic);
    snprintf(payload, sizeof(payload), "%.2f", hum);
    client.publish(topic, payload);
  }
}

//-----------------------------------------OTRAS FUNCIONES---------------------------
void reconnect() {
  char esp_id[20];
  snprintf(esp_id, sizeof(esp_id), "%s", ESP_ID);
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(esp_id)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


//callback notifying us of the need to save config
void saveConfigCallback () {
  Serial.println("Should save config");
  shouldSaveConfig = true;
}

// -------------------------------------------- callback
// aqui se lee el mensaje letra por letra
void callback(char* topic, byte* payload, unsigned int length)
{
  String StrDisplay = "";
  String StrTopic = topic;
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  if (StrTopic == ColorTopicWithESP_ID)
  {
    for (int i = 0; i < length; i++)
    {
      StrDisplay += (char)payload[i];

    }
    display1.setPixelColor(StrDisplay.toInt());
    display1.show();
    Serial.print(StrDisplay);
    StrDisplay = "";
  }
  else if (StrTopic == NumberTopicWithESP_ID)
  {
    display1.clear();
    for (int i = 0; i < length; i++)
    {
      Serial.print((char)payload[i]);
      StrDisplay += (char)payload[i];
    }

    display1.print(StrDisplay);
    Serial.println();
    display1.show();
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