/*
 * tSIMCard.h
 *
 *  Created on: 30 ao�t 2013
 *      Author: cyrille.savy
 */

#ifndef TSIMCARD_H_
#define TSIMCARD_H_

#include <string>
#include <assert.h>
#include "Def/def.h"
#include "tParameters.h"
#include "Modules/mEEPROM.h"

class tSIMCard: public tParameters
    {
public:
    union
	{
	UInt8 aDataTab[20];
	struct
	    {
	    char theOwnNumber[15];
	    char thePINCode[5];
	    } aDataStruct;
	} aData;

    tSIMCard(mEEPROM *mEeprom, UInt16 aModeNum);

    void save();
    void load();

    virtual ~tSIMCard();
    };

#endif /* TSIMCARD_H_ */
