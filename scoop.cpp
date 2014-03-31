#include "scoop.h"
#include "constants.h"
#include "otherfunctions.h"
#include "drivefunctions.h"

#define DISTANCE_RED 5.5
#define DISTANCE_BLUE 21

#define DISTANCE_1 14
#define INCREMENTS 3

Scoop::Scoop()
{
}

void Scoop::Run(int lightState) {
    //Back into wall and retract forklift
    driveUntilSwitchPress(FORWARD_POWER * -1, BACK_SWITCH, 30);
    forklift.SetDegree(START_ANGLE);
    //Turn, back into other wall
    turnToRPSHeading(90, TURN_POWER, RIGHT, false, 1);
    turnUntilRPSHeading(90, TURN_POWER);
    driveUntilSwitchPress(FORWARD_POWER * -1, BACK_SWITCH, 20);
    turnUntilRPSHeading(87, TURN_POWER);

    //Drive to the correct bin based on light
    float scoopDistance = lightState == RED ? DISTANCE_RED : DISTANCE_BLUE;
    for (int i = 0; i < INCREMENTS; i++) {
        drive(FORWARD_POWER, scoopDistance / INCREMENTS, false, false);
        turnUntilRPSHeading(90, TURN_POWER, 2.0);
    }
    //Drop the scoop in the bin
    dropOffScoop();
    //Back into the wall again to ensure alignment
    driveUntilSwitchPress(FORWARD_POWER * -1, BACK_SWITCH, TIMEOUT_DISTANCE);
    //Drive to center of shop, turn, and back into wall
    turnUntilRPSHeading(90, TURN_POWER);
    drive(FORWARD_POWER, DISTANCE_1, false, false);
    turn(false, TURN_POWER, 180, false);
    driveToRPSCoordinate(RPS_POWER, rampX, false, false);
    turnToRPSHeading(0, TURN_POWER, RIGHT, false, 1);
    turnUntilRPSHeading(0, TURN_POWER);
}
