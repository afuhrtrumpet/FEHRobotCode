#include "drivefunctions.h"
#include "constants.h"

void driveUntilSwitchPress(float power, int switchId) {
    leftencoder.ResetCounts();
    rightencoder.ResetCounts();
    left.SetPower(power * LEFT_MODIFIER);
    right.SetPower(power);
    while ((switchId == FORKLIFT_SWITCH && forkliftSwitch.Value()) || switchId == BACK_SWITCH && backSwitch.Value() && rightencoder.Counts() < TIMEOUT_DISTANCE * COUNTS_PER_INCH) {}
    left.SetPower(0);
    right.SetPower(0);
}

void turn(bool isRight, float power, int degrees, bool withSkid) {
    if (!isRight) {
        right.SetPower(power);
        left.SetPower(-1 * power * LEFT_MODIFIER);
    } else {
        right.SetPower(-1 * power);
        left.SetPower(power * LEFT_MODIFIER);
    }
    leftencoder.ResetCounts();
    rightencoder.ResetCounts();
    while (rightencoder.Counts() < degrees * COUNTS_PER_DEGREE / (withSkid ? 1.0 : 1.0)) {
        LCD.Clear();
        LCD.Write("The value of the left encoder is ");
        LCD.WriteLine(leftencoder.Counts());
        LCD.Write("The value of the right encoder is ");
        LCD.WriteLine(rightencoder.Counts());
        Sleep(50);
    }
    left.SetPower(0);
    right.SetPower(0);
}

void turnToRPSHeading(int angle, float power, int turnOption, bool withSkid) {
    float leftDistance;
    if (angle < wonka.Heading()) {
        leftDistance = 180 + angle - wonka.Heading();
    } else {
        leftDistance = angle - wonka.Heading();
    }
    float rightDistance;
    if (angle > wonka.Heading()) {
        rightDistance = 180 + wonka.Heading() - angle;
    } else {
        rightDistance = wonka.Heading() - angle;
    }
    /* FOR DEBUGGING *
    LCD.Write("RPS Heading is ");
    LCD.WriteLine(wonka.Heading());
    LCD.Write("Estimated leftward angle needed is ");
    LCD.WriteLine(leftDistance);
    LCD.Write("Estimated rightward angle needed is ");
    LCD.WriteLine(rightDistance);
    while (!buttons.MiddlePressed());
    while (!buttons.MiddleReleased());
    /* END DEBUGGING */
    switch (turnOption) {
    case CLOSEST:
        if (leftDistance < rightDistance) {
            turn(false, power, leftDistance, withSkid);
        } else {
            turn(true, power, rightDistance, withSkid);
        }
        break;
    case LEFT:
        turn(false, power, leftDistance, withSkid);
        break;
    case RIGHT:
        turn(true, power, rightDistance, withSkid);
        break;
    }
}

void followLineUntilSwitchPress(float power, int switchId, bool yellow) {
    int state = LINE_ON_RIGHT;

    while((switchId == FORKLIFT_SWITCH && forkliftSwitch.Value()) || (switchId == BACK_SWITCH && backSwitch.Value()))
    {
        if ((yellow && centeropto.Value() < yellowCenter) || (!yellow && centeropto.Value() > blackCenter)) {
            setToForward();
            if (state == LINE_ON_RIGHT) {
                state = ON_LINE_FIRST;
            } else if (state == LINE_ON_LEFT) {
                state = ON_LINE_SECOND;
            }
        } else if ((yellow && leftopto.Value() < yellowLeft) || (!yellow && leftopto.Value() > blackLeft)) {
            setToTurn(true);
            state = LINE_ON_LEFT;
        } else if ((yellow && rightopto.Value() < yellowRight) || (!yellow && rightopto.Value() > blackRight)) {
            setToTurn(false);
            state = LINE_ON_RIGHT;
        } else {
            switch (state) {
            case LINE_ON_LEFT:
                setToTurn(true);
                break;
            case ON_LINE_FIRST:
                state = LINE_ON_RIGHT;
                setToTurn(false);
                break;
            case LINE_ON_RIGHT:
                setToTurn(false);
                break;
            case ON_LINE_SECOND:
                state = LINE_ON_LEFT;
                setToTurn(true);
                break;
            }
        }
        LCD.Clear();
        switch (state) {
        case LINE_ON_LEFT:
            LCD.WriteLine("Line on the left");
            break;
        case ON_LINE_FIRST:
            LCD.WriteLine("On line, going right");
            break;
        case LINE_ON_RIGHT:
            LCD.WriteLine("Line on the right");
            break;
        case ON_LINE_SECOND:
            LCD.WriteLine("On light, going left");
            break;
        }
        LCD.Write("Left opto value: ");
        LCD.WriteLine(leftopto.Value());
        LCD.Write("Center opto value: ");
        LCD.WriteLine(centeropto.Value());
        LCD.Write("Right opto value: ");
        LCD.WriteLine(rightopto.Value());
        Sleep(50);
    }
    left.SetPower(0);
    right.SetPower(0);
}

void setToForward() {
    left.SetPower(FORWARD_POWER * LEFT_MODIFIER);
    right.SetPower(FORWARD_POWER);
}

void setToTurn (bool isLeft) {
    if (isLeft) {
        right.SetPower(TURN_POWER);
        left.SetPower(0);
    } else {
        left.SetPower(TURN_POWER * LEFT_MODIFIER);
        right.SetPower(0);
    }
}

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
