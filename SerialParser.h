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

public:
    static bool run(char *cmd, long &code);
    static void setFeedbackEnable(bool enable);
    static void setAllowEmptyCode(bool enable);
};

#endif
