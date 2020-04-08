#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <Wire.h>

const float MPU_GYRO_250_SCALE = 131.0;
const float MPU_GYRO_500_SCALE = 65.5;
const float MPU_GYRO_1000_SCALE = 32.8;
const float MPU_GYRO_2000_SCALE = 16.4;
const float MPU_ACCL_2_SCALE = 16384.0;
const float MPU_ACCL_4_SCALE = 8192.0;
const float MPU_ACCL_8_SCALE = 4096.0;
const float MPU_ACCL_16_SCALE = 2048.0;

const char* ssid      = "Medialab";
const char* password  = "Mediacollege";
const char* server    = "29980.hosts2.ma-cloud.nl";
const int MPU_addr    = 0x68; // I2C address of the MPU-6050
const int portNr      = 80;
const int docCapacity = JSON_OBJECT_SIZE(6);

String aPath         = "/bewijzenmap/SpIO/testGetPost.php";
String g             = "GET";
String gyroString    = "{}";
String httpResponse;

StaticJsonDocument<docCapacity> jsonDoc;
JsonObject jsonObj = jsonDoc.to<JsonObject>();

static const uint8_t wifiPin = D4; //Use D4-pin as Output

struct rawdata
{
  int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
};

struct scaleddata
{
  int AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
};

scaleddata sdValues;

void setup()
{
  Wire.begin();
  Serial.begin(115200); //Baud-rate: 115200
  
  mpu6050Begin(MPU_addr);
  pinMode(wifiPin, OUTPUT); //LED Indicates WiFi Connection
}

void loop()
{
  if (WiFi.status() != WL_CONNECTED) {
    wifiConnect();
  }
  setMPU6050scales(MPU_addr,0b00000000,0b00010000);
  sdValues = convertRawToScaled(MPU_addr, mpu6050Read(MPU_addr));
  jsonObj = addValuesToJsonDoc(&sdValues);

  Serial.println(jsonDoc.as<String>());
  
  delay(500);
}

//Wake Up MPU-6050
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
rawdata mpu6050Read(byte addr)
{
  rawdata values;
  
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  //Starting with Register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true);  //Request a Total of 14 Registers

  values.AcX = Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  values.AcY = Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  values.AcZ = Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  values.Tmp = Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  values.GyX = Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  values.GyY = Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  values.GyZ = Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  return values;
}

String addToJsonString(int16_t value, String valueName, String jsonString, bool lastValue)
{
  jsonString += ("\"" + valueName + "\":" + String(value));
  if (!lastValue) jsonString += ",";
  else jsonString += "}";
  
  return jsonString;
}

void setMPU6050scales(byte addr, uint8_t Gyro, uint8_t Accl)
{
  Wire.beginTransmission(addr);
  Wire.write(0x1B); // Write to Register Starting at 0x1B
  Wire.write(Gyro);
  Wire.write(Accl);
  Wire.endTransmission(true);
}

void getMPU6050scales(byte addr,uint8_t &Gyro,uint8_t &Accl)
{
  Wire.beginTransmission(addr);
  Wire.write(0x1B); // Starting with Register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(addr,2,true); // Request a Total of 14 Registers
  Gyro = (Wire.read()&(bit(3)|bit(4)))>>3;
  Accl = (Wire.read()&(bit(3)|bit(4)))>>3;
}

//Convert Raw  Data to Scaled Data
scaleddata convertRawToScaled(byte addr, rawdata data_in)
{
  scaleddata values;
  float scale_value = 0.0;
  byte Gyro, Accl;
 
  getMPU6050scales(MPU_addr, Gyro, Accl);
 
  switch (Gyro) {
    case 0: scale_value = MPU_GYRO_250_SCALE; break;
    case 1: scale_value = MPU_GYRO_500_SCALE; break;
    case 2: scale_value = MPU_GYRO_1000_SCALE; break;
    case 3: scale_value = MPU_GYRO_2000_SCALE; break;
    default:  break;
  }
 
  values.GyX = (float) data_in.GyX / scale_value;
  values.GyY = (float) data_in.GyY / scale_value;
  values.GyZ = (float) data_in.GyZ / scale_value;
  scale_value = 0.0;
  
  switch (Accl) {
    case 0: scale_value = MPU_ACCL_2_SCALE; break;
    case 1: scale_value = MPU_ACCL_4_SCALE; break;
    case 2: scale_value = MPU_ACCL_8_SCALE; break;
    case 3: scale_value = MPU_ACCL_16_SCALE; break;
    default:  break;
  }

  values.AcX = (float) data_in.AcX / scale_value;
  values.AcY = (float) data_in.AcY / scale_value;
  values.AcZ = (float) data_in.AcZ / scale_value;
  values.Tmp = (float) data_in.Tmp / 340.0 + 36.53;

  //gyroString = generateJson(gyroString, &values);
  return values;
}

String generateJson(String stringStart, scaleddata* val)
{
  //Generate Json-string from Values
  stringStart = "{";
  stringStart = addToJsonString(val->AcX, "AcX", stringStart, false);
  stringStart = addToJsonString(val->AcY, "AcY", stringStart, false);
  stringStart = addToJsonString(val->AcZ, "AcZ", stringStart, false);
  stringStart = addToJsonString(val->GyX, "GyX", stringStart, false);
  stringStart = addToJsonString(val->GyY, "GyY", stringStart, false);
  stringStart = addToJsonString(val->GyZ, "GyZ", stringStart, true);
  
  Serial.println(stringStart);
  return stringStart;
}

JsonObject addValuesToJsonDoc(scaleddata* val)
{
  jsonObj["AcX"] = val->AcX;
  jsonObj["AcY"] = val->AcY;
  jsonObj["AcZ"] = val->AcZ;
  jsonObj["GyX"] = val->GyX;
  jsonObj["GyY"] = val->GyY;
  jsonObj["GyZ"] = val->GyZ;

  return jsonObj;
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
