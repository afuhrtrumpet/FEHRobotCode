#include "charger.h"
#include "drivefunctions.h"
#include "constants.h"

#define DISTANCE_1 30

/* CHARGER
 *=========
 *Takes robot from top of ramp to the beginning.
 *Only quits when middle button is held for a while. */

Charger::Charger()
{
}

void Charger::Run() {
    turnUntilRPSHeading(90, TURN_POWER);
    //Keep driving until middle button is pressed
    while (!buttons.MiddlePressed()) {
    //Drive in 10-inch increments
        if (driveUntilSwitchPress(CHARGER_POWER * -1, BACK_SWITCH, 10)) {
            //If switch was pressed, adjust, back into wall, adjust
            turnToRPSHeading(0, TURN_POWER, LEFT, false, 1);
            driveUntilSwitchPress(FORWARD_POWER * -1, BACK_SWITCH, 10);
            turnToRPSHeading(90, TURN_POWER, RIGHT, false, 1);
        }
        //Adjust after every 10 inches
        turnUntilRPSHeading(90, TURN_POWER, 2.0);
    }
    while (!buttons.MiddleReleased());
}
