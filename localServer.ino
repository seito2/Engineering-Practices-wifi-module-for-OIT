#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char *ssid = "robot02";
const char *password = "robot02";

const int LED_PIN = 12;

ESP8266WebServer server(80);

static const char *cpResponse200 = "<HTML><BODY style='font-size:48px;'>ESP_HTTPD_LED1<br/><br/>"
                                   "<br/><a href=/?LED=on>on</a><br/><a href=/?LED=off>off</a><br/>"
                                   "</BODY></HTML>\r\n";


void connectServerToOn() {
  digitalWrite(LED_PIN, HIGH);
  server.send(200, "text/html", cpResponse200);
}

void connectServerToOff() {
  digitalWrite(LED_PIN, LOW);
  server.send(200, "text/html", cpResponse200);
}

void setup() {
  delay(1000);
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());
  server.on("/on", connectServerToOn);
  server.on("/off", connectServerToOff);

  server.begin();
}

void loop() {
  server.handleClient();
}