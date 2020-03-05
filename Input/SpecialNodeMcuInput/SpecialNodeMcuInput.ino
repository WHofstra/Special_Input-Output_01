//werkt met ArduinoJson library version 6.9.1
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <Servo.h> // servo library

const char* ssid     = "Medialab"; // wifi lan
const char* password = "Mediacollege"; // wifi lan
const char*  server  = "29980.hosts2.ma-cloud.nl"; // deployment server

String path          = "/test.json"; // path to file
static const uint8_t wifiConnecting = D1;//LED indicator wifi status flashing while connecting
static const uint8_t wifiOk = D2;//LED indicator wifi status ON if connected
//static const uint8_t servo1 = D3; //servo 1 op D3

boolean debug = true;// print debug messages to terminal
String httpResponse;// response from webserver

Servo servo1;// define servo
Servo servo2;// define servo

void setup() {
  Serial.begin(115200);// start serial monitor
  pinMode(wifiConnecting, OUTPUT);//LED indicator wifi status flashing while connecting
  pinMode(wifiOk, OUTPUT);//LED indicator wifi status ON if connected
  digitalWrite(wifiConnecting, LOW);//init off
  digitalWrite(wifiOk, LOW);//init off
  delay(10);
  //servo
  servo1.attach(D3);// servo on D3
  servo2.attach(D4);// servo on D4
}

void loop()
{
  if (WiFi.status() != WL_CONNECTED) wifiConnect();
  httpRequest();//get data from webserver
  
  if (debug) Serial.println(httpResponse);
  payload();//extract wanted data from HTTP response
  
  if (debug)Serial.println(httpResponse); //debug
  extractJson();
}

void parseJson(JsonObject& json_object) //parse the commands from the json object
{
  if (strcmp(json_object["device1"], "on") == 0) // ==0 is equal
  {
    Serial.print("device 1 on value => ");
    String range1Str = json_object["range1"];
    int range1 = map (range1Str.toInt(), 0, 1000, 0, 180);
    servo1.write(range1);
    Serial.println(range1Str);//debug

  }
  
  if (strcmp(json_object["device2"], "on") == 0) // ==0 is equal
  {
    Serial.print("device 2 on value => ");
    String range2Str = json_object["range2"];
    int range2 = map (range2Str.toInt(), 0, 1000, 0, 180);
    servo2.write(range2);
    Serial.println(range2Str);//debug
    //digitalWrite(D2, HIGH);
    //analogWrite(D2, range1);
  }
}

void extractJson()//extract JSON string from HTTP data
{
  int size = httpResponse.length() + 1;
  char json[size];
  httpResponse.toCharArray(json, size);
 StaticJsonBuffer<200> jsonBuffer;  // <===== oude lib
 // StaticJsonDocument<256> json_object; //<==== nieuwe lib
 JsonObject& json_object = jsonBuffer.parseObject(json);  // <===== oude lib
 // deserializeJson(json_object, json); // <==== nieuwe lib
 
  if (!json_object.success())
  {
    Serial.println("parseObject() failed");
    return;
  }
  parseJson(json_object);//parse the commands from the json object
  
}

void payload() // extract wanted data from HTTP response
{
  String endOfHeader = "\r\n\r\n";
  int foundEOH = -1;
  // look for EOH end of header
  for (int i = 0; i <= httpResponse.length() - endOfHeader.length(); i++)
  {
    if (httpResponse.substring(i, endOfHeader.length() + i) == endOfHeader)
    {
      foundEOH = i;
    }
  }
  httpResponse = httpResponse.substring(foundEOH);// strip the HTTP header
}

void httpRequest()// get HTTP response from webserver
{
  digitalWrite(wifiOk, LOW);//flash LED
  delay(2000);//time between requests
  digitalWrite(wifiOk, HIGH);//flash LED
  httpResponse = ""; //empty string
  WiFiClient client; //instance
  
  if (client.connect(server, 80)) { //connect to webserver on port 80
    client.println("GET " + path +  " HTTP/1.1");//construct a HTTP GET request
    client.println("Host: " + String(server));
    client.println("Connection: keep-alive");
    client.println();
  }
  else {
    Serial.println("Webserver does not respond");
    return;
  }
  
  while (client.connected()) {
    while (client.available()) {
      httpResponse += char(client.read());//mogelijk memory problemen
      
      if (httpResponse.length() > 450) {
        Serial.println("Receive buffer overflow");//prevent buffer overflow
        httpResponse = ""; //empty string
        return;
      }
    }
  }
}

void wifiConnect()// connect to local network
{
  int ledState = 0;//flasher
  digitalWrite(wifiOk, LOW);
  digitalWrite(wifiConnecting, HIGH);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (ledState == 0) ledState = 1;
    else ledState = 0;
    digitalWrite(wifiConnecting, ledState);
  }
  
  Serial.println("");
  Serial.print("WiFi connected, IP address: " + WiFi.localIP());
  
  if (debug) WiFi.printDiag(Serial); // print Wi-Fi diagnostic information
  digitalWrite(wifiConnecting, LOW);
  digitalWrite(wifiOk, HIGH);
}
