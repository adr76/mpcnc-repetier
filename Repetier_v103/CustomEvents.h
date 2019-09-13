/*
MCP23017 Keypad
*/
#ifndef CustomEvents_H
#define CustomEvents_H


#define FEATURE_I2C_MACROS true

//############### MCP23017 ########################

#define MCP23017_IODIR 0x00
#define MCP23017_IPOL 0x2
#define MCP23017_GPPU 0x0C
#define MCP23017_GPIO 0x12

class MCP23017
{
	public:
	MCP23017(uint8_t address);
	void Init(void);
	void SetInput(uint8_t pin);
	void SetOutput(uint8_t pin);
	void Write(uint8_t pin, bool val);
    bool Read(uint8_t pin);
    uint16_t ReadPort();
    void WritePort(uint16_t data);
  
  private:

    uint8_t i2c_add;
	void writeRegister(uint16_t regaddress, uint16_t val);
	uint16_t readRegister(uint16_t regaddress);
	uint16_t _GPIO, _IODIR, _GPPU;
	
    };
//end MCP23017

// Function list
extern void Custom_Init_Early();
extern int  Custom_Execute(int action,bool allowMoves);
extern int  Custom_CheckSlowKeys();

// replace original stuff
#undef EVENT_UI_EXECUTE
#define EVENT_UI_EXECUTE(action,allowMoves) Custom_Execute(action,allowMoves)

#undef EVENT_INITIALIZE_EARLY
#define EVENT_INITIALIZE_EARLY {Custom_Init_Early();}

#undef EVENT_CHECK_SLOW_KEYS(action) {}
#define EVENT_CHECK_SLOW_KEYS(action) {action=Custom_CheckSlowKeys();}

#undef EVENT_CHECK_FAST_KEYS(action) {}
#define EVENT_CHECK_FAST_KEYS(action) {}

#define RunMacro(macro) GCode::executeFString(PSTR(macro))

// New menu actions
// repeatable actions 700-999 

#define UI_ACTION_X_UP1                  700
#define UI_ACTION_X_DOWN1                701
#define UI_ACTION_X_UP01                 702
#define UI_ACTION_X_DOWN01               703
#define UI_ACTION_X_UP001                704
#define UI_ACTION_X_DOWN001              705
#define UI_ACTION_X_UP10                 706
#define UI_ACTION_X_DOWN10               707

#define UI_ACTION_Y_UP1                  708
#define UI_ACTION_Y_DOWN1                709
#define UI_ACTION_Y_UP01                 710
#define UI_ACTION_Y_DOWN01               711
#define UI_ACTION_Y_UP001                712
#define UI_ACTION_Y_DOWN001              713
#define UI_ACTION_Y_UP10                 714
#define UI_ACTION_Y_DOWN10               715


#define UI_ACTION_Z_UP1                  716
#define UI_ACTION_Z_DOWN1                717
#define UI_ACTION_Z_UP01                 718
#define UI_ACTION_Z_DOWN01               719
#define UI_ACTION_Z_UP001                720
#define UI_ACTION_Z_DOWN001              721


// single actions 1500-2500

#define UI_ACTION_X_ZERO                 1500
#define UI_ACTION_Y_ZERO                 1501
#define UI_ACTION_Z_ZERO                 1502



//some macros

#define HomeX   "G28 x\nM117 Home X"
#define HomeY   "G28 y\nM117 Home Y " 
#define HomeZ   "G28 z\nM117 Home Z "  
#define HomeAll "M117 Home all\nG28"  
#define ZeroX   "G92 x0\nM117 Reset X coord "
#define ZeroY   "G92 y0\nM117 Reset Y coord "
#define ZeroZ   "G92 z0\nM117 Reset Z coord "
#define Clear   "M117                       "



#endif
