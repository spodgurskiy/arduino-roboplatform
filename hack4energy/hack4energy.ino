#include <dht11.h>
#include <SPI.h>
#include <Ethernet.h>
dht11 DHT11;

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
//char server[] = "192.168.0.77:8080";
char server[] = "web-manufacture.net";    
IPAddress ip(192, 168, 0, 177);
EthernetClient client;

void setup(){
  Serial.begin(115200);
  Serial.println("web-manufacture compatible");

  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    Ethernet.begin(mac, ip);
  }
}

void loop(){
  if (!client.connected()){
    connect();
  }else{
    client.println(reportSensor(2));
  }

//  Serial.print("\n");
//  reportSensor(2);
//  reportSensor(3);
//  reportSensor(4);
  delay(2000);
}

int reportSensor(int port){
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
  return DHT11.temperature;
}

void connect(){
  delay(1000);
  Serial.println("connecting...");

  if (client.connect(server, 4000)) {
    Serial.println("connected");
    client.println(0x1A01FC03);
  } else {
    Serial.println("connection failed");
  }
}
//
// END OF FILE


