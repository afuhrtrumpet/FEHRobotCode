#include "skid.h"
#include "drivefunctions.h"
#include "constants.h"
#include "math.h"

#define DISTANCE_1 9
#define DISTANCE_2 20.0
#define DISTANCE_3 2.0
#define DISTANCE_4 5.5
#define DISTANCE_5 10
#define DISTANCE_6 6
#define DISTANCE_7 7.5
#define DISTANCE_8 5
#define DISTANCE_9 10

#define CORRECTION_DISTANCE 3.0

/* SKID
 *=======
 *Takes robot from directly after pulling pin to
 *getting the skid and navigating to the shop floor */

Skid::Skid()
{
}

int Skid::Run() {
    driveToRPSCoordinate(RPS_POWER, skidX, false, true);
    //Turn left, adjust, then back into wall
    turnToRPSHeading(0, TURN_POWER, LEFT, false, 1);
    Sleep(250);
    turnUntilRPSHeading(0, RPS_POWER);
    if (!driveUntilSwitchPress(FORWARD_POWER * -1, BACK_SWITCH, 10)) {
        turnUntilRPSHeading(0, TURN_POWER);
    }
    //Put forklift at horizontal
    forklift.SetDegree(HORIZONTAL);
    //Drive forward at first past pin line, then adjust
    drive(SKID_POWER, DISTANCE_2 / 5, false, false, 1.15);
    forklift.SetDegree(START_ANGLE);
    Sleep(200);
    forklift.SetDegree(HORIZONTAL);
    Sleep(250);
    turnUntilRPSHeading(0, RPS_POWER, 2.0);
    forklift.SetDegree(HORIZONTAL);
    //Keep going to skid
    drive(SKID_POWER, DISTANCE_2 * 4 / 5, false, false, 1.15);
    Sleep(250);
    turnUntilRPSHeading(0, TURN_POWER);
    //Set forklift past vertical to lift up skid
    forklift.SetDegree(SKID_ANGLE);
    //Drive back and forward to hit wall again
    drive(FORWARD_POWER * -1, DISTANCE_3, false, false);
    Sleep(50);
    forklift.SetDegree(HORIZONTAL);
    turnUntilRPSHeading(0, TURN_POWER);
    drive(FORWARD_POWER, DISTANCE_8, false, false);
    Sleep(100);
    turnUntilRPSHeading(0, TURN_POWER);
    forklift.SetDegree(SKID_ANGLE);
    //Drive all the way back and forward again to ensure skid is up
    drive(FORWARD_POWER * -1, 15, false, false, .6);
    Sleep(200);
    turnUntilRPSHeading(0, TURN_POWER);
    if (!driveUntilSwitchPress(FORWARD_POWER * -1, BACK_SWITCH, 15)) {
        turnUntilRPSHeading(0, TURN_POWER, 2.0);
    }
    Sleep(250);
    drive(FORWARD_POWER, DISTANCE_3, false, false);
    driveUntilSwitchPress(-1 * FORWARD_POWER, BACK_SWITCH, 10);
    //Turn left, and drive in position to go down ramp
    Sleep(200);
    drive(FORWARD_POWER, 1, false, false);
    turnToRPSHeading(90, TURN_POWER, LEFT, true, 1);
    Sleep(250);
    turnUntilRPSHeading(90, TURN_POWER, 4.0, 0.125);
    drive(FORWARD_POWER, DISTANCE_9, false, false);
    driveToRPSCoordinate(FORWARD_POWER, rampX, false, false);
    //Turn and drive backwards down ramp
    turnToRPSHeading(0, TURN_POWER, RIGHT, true, 1);
    turn(false, TURN_POWER, 10, true);
    Sleep(250);
    //Do a check after a little bit of driving
    turnUntilRPSHeading(0, TURN_POWER);
    for (int i = 0; i < 2; i++) {
        //Drive periodically and check two more times
        drive(FORWARD_POWER * -1, DISTANCE_6, false, false);
        Sleep(250);
        if (wonka.Y() < SWITCH_Y) {
            turnToRPSHeading(90, TURN_POWER, LEFT, false, 1);
            turnToRPSHeading(0, TURN_POWER, LEFT, false, 1);
        }
        turnUntilRPSHeading(0, TURN_POWER, 2.0);
    }
    //Read light state and drive the rest of the way
    int lightState = driveAndReadLight(FORWARD_POWER * -1, DISTANCE_5, false);
    float start = TimeNow();
    while (!drivePastRPSCoordinate(RAMP_POWER * -1, DOWN_RAMP_Y, true, false, UP_RAMP_TIME_LIMIT) && TimeNow() - start < 15.0) {
        Sleep(200);
        turnUntilRPSHeading(0, TURN_POWER);
    }
    return lightState;
}
