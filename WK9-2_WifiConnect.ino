#include "WiFi.h"

//輸入你的SSID/password
const char* ssid = "全聯福利中心";
const char* password = "12345678";
 
void setup() {
  Serial.begin(115200);
  
  Serial.println("Try Connecting to ");
  Serial.println(ssid);

  // Connect to your wi-fi modem
  WiFi.begin(ssid, password);

  // Check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected successfully");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());  //Show ESP32 IP on serial
}

void loop(){
  
}
