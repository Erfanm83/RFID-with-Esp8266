#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "HTTPSRedirect.h"
#include "Display.h"
#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>
#include <LiquidCrystal_I2C.h>

const char* ssid     = "hossein";
const char* password = "hossein122133@!";

const char *GScriptId = "AKfycby3o0voFb1YA4voIMcL9oC3iDWXYdOscl-w0u8fOQLO3EohFxk5YSSiIfqbWbfsBWeJ";
String payload_base =  "{\"command\": \"insert_row\", \"sheet_name\": \"Sheet1\", \"values\": ";
String payload = "";
const char* host = "script.google.com";
const int httpsPort = 443;
const char* fingerprint = "";
String url = String("/macros/s/") + GScriptId + "/exec";
HTTPSRedirect* client = nullptr;
String user = "";
String id = "";
String enter ="";

String tagId1 = "69 C9 D2 35";
String tagId2= "39 0B B6 B0";
String tagId = "None";
byte nuidPICC[4];
bool isPend = false;
bool IN = false;
bool IN2 = false;

String header;
String output5State = "off";
String output4State = "off";
const int pin5 = 14;
const int pin6 = 12;
unsigned long currentTime = millis();
unsigned long previousTime = 0; 
const long timeoutTime = 2000;

PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);
Display display(isPend);
WiFiServer server(80);

void setup() {
  Serial.begin(9600);        

  Serial.println();

  display.initialize();
  nfc.begin();
  WiFi.begin(ssid, password);             
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  pinMode(pin5, OUTPUT);
  pinMode(pin6, OUTPUT);
  digitalWrite(pin5, LOW);
  digitalWrite(pin6, LOW);

  server.begin();

  Serial.println("System initialized\n");
  Serial.println("********************\n");
}


void loop(){
  WiFiClient webClient = server.available();   // Listen for incoming clients

  if (webClient) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    while (webClient.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      currentTime = millis();         
      if (webClient.available()) {             // if there's bytes to read from the client,
        char c = webClient.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            webClient.println("HTTP/1.1 200 OK");
            webClient.println("Content-type:text/html");
            webClient.println("Connection: close");
            webClient.println();
            
            // Display the HTML web page
            webClient.println("<!DOCTYPE html><html>");
            webClient.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            webClient.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            webClient.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            webClient.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            webClient.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            webClient.println(".button2 {background-color: #77878A;}</style></head>");
            
            // Web Page Heading
            webClient.println("<body><h1>ESP8266 Web Server</h1>");
            
            // Display current state, and ON/OFF buttons for GPIO 5  
            webClient.println("<h3>ID : " + id + "</h3>");

            webClient.println("<p><a href=\"javascript:void(0)\" onclick=\"window.location.reload();\"><button class=\"button\">Update</button></a></p>");
            
            readNFC();

            webClient.println("<script>window.location.reload();</script>");
            webClient.println("</body></html>");
            
            // The HTTP response ends with another blank line
            webClient.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    webClient.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }

}


bool readNFC() {
  if (nfc.tagPresent()) {
    NfcTag tag = nfc.read();
    tag.print();

    id = tag.getUidString();
    Serial.print("Tag id : "); Serial.println(id);

    Serial.println("tag details :");
    String content = "";
    byte myByte[] = {0x00, 0xFF};
    tag.getUid(myByte, tag.getUidLength());
    for (int i = 0 ; i < tag.getUidLength(); i++){
      Serial.println(myByte[i]);
    }
    content.toUpperCase();
    Serial.println("********************\n\n");

    delay(1000);
    return true;
  }
  return false;
}


void updatesheet(String user, String id, String enter) {
  static bool flag = false;

  if (!flag) {
    client = new HTTPSRedirect(httpsPort);
    client->setInsecure();
    flag = true;
    client->setPrintResponseBody(true);
    client->setContentTypeHeader("application/json");
  }
  if (client != nullptr) {
    if (!client->connected()) {
      client->connect(host, httpsPort);
    }
  }
  else {
    Serial.println("Error creating client object!");
  }
  
  // Create json object string to send to Google Sheets
  payload = payload_base + "\"" + user + "," + id + "," + enter + "\"}";
  
  // Publish data to Google Sheets
  Serial.println("Publishing data...");
  Serial.println(payload);
  if(client->POST(url, host, payload)) {
    // do stuff here if publish was successful
  }
  else {
    // do stuff here if publish was not successful
    Serial.println("Error while connecting");
  }

  // a delay of several seconds is required before publishing again    
  delay(1000);
}