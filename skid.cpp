#include "skid.h"
#include "drivefunctions.h"
#include "constants.h"
#include "math.h"

#define DISTANCE_1 9
#define DISTANCE_2 20.0
#define DISTANCE_3 2
#define DISTANCE_4 5.5
#define DISTANCE_5 25
#define DISTANCE_6 30
#define DISTANCE_7 10
#define DISTANCE_8 6
#define DISTANCE_9 8
#define DISTANCE_10 14

#define CORRECTION_DISTANCE 3.0


Skid::Skid()
{
}

int Skid::Run() {
    drive(FORWARD_POWER * -1, DISTANCE_8, false, false);
    turnToRPSHeading(90, TURN_POWER, RIGHT, false, 1);
    turnUntilRPSHeading(90, TURN_POWER);
    //Drive to RPS coordinate representing skid alignment
    drive(FORWARD_POWER, DISTANCE_1, false, false);
    driveToRPSCoordinate(RPS_POWER, skidX, false, true);
    //drive(FORWARD_POWER, DISTANCE_1, false, false);
    //Turn left, adjust, then back into wall
    turnToRPSHeading(0, TURN_POWER, LEFT, false, 1);
    Sleep(250);
    turnUntilRPSHeading(0, RPS_POWER);
    //turnUntilRPSHeading(0, RPS_POWER);
    bool hitWall = driveUntilSwitchPress(FORWARD_POWER * -1, BACK_SWITCH, 10);
    /*if (!hitWall) {
        turnToRPSHeading(90, TURN_POWER, LEFT, false, 1);
        driveToRPSCoordinate(RPS_POWER, 2, false, true);

    }*/
    //Set forklift to horizontal then move forward to pick up skid
    forklift.SetDegree(HORIZONTAL);
    //Drive forward at first past pin line, then follow skid line
    drive(FORWARD_POWER, DISTANCE_2 / 3, false, false);
    turnUntilRPSHeading(0, RPS_POWER);
    drive(FORWARD_POWER, DISTANCE_2 * 2 / 3, false, false);
    Sleep(250);
    turnUntilRPSHeading(175, TURN_POWER);
    //Set forklift past vertical to lift up skid
    forklift.SetDegree(SKID_ANGLE);
    //Back up, go forward, and then back up again to ensure skid is up
    driveUntilSwitchPress(-1 * FORWARD_POWER, BACK_SWITCH, 30);
    Sleep(250);
    drive(FORWARD_POWER, DISTANCE_3, false, false);
    driveUntilSwitchPress(-1 * FORWARD_POWER, BACK_SWITCH, 30);
    //Turn left, and drive in position to go down ramp
    drive(FORWARD_POWER, 1, false, false);
    turnToRPSHeading(90, TURN_POWER, LEFT, true, 1);
    Sleep(250);
    turnUntilRPSHeading(90, TURN_POWER);
    //drive(FORWARD_POWER, DISTANCE_4, false, false);
    driveToRPSCoordinate(FORWARD_POWER, rampX, false, false);
    //Turn and drive backwards down ramp
    turnToRPSHeading(0, TURN_POWER, RIGHT, true, 1);
    turnUntilRPSHeading(0, TURN_POWER);
    //driveUntilSwitchPress(FORWARD_POWER, FRONT_SWITCH, 30);
    float pastY = wonka.Y();
    drive(FORWARD_POWER * -1, DISTANCE_7, false, false);
    Sleep(250);
    turnUntilRPSHeading(0, TURN_POWER);
    int lightState = driveAndReadLight(FORWARD_POWER * -1, DISTANCE_5, false);
    driveUntilSwitchPress(FORWARD_POWER * -1, BACK_SWITCH, 30);
    //Turn and drive to hit wall in shop
    turnToRPSHeading(90, TURN_POWER, RIGHT, true, 1);
    driveUntilSwitchPress(-1 * FORWARD_POWER, BACK_SWITCH, 20);
    //Drive away from wall and turn
    //drive(FORWARD_POWER, 2, false, false);
    driveToRPSCoordinate(RPS_POWER, CHILLER_X, false, true);
    turnToRPSHeading(0, TURN_POWER, LEFT, true, 1);
    Sleep(250);
    turnToRPSHeading(0, TURN_POWER, CLOSEST, true, 1);
    turnUntilRPSHeading(0, RPS_POWER);
    driveUntilSwitchPress(-1 * FORWARD_POWER, BACK_SWITCH, 20);
    //Set forklift to horizontal to drop off skid
    forklift.SetDegree(DROP_OFF_ANGLE);
    //Drive to chiller
    drive(FORWARD_POWER, DISTANCE_6, false, false);
    drive(FORWARD_POWER * -1, DISTANCE_9, false, false);
    forklift.SetDegree(SKID_PUSH_ANGLE);
    drive(FORWARD_POWER, DISTANCE_10, false, false);
    return lightState;
}
