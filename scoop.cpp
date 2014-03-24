#include "scoop.h"
#include "constants.h"
#include "otherfunctions.h"
#include "drivefunctions.h"

#define DISTANCE_RED 7
#define DISTANCE_BLUE 23
#define DISTANCE_1 13

Scoop::Scoop()
{
}

void Scoop::Run(int lightState) {
    driveUntilSwitchPress(FORWARD_POWER * -1, BACK_SWITCH, 30);
    forklift.SetDegree(START_ANGLE);
    turnToRPSHeading(90, TURN_POWER, RIGHT, false);
    driveUntilSwitchPress(FORWARD_POWER * -1, BACK_SWITCH, 20);
    if (lightState == RED) {
        drive(FORWARD_POWER, DISTANCE_RED, false, false);
    } else {
        drive(FORWARD_POWER, DISTANCE_BLUE, false, false);
    }
    dropOffScoop();
    driveUntilSwitchPress(FORWARD_POWER * -1, BACK_SWITCH, TIMEOUT_DISTANCE);
    drive(FORWARD_POWER, DISTANCE_1, false, false);
    turnToRPSHeading(0, TURN_POWER, LEFT, false);
    driveUntilSwitchPress(FORWARD_POWER * -1, BACK_SWITCH, TIMEOUT_DISTANCE);
}
