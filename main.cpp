#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHServo.h>
#include <FEHWONKA.h>
#include "constants.h"
#include "drivefunctions.h"

float distance1 = 20;
float distance2 = 30;

int main(void)
{
    LCD.Clear( FEHLCD::Scarlet);
    LCD.SetFontColor( FEHLCD::Gray );

    wonka.InitializeMenu();
    wonka.Enable();

    while (true) {
        //Display options and wait for user to select an option
        LCD.WriteLine("Press the left button to calibrate optosensors or the middle button to start.");
        while (!buttons.LeftPressed() && !buttons.MiddlePressed());
        if (buttons.MiddlePressed()) {
            while (!buttons.MiddleReleased());
        } else {
            while (!buttons.LeftReleased());
            calibrateOptosensors(false);
            continue;
        }

        //Wait for start light and display opto value for debugging.
        waitForStartLight();

        //Starting actions: clear LCD and move forklift to start angle
        LCD.Clear();
        forklift.SetDegree(START_ANGLE);

        /* START MAIN SEQUENCE OF EVENTS */



        /* END MAIN SEQUENCE OF EVENTS */

        LCD.WriteLine("Press the middle button to reset.");
        while (!buttons.MiddlePressed());
        while (!buttons.MiddleReleased());
        Sleep(500);
    }
    return 0;

}
