#ifndef DRIVEFUNCTIONS_H
#define DRIVEFUNCTIONS_H

//Function prototypes
void drive(float, float, bool);
void driveAndCheckForLight(float, float, bool);
void driveUntilSwitchPress(float, int);
void turn(bool, float, int, bool);
void setToForward();
void setToTurn(bool);
void followLineUntilSwitchPress(float, int, bool);
void turnToRPSHeading(int, float, int, bool);
void waitForStartLight();
void calibrateOptosensors(bool);

#endif // DRIVEFUNCTIONS_H
