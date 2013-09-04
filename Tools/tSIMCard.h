/*
 * tSIMCard.h
 *
 *  Created on: 30 août 2013
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
    char thePINCode[5];
    char theOwnNumber[15];

    tSIMCard(mEEPROM *mEeprom, UInt16 aModeNum);

    void save();
    void load();

    virtual ~tSIMCard();
    };

#endif /* TSIMCARD_H_ */
