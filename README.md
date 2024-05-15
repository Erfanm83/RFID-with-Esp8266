# NFC Attendance System Project Overview

## Introduction
This project aims to create an attendance system using Near Field Communication (NFC) technology integrated with an ESP8266 microcontroller, a 16x2 LCD with I2C interface, and a Mifare Classic Tag. The system will detect the NFC tag, read its content, determine if the ID belongs to a specific person (e.g., Erfan or Hossein), and then log the attendance details onto a Google Spreadsheet. 

## Components Used
- ESP8266 microcontroller with NFC module
- 16x2 LCD with I2C interface
- Mifare Classic NFC Tag
- Google Spreadsheet API for logging attendance details

## Project Workflow

1. **Initialization and Setup**
    - Set up the ESP8266 microcontroller with the necessary libraries for NFC communication and connecting to the internet.
    - Initialize the LCD and connect it to the microcontroller using the I2C interface.
    - Set up authentication for accessing the Google Spreadsheet API.

2. **Reading NFC Tag**
    - Continuously monitor the NFC module for the presence of a tag.
    - When a tag is detected, read its content.

3. **Tag Content Verification**
    - Check if the ID extracted from the NFC tag belongs to Erfan, Hossein, or anyone else.
    - This step may involve comparing the ID against predefined lists or databases.

4. **Attendance Logging**
    - Based on the verification result, determine if the person is logging in or logging out.
    - Log the attendance details including timestamp, person's name, and action (login/logout) onto the Google Spreadsheet.

5. **Display Feedback on LCD**
    - Provide visual feedback on the LCD display to indicate successful tag detection and attendance logging.
    - Display relevant information such as the person's name and action (login/logout).

## Challenges and Considerations
- **NFC Communication**: Ensuring reliable communication between the NFC module and the microcontroller.
- **Data Verification**: Accurately verifying the tag content and mapping it to the correct person.
- **Internet Connectivity**: Maintaining a stable internet connection for logging attendance details onto the Google Spreadsheet.
- **Security**: Implementing measures to prevent unauthorized access or tampering with attendance records.

## Conclusion
By integrating NFC technology with an ESP8266 microcontroller and Google Spreadsheet API, this project creates an efficient and automated attendance system. The system provides a convenient way to track attendance and can be further expanded with additional features such as notifications and reporting.
