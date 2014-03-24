#include "button.h"
#include "constants.h"
#include "drivefunctions.h"

#define DISTANCE_1 6.0
#define DISTANCE_2 6.5
#define DISTANCE_3 1.0

Button::Button()
{
}

void Button::Run() {
    forklift.SetDegree(BUTTON_ANGLE);
    drive(FORWARD_POWER, DISTANCE_1, false, false);
    turnToRPSHeading(0, TURN_POWER, LEFT, false);
    drive(FORWARD_POWER, DISTANCE_2, false, false);
    turnToRPSHeading(90, TURN_POWER, LEFT, false);
    while (wonka.OvenPressed() < wonka.Oven()) {
        int previousPresses = wonka.OvenPressed();
        //Press button
        driveUntilSwitchPress(FORWARD_POWER, FRONT_SWITCH, 7);
        drive(-1 * FORWARD_POWER, DISTANCE_3, false, false);
        //If the button was not pressed
        if (previousPresses == wonka.OvenPressed()) {
            turnToRPSHeading(90, TURN_POWER, CLOSEST, false);
        }
    }
    turnToRPSHeading(0, TURN_POWER, RIGHT, false);
}
