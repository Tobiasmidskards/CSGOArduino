
void networkSetup()
{ 
  stateMachine("AP");
  Serial.print("Setting soft-AP configuration ... ");
  Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Ready" : "Failed!");

  Serial.print("Setting soft-AP ... ");

  String randString = "";

  char *letters = "abcdefghijklmnopqrstuvwxyz0123456789";

  for(int i = 0; i<4; i++)
  {
   randString += letters[random(0, 36)];
  }

  Serial.println(WiFi.softAP("CSGO setup - " + randString) ? "Ready" : "Failed!");

  Serial.print("Soft-AP IP address = ");
  Serial.println(WiFi.softAPIP());
  
  server.on("/", configHTML);
  server.on("/config", configureWifi);
  
  server.begin();
}


void stateMachine(String change)
{
  server.handleClient();
  if(change.length() > 0)
  {
    state = change;
  }
  if(state == "AP")
  {
    if (brightness > 100) {
      way = 0;
    }
    
    if (brightness < 10) {
      way = 1;
    }

    if (way == 1) 
    {
      brightness++;
    } else {
      brightness--;
    }

    strip.setBrightness(brightness);
    strip.fill(strip.Color(255, 0, 255),0,60);
    strip.show();
    delay(35);
  }
}

void configureWifi()
{
  server.send(200, "text/plain", "");
  ssid = server.arg("ssid");
  password = server.arg("pwd");

  if(ssid.length() > 3 && password.length() > 3)
  {
    Serial.println("Trying with:");
    Serial.println(ssid);
    Serial.println(password);
    attemptConnection(true);
  } else {
    Serial.println("Try again");
  }
}

void imHere()
{
  sendHeaders();
  server.send(200, "text/plain", "CSGOLIGHT");
}
