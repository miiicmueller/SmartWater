#ifndef G_COMPUTE_H
#define G_COMPUTE_H

#include <string>
#include <assert.h>

#include "Gestionnaire.h"
#include "../Tools/tDate.h"
#include "gInput.h"

class gCompute: public Gestionnaire
    {
private:
    char* smsToSend;

    int smsNb;

    tDate nextAlarm;

    gInput* theGInput;

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
