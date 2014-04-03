#include "pin.h"
#include "drivefunctions.h"
#include "constants.h"

#define DISTANCE_1 5
#define DISTANCE_2 4
#define DISTANCE_3 2.5

/* PIN
 *======
 *Takes robot from directly after flipping switch
 *to after it pulls out the pin and aligns with the skid */

Pin::Pin()
{
}

void Pin::Run() {
    //Back up, turn right
    drive(FORWARD_POWER * -1, DISTANCE_1, false, false);
    turnToRPSHeading(90, TURN_POWER, RIGHT, false, 1);
    turnUntilRPSHeading(90, TURN_POWER);
    //Drive to RPS coordinate representing skid alignment
    drive(FORWARD_POWER, DISTANCE_1, false, false);
    driveToRPSCoordinate(RPS_POWER, skidX, false, true);
    Sleep(200);
    //Adjust before pulling out pin
    turnUntilRPSHeading(90, TURN_POWER);
    //Drive backwards, move forklift down, drive forwards, move forklift up
    drive (FORWARD_POWER * -1, DISTANCE_2, false, false);
    forklift.SetDegree(PIN_DOWN_ANGLE);
    float start = TimeNow();
    while (TimeNow() - start < .5);
    drive(FORWARD_POWER, DISTANCE_3, false, false);
    forklift.SetDegree(PIN_ANGLE);
    start = TimeNow();
    while (TimeNow() - start < .75);
    forklift.SetDegree(START_ANGLE);
    //Drive back then forwards again
    start = TimeNow();
    while (TimeNow() - start < .75);
    drive(PIN_POWER * -1, DISTANCE_3, false, false);
    drive(PIN_POWER, DISTANCE_2, false, false);
}
