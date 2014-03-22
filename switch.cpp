#include "switch.h"
#include "constants.h"
#include "drivefunctions.h"

#define DISTANCE_1 17.0
#define DISTANCE_2

Switch::Switch()
{
}

void Switch::Run() {
    forklift.SetDegree(START_ANGLE);
    drive(FORWARD_POWER, DISTANCE_1, false);
    turnToRPSHeading(0, TURN_POWER, LEFT, false);
    driveUntilSwitchPress(FORWARD_POWER, FRONT_SWITCH, 10);
    turnToRPSHeading(135, TURN_POWER, RIGHT, false);
    forklift.SetDegree(SWITCH_ANGLE);
    turnToRPSHeading(45, TURN_POWER, LEFT, false);
    forklift.SetDegree(START_ANGLE);
    turnToRPSHeading(0, TURN_POWER, CLOSEST, false);
}
