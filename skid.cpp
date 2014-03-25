#include "skid.h"
#include "drivefunctions.h"
#include "constants.h"
#include "math.h"

#define DISTANCE_1 9
#define DISTANCE_2 20
#define DISTANCE_3 2
#define DISTANCE_4 5.5
#define DISTANCE_5 32
#define DISTANCE_6 30
#define DISTANCE_7 8

#define CORRECTION_DISTANCE 3.0

Skid::Skid()
{
}

int Skid::Run() {
    //Drive to RPS coordinate representing skid alignment
    drivePastRPSCoordinate(FORWARD_POWER, 1.5, false, true);
    //drive(FORWARD_POWER, DISTANCE_1, false, false);
    //Turn left, adjust, then back into wall
    turnToRPSHeading(0, TURN_POWER, LEFT, false, 1);
    Sleep(250);
    turnToRPSHeading(0, TURN_POWER, CLOSEST, false, 0.5);
    driveUntilSwitchPress(FORWARD_POWER * -1, BACK_SWITCH, 40);
    //Set forklift to horizontal then move forward to pick up skid
    forklift.SetDegree(HORIZONTAL);
    //Drive forward at first past pin line, then follow skid line
    drive(FORWARD_POWER, DISTANCE_2, false, false);
    //followLine(FORWARD_POWER, 20, true);
    Sleep(250);
    //Adjust to vertical
    turnToRPSHeading(0, TURN_POWER, CLOSEST, false, 1);
    //Set forklift past vertical to lift up skid
    forklift.SetDegree(SKID_ANGLE);
    //Back up, go forward, and then back up again to ensure skid is up
    driveUntilSwitchPress(-1 * FORWARD_POWER, BACK_SWITCH, 30);
    Sleep(250);
    drive(FORWARD_POWER, DISTANCE_3, false, false);
    driveUntilSwitchPress(-1 * FORWARD_POWER, BACK_SWITCH, 30);
    //Turn left, and drive in position to go down ramp
    turnToRPSHeading(90, TURN_POWER, LEFT, true, 1);
    drive(FORWARD_POWER, DISTANCE_4, false, false);
    //Turn and drive backwards down ramp
    turnToRPSHeading(0, TURN_POWER, RIGHT, true, 1);
    //driveUntilSwitchPress(FORWARD_POWER, FRONT_SWITCH, 30);
    float pastY = wonka.Y();
    drive(FORWARD_POWER * -1, DISTANCE_7, false, false);
    if (abs(wonka.Y() - pastY) < 5) {
        turnToRPSHeading(90, TURN_POWER, RIGHT, false, 1);
        drive(FORWARD_POWER, CORRECTION_DISTANCE, false, false);
        turnToRPSHeading(0, TURN_POWER, LEFT, false, 1);
    }
    int lightState = driveAndReadLight(FORWARD_POWER * -1, DISTANCE_5, false);
    driveUntilSwitchPress(FORWARD_POWER * -1, BACK_SWITCH, 30);
    //Turn and drive to hit wall in shop
    turnToRPSHeading(90, TURN_POWER, RIGHT, true, 1);
    driveUntilSwitchPress(-1 * FORWARD_POWER, BACK_SWITCH, 20);
    //Drive away from wall and turn
    drive(FORWARD_POWER, 2, false, false);
    turnToRPSHeading(0, TURN_POWER, LEFT, true, 1);
    Sleep(250);
    turnToRPSHeading(0, TURN_POWER, CLOSEST, true, 1);
    driveUntilSwitchPress(-1 * FORWARD_POWER, BACK_SWITCH, 20);
    //Set forklift to horizontal to drop off skid
    forklift.SetDegree(DROP_OFF_ANGLE);
    //Drive to chiller
    drive(FORWARD_POWER, DISTANCE_6, false, false);
    return lightState;
}
