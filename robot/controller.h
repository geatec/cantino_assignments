#pragma once

#include <Servo.h>

struct Command {
    int baseAngle, upperAngle, lowerAngle, fingerAngle;
};

class Controller {
    public:
        virtual Command getCommand () = 0;
};

class ConsoleController: public Controller {
    public:
        Command getCommand ();
};

class SequenceController: public Controller {
    public:
        SequenceController ();
        Command getCommand ();
    private:
        int baseAngle, upperAngle, lowerAngle, fingerAngle;
};

