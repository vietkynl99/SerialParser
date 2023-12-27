
#include "SerialParser.h"

#define DEFAULT_CODE_VALUE 0
#define STRING_LENGTH_LIMIT 64
#define USE_UPPER_CASE_CMD

bool SerialParser::mEnableFeedback = false;
bool SerialParser::mAllowEmptyCode = false;

bool SerialParser::run(String *cmd, long *value, String *valueStr)
{
    static unsigned long long time = 0;

    if (!Serial.available())
    {
        return false;
    }

    String buffer = "";
    while (1)
    {
        if (millis() > time)
        {
            time = millis() + SERIAL_READ_DELAY_TIME;
            char ch = Serial.read();
            if (ch == '\n')
            {
                break;
            }
            else if (buffer.length() < STRING_LENGTH_LIMIT)
            {
                buffer += ch;
            }
        }
    }
    trim(buffer);
    if (buffer.length() <= 0)
    {
        return false;
    }

    bool ret = false;
    int index = buffer.indexOf(' ');
    if (index <= 0)
    {
        if (mAllowEmptyCode)
        {
            *cmd = buffer;
            *value = DEFAULT_CODE_VALUE;
            if (valueStr)
            {
                *valueStr = "";
            }
            ret = true;
        }
    }
    else
    {
        String str1 = buffer.substring(0, index);
        String str2 = buffer.substring(index + 1);
        trim(str1);
        trim(str2);
        if (str1.length() > 0 && str2.length() > 0)
        {
            long longValue = str2.toInt();
            if (!(longValue == 0 && !str1.equals("0")))
            {
                *cmd = str1;
                *value = longValue;
                if (valueStr)
                {
                    *valueStr = str2;
                }
                ret = true;
            }
            else if (valueStr)
            {
                *cmd = str1;
                *value = DEFAULT_CODE_VALUE;
                *valueStr = str2;
                ret = true;
            }
        }
    }

#ifdef USE_UPPER_CASE_CMD
    if (ret)
    {
        cmd->toUpperCase();
    }
#endif

    if (mEnableFeedback)
    {
        if (ret)
        {
            Serial.print(F("[SERIAL] Cmd: '"));
            Serial.print(*cmd);
            Serial.print(F("', value: '"));
            if (valueStr && valueStr->length() > 0)
            {
                Serial.print(*value);
                Serial.print(F("', valueStr: '"));
                Serial.print(*valueStr);
                Serial.println("'");
            }
            else
            {
                Serial.print(*value);
                Serial.println("'");
            }
        }
        else
        {
            Serial.print(F("[SERIAL] Error: '"));
            Serial.print(buffer);
            Serial.println("'");
        }
    }
    return ret;
}

bool SerialParser::run(String *cmd, long *value)
{
    return run(cmd, value, nullptr);
}

void SerialParser::setFeedbackEnable(bool enable)
{
    mEnableFeedback = enable;
}

void SerialParser::setAllowEmptyCode(bool enable)
{
    mAllowEmptyCode = enable;
}

void SerialParser::trim(String &str)
{
    while (str.length() > 0 && (str.indexOf(' ') == 0 || str.indexOf('\r') == 0 || str.indexOf('\n') == 0))
    {
        str = str.substring(1);
    }
    while (str.length() > 0 && (str.lastIndexOf(' ') == str.length() - 1 || str.lastIndexOf('\r') == str.length() - 1 || str.lastIndexOf('\n') == str.length() - 1))
    {
        str = str.substring(0, str.length() - 1);
    }
}