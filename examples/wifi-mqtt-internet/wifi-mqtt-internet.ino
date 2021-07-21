/* NeoDigito example code: wifi mqtt internet

    Created and empowered by Inventoteca and Xircuitos.
    Puebla, Pue. October 21, 2020.

    https://github.com/Inventoteca/NeoDigito

    This example code is in the public domain.
	Remember that you must have installed Adafruit_NeoPixel library,
    the ESP8266 board, (using Arduino 1.6.4+):
  - Add the following 3rd party board manager under "File -> Preferences -> Additional Boards Manager URLs":
       http://arduino.esp8266.com/stable/package_esp8266com_index.json
    and the PubSubClient library.
*/

#include <NeoDigito.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.

const char* ssid = "Inventoteca_2G";
const char* password = "science_7425";
const char* mqtt_server = "broker.mqtt-dashboard.com";

// Configure the mqtt client
WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE	(50)
char msg[MSG_BUFFER_SIZE];

// Pin where the display will be attached
#define PIN 0       // Specifically for the ESP8266 board with battery, D3 - GPIO0

// Number of NeoDigitos connected
#define DIGITS 10

// NeoPixel per segment
#define PIXPERSEG 2

// Once you have specified the number of displays
// and the number of neopixels per segment, some
// arguments of the neopixel strip used must be
// added. NeoDigito() also admits the number of
// delimiters and the number of pixels per delimiter.

NeoDigito display1 = NeoDigito(DIGITS, PIXPERSEG, PIN, NEO_GRB + NEO_KHZ800);


void setup()
{
  display1.begin();
    // This function calls Adafruit_NeoPixel begin();

  display1.setPixelColor(0x090000);
    // This function sets a default color for the whole strip. It can be specified by
    // a 32bit hexadecimal number or three 8bit hexadecimal numbers that represents
    // red, green and blue separately.

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
  display1.print(WiFi.localIP().toString());
  display1.show();
  delay(500);
}

// -------------------------------------------- callback
// here reads the message letter by letter
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
