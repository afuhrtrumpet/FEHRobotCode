#include "charger.h"
#include "drivefunctions.h"
#include "constants.h"

#define DISTANCE_1 30

Charger::Charger()
{
}

void Charger::Run() {
    drive(FORWARD_POWER * -1, DISTANCE_1, false, false);
    turnToRPSHeading(0, TURN_POWER, LEFT, false, 1);
    driveUntilSwitchPress(FORWARD_POWER * -1, BACK_SWITCH, 15);
    //Turn to horizontal and drive backwards to hit charger
    turnToRPSHeading(90, TURN_POWER, CLOSEST, false, 1);
    driveUntilSwitchPress(FORWARD_POWER * -1, BACK_SWITCH, 1000);
}
