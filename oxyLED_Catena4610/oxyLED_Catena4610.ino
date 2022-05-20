/*
Module: oxy_Catena4610.ino

Function:
        To measure the oxygen reading from Oxygen Sensor using MCCI Catena4610.

Copyright notice:
        This file copyright (C) 2022 by
        MCCI Corporation
        3520 Krums Corners Road
        Ithaca, NY 14850
        An unpublished work. All rights reserved.
        This file is proprietary information, and may not be disclosed or
        copied without the prior permission of MCCI Corporation.

Author:
        Pranau R, MCCI Corporation   May 2022
*/

#include <DFRobot_OxygenSensor.h>
#include <Catena.h>
#include <Catena_Led.h>

#define Oxygen_IICAddress ADDRESS_3
#define COLLECT_NUMBER  10
DFRobot_OxygenSensor oxygen;

using namespace McciCatena;

Catena gCatena;
StatusLed gLed(Catena::PIN_STATUS_LED);

/****************************************************************************\
|
|   Setup Function.
|
\****************************************************************************/

/*
Name: setup()

Function:
        To initiate a serial connection between board and display and to check the connectivity of Oxygen Sensor.

Definition:
        void setup (void);

Returns:
        Functions returning type void: nothing.
*/

void setup()
  {
  gCatena.begin();
  gLed.begin();

  gCatena.registerObject(&gLed);
  gLed.Set(LedPattern::ThreeShort);

  Serial.begin(9600);
  while(!Serial);

  while(!oxygen.begin(Oxygen_IICAddress))
    {
    gCatena.SafePrintf("Oxygen Sensor not connected!\n");
    delay(1000);
    }

  gCatena.SafePrintf("Oxygen Sensor connected successfully!\n");

  gCatena.SafePrintf("The Oxygen Values are:\n");
  delay(3000);
  }

/****************************************************************************\
|
|   Setup Function.
|
\****************************************************************************/

/*
Name:   loop()

Function:
        To get oxygen readings and display it in serial monitor.

Definition:
        void loop (void);

Returns:
        Functions returning type void: nothing.
*/

void loop()
  {
  int oxygenData = oxygen.getOxygenData(COLLECT_NUMBER);

  gCatena.registerObject(&gLed);
  gLed.Set(LedPattern::FastFlash);

  gCatena.SafePrintf(" oxygen concentration = ");
  gCatena.SafePrintf("%d", oxygenData);
  gCatena.SafePrintf(" vol in percentage\n");

  delay(3000);
  }
