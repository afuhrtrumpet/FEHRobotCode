#include "ramp.h"
#include "drivefunctions.h"
#include "constants.h"

Ramp::Ramp()
{
}

void Ramp::Run() {
    forklift.SetDegree(HORIZONTAL);
    //Drive up ramp and don't stop until the robot is up
    while (!drivePastRPSCoordinate(RAMP_POWER, 38, true, true, UP_RAMP_TIME_LIMIT)) {
        Sleep(1000);
        turnUntilRPSHeading(0, TURN_POWER);
    }
    drivePastRPSCoordinate(RAMP_POWER, 38, true, true, UP_RAMP_TIME_LIMIT);
    forklift.SetDegree(START_ANGLE);
    turnToRPSHeading(90, TURN_POWER, RIGHT, false, 1);
    turnUntilRPSHeading(90, TURN_POWER);
}
