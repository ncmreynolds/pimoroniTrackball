/*
 *	Arduino library for the Pimoroni RGBW trackball breakout
 *
 *	See LICENSE for license
 *
 *	This library implements similar functionality to https://github.com/pimoroni/trackball-python/ but in C++
 *
 *
 */
#ifndef pimoroniTrackball_cpp
#define pimoroniTrackball_cpp
#include "pimoroniTrackball.h"


pimoroniTrackball::pimoroniTrackball()		//Constructor function
{
}

pimoroniTrackball::~pimoroniTrackball()	//Destructor function
{
}

bool pimoroniTrackball::begin(uint8_t address, TwoWire &wirePort)
{
	_trackballAddress = address;	//Set the I2C address of the trackball
	_i2cPort = &wirePort;			//Set the wire port used for the trackball
}

bool pimoroniTrackball::isConnected()
{
	uint8_t deviceId[2];
    _i2cPort->beginTransmission(_trackballAddress);
	_i2cPort->write(TRACKBALL_REG_CHIP_ID_L);
    if (_i2cPort->endTransmission() == 0)
    {
		_i2cPort->requestFrom(_trackballAddress, 2, true);
		if(_i2cPort->available())
		{
			deviceId[0] = _i2cPort->read();
			if(_i2cPort->available())
			{
				deviceId[1] = _i2cPort->read();
				if(deviceId[0] == 0x11 && deviceId[1] == 0xBA)
				{
					return(true);
				}
				else
				{
					return(false);
				}
			}
			else
			{
				return(false);
			}
		}
		else
		{
			return(false);
		}
        return false;
    }
	else
	{
		return false;
	}
}

void pimoroniTrackball::setRGBW(uint8_t redBrightness, uint8_t greenBrightness, uint8_t blueBrightness, uint8_t whiteBrightness)
{
	setRed(redBrightness);
	setGreen(greenBrightness);
	setBlue(blueBrightness);
	setWhite(whiteBrightness);
}
void pimoroniTrackball::setRed(uint8_t redBrightness)	//Set the brightness of the red LED
{
	uint8_t data[2] = {TRACKBALL_REG_LED_RED, redBrightness};
	_i2cPort->beginTransmission(_trackballAddress);	//Start I2C transmission
	_i2cPort->write(data,2);							//Send the register and value
	_i2cPort->endTransmission();						//End I2C transmission
}
void pimoroniTrackball::setGreen(uint8_t greenBrightness)	//Set the brightness of the green LED
{
	uint8_t data[2] = {TRACKBALL_REG_LED_GRN, greenBrightness};
	_i2cPort->beginTransmission(_trackballAddress);	//Start I2C transmission
	_i2cPort->write(data,2);							//Send the register and value
	_i2cPort->endTransmission();						//End I2C transmission
}
void pimoroniTrackball::setBlue(uint8_t blueBrightness)	//Set the brightness of the blue LED
{
	uint8_t data[2] = {TRACKBALL_REG_LED_BLU, blueBrightness};
	_i2cPort->beginTransmission(_trackballAddress);	//Start I2C transmission
	_i2cPort->write(data,2);							//Send the register and value
	_i2cPort->endTransmission();						//End I2C transmission
}
void pimoroniTrackball::setWhite(uint8_t whiteBrightness)	//Set the brightness of the white LED
{
	uint8_t data[2] = {TRACKBALL_REG_LED_WHT, whiteBrightness};
	_i2cPort->beginTransmission(_trackballAddress);	//Start I2C transmission
	_i2cPort->write(data,2);							//Send the register and value
	_i2cPort->endTransmission();						//End I2C transmission
}
bool pimoroniTrackball::changed()
{
	bool changed = false;
	uint8_t currentState[5] = {0, 0, 0, 0, 0b10000000};
	uint8_t index = 0;
	_i2cPort->beginTransmission(_trackballAddress);		//Start I2C transmission
	_i2cPort->write(TRACKBALL_REG_LEFT);					//Send the register and value
	_i2cPort->requestFrom(_trackballAddress, 5, true);	//Request 5 bytes from the trackball
	while(_i2cPort->available() && index < 5)
	{
		currentState[index] = _i2cPort->read();			//Read the current state
		if(currentState[index] != _lastState[index])
		{
			_lastState[index] = currentState[index];
			changed = true;
		}
		index++;
	}
	_i2cPort->endTransmission();							//End I2C transmission
	return(changed);
}
uint8_t pimoroniTrackball::left()
{
	uint8_t temp = _lastState[0];
	_lastState[0] = 0;
	return(temp);
}
uint8_t pimoroniTrackball::right()
{
	uint8_t temp = _lastState[1];
	_lastState[1] = 0;
	return(temp);
}
uint8_t pimoroniTrackball::up()
{
	uint8_t temp = _lastState[2];
	_lastState[2] = 0;
	return(temp);
}
uint8_t pimoroniTrackball::down()
{
	uint8_t temp = _lastState[3];
	_lastState[3] = 0;
	return(temp);
}
bool pimoroniTrackball::click()
{
	if(_lastState[4] == 0b10000001)
	{
		_lastState[4] == 0b10000000;
		return(true);
	}
	return(false);
}
bool pimoroniTrackball::release()
{
	if(_lastState[4] == 0b00000001)
	{
		_lastState[4] == 0b00000000;
		return(true);
	}
	return(false);
}
pimoroniTrackball trackball;
#endif
