#include <LiquidCrystal_I2C.h>

class Display
{
    public:
        int UpWordThreshold = 3;
        int DownWordThreshold = 10;
        String upWord = "Waiting";
        String downWord = "close your card";
        // set the LCD address to 0x27 for a 16 chars and 2 line display
        LiquidCrystal_I2C lcd;
        bool isPend;
        int k;
        
        Display(bool ispend) : lcd(0x27, 16, 2) {
            this->isPend = ispend;
        }

        void initialize() {
            lcd = LiquidCrystal_I2C(0x27, 16, 2);
            lcd.init();
            lcd.clear();
            lcd.backlight();      // Make sure backlight is on
        }

        void pend ()
        {
            // Print a message on both lines of the LCD.
            lcd.setCursor(UpWordThreshold , 0);   //Set cursor to character 2 on line 0
            lcd.print(upWord);
            lcd.setCursor(0 , 1);
            lcd.print("                ");
            // Access each character in the string using indexing
            for (int j = 0; j < downWord.length(); ++j) 
            {
                k = j % 4;
                //print dots of Waiting
                if (DownWordThreshold + k == DownWordThreshold + 3) {
                lcd.setCursor(DownWordThreshold, 0);
                lcd.print("     ");
                }
                else {
                lcd.setCursor(DownWordThreshold + k, 0);
                lcd.print(".");
                delay(100);
                }
                // Print each character
                lcd.setCursor(j , 1);
                lcd.print(downWord[j]);
                delay(100);
            }
            delay(100);

        }

        void successIN(String username, String status)
        {
            upWord = "Welcome";
            downWord = "  " + username + "   #" + status;

            // Print a message on both lines of the LCD.
            lcd.setCursor(UpWordThreshold , 0);   //Set cursor to character 2 on line 0
            lcd.print(upWord);
            lcd.setCursor(0 , 1);
            lcd.print("                ");
            // Access each character in the string using indexing
            for (int j = 0; j < downWord.length(); ++j) 
            {
                k = j % 4;
                //print dots of Waiting
                if (DownWordThreshold + k == DownWordThreshold + 3) {
                lcd.setCursor(DownWordThreshold, 0);
                lcd.print("     ");
                }
                else {
                lcd.setCursor(DownWordThreshold + k, 0);
                lcd.print("!");
                delay(100);
                }
                // Print each character
                lcd.setCursor(j , 1);
                lcd.print(downWord[j]);
                delay(100);
            }
            delay(100);
        }

        void successOUT(String username, String status)
        {
            upWord = "See You Later;)";
            downWord = "  " + username + "   #" + status;
            UpWordThreshold = 1;

            // Print a message on both lines of the LCD.
            lcd.setCursor(UpWordThreshold , 0);   //Set cursor to character 2 on line 0
            lcd.print(upWord);
            lcd.setCursor(0 , 1);
            lcd.print("                ");
            // Access each character in the string using indexing
            for (int j = 0; j < downWord.length(); ++j) 
            {
                k = j % 2;
                //print dots of Waiting
                if (DownWordThreshold + k == DownWordThreshold + 3) {
                lcd.setCursor(DownWordThreshold, 0);
                lcd.print("     ");
                }
                // else {
                // lcd.setCursor(DownWordThreshold + k, 0);
                // lcd.print();
                // delay(100);
                // }
                // Print each character
                lcd.setCursor(j , 1);
                lcd.print(downWord[j]);
                delay(100);
            }
            delay(100);
        }

};
