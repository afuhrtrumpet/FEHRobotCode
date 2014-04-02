#include "charger.h"
#include "drivefunctions.h"
#include "constants.h"

#define DISTANCE_1 30

Charger::Charger()
{
}

void Charger::Run() {
    turnUntilRPSHeading(90, TURN_POWER);
    /*drive(FORWARD_POWER * -1, DISTANCE_1 / 2, false, false);
    turnUntilRPSHeading(90, TURN_POWER);
    drive(FORWARD_POWER * -1, DISTANCE_1 / 2, false, false);
    turnToRPSHeading(0, TURN_POWER, LEFT, false, 1);
    driveUntilSwitchPress(FORWARD_POWER * -1, BACK_SWITCH, 10);
    //Turn to horizontal and drive backwards to hit charger
    turnToRPSHeading(90, TURN_POWER, RIGHT, false, 1);
    turnUntilRPSHeading(90, TURN_POWER);
    driveUntilSwitchPress(FORWARD_POWER * -1, BACK_SWITCH, 1000);*/
    while (!buttons.MiddlePressed()) {
        if (driveUntilSwitchPress(CHARGER_POWER * -1, BACK_SWITCH, 10)) {
            turnToRPSHeading(0, TURN_POWER, LEFT, false, 1);
            driveUntilSwitchPress(FORWARD_POWER * -1, BACK_SWITCH, 10);
            turnToRPSHeading(90, TURN_POWER, RIGHT, false, 1);
        }
        turnUntilRPSHeading(90, TURN_POWER, 2.0);
    }
    while (!buttons.MiddleReleased());
}
