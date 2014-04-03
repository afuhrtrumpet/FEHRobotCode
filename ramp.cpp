#include "ramp.h"
#include "drivefunctions.h"
#include "constants.h"

#define DISTANCE_1 5.0

/* RAMP
 *======
 *Drives robot up the ramp and turns in position
 *to go back to the charger */

Ramp::Ramp()
{
}

void Ramp::Run() {
    forklift.SetDegree(HORIZONTAL);
    //Drive up ramp and don't stop until the robot is up
    //Do two adjustments at first
    for (int i = 0; i < 2; i++) {
        drive(FORWARD_POWER, DISTANCE_1, false, false);
        Sleep(100);
        turnUntilRPSHeading(0, FORWARD_POWER, 2.0);
    }
    drivePastRPSCoordinate(RAMP_POWER, UP_RAMP_Y, true, true, 30.0);
    forklift.SetDegree(START_ANGLE);
    //Turn to face charger
    turnToRPSHeading(90, TURN_POWER, RIGHT, false, 1);
    turnUntilRPSHeading(90, TURN_POWER);
}
