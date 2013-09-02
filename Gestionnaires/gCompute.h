#ifndef G_COMPUTE_H
#define G_COMPUTE_H

#include <string>
#include <assert.h>

#include "Gestionnaire.h"
#include "../Tools/tDate.h"
#include "gInput.h"
#include "gTerminal.h"

class gCompute: public Gestionnaire
    {
private:
    char* smsToSend;

    int smsNb;

    tDate nextAlarm;

    tToolsCluster* theTools;

    gInput* theGInput;

    gTerminal* theGTerminal;

    void computeTerminal();

    void computeSMS();

    void computeConsumption();

public:
    //----------------------------------------------------------------
    //constructeur
    //
    //gInput : le gestionnaire qui contient les entrées
    //----------------------------------------------------------------
    gCompute(gInput* theGInput, gTerminal* theGTerminal,
	    tToolsCluster* theTools);

    void setup();

    void execute();

    };
#endif
