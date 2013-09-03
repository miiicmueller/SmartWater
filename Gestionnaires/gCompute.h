#ifndef G_COMPUTE_H
#define G_COMPUTE_H

#include <string>
#include <assert.h>

#include "Gestionnaire.h"
#include "../Tools/tDate.h"
#include "../Def/def.h"
#include "gInput.h"
#include "gTerminal.h"
#include "mCompteur.h"

class gCompute: public Gestionnaire
    {
private:
    char* smsToSend;

    int smsNb;

    tDate nextAlarm;

    gInput* theGInput;

    gTerminal* theGTerminal;

    void computeTerminal();

    void computeSMS();

    bool computeConsumption(iMeterChannel aChannel);

public:
    //----------------------------------------------------------------
    //constructeur
    //
    //gInput : le gestionnaire qui contient les entrées
    //----------------------------------------------------------------
    gCompute(gInput* theGInput);

    void setup();

    void execute();

    };
#endif
