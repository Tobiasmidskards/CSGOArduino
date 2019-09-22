void inter(){
  interrupt = 1;
  sendHeaders();
  server.send(200, "text/plain", "");
}

void resetCon()
{
  ssid = "";
  password = "";
  sendHeaders();
  server.send(200, "text/plain", "");
  attemptConnection(true);
}

void sendHeaders()
{
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Allow", "HEAD,GET,PUT,POST,DELETE,OPTIONS");
  server.sendHeader("Access-Control-Allow-Methods", "GET, HEAD, POST, PUT");
  server.sendHeader("Access-Control-Allow-Headers", "X-Requested-With, X-HTTP-Method-Override, Content-Type, Cache-Control, Accept");
}

void handleNotFound()
{
    if (server.method() == HTTP_OPTIONS)
    {
        server.sendHeader("Access-Control-Allow-Origin", "*");
        server.sendHeader("Access-Control-Max-Age", "10000");
        server.sendHeader("Access-Control-Allow-Methods", "PUT,POST,GET,OPTIONS");
        server.sendHeader("Access-Control-Allow-Headers", "*");
        server.send(204);
    }
    else
    {
        server.send(404, "text/plain", "");
    }
}
