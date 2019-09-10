/* --------------------------------------------------
Manual controls XY-axis by Analog Joystick
-----------------------------------------------------
Joystick.h
*/

#ifndef JOYSTICK_H
#define JOYSTICK_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif


int get_joystick_position_x();
int get_joystick_position_y();
int get_joystick_position_z();
int get_joystick_btn();
void set_joystick_run();
void joy_print();                //only for joystick check
#endif // JOYSTICK_H