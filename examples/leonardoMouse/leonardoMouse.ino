/*
 * Example for basic use of the Pimoroni RGBW Trackball breakout as a mouse when connected to an Arduino Leonardo
 * 
 * Connect SDA to pin 2
 * Connect SCL to pin 3
 * 
 */

#include <Wire.h>
#include "Mouse.h"
#include <pimoroniTrackball.h>  //From https://github.com/ncmreynolds/pimoroniTrackball

uint8_t mouseSpeed = 5; //Change this to alter the mouse speed
int16_t x = 0;
int16_t y = 0;

void setup() {
  Wire.begin(); //Initialise I2C
  trackball.begin();  //Initialise the trackball
  if(trackball.isConnected()) {
    Mouse.begin();
  }
  else {
    while(true)
    {
      delay(1000);
    }
  }
}

void loop() {
  if(trackball.changed()) {
    x = (trackball.right() - trackball.left()) * mouseSpeed;
    y = (trackball.down() - trackball.up()) * mouseSpeed;
    if(x != 0 || y != 0) {
      Mouse.move(x, y, 0);
    }
    if(trackball.click())
    {
      Mouse.press(MOUSE_LEFT);
    }
    else if(trackball.release())
    {
      if (Mouse.isPressed(MOUSE_LEFT)) {
        Mouse.release(MOUSE_LEFT);
      }
    }
  }
}
