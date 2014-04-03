#ifndef DRIVEFUNCTIONS_H
#define DRIVEFUNCTIONS_H

//Function prototypes

//Drives the robot at the specified power for the specified distance (using the right encoder), and adjusts the left motor if encodingCorrection is true
//encodingCorrection: true if you want motors to adjust to equal power based on encoding (requires both encoders to work)
//debug: true if you want robot to stop and let you set the distance, then display that distance to screen.
void drive(float power, float distance, bool encodingCorrection, bool debug);

//Same as previous, but adds:
//leftModifier: number to multiply the left motor by
void drive(float power, float distance, bool encodingCorrection, bool debug, float leftModifier);

//Same as drive method, but returns the minimum photosensor value
//encodingCorrection: true if you want motors to adjust to equal power based on encoding(requires both encoders to work
int driveAndReadLight(float power, float distance, bool encodingCorrection);

//Drives the robot at the specified power until the switch specified by switchId is triggered (either FORKLIFT_SWITCH or BACK_SWITCH)
//timeoutDistance: robot stops no matter what after this distance has been traveled
//switchId: constant representing switch (use FRONT_SWITCH, BACK_SWITCH, RIGHT_SWITCH, etc)
//returns true if switch was in fact pressed, false if timeout was triggered
bool driveUntilSwitchPress(float power, int switchId, float timeoutDistance);

//Drives the robot until light is detected
//encodingCorrection: true if you want motors to adjust to equal power based on encoding(requires both encoders to work
void driveUntilLight(float power, bool encodingCorrection);

//Drive to the specified RPS heading
//y: true if coordinate specified is the y coordinate
//facingIncreasingDirection: true if direction robot is facing is increasing in either the x or y direction (specified by y)
void driveToRPSCoordinate(float power, float coordinate, bool y, bool facingIncreasingDirection);

//Same as previous, but adds
//degree: heading to periodically adjust to after imcrementally driving (if degree is negative nothing happens)
void driveToRPSCoordinate(float power, float coordinate, bool y, bool facingIncreasingDirection, float degree);

//Drive past the specified RPS coordinate
//y: true if coordinate specified is the y coordinate
//facingIncreasingDirection: true if direction robot is facing is increasing in either the x or y direction (specified by y)
bool drivePastRPSCoordinate(float power, float coordinate, bool y, bool facingIncreasingDirection, float timeoutSeconds);

//Uses side switches to keep robot against a wall while driving
//Bool right side: true if robot should stay aligned along the right side (only option at this point)
void driveAgainstWall(float power, float distance, bool rightSide);

//Turns the robot using shaft encoding; set withSkid to true if the robot is holding the skid during this turn
//withSkid: Used to adjust turning if robot has skid (does nothing right now because weight is not thrown off
void turn(bool isRight, float power, int degrees, bool withSkid);

//Follows line for a specified distance
//Yellow: true if line is yellow
void followLine(float power, float distance, bool yellow);

//Follows a line (yellow line if yellow is true) until the switch specified by switchId is triggered
//Yellow: true if line is yellow
//switchId: constant representing switch (use FRONT_SWITCH, BACK_SWITCH, RIGHT_SWITCH, etc)
void followLineUntilSwitchPress(float power, int switchId, bool yellow, float timeoutDistance);

//Turns the robot to face the RPS heading specified by degree.
//turnOption: LEFT, RIGHT, or CLOSEST
//withSkid: Used to adjust turning if robot has skid (does nothing right now because weight is not thrown off
void turnToRPSHeading(int degree, float power, int turnOption, bool withSkid, float turnMultiplier);

//Keeps turning until the robot is within an acceptable range of the specified angle.
void turnUntilRPSHeading(int angle, float power);

//Same as previous, but adds:
//timeoutSeconds: time until robot stops adjusting
void turnUntilRPSHeading(int angle, float power, float timeoutSeconds);

//Same as previous, but adds:
//turnModifier: number to multiply all incremental turns by
void turnUntilRPSHeading(int angle, float power, float timeoutSeconds, float turnModifier);

//Turns the robot until wonka records switch press, or until timeout is triggered
//Timeout angle: angle at which the robot stops no matter what
void turnUntilSwitchFlip(float power, bool isRight, float timeoutAngle);

//Sets robot to drive forward
//true if robot is going forward, false to go backwards
void setToForward(bool);

//Sets robots motors to turn
//true if robot is going left
void setToTurn(bool);

//Drives robot until button detects an additional press
//timeoutDistance: encoder recording at which robot stops
bool driveUntilButtonPress(float power, float timeoutDistance);

#endif
