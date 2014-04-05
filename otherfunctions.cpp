#include "constants.h"
#include "otherfunctions.h"
#include "drivefunctions.h"

void waitForStartLight() {
    float start = TimeNow();
    while (photosensor.Value() > LIGHT_START_THRESHOLD && TimeNow() - start < 40.0) {
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
    LCD.Clear();
    if (yellow) {
        yellowLeft = (leftOff + leftOn) / 2;
        yellowRight = (rightOff + rightOn) / 2;
        yellowCenter = (centerOff + centerOn) / 2;
        LCD.WriteLine("Yellow Line");
        LCD.WriteLine("==========");
        LCD.Write("The new left threshold was set to ");
        LCD.WriteLine(yellowLeft);
        LCD.Write("The new right threshold was set to ");
        LCD.WriteLine(yellowRight);
        LCD.Write("The new center threshold was set to ");
        LCD.WriteLine(yellowCenter);
    } else {
        blackLeft = (leftOff + leftOn) / 2;
        blackRight = (rightOff + rightOn) / 2;
        blackCenter = (centerOff + centerOn) / 2;
        LCD.WriteLine("Black Line");
        LCD.WriteLine("==========");
        LCD.Write("The new left threshold was set to ");
        LCD.WriteLine(blackLeft);
        LCD.Write("The new right threshold was set to ");
        LCD.WriteLine(blackRight);
        LCD.Write("The new center threshold was set to");
        LCD.WriteLine(blackCenter);
    }
    LCD.WriteLine("Press the middle button to continue.");
    while (!buttons.MiddlePressed());
    while (!buttons.MiddleReleased());
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

void calibrateEncoders() {
    LCD.WriteLine("Press left button to calibrate left turning, right button to calibrate right turning, middle button to calibrate straight driving.");
    while (!buttons.LeftPressed() && !buttons.RightPressed() && !buttons.MiddlePressed());
    if (buttons.LeftPressed()) {
        while (!buttons.LeftReleased());
        LCD.Clear();
        LCD.WriteLine("Press the switch after 4 revolutions.");
        LCD.WriteLine("Press the middle button to begin.");
        while (!buttons.MiddlePressed());
        while (!buttons.MiddleReleased());
        left.SetPower(-TURN_POWER);
        right.SetPower(TURN_POWER);
        leftencoder.ResetCounts();
        rightencoder.ResetCounts();
        while (stopSwitch.Value());
        LCD.Clear();
        left.Stop();
        right.Stop();
        LCD.Write("The left encoder total was ");
        LCD.WriteLine(leftencoder.Counts());
        LCD.Write("The right encoder total was ");
        LCD.WriteLine(rightencoder.Counts());
        LCD.Write("The left counts per degree was ");
        LCD.WriteLine(leftencoder.Counts() / (4 * 360.0));
        LCD.Write("The right counts per degree was ");
        LCD.WriteLine(rightencoder.Counts() / (4 * 360.0));
        countsPerDegreeLeft = leftencoder.Counts() / (4 * 360.0);
    } else if (buttons.RightPressed()) {
        while (!buttons.RightReleased());
        LCD.Clear();
        LCD.WriteLine("Press the switch after 4 revolutions.");
        LCD.WriteLine("Press the middle button to begin.");
        while (!buttons.MiddlePressed());
        while (!buttons.MiddleReleased());
        left.SetPower(TURN_POWER);
        right.SetPower(-TURN_POWER);
        leftencoder.ResetCounts();
        rightencoder.ResetCounts();
        while (stopSwitch.Value());
        LCD.Clear();
        left.Stop();
        right.Stop();
        LCD.Write("The left encoder total was ");
        LCD.WriteLine(leftencoder.Counts());
        LCD.Write("The right encoder total was ");
        LCD.WriteLine(rightencoder.Counts());
        LCD.Write("The left counts per degree was ");
        LCD.WriteLine(leftencoder.Counts() / (4 * 360.0));
        LCD.Write("The right counts per degree was ");
        LCD.WriteLine(rightencoder.Counts() / (4 * 360.0));
        countsPerDegreeRight = leftencoder.Counts() / (4 * 360.0);
    } else {
        while (!buttons.MiddleReleased());
        LCD.Clear();
        LCD.WriteLine("Press the switch after 3 feet.");
        LCD.WriteLine("Press the middle button to begin.");
        while (!buttons.MiddlePressed());
        while (!buttons.MiddleReleased());
        left.SetPower(TURN_POWER);
        right.SetPower(TURN_POWER);
        leftencoder.ResetCounts();
        rightencoder.ResetCounts();
        while (stopSwitch.Value());
        LCD.Clear();
        left.Stop();
        right.Stop();
        LCD.Write("The left encoder total was ");
        LCD.WriteLine(leftencoder.Counts());
        LCD.Write("The right encoder total was ");
        LCD.WriteLine(rightencoder.Counts());
        LCD.Write("The left counts per inch was ");
        LCD.WriteLine(leftencoder.Counts() / (36.0));
        LCD.Write("The right counts per degree was ");
        LCD.WriteLine(rightencoder.Counts() / (36.0));
    }
    LCD.WriteLine("Press the middle button to end again.");
    while (!buttons.MiddlePressed());
    while (!buttons.MiddleReleased());
}

void calibrateRPS() {
    while (!buttons.MiddlePressed()) {
        LCD.Clear();
        LCD.WriteLine("Place the robot facing the pin parallel to the skid.");
        LCD.Write("X: ");
        LCD.WriteLine(wonka.X());
        Sleep(20);
    }
    while (!buttons.MiddleReleased());
    skidX = wonka.X();
    while (!buttons.MiddlePressed()) {
        LCD.Clear();
        LCD.WriteLine("Place the robot facing the button and align it with the ramp.");
        LCD.Write("X: ");
        LCD.WriteLine(wonka.X());
        Sleep(20);
    }
    while (!buttons.MiddleReleased());
    rampX = wonka.X();
    LCD.Clear();
    LCD.Write("The new skid X is ");
    LCD.WriteLine(skidX);
    LCD.Write("The new ramp X is ");
    LCD.WriteLine(rampX);
    while (!buttons.MiddlePressed());
    while (!buttons.MiddleReleased());
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

void resetRPSCoordinates() {
    rampX = RAMP_X;
    skidX = SKID_X;
    LCD.WriteLine("RPS coordinates reset. Press the middle button to continue.");
    while (!buttons.MiddlePressed());
    while (!buttons.MiddleReleased());
}

int adjustToLight() {
    int lightState = readLight();
    while (lightState == NO_LIGHT) {
        float y = wonka.Y();
        if (y < LIGHT_Y) { //Robot is in front of light
            drive(FORWARD_POWER * -1, ADJUST_DISTANCE, false, false);
        } else { //Robot is behind light
            drive(FORWARD_POWER, ADJUST_DISTANCE, false, false);
        }
        lightState = readLight();
    }
    return lightState;
}

void dropOffScoop() {
    door.SetDegree(DOOR_OPEN);
    Sleep(200);
    drive(FORWARD_POWER, 2.0, false, false);
    door.SetDegree(DOOR_CLOSED);
}
