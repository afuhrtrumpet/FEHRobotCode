#include "pin.h"
#include "drivefunctions.h"
#include "constants.h"

#define DISTANCE_1 5
#define DISTANCE_2 4
#define DISTANCE_3 3

Pin::Pin()
{
}

void Pin::Run() {
    drive(FORWARD_POWER * -1, DISTANCE_1, false, false);
    turnToRPSHeading(90, TURN_POWER, RIGHT, false, 1);
    turnUntilRPSHeading(90, TURN_POWER);
    //Drive to RPS coordinate representing skid alignment
    drive(FORWARD_POWER, DISTANCE_1, false, false);
    driveToRPSCoordinate(RPS_POWER, skidX, false, true);
    Sleep(200);
    turnUntilRPSHeading(90, TURN_POWER);
    drive (FORWARD_POWER * -1, DISTANCE_2, false, false);
    forklift.SetDegree(PIN_DOWN_ANGLE);
    float start = TimeNow();
    while (TimeNow() - start < .5);
    drive(FORWARD_POWER, DISTANCE_3, false, false);
    forklift.SetDegree(PIN_ANGLE);
    start = TimeNow();
    while (TimeNow() - start < .5);
    forklift.SetDegree(START_ANGLE);
    start = TimeNow();
    while (TimeNow() - start < .5);
    drive(PIN_POWER * -1, DISTANCE_3, false, false);
    drive(PIN_POWER, DISTANCE_2, false, false);
}
