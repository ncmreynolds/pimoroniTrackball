/*
 * Example for basic use of the Pimoroni RGBW Trackball breakout
 * 
 * This sets each LED then prints output from the trackball
 * 
 * 
 * 
 */

#include <Wire.h>
#include <pimoroniTrackball.h>	  //From https://github.com/ncmreynolds/pimoroniTrackball

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial); // Leonardo: wait for serial monitor
  Serial.println("\nPimoroni RGBW trackball breakout");
  Wire.begin(); //Initialise I2C
  trackball.begin();  //Initialise the trackball
  if(trackball.isConnected())
  {
    Serial.println("Trackball connected");
    Serial.println("Red");
    trackball.setRed(255);
    delay(1000);
    trackball.setRed(0);
    delay(1000);
    Serial.println("Green");
    trackball.setGreen(255);
    delay(1000);
    trackball.setGreen(0);
    delay(1000);
    Serial.println("Blue");
    trackball.setBlue(255);
    delay(1000);
    trackball.setBlue(0);
    delay(1000);
    Serial.println("White");
    trackball.setWhite(255);
    delay(1000);
    trackball.setWhite(0);
    delay(1000);
    Serial.println("All LEDs");
    trackball.setRGBW(255,255,255,255);
    delay(1000);
    trackball.setRGBW(0,0,0,0);
  }
  else
  {
    Serial.println("Trackball not connected!");
    while(true)
    {
      delay(1000);
    }
  }
}

void loop() {
  if(trackball.changed())
  {
    Serial.print("Left:");
    Serial.print(trackball.left());
    Serial.print(' ');
    Serial.print("Right:");
    Serial.print(trackball.right());
    Serial.print(' ');
    Serial.print("Up:");
    Serial.print(trackball.up());
    Serial.print(' ');
    Serial.print("Down:");
    Serial.print(trackball.down());
    Serial.print(' ');
    Serial.print("Click:");
    Serial.print(trackball.click());
    Serial.print(' ');
    Serial.print("Release:");
    Serial.print(trackball.release());
    Serial.println();
    delay(50);
  }
}
