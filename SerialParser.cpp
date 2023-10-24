
#include "SerialParser.h"

bool SerialParser::enableFeedback = false;

bool SerialParser::run(char *cmd, long &code)
{
    if (!Serial.available())
    {
        return false;
    }

    char buffer[32];
    int length = 0;

    while (Serial.available())
    {
        char ch = Serial.read();
        if (ch == '\n')
        {
            break;
        }
        else if (length < sizeof(buffer) - 1)
        {
            if (ch >= 'a' && ch <= 'z')
            {
                ch -= 32;
            }
            buffer[length] = ch;
            length++;
        }
        delay(SERIAL_READ_DELAY_TIME);
    }

    if (length <= 0)
    {
        return false;
    }

    buffer[length] = '\0';
    int ret = sscanf(buffer, "%s %ld", cmd, &code);
    if (ret != 2)
    {
        if (enableFeedback)
        {
            Serial.print(F("[SERIAL] Error: "));
            Serial.println(buffer);
        }
        return false;
    }
    else
    {
        if (enableFeedback)
        {
            Serial.print(F("[SERIAL] Cmd:"));
            Serial.print(cmd);
            Serial.print(F(", Code:"));
            Serial.println(code);
        }
        return true;
    }
}

void SerialParser::setFeedbackEnable(bool enable)
{
    enableFeedback = enable;
}