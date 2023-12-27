/*
 * Gui va nhan du lieu theo FORMAT: <cmd><space><value><enter>
 * Khi nhan duoc thong tin tuong ung "FUNCTION_NAME" thi ta se thuc hien lenh "do something"
 */

#include <Arduino.h>
#include <SerialParser.h>

String cmd;
long value;
String valueStr;

void setup()
{
    Serial.begin(115200);
    SerialParser::setFeedbackEnable(true);
}

void loop()
{
    // Template: <cmd><space><value><enter>
    if (SerialParser::run(&cmd, &value, &valueStr))
    {
        if (cmd.equals("FUNCTION_NAME"))
        {
            // do something
        }
    }
}
