#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHServo.h>
#include <FEHWONKA.h>

/* constants.h
 *=============
 *This file contains constants universal to various segments of the robot code.
 */

//Line is on right
#define LINE_ON_RIGHT 0
//On line, but moving right
#define ON_LINE_FIRST 1
//Line is on left
#define LINE_ON_LEFT 2
//On line, but moving left
#define ON_LINE_SECOND 3

//Acceptable degrees of error in turn to RPS method
#define ANGLE_TOLERANCE 1.0

//Turn options to be used with RPS method 2
#define CLOSEST 0
#define LEFT 1
#define RIGHT 2
//Constants representing switches
#define FORKLIFT_SWITCH 0
#define BACK_SWITCH 1

//Encoding methods check if motors are going the same amount at every multiple of this number of count
#define COUNTS_PER_CHECK 10

//Multiplier of left motor's power to match right
#define LEFT_MODIFIER 1.1

//Light thresholds
#define NO_LIGHT_THRESHOLD 1
#define RED_BLUE_THRESHOLD 0.7

#define TIMEOUT_DISTANCE 40

//Light must below this value to start
#define LIGHT_START_THRESHOLD 1.2
//Power normally used when driving forward
#define FORWARD_POWER 100
//Power normally used when turning
#define TURN_POWER 80
//Angle forklift is placed to start
#define START_ANGLE 0
//Angle of forklift that makes it horizontal
#define HORIZONTAL 125
//Angle of forklift used to pull out the pin
#define PIN_ANGLE 30
//Angle to move to when lifting up skid
#define SKID_ANGLE 20
//Angle when dropping off skid
#define DROP_OFF_ANGLE 135
//Constants used to determine distances/angles by the encoders
#define COUNTS_PER_INCH 5
#define COUNTS_PER_DEGREE 0.45

//Default thresholds for optosensors (probably wrong)
extern float yellowLeft;
extern float yellowCenter;
extern float yellowRight;
extern float blackLeft;
extern float blackCenter;
extern float blackRight;

extern ButtonBoard buttons;
extern AnalogInputPin photosensor;
extern FEHMotor left;
extern FEHMotor right;
extern FEHServo forklift;
extern AnalogInputPin leftopto;
extern AnalogInputPin centeropto;
extern AnalogInputPin rightopto;
extern DigitalInputPin forkliftSwitch;
extern DigitalInputPin backSwitch;
extern FEHEncoder leftencoder;
extern FEHEncoder rightencoder;
extern FEHWONKA wonka;

#endif // CONSTANTS_H
