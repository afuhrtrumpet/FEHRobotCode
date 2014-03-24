#include "pin.h"
#include "drivefunctions.h"
#include "constants.h"

#define DISTANCE_1 40
#define DISTANCE_2 10
#define DISTANCE_3 5
#define DISTANCE_4 18

Pin::Pin()
{
}

void Pin::Run() {
    drivePastRPSCoordinate(RAMP_POWER, 38, true, true);
    turnToRPSHeading(90, TURN_POWER, RIGHT, false);
    drive(FORWARD_POWER * -1, DISTANCE_2, false, false);
    turnToRPSHeading(0, TURN_POWER, LEFT, false);
    driveUntilSwitchPress(FORWARD_POWER * -1, BACK_SWITCH, 10);
    drive(FORWARD_POWER, DISTANCE_3, false, false);
    turnToRPSHeading(90, TURN_POWER, RIGHT, false);
    Sleep(250);
    turnToRPSHeading(90, TURN_POWER, CLOSEST, false);
    forklift.SetDegree(HORIZONTAL);
    followLine(FORWARD_POWER, DISTANCE_4, false);
    forklift.SetDegree(PIN_ANGLE);
}
