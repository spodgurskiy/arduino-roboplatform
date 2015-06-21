#include <dht11.h>
dht11 DHT11;
#define DHT11PIN 2

void setup(){
  Serial.begin(115200);
  Serial.println("DHT11 TEST PROGRAM ");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHT11LIB_VERSION);
  Serial.println();
}

void loop(){
  Serial.print("\n");
  reportSensor(2);
  reportSensor(3);
  reportSensor(4);
  delay(2000);
}

void reportSensor(int port){
  Serial.print("\n");
  int chk = DHT11.read(port);
  Serial.print("Status, Humidity, Temperature: ");
  switch (chk)
  {
    case DHTLIB_OK: 
    Serial.print("OK "); 
    break;
    case DHTLIB_ERROR_CHECKSUM: 
    Serial.print("Checksum error "); 
    break;
    case DHTLIB_ERROR_TIMEOUT: 
    Serial.print("Time out error "); 
    break;
    default: 
    Serial.print("Unknown error "); 
    break;
  }
  
  Serial.print((float)DHT11.humidity, 2);
  Serial.print("/");
  Serial.print((float)DHT11.temperature, 2);
}
//
// END OF FILE

