#include <cantino.h>

#include "servo.h"
#include "controller.h"

using namespace cantino;
    
int main () {   
    Serial.begin(9600);

    Servo baseServo ("base", 5, -90, 90, 0, 0, true);
    Servo upperArmServo ("upper", 7, -90, 90, 0, 0, false);
    Servo lowerArmServo ("lower", 4, -90, 90, 0, 0, true);
    Servo fingerServo ("finger", 6, -90, 90, 0, 0, true);   

    bool useSequenceController = true;
    cout << endl;

    // Activate this code to work on real hardware rather than simulator
    cout << "Use sequence controller <true/false>: ";
    cin >> useSequenceController;

    Controller *controller = useSequenceController ? (Controller *) new SequenceController () : (Controller *) new ConsoleController ();
      
    while (true) {
        Command command = controller->getCommand ();
        
        baseServo.rotateTo (command.baseAngle);
        upperArmServo.rotateTo (command.upperAngle);
        lowerArmServo.rotateTo (command.lowerAngle);
        fingerServo.rotateTo (command.fingerAngle);

        cout << endl;
    }

    delete controller;
    
    return 0;
}
