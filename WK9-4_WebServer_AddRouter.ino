#include "WiFi.h"
#include "WebServer.h"

// SSID & Password
const char* ssid = "全聯福利中心";
const char* password = "12345678";

WebServer server(80);  // Object of WebServer(HTTP port, 80 is defult)

void setup() {
  Serial.begin(115200);
  Serial.println("Try Connecting to ");
  Serial.println(ssid);
  pinMode(12,INPUT);
  pinMode(13,INPUT);

  // Connect to your wi-fi modem
  WiFi.begin(ssid, password);

  // Check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("");
  Serial.println("WiFi connected successfully");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());  //Show ESP32 IP on serial

  //建立server的路徑
  createWebServer();
  
  //server啟動
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();  //handleClient要寫在loop
}

//----設定HTML資料----
String htmlContent = "\
  <!DOCTYPE html>\
   <html>\
    <head>\
      <style>\
        body{ display: flex; flex-direction: column;}\
        a { background: #CEF2F4; width: 200px; height: 50px; margin: 20px; font-size: 30pt; text-decoration: none;}\
      </style>\
    </head>\
    <body>\
      <a href='/led/on'>LED ON</a>\
      <a href='/led/off'>LED OFF</a>\
    </body>\
  </html>";

//------設定路徑------
void createWebServer()
{
  //初始頁面
  server.on("/", []() {
      server.send(200, "text/html", htmlContent);
  });
  server.on("/led/on", []() {
    Serial.println("LED On");
    digitalWrite(12,HIGH);
    digitalWrite(13,HIGH);
    String response = "{\"LED On Success\"}";
    server.send(200, "application/json", response);
  });
  server.on("/led/off", []() {
    Serial.println("LED Off");
    digitalWrite(12,LOW);
    digitalWrite(13,LOW);
    String response = "{\"LED Off Success\"}";
    server.send(200, "application/json", response);
  });
}
