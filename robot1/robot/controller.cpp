#include <cantino.h>

#include "controller.h"

using namespace cantino;

Command ConsoleController::getCommand () {
        Command command;
        cout << "base upper lower fingers: ";
        cin >> command.baseAngle >> command.upperAngle >> command.lowerAngle >> command.fingerAngle;  
        return command; 
}

SequenceController::SequenceController ():
    commands ({
        // base, upperarm, lowerarm, fingers
        {99, 99, 99, 90},
        {-45, 99, 99, 99},
        {99, 99, 50, 99},
        {99, 45, 99, 99},
        {99, 99, 99, 0},
        {99, 99, 0, 99},
        {99, 0, 99, 99},
        {45, 99, 99, 99},
        {99, 99, 50, 99},
        {99, 45, 99, 99},
        {99, 99, 99, 90},
        {99, 0, 99, 99},
        {99, 99, 0, 99}
    }),
    commandIndex (0)
{
    baseAngle = upperAngle = lowerAngle = fingerAngle = 1000;
}

Command  SequenceController::getCommand () {
    Command command;
    
    command.baseAngle = commands [commandIndex][0];
    command.upperAngle = commands [commandIndex][1];
    command.lowerAngle = commands [commandIndex][2];
    command.fingerAngle = commands [commandIndex][3];

    commandIndex = (commandIndex + 1) % nrOfCommands;
    return command;
}

