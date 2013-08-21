#ifndef T_MD_P_USER_H
#define T_MD_P_USER_H

#include <string>
#include <assert.h>

#include "tParameters.h"
#include "Modules/mEEPROM.h"

class tMdPUser: public tParameters {
public:
	UInt8 mdPUser[20];

	tMdPUser(mEEPROM *mEeprom,UInt16 aModeNum);
	void save();
	void load();
};
#endif
