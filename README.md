# NFC Tag Detection and Google Spreadsheet Logging

Project to detect NFC tag card, read its content, distinguish between users, and log details on Google Spreadsheet.

### Contents:

* [Introduction](#Introduction)
* [Hardware Components](#Hardware-Components)
  * [NFC Module with ESP8266](#NFC-Module-with-ESP8266)
  * [16x2 LCD with I2C Interface](#16x2-LCD-with-I2C-Interface)
  * [Mifare Classic Tag](#Mifare-Classic-Tag)
  * [Additional Components](#Additional-Components)
* [Software Setup](#Software-Setup)
  * [Installing Libraries](#Installing-Libraries)
  * [Configuring ESP8266](#Configuring-ESP8266)
* [Reading NFC Tag](#Reading-NFC-Tag)
* [User Identification](#User-Identification)
* [Logging Details](#Logging-Details)
* [Google Spreadsheet Integration](#Google-Spreadsheet-Integration)
* [Conclusion](#Conclusion)

## Introduction

This project aims to create an attendance system using Near Field Communication (NFC) technology integrated with an ESP8266 microcontroller, a 16x2 LCD with I2C interface, and a Mifare Classic Tag. The system will detect the NFC tag, read its content, determine if the ID belongs to a specific person (e.g., Erfan or Hossein), and then log the attendance details onto a Google Spreadsheet.

## Hardware Components

Details of the hardware components used in the project.

### NFC Module with ESP8266

The NFC module is used to read NFC tags. It is integrated with the ESP8266 microcontroller, a powerful and low-cost Wi-Fi module. The key specifications of the ESP8266 module are:
- Model: ESP8266MOD
- ISM 2.4GHz
- PA +25dBm
- Supports 802.11b/g/n Wi-Fi standards

The NFC Module V3 uses the I2C protocol instead of SPI or HSU, making it easier to connect with the ESP8266.

### 16x2 LCD with I2C Interface

The 16x2 C0421A LCD module is used to display messages and information. It is interfaced using the I2C protocol through the NXD PCF85741 I2C module, which reduces the number of pins required for connection to the microcontroller.

### Additional Components

- Two breadboards for creating the circuit.
- Jumper wires for connections between the components.
- A USB Type-A cable for powering the ESP8266 and for serial communication with a computer.

### Mifare Classic Tag

Overview of the Mifare Classic tag and its usage.

## Software Setup

Configuration and setup of required software components.

### Installing Libraries

Instructions for installing necessary libraries.

### Configuring ESP8266

Steps to configure ESP8266 for NFC tag detection.

## Reading NFC Tag

Code snippets for reading NFC tag content.

## User Identification

Algorithm for distinguishing between users based on tag ID.

## Logging Details

Implementation of logging details functionality.

## Google Spreadsheet Integration

Guide for integrating with Google Spreadsheet for logging.

## Conclusion

Summary and final thoughts.
