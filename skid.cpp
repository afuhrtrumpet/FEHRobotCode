#include "skid.h"
#include "drivefunctions.h"
#include "constants.h"

#define DISTANCE_1 9
#define DISTANCE_2 28
#define DISTANCE_3 2
#define DISTANCE_4 9
#define DISTANCE_5 40
#define DISTANCE_6 30

Skid::Skid()
{
}

int Skid::Run() {
    drive(FORWARD_POWER, DISTANCE_1, false);
    turnToRPSHeading(0, TURN_POWER, LEFT, false);
    Sleep(250);
    turnToRPSHeading(0, TURN_POWER, CLOSEST, false);
    driveUntilSwitchPress(FORWARD_POWER * -1, BACK_SWITCH, 40);
    forklift.SetDegree(HORIZONTAL);
    //drive(FORWARD_POWER, DISTANCE_2, false);
    drive(FORWARD_POWER, 7, false);
    followLine(FORWARD_POWER, 14, true);
    //Adjust to vertical
    turnToRPSHeading(0, TURN_POWER, CLOSEST, false);
    turnToRPSHeading(0, TURN_POWER, CLOSEST, false);
    //Set forklift past vertical to lift up skid
    forklift.SetDegree(SKID_ANGLE);
    //Back up
    driveUntilSwitchPress(-1 * FORWARD_POWER, BACK_SWITCH, 30);
    Sleep(500);
    drive(FORWARD_POWER, DISTANCE_3, false);
    driveUntilSwitchPress(-1 * FORWARD_POWER, BACK_SWITCH, 30);
    turnToRPSHeading(90, TURN_POWER, LEFT, true);
    drive(FORWARD_POWER, DISTANCE_4, false);
    //Turn and drive backwards down ramp
    turnToRPSHeading(0, TURN_POWER, RIGHT, true);
    //driveUntilSwitchPress(FORWARD_POWER, FRONT_SWITCH, 30);
    int lightState = driveAndReadLight(FORWARD_POWER * -1, DISTANCE_5, false);
    driveUntilSwitchPress(FORWARD_POWER * -1, BACK_SWITCH, 30);
    //Turn and drive to hit wall in shop
    turnToRPSHeading(90, TURN_POWER, RIGHT, true);
    driveUntilSwitchPress(-1 * FORWARD_POWER, BACK_SWITCH, 20);
    //Drive away from wall and turn
    drive(FORWARD_POWER, 2, false);
    turnToRPSHeading(0, TURN_POWER, LEFT, true);
    driveUntilSwitchPress(-1 * FORWARD_POWER, BACK_SWITCH, 20);
    //Set forklift to horizontal to drop off skid
    forklift.SetDegree(DROP_OFF_ANGLE);
    //Drive to chiller
    drive(FORWARD_POWER, DISTANCE_6, false);
    return lightState;
}
