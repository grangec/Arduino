/***********************************************************************
                        Récepteur TIC Linky
                        Mode historique

V03  : External SoftwareSerial. Tested OK on 07/03/18.
V04  : Replaced available() by new(). Tested Ok on 08/03/18.
V05  : Internal SoftwareSerial. Cf special construction syntax.
V06  : Separate compilation version.

***********************************************************************/

/***************************** Includes *******************************/
#include <string.h>
#include <Streaming.h>
#include "LinkyHistTIC.h"


/****************************** Defines *******************************/



/****************************** Constants *****************************/
const uint8_t pin_LkyRx = 8;
const uint8_t pin_LkyTx = 9;   /* !!! Not used but reserved !!! 
                                  * Do not use for anything else */

/************************* Global variables ***************************/




/************************* Object instanciation ***********************/
LinkyHistTIC Linky(pin_LkyRx, pin_LkyTx);

/****************************  Routines  ******************************/




/******************************  Setup  *******************************/
void setup()
  {

  /* Initialise serial link */
  Serial.begin(9600);

  /* Initialise the Linky receiver */
  Linky.Init();

  Serial << F("Bonjour") << endl;
  }


/******************************* Loop *********************************/
void loop()
  {
  Linky.Update();

  if (Linky.baseIsNew())
    {
    Serial << F("Index base = ") << Linky.base() << F(" Wh") << endl;
    }

  if (Linky.iinstIsNew())
    {
    Serial << F("I instant. = ") << Linky.iinst() << F(" A") << endl;
    }

  if (Linky.pappIsNew())
    {
    Serial << F("Puis. app. = ") << Linky.papp() << F(" VA") << endl;
    }

  };
