/* NeoDigito ejemplo de código: wifi mqtt internet
    Cuenta de 0 a 9999 y luego hace una cuentra regresiva
    el color por defecto es rojo.

    Creado por David Figueroa
    Potenciado por Inventoteca y Xircuitos, Junio 11, 2021.
    basado en la libreria de Seven_Segment_Pixel, de Peter Hartmann.

    

    https://github.com/Inventoteca/NeoDigito

    This example code is in the public domain.
    
    Recuerda que debes tener instalada la librería de 

    Adafruit_NeoPixel

    Así como instalado la tarjeta ESP8266, (using Arduino 1.6.4+):
  - Add the following 3rd party board manager under "File -> Preferences -> Additional Boards Manager URLs":
       http://arduino.esp8266.com/stable/package_esp8266com_index.json

  y la PubSubClient


*/

#include <NeoDigito.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.

const char* ssid = "Inventoteca_2G";
const char* password = "science_7425";
const char* mqtt_server = "broker.mqtt-dashboard.com";

// Para configurar el cliente de mqtt
WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE	(50)
char msg[MSG_BUFFER_SIZE];

// Pin donde estará conectado el display
#define PIN 0           // Para el caso especifico del ESP8266 con batería, D3 - GPIO0
#define DIGITS 8        // Neodigitos conectados
#define PIXPERSEG 3     // Neopixels por segmento


// Una vez especificado el número de displays,
// así como el número de neopixels por segmento.
// adicionalmente se agregan algunos argumentos de 
// la tira de neopixes usado

NeoDigito display1 = NeoDigito(DIGITS, PIXPERSEG, PIN, NEO_GRB + NEO_KHZ800);


void setup()
{
  display1.begin(); // Esta función llama Adafruit_NeoPixel.begin() para configurar;

  // Esta función puede controlar un solo led o toda la tira
  // si se especifica el número del led: display1.setPixelColor(0,0xff00ff);
  // y para toda la tira no se especifica el numero del display solo el color en 32 bits
  display1.setPixelColor(0x090000);
  Serial.begin(115200);
  
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

}

void loop()
{

  if (!client.connected()) 
  {
    reconnect();
  }
  client.loop();

  //unsigned long now = millis();
  //if (now - lastMsg > 2000) 
  //{
  //  lastMsg = now;
  //  ++value;
  //  snprintf (msg, MSG_BUFFER_SIZE, "hello world #%ld", value);
  //  Serial.print("Publish message: ");
  //  display1.print(msg);
  //  Serial.println(msg);
  //  client.publish("outTopic", msg);
  //}
}

// ------------------------------------- setup_wifi
void setup_wifi() 
{

  int i = 1;
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  display1.print(ssid);
  display1.show();
  delay(500);
  display1.clear();

  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
    display1.write('.',i++);
    display1.show();
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  display1.print("Internet");
  display1.show();
  delay(500);
}

// -------------------------------------------- callback
// aqui se lee el mensaje letra por letra
void callback(char* topic, byte* payload, unsigned int length) 
{
  String StrColor = "";
  String StrTopic = topic;
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  if(StrTopic == "neoColor")
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

  else if(StrTopic == "neoNumber")
  {
    display1.clear();
    for (int i = 0; i < length; i++) 
    {
      Serial.print((char)payload[i]);
      display1.write((char)payload[i],i);
    }
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
      client.publish("neoStatus", "hello world");
      // ... and resubscribe
      client.subscribe("neoNumber");
      client.subscribe("neoColor");
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