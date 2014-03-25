#include "button.h"
#include "constants.h"
#include "drivefunctions.h"

#define DISTANCE_1 6.0
#define DISTANCE_2 5.5
#define DISTANCE_3 1.0
#define DISTANCE_4 4.0

Button::Button()
{
}

void Button::Run() {
    //Set forklift to vertical position
    forklift.SetDegree(BUTTON_ANGLE);
    //Drive forward, turn left, drive forward, turn left to reach button
    drive(FORWARD_POWER, DISTANCE_1, false, false);
    turnToRPSHeading(0, TURN_POWER, LEFT, false, 1);
    drive(FORWARD_POWER, DISTANCE_2, false, false);
    turnToRPSHeading(90, TURN_POWER, LEFT, false, 1);
    //Press button until button has been pressed right number of times
    while (wonka.OvenPressed() < wonka.Oven()) {
        int previousPresses = wonka.OvenPressed();
        //Press button
        driveUntilSwitchPress(FORWARD_POWER, FRONT_SWITCH, 7);
        drive(-1 * FORWARD_POWER, DISTANCE_3, false, false);
        //If the button was not pressed
        if (previousPresses == wonka.OvenPressed()) {
            //Adjust to horizontal
            turnToRPSHeading(90, TURN_POWER, CLOSEST, false, 1);
        }
    }
    drive(FORWARD_POWER * -1, DISTANCE_4, false, false);
    //Face towards center of field
    turnToRPSHeading(0, TURN_POWER, RIGHT, false, 1);
}
