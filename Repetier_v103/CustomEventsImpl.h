/*
MCP23017 Keypad
*/

#ifndef CustomEventsImpl_H
#define CustomEventsImpl_H

MCP23017 MCP1(0x24);  
//#########################################################################################
//##### Initialization, Setup of I2C and Components
//#########################################################################################

void Custom_Init_Early()
{ 

#ifndef COMPILE_I2C_DRIVER
HAL::i2cInit(400000);  // usually 100000 Hz  , my setup works on 400000Hz
#endif  

#if defined( FEATURE_I2C_MACROS) && FEATURE_I2C_MACROS !=0
  MCP1.Init();
#endif 
}

//#########################################################################################
//##### I2C MCP23017
//#########################################################################################

MCP23017::MCP23017(uint8_t address)
{
  i2c_add=address<<1;
}

void MCP23017::Init(void)
{
	_GPIO = 0x0000;
 	_IODIR = 0xFFFF; //set all to inputs
	_GPPU = 0x0000;
	
   HAL::i2cStartWait(i2c_add + I2C_WRITE);
   HAL::i2cWrite(0x05);
   HAL::i2cWrite(0x00);
   HAL::i2cStop(); 
	 writeRegister(MCP23017_IODIR, _IODIR);
	
}

void MCP23017::SetInput(uint8_t pin) {

   _IODIR |= 1 << pin;
	 writeRegister(MCP23017_IODIR, _IODIR);
}


void MCP23017::SetOutput(uint8_t pin) {
	
	 _IODIR &= ~(1 << pin);
	 writeRegister(MCP23017_IODIR, _IODIR);
}


bool MCP23017::Read(uint8_t pin) {
	 _GPIO = readRegister(MCP23017_GPIO);
	 if ( _GPIO & (1 << pin)) return HIGH;
	 else return LOW;
}

void MCP23017::Write(uint8_t pin, bool val) {
	//If this pin is an INPUT pin, a write here will
	//enable the internal pullup
	//otherwise, it will set the OUTPUT voltage
	//as appropriate.
	 bool isOutput = !(_IODIR & 1<<pin);

	  if (isOutput) {
		 //This is an output pin so just write the value
		  if (val) _GPIO |= 1 << pin;
		  else _GPIO &= ~(1 << pin);
		 writeRegister(MCP23017_GPIO, _GPIO);
	   }
	  else {
		 //This is an input pin, so we need to enable the pullup
		  if (val) _GPPU |= 1 << pin;
		  else _GPPU &= ~(1 << pin);
		 writeRegister(MCP23017_GPPU, _GPPU);
	   }
}

uint16_t MCP23017::ReadPort() {
 InterruptProtectedBlock noInts;
 noInts.protect();
	 _GPIO = readRegister(MCP23017_GPIO);
	 return _GPIO;
 noInts.unprotect(); 
}
void MCP23017::WritePort(uint16_t data) {
	 _GPIO = data;
	 writeRegister(MCP23017_GPIO, _GPIO);
}

//PRIVATE

void MCP23017::writeRegister(uint16_t regAddress, uint16_t data) {
	
	 HAL::i2cStartWait(i2c_add + I2C_WRITE);
   HAL::i2cWrite(regAddress);
   HAL::i2cWrite(data>>8);
   HAL::i2cWrite(data);
   HAL::i2cStop(); 
}

uint16_t MCP23017::readRegister(uint16_t regAddress) {
	
	uint16_t data = 0x00;
	 
	 HAL::i2cStartWait(i2c_add + I2C_WRITE);
   HAL::i2cWrite(regAddress);
	 HAL::i2cStop();
	 HAL::i2cStartWait(i2c_add + I2C_READ);
   data = (HAL::i2cReadAck()<<8);
   data += HAL::i2cReadNak();
   HAL::i2cStop();
   return data ;
} 

// End MCP23017

//#########################################################################################
//###  User defined Events
//#########################################################################################

int Custom_Execute(int action,bool allowMoves) 
{
            
  switch(action) {
  
        case UI_ACTION_X_UP001:
        case UI_ACTION_X_DOWN001:
            if(!allowMoves) return action;
            PrintLine::moveRelativeDistanceInStepsReal(((action == UI_ACTION_X_UP001) ? 1.0 : -1.0) * (Printer::axisStepsPerMM[X_AXIS]/100), 0, 0, 0, JOGRATE, false,false);
            GCode::executeFString(PSTR("M117 moveX manual")); 
            break;
 
        case UI_ACTION_X_UP01:
        case UI_ACTION_X_DOWN01:
            if(!allowMoves) return action;
            PrintLine::moveRelativeDistanceInStepsReal(((action == UI_ACTION_X_UP01) ? 1.0 : -1.0) * (Printer::axisStepsPerMM[X_AXIS]/10), 0, 0, 0, JOGRATE, false,false);
            GCode::executeFString(PSTR("M117 moveX manual")); 
            break;    
      
        case UI_ACTION_X_UP1:
        case UI_ACTION_X_DOWN1:
            if(!allowMoves) return action;
            PrintLine::moveRelativeDistanceInStepsReal(((action == UI_ACTION_X_UP1) ? 1.0 : -1.0) * Printer::axisStepsPerMM[X_AXIS], 0, 0, 0, JOGRATE, false,false);
            GCode::executeFString(PSTR("M117 moveX manual")); 
            break;
       
        case UI_ACTION_X_UP10:
        case UI_ACTION_X_DOWN10:
            if(!allowMoves) return action;
            PrintLine::moveRelativeDistanceInStepsReal(((action == UI_ACTION_X_UP10) ? 1.0 : -1.0) * (Printer::axisStepsPerMM[X_AXIS]*10), 0, 0, 0, JOGRATE, false,false);
            GCode::executeFString(PSTR("M117 moveX manual")); 
            break;
              
        case UI_ACTION_Y_UP001:
        case UI_ACTION_Y_DOWN001:
            if(!allowMoves) return action;
            PrintLine::moveRelativeDistanceInStepsReal(0, ((action == UI_ACTION_Y_UP001) ? 1.0 : -1.0) * Printer::axisStepsPerMM[Y_AXIS]/100, 0, 0, JOGRATE, false,false);
            GCode::executeFString(PSTR("M117 moveY manual")); 
            break;
            
        case UI_ACTION_Y_UP01:
        case UI_ACTION_Y_DOWN01:
            if(!allowMoves) return action;
            PrintLine::moveRelativeDistanceInStepsReal(0, ((action == UI_ACTION_Y_UP01) ? 1.0 : -1.0) * Printer::axisStepsPerMM[Y_AXIS]/10, 0, 0, JOGRATE, false,false);
            GCode::executeFString(PSTR("M117 moveY manual")); 
            break;
            
        case UI_ACTION_Y_UP1:
        case UI_ACTION_Y_DOWN1:
            if(!allowMoves) return action;
            PrintLine::moveRelativeDistanceInStepsReal(0, ((action == UI_ACTION_Y_UP1) ? 1.0 : -1.0) * Printer::axisStepsPerMM[Y_AXIS], 0, 0, JOGRATE, false,false);
            GCode::executeFString(PSTR("M117 moveY manual")); 
            break;
            
        case UI_ACTION_Y_UP10:
        case UI_ACTION_Y_DOWN10:
            if(!allowMoves) return action;
            PrintLine::moveRelativeDistanceInStepsReal(0, ((action == UI_ACTION_Y_UP10) ? 1.0 : -1.0) * Printer::axisStepsPerMM[Y_AXIS]*10, 0, 0, JOGRATE, false,false);
            GCode::executeFString(PSTR("M117 moveY manual")); 
            break;
                     
        case UI_ACTION_Z_UP001:
        case UI_ACTION_Z_DOWN001:
            if(!allowMoves) return action;
            PrintLine::moveRelativeDistanceInStepsReal(0, 0, ((action == UI_ACTION_Z_UP001) ? 1.0 : -1.0) * Printer::axisStepsPerMM[Z_AXIS]/100, 0, JOGRATE, false,false);
            GCode::executeFString(PSTR("M117 moveZ manual")); 
            break;
            
        case UI_ACTION_Z_UP01:
        case UI_ACTION_Z_DOWN01:
            if(!allowMoves) return action;
            PrintLine::moveRelativeDistanceInStepsReal(0, 0, ((action == UI_ACTION_Z_UP01) ? 1.0 : -1.0) * Printer::axisStepsPerMM[Z_AXIS]/10, 0, JOGRATE, false,false);
            GCode::executeFString(PSTR("M117 moveZ manual"));           
            break;
            
        case UI_ACTION_Z_UP1:
        case UI_ACTION_Z_DOWN1:
            if(!allowMoves) return action;
            PrintLine::moveRelativeDistanceInStepsReal(0, 0, ((action == UI_ACTION_Z_UP1) ? 1.0 : -1.0) * Printer::axisStepsPerMM[Z_AXIS], 0, JOGRATE, false,false);
            GCode::executeFString(PSTR("M117 moveZ manual"));           
            break;
     
        case UI_ACTION_X_ZERO:
            if(!allowMoves) return UI_ACTION_X_ZERO;
            Printer::coordinateOffset[X_AXIS] -= Printer::currentPosition[X_AXIS];
            break;
            
        case UI_ACTION_Y_ZERO:
            if(!allowMoves) return UI_ACTION_Y_ZERO;
            Printer::coordinateOffset[Y_AXIS] -= Printer::currentPosition[Y_AXIS];
            break;
            
        case UI_ACTION_Z_ZERO:
            if(!allowMoves) return UI_ACTION_Z_ZERO;
            Printer::coordinateOffset[Z_AXIS] -= Printer::currentPosition[Z_AXIS];
            break;
        }
return 0 ;
}//Custom_Execute


//#########################################################################################
//#### Read buttons from MCP1 external I2C device  
//#### as we read the complete bitmask it´s possible to realize two or more buttons pressed
//#### at the same time in order to realize "shift" Functions etc.
//#########################################################################################

int Custom_CheckSlowKeys()
{
  int action=0;
  char buf[20];
  
#if defined( FEATURE_I2C_MACROS) && FEATURE_I2C_MACROS !=0
{
	 uint16_t buttonval = 0xFFFF-MCP1.ReadPort();
	    
switch (buttonval) {
  
      case 1:       RunMacro(HomeAll);
                    break;
            
      case 2:
                    GCode::executeFString(PSTR("M117 moveZ+ manual")); 
                    HAL::delayMilliseconds(100);
                    GCode::executeFString(PSTR("G91\n G1 Z0.001 F20 \n G90\n")); 
                    break;
   
      case 3:       action = UI_ACTION_Z_UP1 ;
                    break;
               
      case 4:       GCode::executeFString(PSTR("M117 set FFF Mode")); 
                    GCode::executeFString(PSTR("M451")); 
                    HAL::delayMilliseconds(200);
                    GCode::executeFString(PSTR("M117")); 
                    break;        
     
      case 5:       action = UI_ACTION_Z_DOWN01 ;
                    break;  
                  
      case 6:       action = UI_ACTION_Z_DOWN1 ;
                    break;        
      
      case 7:       action = UI_ACTION_Y_UP001 ;
                    break;
            
      case 8:       GCode::executeFString(PSTR("M117 set LASER Mode")); 
                    GCode::executeFString(PSTR("M452")); 
                    HAL::delayMilliseconds(200);
                    GCode::executeFString(PSTR("M117")); 
                    break;
           
      case 9:       action = UI_ACTION_Y_UP1 ;
                    break;

      case 10:
                    action = UI_ACTION_Y_UP1 ;
                    break;
     
      
      case 11:      action = UI_ACTION_Y_DOWN001 ;
                    break;        
      
      case 12:      action = UI_ACTION_Y_DOWN01 ;
                    break;  
                  
      case 13:      action = UI_ACTION_Y_DOWN1 ;
                    break;        
    
      case 14:      action = UI_ACTION_Y_DOWN10 ;
                    break;

      case 15:      action = UI_ACTION_Y_DOWN10 ;
                    break;
            
      case 16:      GCode::executeFString(PSTR("M117 set CNC Mode")); 
                    GCode::executeFString(PSTR("M453")); 
                    HAL::delayMilliseconds(200);
                    break;

      case 32:      if(Gamma_on==false)
                    {
                    Gamma_on=true;
                    GCode::executeFString(PSTR("M117 Gamma on")); 
                    Com::print("Gamma on");
                    HAL::delayMilliseconds(300);
                    }
                    else
                    {
                      Gamma_on=false;
                      GCode::executeFString(PSTR("M117 Gamma off")); 
                      Com::print("Gamma off");
                      HAL::delayMilliseconds(300);
                    } 
                    break;

      case 64:      LASER_BASE_OFFSET+=5; 
                    HAL::delayMilliseconds(200);  
                    Com::printFLN(PSTR("LASER_BASE_VALUE:"),(int)LASER_BASE_OFFSET); 
                    break;                    
                         
      case 128:     LASER_BASE_OFFSET-=5;  
                    HAL::delayMilliseconds(200); 
                    Com::printFLN(PSTR("LASER_BASE_VALUE:"),(int)LASER_BASE_OFFSET); 
                   
                    break;                   
      case 256:     GAMMA+=0.10;
                    HAL::delayMilliseconds(200);   
                    Com::printFLN(PSTR("GAMMA_VALUE:"),(float)GAMMA,1);
                    break;                    
                         
      case 512:     GAMMA-=0.10; 
                    HAL::delayMilliseconds(200); 
                    Com::printFLN(PSTR("GAMMA_VALUE:"),(float)GAMMA,1); 
                    break;                   
      
      case 1024:    LASER_LIMIT-=50;
                    if(LASER_LIMIT<LASER_PWM_MAX/4) LASER_LIMIT=LASER_PWM_MAX/4;
                    HAL::delayMilliseconds(200); 
                    Com::printFLN(PSTR("LIMIT:"),(int)LASER_LIMIT); 
                    break;

      case 2048:    LASER_LIMIT+=50;
                    if(LASER_LIMIT>LASER_PWM_MAX) LASER_LIMIT=LASER_PWM_MAX;
                    HAL::delayMilliseconds(200); 
                    Com::printFLN(PSTR("LIMIT:"),(int)LASER_LIMIT); 
                    break;
     
      default: 
                    break;
   }

   return(action);
 }
#endif //macros

}//SLOWKEYS



#endif
