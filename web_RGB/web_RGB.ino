#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char* ssid = "Virus infected Wi-Fi!";
const char* password = "WF647241BB1";


int R = D3 ;//D3
int G = D2;//D2
int B = D4;//D4
WiFiServer Server(80);
 
void setup() 
{
Serial.begin(115200);
delay(10);

pinMode(R, OUTPUT);
pinMode(G, OUTPUT);
pinMode(B, OUTPUT);

digitalWrite(R,LOW);
digitalWrite(G,LOW);
digitalWrite(B,LOW);
//Connect to WiFi network
Serial.println();
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);

WiFi.begin(ssid,password);

while (WiFi.status() != WL_CONNECTED) 
{
  delay(500);
  Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");

//Start the server
Server.begin();
Serial.println("Server started");

//Print the IP address
Serial.print("Use this URL to connect:");
Serial.print("http://");
Serial.print(WiFi.localIP());
Serial.println("/");

}

void loop() {
//Check if a client has connected
WiFiClient client = Server.available();
if (!client){
  return;
}

//Wait until the clent sends some data
Serial.println("new client");
while(!client.available()){
  delay(1);
}

// Read the first line of the request
String request = client.readStringUntil('\r');
Serial.println(request);
client.flush();

//Match the request

int value1 = LOW;
int value2 = LOW;
int value3 = LOW;

if (request.indexOf("/RLED=ON") != -1) {
  digitalWrite(R, HIGH);
  value1 = HIGH;
}
if(request.indexOf("/RLED=OFF") != -1) {
  digitalWrite(R,LOW);
  value1 = LOW;
}

if (request.indexOf("/GREENLED=ON") != -1) {
  digitalWrite(G, HIGH);
  value2 = HIGH;
}
if(request.indexOf("/GREENLED=OFF") != -1) {
  digitalWrite(G,LOW);
  value2 = LOW;
}

if (request.indexOf("/BLUELED=ON") != -1) {
  digitalWrite(B, HIGH);
  value3 = HIGH;
}
if(request.indexOf("/BLUELED=OFF") != -1) {
  digitalWrite(B,LOW);
  value3 = LOW;
}
//Set ledPin according to the 
//digitalWrite(ledPin, Value);

//Return the response
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println(""); // do not forget this one
client.println("<!DOCTYPE HTML>");
client.println("<html>");

client.print("R LED is now : ");

if (value1 == HIGH) {
  client.print("On");
}else {
  client.print("Off");
}
  
client.println("<br><br>");
  client.println("<a href=\"/RLED=ON\"\"><button>Turn On </button></a>");
  client.println("<a href =\"/RLED=OFF\"\"><button>Turn Off </button></a><br/>");
  
  client.print("GREEN LED is now : ");
if (value2 == HIGH) {
  client.print("On");
}else {
  client.print("Off");
}
  client.println("<br><br>");
  client.println("<a href=\"/GREENLED=ON\"\"><button>Turn On </button></a>");
  client.println("<a href =\"/GREENLED=OFF\"\"><button>Turn Off </button></a><br/>");
  
  client.print("R LED is now : ");
if (value3 == HIGH) {
  client.print("On");
}else {
  client.print("Off");
}
  client.println("<br><br>");
  client.println("<a href=\"/BLUELED=ON\"\"><button>Turn On </button></a>");
  client.println("<a href =\"/BLUELED=OFF\"\"><button>Turn Off </button></a><br/>");
  client.println("</html>");

  delay(1);
 Serial.println("Client disconnected");
  Serial.println("");
  
}
