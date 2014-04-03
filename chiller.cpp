#include "chiller.h"
#include "drivefunctions.h"
#include "constants.h"

#define DISTANCE_1 20
#define DISTANCE_2 7
#define DISTANCE_3 12

/* CHILLER
 *==========
 *Takes robot from shop floor to putting the skid in chiller */

Chiller::Chiller()
{
}

void Chiller::Run() {
    //Turn and drive to hit wall in shop
    turnToRPSHeading(90, TURN_POWER, RIGHT, true, 1);
    Sleep(250);
    turnUntilRPSHeading(90, TURN_POWER);
    driveUntilSwitchPress(-1 * FORWARD_POWER, BACK_SWITCH, 20);
    //Drive away from wall and turn
    driveToRPSCoordinate(RPS_POWER, CHILLER_X, false, true, 90);
    turnToRPSHeading(0, TURN_POWER, LEFT, true, 1);
    turn(true, TURN_POWER, 10, true);
    Sleep(250);
    turnToRPSHeading(0, TURN_POWER, CLOSEST, true, 1);
    turnUntilRPSHeading(0, RPS_POWER);
    driveUntilSwitchPress(-1 * FORWARD_POWER, BACK_SWITCH, 10);
    //Set forklift to horizontal to drop off skid
    forklift.SetDegree(DROP_OFF_ANGLE);
    //Drive to chiller
    drive(SCOOP_POWER, DISTANCE_1, false, false, 1.1);
    drive(FORWARD_POWER * -1, DISTANCE_2, false, false);
    //Raise forklift a little bit and go in again to push skid in
    forklift.SetDegree(SKID_PUSH_ANGLE);
    drive(FORWARD_POWER, DISTANCE_3, false, false);
    Sleep(50);
    turnUntilRPSHeading(0, TURN_POWER, 2.5);
}
