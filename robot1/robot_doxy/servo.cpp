#include <cantino.h>

#include "servo.h"

using namespace cantino;

Servo::Servo (char *aName, int pinIndex, int aMin, int aMax, int initial, int offset, bool invert):
    aName (aName), pinIndex (pinIndex), aMin (aMin), aMax (aMax), initial (initial), offset (offset), invert (invert), angle (1000)
{
    standardServo.attach (pinIndex);
    rotateTo (initial);
}

Servo::rotateTo (int angle) {
    if (aMin <= angle && angle <= aMax && angle != this->angle) {
        this->angle = angle;
        cout << "Adjusting " << aName << " to " << this->angle << " degrees" << endl;
        standardServo.write ((invert ? -(this->angle + offset) : (this->angle + offset)) + 90);        
        delay (1000);
    }
    else {
        cout << "Keeping " << aName << " to " << this->angle << " degrees" << endl;        
    }
}
