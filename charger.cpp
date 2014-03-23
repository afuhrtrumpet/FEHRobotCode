#include "charger.h"
#include "drivefunctions.h"
#include "constants.h"

Charger::Charger()
{
}

void Charger::Run() {
    turn(false, TURN_POWER, 30, false);
    driveUntilSwitchPress(FORWARD_POWER * -1, RIGHT_SWITCH, 30);
    turnToRPSHeading(90, TURN_POWER, RIGHT, false);
    driveUntilSwitchPress(FORWARD_POWER * -1, BACK_SWITCH, 1000);
}
