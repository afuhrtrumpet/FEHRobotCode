#ifndef DRIVEFUNCTIONS_H
#define DRIVEFUNCTIONS_H

//Function prototypes
void drive(float power, float distance, bool encodingCorrection);
bool driveAndCheckForLight(float power, float distance, bool encodingCorrection);
void driveUntilSwitchPress(float power, int switchId);
void turn(bool isRight, float power, int degrees, bool withSkid);
void setToForward();
void setToTurn(bool isLeft);
void followLineUntilSwitchPress(float power, int switchId, bool yellow);
void turnToRPSHeading(int degrees, float power, int turnOption, bool withSkid);
void waitForStartLight();
void calibrateOptosensors(bool yellow);

#endif // DRIVEFUNCTIONS_H
