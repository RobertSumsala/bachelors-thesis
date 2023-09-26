#include <PIDLoop.h>
#include <Pixy2.h>
#include <Pixy2CCC.h>
#include <Pixy2I2C.h>
#include <Pixy2Line.h>
#include <Pixy2SPI_SS.h>
#include <Pixy2UART.h>
#include <Pixy2Video.h>
#include <TPixy2.h>
#include <ZumoBuzzer.h>
#include <ZumoMotors.h>

#include <IRremote.hpp>

#include "DriveLogic.h"
#include "UltraSonic.h"
#include "Camera.h"
#include "FindStation_Sun.h"






/* - - - - - - - - - - - - - - - - - CODE - - - - - - - - - - - - - - - - - */


//The setup function is called once at startup of the sketch
void setup()
{
  Serial.begin(9600);

  configMotorPins();
  UltraSonicSetUp();
  setUpPixy();
}



// The loop function is called in an endless loop
void loop()
{
  int x_red = 0, x_blue = 0;
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println("begin");

  // time to get the robot in position
  delay(22000);

  Serial.println("Get into a docking station (main while cycle): ");
  int returnValue = getToDockingPosition_UsingCam();
  Serial.println("Finding docking station run done. Results: ");
  if (returnValue == -1){
    Serial.println("Error Finding station");
    Serial.println("end");
  } else if (returnValue == 0){
    Serial.println("Front Found");
    Serial.println("ALL GOOD. Let's park");
    delay(800);
    park(6);
    Serial.println("end");
  }
  
  delay(3000);
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
}

