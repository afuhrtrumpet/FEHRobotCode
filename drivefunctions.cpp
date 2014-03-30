#include "drivefunctions.h"
#include "constants.h"
#include "math.h"

void drive(float power, float distance, bool encodingCorrection, bool debug) {
    if (debug) {
        leftencoder.ResetCounts();
        rightencoder.ResetCounts();
        LCD.WriteLine("Press the switch to begin moving.");
        while (stopSwitch.Value());
        while (!stopSwitch.Value());
        left.SetPower(power * LEFT_MODIFIER);
        right.SetPower(power);
        while (stopSwitch.Value());
        while (!stopSwitch.Value());
        left.Stop();
        right.Stop();
        LCD.Clear();
        LCD.Write("The distance traveled was ");
        LCD.WriteLine(rightencoder.Counts() * COUNTS_PER_INCH);
        LCD.WriteLine("Press the switch to resume.");
        while (stopSwitch.Value());
        while (!stopSwitch.Value());
    } else {
        left.SetPower(power * LEFT_MODIFIER);
        right.SetPower(power);
        leftencoder.ResetCounts();
        rightencoder.ResetCounts();
        while (rightencoder.Counts() < distance * COUNTS_PER_INCH) {
            if (rightencoder.Counts() % COUNTS_PER_CHECK == 0 && encodingCorrection) {
                //Look at encoder counts and adjust right motor based on results
                if (rightencoder.Counts() != 0) {
                    left.SetPower(power * rightencoder.Counts() / rightencoder.Counts());
                }
            }
            LCD.Clear();
            LCD.Write("The value of the left encoder is ");
            LCD.WriteLine(rightencoder.Counts());
            LCD.Write("The value of the right encoder is ");
            LCD.WriteLine(rightencoder.Counts());
            Sleep(50);
        }
        left.SetPower(0);
        right.SetPower(0);
    }
}

float driveAndReadLight(float power, float distance, bool encodingCorrection) {
    float photoValue = 3.3;
    left.SetPower(power * LEFT_MODIFIER);
    right.SetPower(power);
    leftencoder.ResetCounts();
    rightencoder.ResetCounts();
    while (rightencoder.Counts() < distance * COUNTS_PER_INCH) {
        if (rightencoder.Counts() % COUNTS_PER_CHECK == 0 && encodingCorrection) {
            //Look at encoder counts and adjust right motor based on results
            if (rightencoder.Counts() != 0) {
                left.SetPower(power * rightencoder.Counts() / rightencoder.Counts());
            }
        }
        LCD.Clear();
        LCD.Write("The value of the left encoder is ");
        LCD.WriteLine(rightencoder.Counts());
        LCD.Write("The value of the right encoder is ");
        LCD.WriteLine(rightencoder.Counts());
        if (photosensor.Value() < photoValue) {
            photoValue = photosensor.Value();
        }
        Sleep(50);
    }
    left.SetPower(0);
    right.SetPower(0);
    return photoValue;
}

bool driveUntilSwitchPress(float power, int switchId, float timeoutDistance) {
    leftencoder.ResetCounts();
    rightencoder.ResetCounts();
    left.SetPower(power * LEFT_MODIFIER);
    right.SetPower(power);
    while (((switchId == FRONT_SWITCH && frontSwitch.Value()) ||
            (switchId == BACK_SWITCH && backSwitch.Value()) ||
            (switchId == RIGHT_SWITCH && rightSwitch.Value() ||
             (switchId == FORKLIFT_SWITCH && forkliftSwitch.Value()))) &&
                    rightencoder.Counts() < timeoutDistance * COUNTS_PER_INCH);
    left.Stop();
    right.Stop();
    return rightencoder.Counts() < timeoutDistance * COUNTS_PER_INCH;
}

void driveUntilLight(float power, bool encodingCorrection) {
    left.SetPower(power * LEFT_MODIFIER);
    right.SetPower(power);
    leftencoder.ResetCounts();
    rightencoder.ResetCounts();
    while (photosensor.Value() > LIGHT_START_THRESHOLD) {
        if (rightencoder.Counts() % COUNTS_PER_CHECK == 0 && encodingCorrection) {
            //Look at encoder counts and adjust right motor based on results
            if (rightencoder.Counts() != 0) {
                right.SetPower(power * rightencoder.Counts() / rightencoder.Counts());
            }
        }
        LCD.Clear();
        LCD.Write("The value of the left encoder is ");
        LCD.WriteLine(rightencoder.Counts());
        LCD.Write("The value of the right encoder is ");
        LCD.WriteLine(rightencoder.Counts());
        Sleep(50);
    }
    left.SetPower(0);
    right.SetPower(0);
}

void driveToRPSCoordinate(float power, float coordinate, bool y, bool facingIncreasingDirection) {
    float start = TimeNow();
    bool direction; //true if forward
    while ((y && abs(coordinate - wonka.Y()) > RPS_DISTANCE_TOLERANCE) || (!y && abs(coordinate - wonka.X()) > RPS_DISTANCE_TOLERANCE) && (TimeNow() - start) < LINEAR_TIME_LIMIT) {
        if (y) {
            direction = wonka.Y() < coordinate == facingIncreasingDirection;
        } else {
            direction = wonka.X() < coordinate == facingIncreasingDirection;
        }
        drive(FORWARD_POWER * (direction ? 1 : -1), RPS_DISTANCE_TOLERANCE / 2, false, false);
        LCD.Write("RPS X: ");
        LCD.WriteLine(wonka.X());
        LCD.Write("RPS Y: ");
        LCD.WriteLine(wonka.Y());
        Sleep(RPS_DELAY_TIME);
    }
    left.Stop();
    right.Stop();
}

bool drivePastRPSCoordinate(float power, float coordinate, bool y, bool facingIncreasingDirection, float timeoutSeconds) {
    float start = TimeNow();
    while (y && (facingIncreasingDirection && wonka.Y() < coordinate || !facingIncreasingDirection && wonka.Y() > coordinate) ||
                    !y && (facingIncreasingDirection && wonka.X() < coordinate || !facingIncreasingDirection && wonka.X() > coordinate)
           && (TimeNow() - start) < timeoutSeconds) {
        left.SetPower(power);
        right.SetPower(power);
        LCD.Write("RPS X: ");
        LCD.WriteLine(wonka.X());
        LCD.Write("RPS Y: ");
        LCD.WriteLine(wonka.Y());
    }
    left.Stop();
    right.Stop();
    return (TimeNow() - start) < timeoutSeconds;
}


void driveAgainstWall(float power, float distance, bool rightSide) {
    leftencoder.ResetCounts();
    rightencoder.ResetCounts();
    left.SetPower(power * LEFT_MODIFIER);
    right.SetPower(power);
    while (rightencoder.Counts() < distance * COUNTS_PER_INCH) {
        if (rightSide) {
            if (rightSwitch.Value()) {
                right.SetPower(power * 3 / 4);
            } else {
                right.SetPower(power);
            }
        }
        else {
            if (false) {
                left.SetPower(power * 3 / 4);
            } else {
                left.SetPower(power);
            }
        }
        LCD.Write("The value of the right encoder is ");
        LCD.WriteLine(rightencoder.Counts());
        Sleep(50);
    }
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
    while (rightencoder.Counts() < degrees * (isRight ? countsPerDegreeRight : countsPerDegreeLeft) / (withSkid ? 1.0 : 1.0)) {
        LCD.Clear();
        LCD.Write("The value of the left encoder is ");
        LCD.WriteLine(rightencoder.Counts());
        LCD.Write("The value of the right encoder is ");
        LCD.WriteLine(rightencoder.Counts());
        Sleep(50);
    }
    left.SetPower(0);
    right.SetPower(0);
}

void turnToRPSHeading(int angle, float power, int turnOption, bool withSkid, float turnMultiplier) {
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
            turn(false, power, leftDistance * turnMultiplier, withSkid);
        } else {
            turn(true, power, rightDistance * turnMultiplier, withSkid);
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

void turnUntilRPSHeading(int angle, float power) {
    int start = TimeNow();
    while (abs(angle - wonka.Heading()) > RPS_TURNING_TOLERANCE && (TimeNow() - start) < TURN_TIME_LIMIT) {
        turnToRPSHeading(angle, power, CLOSEST, false, 0.25);
        Sleep(RPS_DELAY_TIME);
    }
}

void followLine(float power, float distance, bool yellow) {
    int state = LINE_NOT_SEEN;
    leftencoder.ResetCounts();
    rightencoder.ResetCounts();

    while(rightencoder.Counts() < distance * COUNTS_PER_INCH)
    {
        if ((yellow && centeropto.Value() < yellowCenter) || (!yellow && centeropto.Value() > blackCenter)) {
            setToForward(true);
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
            case LINE_NOT_SEEN:
                setToForward(true);
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
        Sleep(25);
    }
    left.SetPower(0);
    right.SetPower(0);
}


void followLineUntilSwitchPress(float power, int switchId, bool yellow, float timeoutDistance) {
    int state = LINE_NOT_SEEN;

    leftencoder.ResetCounts();
    rightencoder.ResetCounts();

    while(((switchId == FRONT_SWITCH && frontSwitch.Value())
           || (switchId == BACK_SWITCH && backSwitch.Value())
           || (switchId == RIGHT_SWITCH && rightSwitch.Value())
           || (switchId == FORKLIFT_SWITCH && forkliftSwitch.Value()))
                    && rightencoder.Counts() < timeoutDistance * COUNTS_PER_INCH) {
        if ((yellow && centeropto.Value() < yellowCenter) || (!yellow && centeropto.Value() > blackCenter)) {
            setToForward(true);
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
            case LINE_NOT_SEEN:
                setToForward(true);
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
        case LINE_NOT_SEEN:
            LCD.WriteLine("Line not detected");
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

void setToForward(bool forward) {
    if (forward) {
        left.SetPower(FORWARD_POWER * LEFT_MODIFIER);
        right.SetPower(FORWARD_POWER);
    } else {
        left.SetPower(-1 * FORWARD_POWER * LEFT_MODIFIER);
        right.SetPower(-1 * FORWARD_POWER);
    }
}

void setToTurn (bool isLeft) {
    if (isLeft) {
        right.SetPower(TURN_POWER);
        left.SetPower(TURN_POWER * 3 / 4);
    } else {
        left.SetPower(TURN_POWER * LEFT_MODIFIER);
        right.SetPower(TURN_POWER * LEFT_MODIFIER * 3 / 4);
    }
}

void turnUntilSwitchFlip(float power, bool isRight, float timeoutAngle) {
    rightencoder.ResetCounts();
    leftencoder.ResetCounts();
    if (!isRight) {
        right.SetPower(power);
        left.SetPower(-1 * power * LEFT_MODIFIER);
    } else {
        right.SetPower(-1 * power);
        left.SetPower(power * LEFT_MODIFIER);
    }
    while (!wonka.Chute() &&
                    (isRight && rightencoder.Counts() < timeoutAngle * countsPerDegreeLeft ||
                     !isRight && rightencoder.Counts() < timeoutAngle * countsPerDegreeRight)) {
        LCD.Clear();
        LCD.Write("The value of the left encoder is ");
        LCD.WriteLine(rightencoder.Counts());
        LCD.Write("The value of the right encoder is ");
        LCD.WriteLine(rightencoder.Counts());
        Sleep(50);

    }
}

bool driveUntilButtonPress(float power, float timeoutDistance) {
    leftencoder.ResetCounts();
    rightencoder.ResetCounts();
    left.SetPower(power * LEFT_MODIFIER);
    right.SetPower(power);
    int previousPresses = wonka.OvenPressed();
    while (wonka.OvenPressed() == previousPresses && rightencoder.Counts() < timeoutDistance * COUNTS_PER_INCH) {
        LCD.Clear();
        LCD.Write("The value of the left encoder is ");
        LCD.WriteLine(leftencoder.Counts());
        LCD.Write("The value of the right encoder is ");
        LCD.WriteLine(rightencoder.Counts());
        Sleep(50);
    }
    left.Stop();
    right.Stop();
    return rightencoder.Counts() < timeoutDistance * COUNTS_PER_INCH;
}
