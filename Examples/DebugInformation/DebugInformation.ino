/*
 * Gui va nhan du lieu theo FORMAT: <cmd><space><code><enter>
 * Khi nhan duoc thong tin tuong ung "FUNCTION_NAME" thi ta se thuc hien lenh "do something"
 */

#include <Arduino.h>
#include <SerialParser.h>

char cmd[20];
long code;

void setup()
{
    Serial.begin(115200);
    SerialParser::setFeedbackEnable(true);
}
void loop()
{
    // Template: <cmd><space><code><enter>
    if (SerialParser::run(cmd, code))
    {
        if (!strcmp(cmd, "FUNCTION_NAME"))
        {
            // do something
        }
    }
}
