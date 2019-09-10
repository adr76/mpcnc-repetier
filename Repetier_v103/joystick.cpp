/* --------------------------------------------------
Manual controls XY-axis by Analog Joystick
-----------------------------------------------------
Joystick.cpp
*/

#include "Repetier.h"
#include "Printer.h"
#include "HAL.h"
#include "uimenu.h"


#if defined EXT_AJOYSTICK
#define JOY_DIR_X 1
#define JOY_DIR_Y 1
#define JOY_DIR_Z -1      //reversed Z rotation of joystick
#define JOY_CENTER_X 2046 //512
#define JOY_CENTER_Y 2046 //512
#define JOY_CENTER_Z 2046 //512
#define JOY_DEADBAND_X 150
#define JOY_DEADBAND_Y 150
#define JOY_DEADBAND_Z 150
#define JOY_MAX_X 2000
#define JOY_MAX_Y 2000
#define JOY_MAX_Z 2000
#define JOY_SLOW_FEEDRATE 3     //0.01
#define JOY_FAST_FEEDRATE 30    //0.01
#define JOY_SLOW_MOTION 0.1     //0.01
#define JOY_FAST_MOTION 0.5     //0.05
#define JOYZ_SLOW_MOTION 0.01   //0.01
#define JOYZ_FAST_MOTION 0.05   //0.05

#endif
#if defined EXT_AJOYSTICK
int loop_delay = 0;
//extern volatile uint osAnalogInputValues[ANALOG_INPUTS];

int get_joystick_position_x()
{
int Joy_Position_X = 0;

Joy_Position_X = (osAnalogInputValues[KEYPAD_ANALOG_INDEX] - JOY_CENTER_X)*JOY_DIR_X;
if (Joy_Position_X < JOY_DEADBAND_X && Joy_Position_X > -JOY_DEADBAND_X)Joy_Position_X = 0;
else {
if (Joy_Position_X >= JOY_DEADBAND_X) Joy_Position_X -= JOY_DEADBAND_X;
if (Joy_Position_X <= -JOY_DEADBAND_X) Joy_Position_X += JOY_DEADBAND_X;
}
return Joy_Position_X;
}

int get_joystick_position_y()
{
int Joy_Position_Y = 0;
Joy_Position_Y = (osAnalogInputValues[KEYPAD2_ANALOG_INDEX] - JOY_CENTER_Y)*JOY_DIR_Y;
if (Joy_Position_Y < JOY_DEADBAND_Y && Joy_Position_Y > -JOY_DEADBAND_Y)Joy_Position_Y = 0;
else {
if (Joy_Position_Y >= JOY_DEADBAND_Y) Joy_Position_Y -= JOY_DEADBAND_Y;
if (Joy_Position_Y <= -JOY_DEADBAND_Y) Joy_Position_Y += JOY_DEADBAND_Y;
}
return Joy_Position_Y;
}

int get_joystick_position_z()
{
int Joy_Position_Z = 0;

Joy_Position_Z = (osAnalogInputValues[KEYPAD3_ANALOG_INDEX] - JOY_CENTER_Z)*JOY_DIR_Z;
if (Joy_Position_Z < JOY_DEADBAND_Z && Joy_Position_Z > -JOY_DEADBAND_Z)Joy_Position_Z = 0;
else {
if (Joy_Position_Z >= JOY_DEADBAND_Z) Joy_Position_Z -= JOY_DEADBAND_Z;
if (Joy_Position_Z <= -JOY_DEADBAND_Z) Joy_Position_Z += JOY_DEADBAND_Z;
}
return Joy_Position_Z;
}

int get_joystick_btn()
{
int Joy_BtnState = 0;
Joy_BtnState = digitalRead(JOY_BTN_PIN);
return Joy_BtnState;
}


void set_joystick_run()
{
int ad_x, ad_y, ad_z;
loop_delay += 1;
if (loop_delay >= 5)
{

ad_x = get_joystick_position_x();
ad_y = get_joystick_position_y();
ad_z = get_joystick_position_z();

if (get_joystick_btn() == 1 && (ad_x != 0 || ad_y != 0 || ad_z != 0)) //slow motion
{
        PrintLine::moveRelativeDistanceInSteps((int32_t)(ad_x*JOY_SLOW_MOTION), (int32_t)(ad_y*JOY_SLOW_MOTION), (int32_t)(ad_z*JOYZ_SLOW_MOTION), 0, Printer::maxFeedrate[X_AXIS],false, true, true);
Commands::printCurrentPosition(PSTR("UI_ACTION_XPOSITION_FAST "));
}
else if (get_joystick_btn() == 0 && (ad_x != 0 || ad_y != 0 || ad_z != 0)) //fast motion
{
        PrintLine::moveRelativeDistanceInSteps((int32_t)(ad_x*JOY_FAST_MOTION), (int32_t)(ad_y*JOY_FAST_MOTION), (int32_t)(ad_z*JOYZ_FAST_MOTION), 0, Printer::maxFeedrate[X_AXIS],false, true, true);
Commands::printCurrentPosition(PSTR("UI_ACTION_XPOSITION_FAST "));
}
loop_delay = 0;
}
}


void joy_print()
{
loop_delay += 1;
if (loop_delay >= 100)
{
Com::print("X: ");
Com::print(get_joystick_position_x());
Com::print(" | Y: ");
Com::print(get_joystick_position_y());
Com::print(" | Z: ");
Com::print(get_joystick_position_z());
Com::print(" | Button: ");
Com::print(get_joystick_btn());
Com::println();
loop_delay = 0;
}
}
#endif