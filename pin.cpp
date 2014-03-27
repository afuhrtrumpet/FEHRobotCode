#include "pin.h"
#include "drivefunctions.h"
#include "constants.h"

#define DISTANCE_1 40
#define DISTANCE_2 10
#define DISTANCE_3 5
#define DISTANCE_4 8
#define DISTANCE_5 6
#define DISTANCE_6 7

Pin::Pin()
{
}

void Pin::Run() {
    forklift.SetDegree(HORIZONTAL);
    //Drive up ramp and don't stop until the robot is up
    drivePastRPSCoordinate(RAMP_POWER, 38, true, true);
    forklift.SetDegree(START_ANGLE);
    //Turn right, go backwards, turn left, go backwards to align with wall
    turnToRPSHeading(90, TURN_POWER, LEFT, false, 1);
    //drive(FORWARD_POWER * -1, DISTANCE_2, false, false);
    driveToRPSCoordinate(FORWARD_POWER, PIN_X, false, false);
    turnToRPSHeading(0, TURN_POWER, RIGHT, false, 1);
    turnUntilRPSHeading(0, TURN_POWER);
    driveUntilSwitchPress(FORWARD_POWER * -1, BACK_SWITCH, 10);
    //forklift.SetDegree(PIN_SWIPE_ANGLE);
    //Drive forward, turn right, align
    //drive(FORWARD_POWER, DISTANCE_3, false, false);
    driveToRPSCoordinate(FORWARD_POWER, PIN_Y, true, true);
    turnToRPSHeading(90, TURN_POWER, RIGHT, false, 1);
    turnUntilRPSHeading(90, TURN_POWER);
    forklift.SetDegree(PIN_ANGLE);
    //Set forklift to horizontal and begin driving. Follow line if it is detected

    driveUntilSwitchPress(FORWARD_POWER, FORKLIFT_SWITCH, DISTANCE_4);
    drive(FORWARD_POWER * -1, DISTANCE_5, false, false);
    forklift.SetDegree(HORIZONTAL);
    drive(FORWARD_POWER, DISTANCE_6, false, false);
    //Lift up forklift to extract pin
    forklift.SetDegree(PIN_ANGLE);
}
