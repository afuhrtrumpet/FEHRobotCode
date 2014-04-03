#include "button.h"
#include "constants.h"
#include "drivefunctions.h"

#define DISTANCE_1 5.0
#define DISTANCE_2 8.0
#define DISTANCE_3 1.5
#define DISTANCE_4 4.0
#define DISTANCE_5 3.0

#define DISTANCE_HIT 1.0
#define DISTANCE_NOT_HIT 1.25

#define MAX_TIMES 7

/* BUTTON
 *========
 *Takes robot from beginning of course
 *to facing towards the center after pressing the button */

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
    Sleep(100);
    turnUntilRPSHeading(90, TURN_POWER);
    drive(FORWARD_POWER, DISTANCE_5, false, false);
    //Press button until button has been pressed right number of times
    int times = 0;
    int previousMisses = 0;
        //Go until button has been pressed correct number of times or attempts time out
    while (wonka.OvenPressed() < wonka.Oven() && times < MAX_TIMES) {
        int previousPresses = wonka.OvenPressed();
        //Press button
        //Go slower if there is one press remaining to avoid double pressing
        if (wonka.OvenPressed() == wonka.Oven() - 1) {
            driveUntilButtonPress(LAST_PRESS_POWER, 5);
        } else {
            driveUntilButtonPress(FORWARD_POWER, 5);
        }
        Sleep(50);
                //Determine if button was hit. If it was, drive less backwards
        if (previousPresses == wonka.OvenPressed()) {
            drive(-1 * FORWARD_POWER, DISTANCE_NOT_HIT, false, false);
            //Adjust to horizontal
            Sleep(100);
            previousMisses++;
            turnToRPSHeading(90, TURN_POWER, CLOSEST, false, 0.5);
            if (previousMisses != 0 && previousMisses % 2 == 0) {
                turn(true, TURN_POWER, 3, false);
            }
        } else {
            drive(-1 * FORWARD_POWER, DISTANCE_HIT, false, false);
            previousMisses = 0;
        }
        times++;
    }
    drive(FORWARD_POWER * -1, DISTANCE_4, false, false);
    //Face towards center of field
    turnToRPSHeading(0, TURN_POWER, RIGHT, false, 1);
}
