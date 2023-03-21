#include <Servo.h>
#include <ESP8266WiFi.h>

Servo myservo;

const char* ssid = "Av"; //nama wifi yang akan dihubungi
const char* password = "11111111"; //password wifi yang akan dihubungi

WiFiServer server(80);

void setup() {
  myservo.attach(5); //servo dihubungkan ke pin D1
  Serial.begin(115200);
  delay(10);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // If the request contains the keyword smile, move the servo
  if (request.indexOf("smile") != -1) {
    Serial.println("smile detected");
    myservo.write(90);
    delay(1000);
    myservo.write(0);
  }

  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.println("<title>ESP8266 Servo Control</title>");
  client.println("</head>");
  client.println("<body>");
  client.println("<h1>ESP8266 Servo Control</h1>");
  client.println("</body>");
  client.println("</html>");

  delay(1);
  Serial.println("Client disconnected");
}
