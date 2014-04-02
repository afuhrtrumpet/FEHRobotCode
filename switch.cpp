#include "switch.h"
#include "constants.h"
#include "drivefunctions.h"

#define DISTANCE_1 8.0
#define DISTANCE_2 3.0
#define DISTANCE_3 1.25

Switch::Switch()
{
}

//TODO: Add check for RPS coordinate before flipping switch

void Switch::Run() {
    //Put forklift in retracted position
    forklift.SetDegree(START_ANGLE);
    //Drive to back wall and turn right
    driveUntilSwitchPress(FORWARD_POWER * -1, BACK_SWITCH, 30);
    turnToRPSHeading(90, TURN_POWER, RIGHT, false, 1);
    Sleep(250);
    turnUntilRPSHeading(90, TURN_POWER);
    //Drive forward, turn left
    //drive(FORWARD_POWER, DISTANCE_1, false, false);
    drive(FORWARD_POWER, DISTANCE_1, false, false);
    driveToRPSCoordinate(RPS_POWER, SWITCH_X, false, true);
    turnToRPSHeading(0, TURN_POWER, LEFT, false, 1);
    Sleep(250);
    turnUntilRPSHeading(0, TURN_POWER);
    //Drive into switch and then backwards
    driveUntilSwitchPress(FORWARD_POWER, FRONT_SWITCH, 12);
    drive(-1 * FORWARD_POWER, DISTANCE_2, false, false);
    Sleep(50);
    drive(FORWARD_POWER, DISTANCE_3, false, false);
    //Turn right, put forklift down, turn left (this action flips the switch
    turnToRPSHeading(135, TURN_POWER, RIGHT, false, 1);
    forklift.SetDegree(SWITCH_ANGLE);
    turnUntilSwitchFlip(TURN_POWER, false, 100);
    turnUntilRPSHeading(0, TURN_POWER, 1.0);
    //turnToRPSHeading(45, TURN_POWER, LEFT, false, 1);
    //Retract forklift to avoid further contact
    forklift.SetDegree(START_ANGLE);
}
