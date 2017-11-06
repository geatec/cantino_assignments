#pragma once

#include <Servo.h>
typedef Servo StandardServo;
#define Servo BetterServo

class Servo {
    public:
        Servo (char *aName, int pinIndex, int aMin, int aMax, int initial, int offset, bool invert);
        rotateTo (int angle);
    private:
        StandardServo standardServo;
        char *aName;
        int pinIndex, aMin, aMax, initial, offset;
        bool invert;
        int angle;
};
