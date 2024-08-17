// Serial Parser Library
// VietKynl - 24/10/2023

#ifndef _SERIAL_PARSER_H_
#define _SERIAL_PARSER_H_

#include <Arduino.h>

#define SERIAL_READ_DELAY_TIME 2 // (ms) use 1ms when baudrate=115200

class SerialParser
{
private:
    static bool mEnableFeedback;
    static bool mAllowEmptyCode;
    static Stream *mStream;

public:
    static void setStream(const Stream *stream);
    static bool run(String *cmd, long *value, String *valueStr);
    static bool run(String *cmd, long *value);
    static void setFeedbackEnable(bool enable);
    static void setAllowEmptyCode(bool enable);

private:
    static void trim(String &str);
};

#endif
