
#include "SerialParser.h"

#define DEFAULT_CODE_VALUE 0

bool SerialParser::mEnableFeedback = false;
bool SerialParser::mAllowEmptyCode = false;

bool SerialParser::run(char *cmd, long &code)
{
    static unsigned long long time = 0;

    if (!Serial.available())
    {
        return false;
    }

    char buffer[32];
    int length = 0;
    bool hasSpace = false;

    while (1)
    {
        if (millis() > time)
        {
            time = millis() + SERIAL_READ_DELAY_TIME;
            char ch = Serial.read();
            if (ch == ' ')
            {
                if (length == 0)
                {
                    continue;
                }
                else
                {
                    hasSpace = true;
                }
            }
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
        }
    }

    if (length <= 0)
    {
        return false;
    }

    buffer[length] = '\0';
    bool ret = false;
    if (sscanf(buffer, "%s %ld", cmd, &code) == 2)
    {
        ret = true;
    }
    else if (mAllowEmptyCode && !hasSpace && sscanf(buffer, "%s", cmd) == 1)
    {
        code = DEFAULT_CODE_VALUE;
        ret = true;
    }

    if (mEnableFeedback)
    {
        if (ret)
        {
            Serial.print(F("[SERIAL] Cmd:"));
            Serial.print(cmd);
            Serial.print(F(", Code:"));
            Serial.println(code);
        }
        else
        {
            Serial.print(F("[SERIAL] Error: "));
            Serial.println(buffer);
        }
    }
    return ret;
}

void SerialParser::setFeedbackEnable(bool enable)
{
    mEnableFeedback = enable;
}

void SerialParser::setAllowEmptyCode(bool enable)
{
    mAllowEmptyCode = enable;
}