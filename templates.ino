String getDefaultHTML()
{
  return "<html><body><h1>CSGO LIGHT</h1></body></html>";
}

String getConfigHTML()
{
  String configHTML = "";
  configHTML += "<html><head><link href='https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css' rel='stylesheet' integrity='sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T' crossorigin='anonymous'></head><body>";
  configHTML += "<div class='container'>";
  configHTML += "<div class='row'>";
  configHTML += "<div class='col-md-12 pt-5 pb-3' style='text-align:center'>";
  configHTML += "<h1>WiFi config</h1><small>CSGO LIGHT</small>";
  configHTML += "</div>";
  configHTML += "</div>";
  configHTML += "</div>";
  configHTML += "<div class='row'>";
  configHTML += "<div class='col-md-6' style='margin:0 auto'>";
  configHTML += "<div class='form-group'>";
  configHTML += "<form method='POST' action='/config'>";
  configHTML += "<label for='red'>SSID</label>";
  configHTML += "<input class='form-control' type='text' name='ssid'><br>";
  configHTML += "<label for='grn'>PASSWORD</label>";
  configHTML += "<input class='form-control' type='password' name='pwd'><br>";
  configHTML += "<button type='submit' class='btn btn-primary' style='margin:0 auto; display:block; width:150px'>SEND</button>";
  configHTML += "</form>";
  configHTML += "</div>";
  configHTML += "</div>";
  configHTML += "</div>";
  configHTML += "</body></html>";
  return configHTML;
}

String getSetHTML(String r, String g, String b, String bri)
{
  String testingHTML = "";

  testingHTML += "<html><head><link href='https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css' rel='stylesheet' integrity='sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T' crossorigin='anonymous'><script src='https://code.jquery.com/jquery-3.4.1.min.js' integrity='sha256-CSXorXvZcTkaix6Yvo6HppcZGetbYMGWSFlBw8HfCJo=' crossorigin='anonymous'></script> <script src='https://cdnjs.cloudflare.com/ajax/libs/axios/0.19.0/axios.js'></script></head><body>";
  testingHTML += "<div class='container'>";
  testingHTML += "<div class='row'>";
  testingHTML += "<div class='col-md-12 pt-5 pb-3' style='text-align:center'>";
  testingHTML += "<h1>Light control</h1><small>CSGO LIGHT</small>";
  testingHTML += "<h5 class='pt-5'>Red: <b>"+r+"</b>, Green: <b>"+g+"</b>, Blue: <b>"+b + "</b>, Brightness: <b>" + bri+"</b></h5>";
  testingHTML += "</div>";
  testingHTML += "</div>";
  testingHTML += "</div>";
  testingHTML += "<div class='row'>";
  testingHTML += "<div class='col-md-6' style='margin:0 auto'>";
  testingHTML += "<div class='form-group'>";
  testingHTML += "<form method='POST' action='/set'>";
  testingHTML += "<label for='red'>Red</label>";
  testingHTML += "<input id='red' type='range' min='0' max='255' value='"+ r + "' class='form-control-range' name='red'><br>";
  testingHTML += "<label for='grn'>Green</label>";
  testingHTML += "<input id='grn' type='range' min='0' max='255' value='"+ g + "' class='form-control-range' name='grn'><br>";
  testingHTML += "<label for='blu'>Blue</label>";
  testingHTML += "<input id='blu' type='range' min='0' max='255' value='"+ b + "' class='form-control-range' name='blu'><br>";
  testingHTML += "<label for='bri'>Brightness</label>";
  testingHTML += "<input id='bri' type='range' min='0' max='255' value='"+ bri + "' class='form-control-range' name='bri'><br>";
  testingHTML += "<button type='submit' class='btn btn-primary' style='margin:0 auto; display:block; width:150px'>SEND</button>";
  testingHTML += "</form>";
  testingHTML += "</div>";
  testingHTML += "</div>";
  testingHTML += "</div>";
  //testingHTML += "<script>$(function() { var red = document.getElementById('red'); red.addEventListener('click', send);var grn = document.getElementById('grn'); grn.addEventListener('click', send);var blu = document.getElementById('blu'); blu.addEventListener('click', send);var bri = document.getElementById('bri'); bri.addEventListener('click', send);function send(){axios.get('/set', {red:red.value,grn:grn.value,blu:blu.value, bri:bri.value});} });</script>";
  testingHTML += "</body></html>";

  return testingHTML;
}
