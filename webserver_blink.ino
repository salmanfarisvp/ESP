#include <ESP8266WiFi.h>
 
const char* ssid = "salfar";
const char* password = "salfarhome4";
 
int ledPin = 13; // GPIO13
WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
 
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
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
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
 
  // Match the request
 
  int value = LOW;
  if (request.indexOf("/LED=ON") != -1)  {
    digitalWrite(ledPin, HIGH);
    value = HIGH;
  }
  if (request.indexOf("/LED=OFF") != -1)  {
    digitalWrite(ledPin, LOW);
    value = LOW;
  }
 
// Set ledPin according to the request
//digitalWrite(ledPin, value);
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.print("<body style='background: #00979C'>");
  client.println("<h1 align ='center'>");
  client.println("<font-color='red'>");
  client.println("FoxLab");
  client.println("</font>");
  client.println("</h1>");

  client.println("<bg color ='#00ff00'>");
  client.println("</bg>");

  client.println("<p align ='center'>");
  client.print("Led is Now: ");
  client.println("</p>");
 
  if(value == HIGH) {
    client.println("<p align ='center'>");
    client.print("On");
    client.println("</p>");
  } else {
    client.println("<p align ='center'>");
    client.print("Off");
    client.println("</p>");
  }
  client.println("<br><br>");
  client.println("<p align ='center'>");
  client.println("<a  href=\"/LED=ON\"\"><button>Turn On </button></a>");
  client.println("<a  href=\"/LED=OFF\"\"><button>Turn Off </button></a><br />");  
  client.println("</p>");
  client.println("<p>");
  client.println("<marquee direction='right'>");
  client.println("Developed by Salman Faris ");
  client.println("</marquee>");
  client.println("</p>");
  client.println("</body>");
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}
 
