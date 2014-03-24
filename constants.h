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
//Initial state of line following
#define LINE_NOT_SEEN 4

//Acceptable degrees of error in turn to RPS method
#define ANGLE_TOLERANCE 1.0

//Turn options to be used with RPS method 2
#define CLOSEST 0
#define LEFT 1
#define RIGHT 2
//Constants representing switches
#define FRONT_SWITCH 0
#define BACK_SWITCH 1
#define RIGHT_SWITCH 2

//Encoding methods check if motors are going the same amount at every multiple of this number of count
#define COUNTS_PER_CHECK 10

//Multiplier of left motor's power to match right
#define LEFT_MODIFIER 1.1

//Light must below this value to start
#define LIGHT_START_THRESHOLD 1.8
//Defined difference between red and blue light
#define RED_BLUE_THRESHOLD 1.3

#define TIMEOUT_DISTANCE 40

//Power going up ramp
#define RAMP_POWER 127
//Power going down ramp
#define RAMP_DOWN_POWER 70
//Power normally used when driving forward
#define FORWARD_POWER 100
//Power normally used when turning
#define TURN_POWER 90

//Angle forklift is placed to start
#define START_ANGLE 30
//Angle of forklift that makes it horizontal
#define HORIZONTAL 125
//Angle of forklift used to pull out the pin
#define PIN_ANGLE 30
//Angle to move to when lifting up skid
#define SKID_ANGLE 10
//Angle when dropping off skid
#define DROP_OFF_ANGLE 125
//Angle when flipping switch
#define SWITCH_ANGLE 75
//Angle when pressing button
#define BUTTON_ANGLE 45

//Starting angle of door
#define DOOR_CLOSED 100
#define DOOR_OPEN 30

//Constants used to determine distances/angles by the encoders
#define COUNTS_PER_INCH 4.5
#define COUNTS_PER_DEGREE_LEFT 0.457
#define COUNTS_PER_DEGREE_RIGHT 0.45

//Light position on course
#define LIGHT_X 0.0
#define LIGHT_Y 20.5

//Constants for light reading result
#define NO_LIGHT 0
#define BLUE 1
#define RED 2

//Distance robot will move to adjust to get to the light it is not on the light
#define ADJUST_DISTANCE 1.0

//Used to account for RPS delay at the end
#define RPS_CORRECTION_DISTANCE 3.5

//RPS distance tolerance
#define RPS_TOLERANCE 0.5

#define YELLOW_LEFT .242
#define YELLOW_RIGHT 1.103
#define YELLOW_CENTER 2.463

//Default thresholds for optosensors (probably wrong)
extern float yellowLeft;
extern float yellowCenter;
extern float yellowRight;
extern float blackLeft;
extern float blackCenter;
extern float blackRight;

extern float lightX;
extern float lightY;

extern float countsPerDegreeLeft;
extern float countsPerDegreeRight;

extern ButtonBoard buttons;
extern AnalogInputPin photosensor;
extern FEHMotor left;
extern FEHMotor right;
extern FEHServo forklift;
extern FEHServo door;
extern AnalogInputPin leftopto;
extern AnalogInputPin centeropto;
extern AnalogInputPin rightopto;
extern DigitalInputPin frontSwitch;
extern DigitalInputPin backSwitch;
extern DigitalInputPin rightSwitch;
extern DigitalInputPin stopSwitch;
extern FEHEncoder leftencoder;
extern FEHEncoder rightencoder;
extern FEHWONKA wonka;

#endif // CONSTANTS_H
