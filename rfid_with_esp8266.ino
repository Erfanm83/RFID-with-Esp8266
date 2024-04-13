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
//added
#include <LiquidCrystal_I2C.h>

PN532_I2C pn532_i2c(Wire);
// int ledpin1 = D5;
// int ledpin2 = D6;
NfcAdapter nfc = NfcAdapter(pn532_i2c);
// Primitive Values
String tagId1 = "69 C9 D2 35";
String tagId2= "39 0B B6 B0";
String tagId = "None";
byte nuidPICC[4];
bool isPend = false;
bool IN = false;
bool IN2 = false;

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

Display display(isPend);

void setup() {

  Serial.begin(9600);        

  Serial.println('\n');
  display.initialize();
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
  
}


void loop() {

    if(readNFC()) {

        if (tagId==tagId1) {
            if (IN) {
                // if( digitalRead(ledpin1) == 1) {
                // digitalWrite(ledpin1, LOW);
                enter="";
                user="Erfan";
                id="123";
                enter="out";
                IN = false;
                updatesheet(user,id, enter);
                display.successOUT(user, enter);
                tagId = "";
                delay(1000);
              // }

            } else {
                // if( digitalRead(ledpin1) == 0) {
                // digitalWrite(ledpin1, HIGH);
                user="Erfan";
                id="123";
                enter="in";
                IN = true;
                updatesheet(user,id, enter);
                tagId = "";
                display.successIN(user, enter);
                delay(1000);
              // }
            }
        } else {
            if (IN2) {
                // if( digitalRead(ledpin2) == 1) {
                // digitalWrite(ledpin2, LOW);
                user="Hossein";
                id="456";
                enter="out";
                IN2 = false;
                updatesheet(user,id, enter);
                display.successOUT(user, enter);
                tagId = "";
                delay(1000);
              // }
            } else {
                // if( digitalRead(ledpin2) == 0) {
                // digitalWrite(ledpin2, HIGH);
                user="";
                id="";
                enter="";
                user="Hossein";
                id="456";
                enter="in";
                IN2 = true;
                updatesheet(user,id, enter);
                display.successIN(user, enter);
                tagId = "";
                delay(1000);
              // }
            }
        }
    }
    else 
        display.pend();
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

bool readNFC() {
  if (nfc.tagPresent()) {
    NfcTag tag = nfc.read();
    tag.print();
    tagId = tag.getUidString();
    Serial.println("Tag id");
    Serial.println(tagId);
    delay(1000);
    return true;
  }
  return false;
}
