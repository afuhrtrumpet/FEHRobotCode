#ifndef OTHERFUNCTIONS_H
#define OTHERFUNCTIONS_H

//Waits until the starting light is on
void waitForStartLight();

//Calibrates the line following optosensors, for yellow line if yellow is true or black line if yellow is false
void calibrateOptosensors(bool yellow);

//Gets RPS coordinates of light
void calibrateLightPosition();

//Calibrate encoding
void calibrateEncoders();

//Calibrate coordinates for skid and ramp
void calibrateRPS();

//Returns an int based on whether the robot detects no light, red light, or blue light
int readLight();

//Used to adjust to the light if the light is not present
int adjustToLight();

//Sets the scoop door to open
void dropOffScoop();

#endif // OTHERFUNCTIONS_H
