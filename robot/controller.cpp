#include <cantino.h>

#include "controller.h"

using namespace cantino;

Command ConsoleController::getCommand () {
        Command command;
        cout << "base upper lower fingers: ";
        cin >> command.baseAngle >> command.upperAngle >> command.lowerAngle >> command.fingerAngle;  
        return command; 
}

SequenceController::SequenceController () {
    baseAngle = upperAngle = lowerAngle = fingerAngle = 1000;
}

Command  SequenceController::getCommand () {
    Command command;
    
    fingerAngle += 90;
    if (fingerAngle > 90) {
        fingerAngle = 0;
        lowerAngle += 15;
        if (lowerAngle > -45) {
            lowerAngle = -90;
            upperAngle += 10;
            if (upperAngle > 40) {
                upperAngle = -10;
                baseAngle += 50;
                if (baseAngle > 50) {
                    baseAngle = -50;
                }
            }
        }
    }

    command.baseAngle = baseAngle;
    command.upperAngle = upperAngle;
    command.lowerAngle = lowerAngle;
    command.fingerAngle = fingerAngle;

    return command;
}

