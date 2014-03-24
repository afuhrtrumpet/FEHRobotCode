#ifndef DRIVEFUNCTIONS_H
#define DRIVEFUNCTIONS_H

//Function prototypes

//Drives the robot at the specified power for the specified distance (using the right encoder), and adjusts the left motor if encodingCorrection is true
//encodingCorrection: true if you want motors to adjust to equal power based on encoding (requires both encoders to work)
//debug: true if you want robot to stop and let you set the distance, then display that distance to screen.
void drive(float power, float distance, bool encodingCorrection, bool debug);

//Same as drive method, but returns the minimum photosensor value
float driveAndReadLight(float power, float distance, bool encodingCorrection);

//Drives the robot at the specified power until the switch specified by switchId is triggered (either FORKLIFT_SWITCH or BACK_SWITCH)
void driveUntilSwitchPress(float power, int switchId, float timeoutDistance);

//Drives the robot until light is detected
void driveUntilLight(float power, bool encodingCorrection);

//Drive to the specified RPS heading
void driveToRPSCoordinate(float power, float coordinate, bool y, bool facingIncreasingDirection);

//Drive past the specified RPS coordinate
void drivePastRPSCoordinate(float power, float coordinate, bool y, bool facingIncreasingDirection);

//Uses side switches to keep robot against a wall while driving
void driveAgainstWall(float power, float distance, bool rightSide);

//Turns the robot using shaft encoding; set withSkid to true if the robot is holding the skid during this turn
void turn(bool isRight, float power, int degrees, bool withSkid);

//Follows line for a specified distance
void followLine(float power, float distance, bool yellow);

//Follows a line (yellow line if yellow is true) until the switch specified by switchId is triggered
void followLineUntilSwitchPress(float power, int switchId, bool yellow);

//Turns the robot to face the RPS heading specified by degree. Turn options are LEFT, RIGHT, and CLOSEST
void turnToRPSHeading(int degree, float power, int turnOption, bool withSkid);

//Turns the robot until wonka records switch press, or until timeout is triggered
void turnUntilSwitchFlip(float power, bool isRight, float timeoutAngle);

void setToForward(bool);
void setToTurn(bool);

#endif
