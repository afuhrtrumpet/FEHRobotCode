#ifndef DRIVEFUNCTIONS_H
#define DRIVEFUNCTIONS_H

//Function prototypes

//Drives the robot at the specified power for the specified distance (using the right encoder), and adjusts the left motor if encodingCorrection is true
void drive(float power, float distance, bool encodingCorrection);

//Same as drive method, but returns the minimum photosensor value
float driveAndReadLight(float power, float distance, bool encodingCorrection);

//Drives the robot at the specified power until the switch specified by switchId is triggered (either FORKLIFT_SWITCH or BACK_SWITCH)
void driveUntilSwitchPress(float power, int switchId, float timeoutDistance);

//Drives the robot until light is detected
void driveUntilLight(float power, bool encodingCorrection);

//Drive to the specified RPS heading
void driveToRPSCoordinate(float power, float coordinate, bool y, bool facingIncreasingDirection);

//Turns the robot using shaft encoding; set withSkid to true if the robot is holding the skid during this turn
void turn(bool isRight, float power, int degrees, bool withSkid);

//Follows a line (yellow line if yellow is true) until the switch specified by switchId is triggered
void followLineUntilSwitchPress(float power, int switchId, bool yellow);

//Turns the robot to face the RPS heading specified by degree. Turn options are LEFT, RIGHT, and CLOSEST
void turnToRPSHeading(int degree, float power, int turnOption, bool withSkid);

void setToForward(bool);
void setToTurn(bool);

#endif
