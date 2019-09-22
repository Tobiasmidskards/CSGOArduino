#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Adafruit_NeoPixel.h>

ESP8266WebServer server;
String ssid = "Fiskenettett";
String password = "lolerfedt";

static int NUM_LEDS = 60;

int interrupt = 0;

IPAddress local_IP(111,111,111,111);
IPAddress gateway(111,111,111,1);
IPAddress subnet(255,255,255,0);

String state = "";
int brightness = 0;
int pixelloop = 0;
int way = 0;

boolean fadeEnabled = true;
unsigned long prevFade = 0;
long fadeTime = 80;

#define PIN D1
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  strip.begin();
  Serial.begin(115200);

  attemptConnection(false);
}

void loop()
{
  stateMachine("");
  fade(0);
}

void attemptConnection(bool resetCreds)
{
  welcomeLED();
  WiFi.softAPdisconnect(true);
  
  if (resetCreds) 
  {
    WiFi.disconnect();
  }

  int count = 0;

  if(ssid.length() > 1 && password.length() > 1) 
  {  
    WiFi.begin(ssid, password);
    while(WiFi.status()!=WL_CONNECTED && count<20)
    {
      Serial.print(".");
      delay(500);
      count++;
    }
  }

  if(WiFi.status()==WL_CONNECTED)
  {
    state = "READY";
    wifiConnected();
    Serial.println("");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  
    server.on("/",[](){server.send(200,"text/html",getDefaultHTML());});
    server.on("/set",toggleLED);
    server.on("/off", resetPixelColor);
    server.on("/find", imHere);
    server.on("/stop", inter);
    server.on("/bomb", bomb);
    server.on("/explode", fire);
    server.on("/sparkle", sparkleLoop);
    server.on("/reset", resetCon);
    server.onNotFound(handleNotFound);
    
    server.begin();
    
  } else {
    WiFi.softAPdisconnect(true);
    WiFi.disconnect();
    Serial.println("No connection -> Creating AP");
    networkSetup();
    
  }

}

void configHTML()
{
  server.send(200, "text/html", getConfigHTML());
}

void wifiConnected()
{
  meteorRain(0x00,0xff,0x00,10, 64, true, 15);
}

void toggleLED()
{ 
  interrupt = 1;
  fadeEnabled = true;
  String r = server.arg("red");
  String g = server.arg("grn");
  String b = server.arg("blu");
  String bri = server.arg("bri");
  
  sendHeaders();
  server.send(200,"text/html", getSetHTML(r, g, b, bri));

  setPixelColor(r.toInt(), g.toInt(), b.toInt(), bri.toInt()); 
}

void setPixelColor(int r, int g, int b, int bri)
{
    if(r<0)r=0;
    if(g<0)g=0;
    if(b<0)b=0;
    if(bri<0)bri=0;
    if(r>254)r=255;
    if(g>254)g=255;
    if(b>254)b=255;
    if(bri>254)bri=255;
    
    uint32_t color = strip.Color(r, g, b);
    
    strip.fill(color, 0, NUM_LEDS);
    if(bri < 10) 
    {
      strip.clear();
    } else 
    {
      strip.setBrightness(bri);
    }
    strip.show();
}

void resetPixelColor()
{
  sendHeaders();
  server.send(200,"text/plain","All LEDs are off!"); 
  strip.clear();
  strip.show();
}
