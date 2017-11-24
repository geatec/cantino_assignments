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
        static int const nrOfCommands = 13;
        int commands [nrOfCommands][4];
        int commandIndex;
        int baseAngle, upperAngle, lowerAngle, fingerAngle;
};

