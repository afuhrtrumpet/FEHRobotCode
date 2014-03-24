#include "drivefunctions.h"
#include "constants.h"
#include "math.h"

void drive(float power, float distance, bool encodingCorrection) {
    left.SetPower(power * LEFT_MODIFIER);
    right.SetPower(power);
    leftencoder.ResetCounts();
    rightencoder.ResetCounts();
    while (leftencoder.Counts() < distance * COUNTS_PER_INCH) {
        if (leftencoder.Counts() % COUNTS_PER_CHECK == 0 && encodingCorrection) {
            //Look at encoder counts and adjust right motor based on results
            if (leftencoder.Counts() != 0) {
                left.SetPower(power * leftencoder.Counts() / leftencoder.Counts());
            }
        }
        LCD.Clear();
        LCD.Write("The value of the left encoder is ");
        LCD.WriteLine(leftencoder.Counts());
        LCD.Write("The value of the right encoder is ");
        LCD.WriteLine(leftencoder.Counts());
        Sleep(50);
    }
    left.SetPower(0);
    right.SetPower(0);
}

float driveAndReadLight(float power, float distance, bool encodingCorrection) {
    float photoValue = 3.3;
    left.SetPower(power * LEFT_MODIFIER);
    right.SetPower(power);
    leftencoder.ResetCounts();
    rightencoder.ResetCounts();
    while (leftencoder.Counts() < distance * COUNTS_PER_INCH) {
        if (leftencoder.Counts() % COUNTS_PER_CHECK == 0 && encodingCorrection) {
            //Look at encoder counts and adjust right motor based on results
            if (leftencoder.Counts() != 0) {
                left.SetPower(power * leftencoder.Counts() / leftencoder.Counts());
            }
        }
        LCD.Clear();
        LCD.Write("The value of the left encoder is ");
        LCD.WriteLine(leftencoder.Counts());
        LCD.Write("The value of the right encoder is ");
        LCD.WriteLine(leftencoder.Counts());
        if (photosensor.Value() < photoValue) {
            photoValue = photosensor.Value();
        }
        Sleep(50);
    }
    left.SetPower(0);
    right.SetPower(0);
    return photoValue;
}

void driveUntilSwitchPress(float power, int switchId, float timeoutDistance) {
    leftencoder.ResetCounts();
    rightencoder.ResetCounts();
    left.SetPower(power * LEFT_MODIFIER);
    right.SetPower(power);
    while (((switchId == FRONT_SWITCH && frontSwitch.Value()) ||
            (switchId == BACK_SWITCH && backSwitch.Value()) ||
            (switchId == RIGHT_SWITCH && rightSwitch.Value())) &&
           leftencoder.Counts() < timeoutDistance * COUNTS_PER_INCH);
    left.Stop();
    right.Stop();
}

void driveUntilLight(float power, bool encodingCorrection) {
    left.SetPower(power * LEFT_MODIFIER);
    right.SetPower(power);
    leftencoder.ResetCounts();
    rightencoder.ResetCounts();
    while (photosensor.Value() > LIGHT_START_THRESHOLD) {
        if (leftencoder.Counts() % COUNTS_PER_CHECK == 0 && encodingCorrection) {
            //Look at encoder counts and adjust right motor based on results
            if (leftencoder.Counts() != 0) {
                right.SetPower(power * rightencoder.Counts() / leftencoder.Counts());
            }
        }
        LCD.Clear();
        LCD.Write("The value of the left encoder is ");
        LCD.WriteLine(leftencoder.Counts());
        LCD.Write("The value of the right encoder is ");
        LCD.WriteLine(leftencoder.Counts());
        Sleep(50);
    }
    left.SetPower(0);
    right.SetPower(0);
}

void driveToRPSCoordinate(float power, float coordinate, bool y, bool facingIncreasingDirection) {
    bool direction; //true if forward
    while ((y && abs(coordinate - wonka.Y()) > RPS_TOLERANCE) || (!y && abs(coordinate - wonka.X()) > RPS_TOLERANCE)) {
        if (y) {
            direction = wonka.Y() < coordinate == facingIncreasingDirection;
        } else {
            direction = wonka.X() < coordinate == facingIncreasingDirection;
        }
        setToForward(direction);
        LCD.Write("RPS X: ");
        LCD.WriteLine(wonka.X());
        LCD.Write("RPS Y: ");
        LCD.WriteLine(wonka.Y());
    }
    //drive(FORWARD_POWER * (direction ? -1 : 1), RPS_CORRECTION_DISTANCE, false);
    left.Stop();
    right.Stop();
}

void drivePastRPSCoordinate(float power, float coordinate, bool y, bool facingIncreasingDirection) {
    while (y && (facingIncreasingDirection && wonka.Y() < coordinate || !facingIncreasingDirection && wonka.Y() > coordinate) ||
           !y && (facingIncreasingDirection && wonka.X() < coordinate || !facingIncreasingDirection && wonka.X() > coordinate)) {
        left.SetPower(power);
        right.SetPower(power);
        LCD.Write("RPS X: ");
        LCD.WriteLine(wonka.X());
        LCD.Write("RPS Y: ");
        LCD.WriteLine(wonka.Y());
    }
    //drive(FORWARD_POWER * (direction ? -1 : 1), RPS_CORRECTION_DISTANCE, false);
    left.Stop();
    right.Stop();
}


void driveAgainstWall(float power, float distance, bool rightSide) {
    left.SetPower(power * LEFT_MODIFIER);
    right.SetPower(power);
    leftencoder.ResetCounts();
    rightencoder.ResetCounts();
    while (leftencoder.Counts() < distance * COUNTS_PER_INCH) {
            if (rightSide) {
                if (rightSwitch.Value()) {
                    right.SetPower(power / 2);
                } else {
                    right.SetPower(power);
                }
            }
            else {
                if (false) {
                    left.SetPower(power / 2);
                } else {
                    left.SetPower(power);
                }
            }
        LCD.Write("The value of the right encoder is ");
        LCD.WriteLine(leftencoder.Counts());
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
    while (leftencoder.Counts() < degrees * (isRight ? countsPerDegreeRight : countsPerDegreeLeft) / (withSkid ? 1.0 : 1.0)) {
        LCD.Clear();
        LCD.Write("The value of the left encoder is ");
        LCD.WriteLine(leftencoder.Counts());
        LCD.Write("The value of the right encoder is ");
        LCD.WriteLine(leftencoder.Counts());
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
            turn(false, power, leftDistance / 4, withSkid);
        } else {
            turn(true, power, rightDistance / 4, withSkid);
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

void followLine(float power, float distance, bool yellow) {
    int state = LINE_NOT_SEEN;
    leftencoder.ResetCounts();
    rightencoder.ResetCounts();

    while(leftencoder.Counts() < distance * COUNTS_PER_INCH)
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


void followLineUntilSwitchPress(float power, int switchId, bool yellow) {
    int state = LINE_ON_RIGHT;

    while((switchId == FRONT_SWITCH && frontSwitch.Value()) || (switchId == BACK_SWITCH && backSwitch.Value()))
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
        left.SetPower(TURN_POWER / 2);
    } else {
        left.SetPower(TURN_POWER * LEFT_MODIFIER);
        right.SetPower(TURN_POWER * LEFT_MODIFIER / 2);
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
                    (isRight && leftencoder.Counts() < timeoutAngle * countsPerDegreeLeft ||
                     !isRight && leftencoder.Counts() < timeoutAngle * countsPerDegreeRight)) {
        LCD.Clear();
        LCD.Write("The value of the left encoder is ");
        LCD.WriteLine(leftencoder.Counts());
        LCD.Write("The value of the right encoder is ");
        LCD.WriteLine(leftencoder.Counts());
        Sleep(50);

    }
}
