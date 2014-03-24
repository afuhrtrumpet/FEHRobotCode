#include "switch.h"
#include "constants.h"
#include "drivefunctions.h"

#define DISTANCE_1 20.0
#define DISTANCE_2 5.0

Switch::Switch()
{
}

void Switch::Run() {
    forklift.SetDegree(START_ANGLE);
    driveUntilSwitchPress(FORWARD_POWER * -1, BACK_SWITCH, 30);
    drive(-1 * FORWARD_POWER, DISTANCE_2, false);
    turnToRPSHeading(90, TURN_POWER, RIGHT, false);
    drive(FORWARD_POWER, DISTANCE_1, false);
    turnToRPSHeading(0, TURN_POWER, LEFT, false);
    driveUntilSwitchPress(FORWARD_POWER, FRONT_SWITCH, 10);
    turnToRPSHeading(135, TURN_POWER, RIGHT, false);
    forklift.SetDegree(SWITCH_ANGLE);
    turnToRPSHeading(45, TURN_POWER, LEFT, false);
    forklift.SetDegree(START_ANGLE);
    turnToRPSHeading(90, TURN_POWER, RIGHT, false);
}
