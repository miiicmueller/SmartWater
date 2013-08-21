#ifndef T_MODE_H
#define T_MODE_H

#include <string>
#include <assert.h>
#include "Def/def.h"
#include "tParameters.h"
#include "Modules/mEEPROM.h"

class tMode: public tParameters {

public:
	UInt8 mode;

	tMode(mEEPROM *mEeprom,UInt16 aModeNum);
	void save();
	void load();

};
#endif
