#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHServo.h>
#include <FEHWONKA.h>
#include "constants.h"

//Default thresholds for optosensors (probably wrong)
float yellowLeft = 0.5;
float yellowCenter = 2.7;
float yellowRight = 2.45;
float blackLeft;
float blackCenter;
float blackRight;
float lightX = LIGHT_X;
float lightY = LIGHT_Y;

//Sensors and motors
ButtonBoard buttons( FEHIO::Bank3 );
AnalogInputPin photosensor(FEHIO::P1_0);
FEHMotor left(FEHMotor::Motor0);
FEHMotor right(FEHMotor::Motor1);
FEHServo forklift(FEHServo::Servo0);
FEHServo door(FEHServo::Servo4);
AnalogInputPin leftopto(FEHIO::P0_4);
AnalogInputPin centeropto(FEHIO::P1_4);
AnalogInputPin rightopto(FEHIO::P2_4);
DigitalInputPin frontSwitch(FEHIO::P2_0);
DigitalInputPin backSwitch(FEHIO::P1_7);
DigitalInputPin rightSwitch(FEHIO::P0_7);
FEHEncoder leftencoder(FEHIO::P0_0);
FEHEncoder rightencoder(FEHIO::P0_1);
FEHWONKA wonka;
