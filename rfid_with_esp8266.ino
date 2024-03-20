#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "HTTPSRedirect.h"
#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>
PN532_I2C pn532_i2c(Wire);
// int ledpin1 = D5;
// int ledpin2 = D6;
NfcAdapter nfc = NfcAdapter(pn532_i2c);
String tagId1 = "FA 5F 99 1A";
String tagId2= "39 0B B6 B0";
String tagId = "None";
byte nuidPICC[4];



// Enter network credentials:
const char* ssid     = "Lucerfan";
const char* password = "erfan_m1383";

// Enter Google Script Deployment ID:
const char *GScriptId = "AKfycby3o0voFb1YA4voIMcL9oC3iDWXYdOscl-w0u8fOQLO3EohFxk5YSSiIfqbWbfsBWeJ";

// Enter command (insert_row or append_row) and your Google Sheets sheet name (default is Sheet1):
String payload_base =  "{\"command\": \"insert_row\", \"sheet_name\": \"Sheet1\", \"values\": ";
String payload = "";

// Google Sheets setup (do not edit)
const char* host = "script.google.com";
const int httpsPort = 443;
const char* fingerprint = "";
String url = String("/macros/s/") + GScriptId + "/exec";
HTTPSRedirect* client = nullptr;

// Declare variables that will be published to Google Sheets
String user = "";
String id = "";
String enter ="";

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void setup() {

  Serial.begin(9600);        

  Serial.println('\n');
  // pinMode(ledpin1,OUTPUT);
  // pinMode(ledpin2,OUTPUT);
  Serial.println("System initialized");

  nfc.begin();
  // digitalWrite(ledpin1, LOW);
  // digitalWrite(ledpin2, LOW);
  // Connect to WiFi
  WiFi.begin(ssid, password);             
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());

  // Use HTTPSRedirect class to create a new TLS connection
  client = new HTTPSRedirect(httpsPort);
  client->setInsecure();
  client->setPrintResponseBody(true);
  client->setContentTypeHeader("application/json");
  
  Serial.print("Connecting to ");
  Serial.println(host);

  // Try to connect for a maximum of 5 times
  bool flag = false;
  for (int i=0; i<5; i++) { 
    int retval = client->connect(host, httpsPort);
    if (retval == 1) {
       flag = true;
       Serial.println("Connected");
       break;
    }
    else
      Serial.println("Connection failed. Retrying...");
  }
  if (!flag){
    Serial.print("Could not connect to server: ");
    Serial.println(host);
    return;
  }
  delete client;    // delete HTTPSRedirect object
  client = nullptr; // delete HTTPSRedirect object

display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  delay(2000);
  display.clearDisplay();
  display.setTextColor(WHITE);
  delay(10);
  
}


void loop() {

  // create some fake data to publish
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 10);
  display.print("Waiting..."); 
  display.display();

  readNFC();
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 10);
  display.print("Success"); 
  display.display();
  if(tagId==tagId1) {    
    // if( digitalRead(ledpin1) == 0) {
      // digitalWrite(ledpin1, HIGH);
      user="Fahad";
      id="123";
      enter="in";
      updatesheet(user,id, enter);
      tagId = "";
      delay(1000);
    // }
  }

  if(tagId==tagId1) {
    // if( digitalRead(ledpin1) == 1) {
      // digitalWrite(ledpin1, LOW);
      enter="";
      user="Fahad";
      id="123";
      enter="out";
      updatesheet(user,id, enter);

      tagId = "";
      delay(1000);
    // }

  }
      
  if(tagId==tagId2) {

    // if( digitalRead(ledpin2) == 0) {
      // digitalWrite(ledpin2, HIGH);
      user="";
      id="";
      enter="";
      user="Fawad";
      id="456";
      enter="in";
      updatesheet(user,id, enter);

      tagId = "";
      delay(1000);
    // }
  }

  if(tagId==tagId2) {
    // if( digitalRead(ledpin2) == 1) {
      // digitalWrite(ledpin2, LOW);
       user="Fawad";
      id="456";
      enter="out";
      updatesheet(user,id, enter);

      tagId = "";
      delay(1000);
    // }
  }
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
  delay(5000);
  }

void readNFC() {
  if (nfc.tagPresent()) {
    NfcTag tag = nfc.read();
    tag.print();
    tagId = tag.getUidString();
    Serial.println("Tag id");
    Serial.println(tagId);
  }
  delay(1000);
}
