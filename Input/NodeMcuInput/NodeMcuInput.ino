#include <ESP8266WiFi.h>
#include <Wire.h>

const char* ssid     = "Medialab";
const char* password = "Mediacollege";
const char* server   = "29980.hosts2.ma-cloud.nl";
const int MPU_addr   = 0x68; // I2C address of the MPU-6050
const int portNr     = 80;

String aPath         = "/bewijzenmap/SpIO/testGetPost.php";
String g             = "GET";
String gyroString    = "{}";
String httpResponse;

static const uint8_t wifiPin = D4; //Use D4-pin as Output
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

void setup()
{
  Wire.begin();
  Serial.begin(115200); //Baud-rate: 115200
  
  mpu6050Begin(MPU_addr);
  pinMode(wifiPin, OUTPUT); //LED Indicates WiFi Connection
}

void loop()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    wifiConnect();
  }
  sendValues();
  httpRequest(aPath, g, gyroString);
}

void mpu6050Begin(byte addr)
{
  if (checkI2C(addr))
  {
    Wire.beginTransmission(addr);
    Wire.write(0x6B);  // PWR_MGMT_1 Register
    Wire.write(0);     // Set to 0 (Wakes up the MPU-6050)
    Wire.endTransmission(true);
    delay(30);
  }
}

bool checkI2C(byte addr)
{
  Wire.beginTransmission(addr);
  
  if (Wire.endTransmission() == 0)
  {
    Serial.print("Device found at 0x");
    Serial.println(addr, HEX);
    return true;
  }
  else
  {
    Serial.print("Device not found at 0x");
    Serial.println(addr, HEX);
    return false;
  }
}

//Assign Registers to Variables
void sendValues()
{
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  //Starting with Register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true);  //Request a Total of 14 Registers

  AcX = Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AcY = Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp = Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX = Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  //Generate Json-string from Values
  gyroString = "{";
  gyroString = addToJsonString(AcX, "AcX", gyroString, false);
  gyroString = addToJsonString(AcY, "AcY", gyroString, false);
  gyroString = addToJsonString(AcZ, "AcZ", gyroString, false);
  gyroString = addToJsonString(GyX, "GyX", gyroString, false);
  gyroString = addToJsonString(GyY, "GyY", gyroString, false);
  gyroString = addToJsonString(GyZ, "GyZ", gyroString, true);
  
  Serial.println(gyroString);
  delay(50);
}

String addToJsonString(int16_t value, String valueName, String jsonString, bool lastValue)
{
  jsonString += ("\"" + valueName + "\":" + String(value));
  if (!lastValue) jsonString += ",";
  else jsonString += "}";
  
  return jsonString;
}

//Connect to Local Network
void wifiConnect()
{
  int ledState = 0;
  digitalWrite(wifiPin, LOW);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
    if (ledState == 0) ledState = 1;
    else ledState = 0;
    digitalWrite(wifiPin, ledState);
  }
  
  Serial.print("WiFi connected, IP address: " + WiFi.localIP());
  WiFi.printDiag(Serial);
  digitalWrite(wifiPin, HIGH);
}

//Get HTTP Response from Server
void httpRequest(String path, String getFrom, String jsonString)
{
  httpResponse = "";
  WiFiClient client;

  //Connect to Webserver on Port 80
  if (client.connect(server, portNr))
  {
    client.println("GET " + path + "?" + getFrom  +"=" + jsonString + " HTTP/1.1");//construct a HTTP GET request
    client.println("Host: " + String(server));
    client.println("Connection: keep-alive");
    client.println();
  }
  else {
    Serial.println("Webserver does not respond.");
    return;
  }

  while (client.connected())
  {
    while (client.available())
    {
      httpResponse += char(client.read());
      //Serial.println(httpResponse);
      
      if (httpResponse.length() > 450) {
        httpResponse = ""; //Empty String
        return;
      }
    }
  }
}
