#include "switch.h"
#include "constants.h"
#include "drivefunctions.h"

#define DISTANCE_1 16.0
#define DISTANCE_2 1.0

Switch::Switch()
{
}

void Switch::Run() {
    //Put forklift in retracted position
    forklift.SetDegree(START_ANGLE);
    //Drive to back wall and turn right
    driveUntilSwitchPress(FORWARD_POWER * -1, BACK_SWITCH, 30);
    turnToRPSHeading(90, TURN_POWER, RIGHT, false, 1);
    //Drive forward, turn left
    drive(FORWARD_POWER, DISTANCE_1, false, false);
    turnToRPSHeading(0, TURN_POWER, LEFT, false, 1);
    //Drive into switch and then backwards
    driveUntilSwitchPress(FORWARD_POWER, FRONT_SWITCH, 12);
    drive(-1 * FORWARD_POWER, DISTANCE_2, false, false);
    //Turn right, put forklift down, turn left (this action flips the switch
    turnToRPSHeading(135, TURN_POWER, RIGHT, false, 1);
    forklift.SetDegree(SWITCH_ANGLE);
    turnToRPSHeading(45, TURN_POWER, LEFT, false, 1);
    //Retract forklift to avoid further contact
    forklift.SetDegree(START_ANGLE);
    //Turn right to end
    turnToRPSHeading(90, TURN_POWER, RIGHT, false, 1);
}
