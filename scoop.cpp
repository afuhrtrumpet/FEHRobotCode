#include "scoop.h"
#include "constants.h"
#include "otherfunctions.h"
#include "drivefunctions.h"

#define DISTANCE_RED 7
#define DISTANCE_BLUE 20

#define DISTANCE_1 14

Scoop::Scoop()
{
}

void Scoop::Run(int lightState) {
    //Back into wall and retract forklift
    driveUntilSwitchPress(FORWARD_POWER * -1, BACK_SWITCH, 30);
    forklift.SetDegree(START_ANGLE);
    //Turn, back into other wall
    turnToRPSHeading(90, TURN_POWER, RIGHT, false, 1);
    turnUntilRPSHeading(90, TURN_POWER);
    driveUntilSwitchPress(FORWARD_POWER * -1, BACK_SWITCH, 20);
    turnUntilRPSHeading(90, TURN_POWER);

    //Drive to the correct bin based on light
    if (lightState == RED) {
        drive(FORWARD_POWER, DISTANCE_RED, false, false);
    } else {
        drive(FORWARD_POWER, DISTANCE_BLUE, false, false);
    }
    //Drop the scoop in the bin
    dropOffScoop();
    //Back into the wall again to ensure alignment
    driveUntilSwitchPress(FORWARD_POWER * -1, BACK_SWITCH, TIMEOUT_DISTANCE);
    //Drive to center of shop, turn, and back into wall
    turnUntilRPSHeading(90, TURN_POWER);
    drive(FORWARD_POWER, DISTANCE_1, false, false);
    turnToRPSHeading(0, TURN_POWER, LEFT, false, 1);
    turnUntilRPSHeading(0, TURN_POWER);
}
