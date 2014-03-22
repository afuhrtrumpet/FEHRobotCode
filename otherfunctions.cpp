#include "constants.h"
#include "otherfunctions.h"
#include "drivefunctions.h"

void waitForStartLight() {
    while (photosensor.Value() > LIGHT_START_THRESHOLD) {
        LCD.Clear();
        LCD.Write("Waiting for start light.\nValue is currently ");
        LCD.WriteLine(photosensor.Value());
        Sleep(200);
    }
}

void calibrateOptosensors(bool yellow) {
    LCD.WriteLine("Place robot off line.");
    while (!buttons.MiddlePressed());
    while (!buttons.MiddleReleased());
    float leftOff = leftopto.Value();
    float rightOff = rightopto.Value();
    float centerOff = centeropto.Value();
    LCD.WriteLine("Place left on line.");
    while (!buttons.LeftPressed());
    while (!buttons.LeftReleased());
    float leftOn = leftopto.Value();
    LCD.WriteLine("Place right on line.");
    while (!buttons.RightPressed());
    while (!buttons.RightReleased());
    float rightOn = rightopto.Value();
    LCD.WriteLine("Place center on line.");
    while (!buttons.MiddlePressed());
    while (!buttons.MiddleReleased());
    float centerOn = centeropto.Value();
    //Update thresholds
    if (yellow) {
        yellowLeft = (leftOff + leftOn) / 2;
        yellowRight = (rightOff + rightOn) / 2;
        yellowCenter = (centerOff + centerOn) / 2;
    } else {
        blackLeft = (leftOff + leftOn) / 2;
        blackRight = (rightOff + rightOn) / 2;
        blackCenter = (centerOff + centerOn) / 2;
    }
    Sleep(500);
}

void calibrateLightPosition() {
    while (!buttons.MiddlePressed()) {
        LCD.Clear();
        LCD.WriteLine("Press middle button to set RPS coordinates.");
        LCD.Write("X: ");
        LCD.WriteLine(wonka.X());
        LCD.Write("Y: ");
        LCD.WriteLine(wonka.Y());
    }
    while (!buttons.MiddleReleased());
    lightX = wonka.X();
    lightY = wonka.Y();
    LCD.Clear();
    LCD.WriteLine("RPS coordinates set.");
    LCD.Write("X: ");
    LCD.WriteLine(lightX);
    LCD.Write("Y: ");
    LCD.WriteLine(lightY);
    Sleep(50);
}

int readLight() {
    LCD.Clear();
    LCD.Write("Photosensor value is ");
    LCD.WriteLine(photosensor.Value());
    if (photosensor.Value() > LIGHT_START_THRESHOLD)
        return NO_LIGHT;
    else if (photosensor.Value() > RED_BLUE_THRESHOLD)
        return BLUE;
    else
        return RED;
}

int adjustToLight() {
    int lightState = readLight();
    while (lightState == NO_LIGHT) {
        float y = wonka.Y();
    if (y < LIGHT_Y) { //Robot is in front of light
        drive(FORWARD_POWER * -1, ADJUST_DISTANCE, false);
    } else { //Robot is behind light
        drive(FORWARD_POWER, ADJUST_DISTANCE, false);
    }
        lightState = readLight();
    }
    return lightState;
}

void dropOffScoop() {
    door.SetDegree(DOOR_OPEN);
    Sleep(2000);
    door.SetDegree(DOOR_CLOSED);
}
