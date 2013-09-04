#ifndef T_PARAMETERS_H
#define T_PARAMETERS_H

#include <string>
#include <assert.h>
#include "Def/def.h"
#include "Modules/mEEPROM.h"

class tParameters
    {
protected:
    UInt16 aId;
    UInt16 aNbBytes;
    mEEPROM *mPeriphSauv;
private:

public:
    void getId();
    void setId();
    virtual void save()= 0;
    virtual void load()= 0;

    ~tParameters();

    };
#endif
