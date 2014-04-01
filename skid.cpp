#include "skid.h"
#include "drivefunctions.h"
#include "constants.h"
#include "math.h"
#include "scoop.h"

#define DISTANCE_1 9
#define DISTANCE_2 20.0
#define DISTANCE_3 2
#define DISTANCE_4 5.5
#define DISTANCE_5 10
#define DISTANCE_6 20
#define DISTANCE_7 7
#define DISTANCE_8 5
#define DISTANCE_9 6
#define DISTANCE_10 12
#define DISTANCE_11 5
#define DISTANCE_12 3
#define DISTANCE_13 3

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
    Sleep(200);
    turnUntilRPSHeading(90, TURN_POWER);
    drive (FORWARD_POWER * -1, DISTANCE_12, false, false);
    forklift.SetDegree(PIN_DOWN_ANGLE);
    float start = TimeNow();
    while (TimeNow() - start < .5);
    drive(FORWARD_POWER, DISTANCE_13, false, false);
    forklift.SetDegree(PIN_ANGLE);
    start = TimeNow();
    while (TimeNow() - start < .5);
    forklift.SetDegree(START_ANGLE);
    start = TimeNow();
    while (TimeNow() - start < .5);
    drive(FORWARD_POWER * -1, DISTANCE_13, false, false);
    drive(FORWARD_POWER, DISTANCE_12, false, false);
    //Turn left, adjust, then back into wall
    turnToRPSHeading(0, TURN_POWER, LEFT, false, 1);
    Sleep(250);
    turnUntilRPSHeading(0, RPS_POWER);
    if (!driveUntilSwitchPress(FORWARD_POWER * -1, BACK_SWITCH, 10)) {
        turnUntilRPSHeading(0, TURN_POWER);
    }
    forklift.SetDegree(HORIZONTAL);
    //door.SetDegree(DOOR_HORIZONTAL);
    //Drive forward at first past pin line, then follow skid line
    drive(SKID_POWER, DISTANCE_2 / 5, false, false, 1.15);
    Sleep(250);
    turnUntilRPSHeading(0, RPS_POWER);
    //door.SetDegree(DOOR_CLOSED);
    //float start = TimeNow();
    //while (TimeNow() - start < 0.75);
    //drive(FORWARD_POWER, 0.5, false, false);
    //door.SetDegree(DOOR_CLOSED);
    //start = TimeNow();
    //while (TimeNow() - start < 0.75);
    //turnUntilRPSHeading(0, RPS_POWER);
    drive(SKID_POWER, DISTANCE_2 * 4 / 5, false, false, 1.15);
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
    turnUntilRPSHeading(90, TURN_POWER, 4.0, 0.125);
    driveToRPSCoordinate(FORWARD_POWER, rampX, false, false);
    //Turn and drive backwards down ramp
    turnToRPSHeading(0, TURN_POWER, RIGHT, true, 1);
    turn(false, TURN_POWER, 10, true);
    Sleep(250);
    turnUntilRPSHeading(0, TURN_POWER);
    for (int i = 0; i < 2; i++) {
        drive(FORWARD_POWER * -1, DISTANCE_7, false, false);
    Sleep(250);
    turnUntilRPSHeading(0, TURN_POWER);
    }
    int lightState = driveAndReadLight(FORWARD_POWER * -1, DISTANCE_5, false);
    driveUntilSwitchPress(FORWARD_POWER * -1, BACK_SWITCH, 30);
    while (!drivePastRPSCoordinate(RAMP_POWER * -1, DOWN_RAMP_Y, true, false, UP_RAMP_TIME_LIMIT)) {
        Sleep(200);
        turnUntilRPSHeading(0, TURN_POWER);
    }
    //Turn and drive to hit wall in shop
    turnToRPSHeading(90, TURN_POWER, RIGHT, true, 1);
    Sleep(250);
    turnUntilRPSHeading(90, TURN_POWER);
    driveUntilSwitchPress(-1 * FORWARD_POWER, BACK_SWITCH, 20);
    //Drive away from wall and turn
    driveToRPSCoordinate(RPS_POWER, CHILLER_X, false, true);
    turnToRPSHeading(0, TURN_POWER, LEFT, true, 1);
    turn(true, TURN_POWER, 10, true);
    Sleep(250);
    turnToRPSHeading(0, TURN_POWER, CLOSEST, true, 1);
    turnUntilRPSHeading(0, RPS_POWER);
    driveUntilSwitchPress(-1 * FORWARD_POWER, BACK_SWITCH, 20);
    //Set forklift to horizontal to drop off skid
    forklift.SetDegree(DROP_OFF_ANGLE);
    //Drive to chiller
    drive(SCOOP_POWER, DISTANCE_6, false, false, 1.1);
    drive(FORWARD_POWER * -1, DISTANCE_9, false, false);
    forklift.SetDegree(SKID_PUSH_ANGLE);
    drive(FORWARD_POWER, DISTANCE_10, false, false);
    Sleep(50);
    turnUntilRPSHeading(0, TURN_POWER, 2.5);
    return lightState;
}
