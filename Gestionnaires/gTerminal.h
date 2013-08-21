#ifndef G_TERMINAL_H
#define G_TERMINAL_H

#include <string>
#include <assert.h>

#include "Gestionnaire.h"
#include "gInput.h"

class gTerminal: public Gestionnaire
    {
private:
    bool pipeOpen;

    gInput* theGInput;

public:
    //----------------------------------------------------------------
    //constructeur
    //
    //gInput : le gestionnaire qui contient les entrées
    //----------------------------------------------------------------
    gTerminal(gInput* theGInput);

    bool getPipeOpen();

    void setup();

    void execute();

    };
#endif
