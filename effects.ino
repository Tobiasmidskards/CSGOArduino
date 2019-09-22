unsigned long prevMillis = 0;
unsigned long prevMillis2 = 0;
unsigned long prevMillis3 = 0;

long ontime = 1000;
long fadeInterval = 1.5;
long count = 100;
int bri = 0;

void welcomeLED()
{
  resetPixelColor();
  for(int i = 0; i < 60; i++)
  {
    strip.setPixelColor(i, 255-i, 0, i*2);
    strip.show();
    delay(30);
  }
}

void fade(long customFade)
{
    long fadeTime_ = fadeTime;
    int brightness = strip.getBrightness() - 5;

    if (brightness < 1) {
      brightness = 0;
    }
    
    unsigned long currentMillis = millis();

    if (customFade > 0){
      fadeTime_ = customFade;
    }

    if (currentMillis - prevFade >= fadeTime_ && fadeEnabled)
    {
      bri -= 2;
      prevFade = currentMillis;
      strip.setBrightness(brightness);
    }

    strip.show();
}

void bombMillis()
{
    unsigned long currentMillis = millis();

    if (currentMillis - prevMillis2 >= fadeInterval)
    {
      bri -= 2;
      prevMillis2 = currentMillis;
      strip.setBrightness(bri);
    }
    
    if (currentMillis - prevMillis >= ontime)
    {
      bri = 254;
      prevMillis = currentMillis;
      strip.fill(strip.Color(255, 0, 0), 0, 60);
    }

    if (currentMillis - prevMillis3 >= count)
    {
      prevMillis3 = currentMillis;
      ontime -= 2;
    }

    strip.show();
}

void bomb()
{
  sendHeaders();
  server.send(200, "text/plain", "");
  fadeEnabled = false;
  ontime = 1000;
  strip.fill(strip.Color(255, 0, 0), 0, 60);
  interrupt = 0;
  while(interrupt == 0)
  {
    server.handleClient();
    bombMillis();
  }
}

void meteorRain(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay) {  
  for(int i = 0; i < NUM_LEDS+NUM_LEDS; i++) {
   
   
    // fade brightness all LEDs one step
    for(int j=0; j<NUM_LEDS; j++) {
      if( (!meteorRandomDecay) || (random(10)>5) ) {
        fadeToBlack(j, meteorTrailDecay );        
      }
    }
   
    // draw meteor
    for(int j = 0; j < meteorSize; j++) {
      if( ( i-j <NUM_LEDS) && (i-j>=0) ) {
        strip.setPixelColor(i-j, red, green, blue);
      }
    }
   
    strip.show();
    delay(SpeedDelay);
  }
}

void fadeToBlack(int ledNo, byte fadeValue) {
 #ifdef ADAFRUIT_NEOPIXEL_H
    // NeoPixel
    uint32_t oldColor;
    uint8_t r, g, b;
    int value;
   
    oldColor = strip.getPixelColor(ledNo);
    r = (oldColor & 0x00ff0000UL) >> 16;
    g = (oldColor & 0x0000ff00UL) >> 8;
    b = (oldColor & 0x000000ffUL);

    r=(r<=10)? 0 : (int) r-(r*fadeValue/256);
    g=(g<=10)? 0 : (int) g-(g*fadeValue/256);
    b=(b<=10)? 0 : (int) b-(b*fadeValue/256);
   
    strip.setPixelColor(ledNo, r,g,b);
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   leds[ledNo].fadeToBlackBy( fadeValue );
 #endif  
}

void fire()
{
  sendHeaders();
  server.send(200, "text/plain", "");
  strip.setBrightness(255);
  strip.show();
  interrupt = 0;
  fadeEnabled = true;
  while(interrupt == 0)
  {
      server.handleClient();
      fade(10);
      if(interrupt == 1) {
        break;
      } 
      //  Uncomment one of these RGB (Red, Green, Blue) values to
      //  set the base color of the flame.  The color will flickr
      //  based on the initial base color
      
      //  Regular (orange) flame:
        int r = 255, g = 80, b = 35;
    
      //  Purple flame:
      //  int r = 158, g = 8, b = 148;
    
      //  Green flame:
      //int r = 74, g = 150, b = 12;
    
      //  Flicker, based on our initial RGB values
      for(int i=0; i<strip.numPixels(); i++) {
        server.handleClient();
        if(interrupt == 1) {
          break;
        } 
        int flicker = random(0,55);
        int r1 = r;
        int g1 = g-flicker;
        int b1 = b-flicker;
        if(g1<0) g1=0;
        if(r1<0) r1=0;
        if(b1<0) b1=0;
        strip.setPixelColor(i,r1,g1, b1);
      }
      strip.show();
      //  Adjust the delay here, if you'd like.  Right now, it randomizes the 
      //  color switch delay to give a sense of realism
      delay(random(10,113));
  }
}


void sparkleLoop()
{
  interrupt = 0;
  while(true)
  {
    server.handleClient();
    if (interrupt == 1) 
    {
      break;
    }
    Sparkle(random(255), 0, random(255), 5, 2);
  }
}

void Sparkle(byte red, byte green, byte blue, int SpeedDelay, int Pixels) {
  strip.setBrightness(255);
  for(int i = 0; i < Pixels; i++)
  {
      int Pixel = random(NUM_LEDS);
      strip.setPixelColor(Pixel,red,green,blue);
  }
  strip.show();
  delay(SpeedDelay);
  strip.fill(strip.Color(0,0,0),0,NUM_LEDS);
}
