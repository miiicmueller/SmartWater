#ifndef T_MD_P_ADMIN_H
#define T_MD_P_ADMIN_H

#include <string>
#include <assert.h>

#include "tParameters.h"

class tMdPAdmin: public tParameters
    {
public:
    char mdPAdmin[20];

    tMdPAdmin(mEEPROM *mEeprom, UInt16 aModeNum);
    void save();
    void load();

    ~tMdPAdmin();

    };
#endif
