#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>

const char *ssid = "robot02";
const char *password = "robot02";

const int LED_PIN = 12;

ESP8266WebServer server(80);

static const char *cpResponse400 = "<HTML><BODY>Bad request</BODY></HTML>\r\n";
static const char *cpResponse200 = "<HTML><BODY style='font-size:48px;'>ESP_HTTPD_LED1<br/><br/>"
                                   "<br/><a href=/?LED=on>on</a><br/><a href=/?LED=off>off</a><br/>"
                                   "</BODY></HTML>\r\n";

enum led_style {
  led_off = 0,
  led_on = 1,
};

static enum led_style led = led_off;

void handleCommand() {
  String cmd = server.arg("LED");
  if (cmd == "on") {
    led = led_on;
  }
  else if (cmd == "off") {
    led = led_off;
  }
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
  server.on("/", handleCommand);

  server.begin();
}

void loop() {
  server.handleClient();
  if (led == led_on) {
    digitalWrite(LED_PIN, HIGH);
  }
  else {
    digitalWrite(LED_PIN, LOW);
  }
}