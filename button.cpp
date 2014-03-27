#include "button.h"
#include "constants.h"
#include "drivefunctions.h"

#define DISTANCE_1 9.0
#define DISTANCE_2 9.0
#define DISTANCE_3 2.0
#define DISTANCE_4 4.0
#define PRESS_DISTANCE 0.5

#define MAX_TIMES 10

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
    int times = 0;
    while (wonka.OvenPressed() < wonka.Oven() && times < MAX_TIMES) {
        int previousPresses = wonka.OvenPressed();
        //Press button
        bool hit = driveUntilSwitchPress(FORWARD_POWER, FRONT_SWITCH, 8);
        drive(FORWARD_POWER, PRESS_DISTANCE, false, false);
        drive(-1 * FORWARD_POWER, DISTANCE_3, false, false);
        //If the button was not pressed
        /*if (!hit) {
            turnToRPSHeading(0, TURN_POWER, RIGHT, false, 1);
            drive(FORWARD_POWER, 0.5, false, false);
            turnToRPSHeading(90, TURN_POWER, LEFT, false, 1);
        } else*/ if (previousPresses == wonka.OvenPressed()) {
            //Adjust to horizontal
            turnToRPSHeading(90, TURN_POWER, CLOSEST, false, 1);
        turn(true, TURN_POWER, 5, false);
        }
        times++;
    }
    drive(FORWARD_POWER * -1, DISTANCE_4, false, false);
    //Face towards center of field
    turnToRPSHeading(0, TURN_POWER, RIGHT, false, 1);
}
