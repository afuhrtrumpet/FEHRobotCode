#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHServo.h>
#include <FEHWONKA.h>
#include "constants.h"
#include "drivefunctions.h"
#include "otherfunctions.h"
#include "button.h"
#include "switch.h"
#include "skid.h"
#include "scoop.h"
#include "pin.h"
#include "charger.h"
#include "ramp.h"

int main(void)
{
    LCD.Clear( FEHLCD::Scarlet);
    LCD.SetFontColor( FEHLCD::Gray );

    wonka.InitializeMenu();
    wonka.Enable();

    while (true) {
        //Display options and wait for user to select an option
        LCD.Clear();
        LCD.WriteLine("Press the left button to calibrate RPS, the right button to calibrate encoders, or the middle button to start.");
        while (!buttons.LeftPressed() && !buttons.MiddlePressed() && !buttons.RightPressed());
        if (buttons.MiddlePressed()) {
            while (!buttons.MiddleReleased());
        } else if (buttons.LeftPressed()) {
            while (!buttons.LeftReleased());
            calibrateRPS();
            continue;
        } else {
            while (!buttons.RightReleased());
            calibrateEncoders();
            continue;
        }

        //Wait for start light and display opto value for debugging.
        waitForStartLight();

        //Starting actions: clear LCD and move forklift to start angle
        LCD.Clear();
        forklift.SetDegree(START_ANGLE);

        /* START MAIN SEQUENCE OF EVENTS */

        Button::Run();
        Switch::Run();
        int lightState = Skid::Run();
        Scoop::Run(lightState);
        //Pin::Run();
        Ramp::Run();
        Charger::Run();

        /* END MAIN SEQUENCE OF EVENTS */

        LCD.WriteLine("Press the middle button to reset.");
        while (!buttons.MiddlePressed());
        while (!buttons.MiddleReleased());
        Sleep(500);
    }
    return 0;
}
