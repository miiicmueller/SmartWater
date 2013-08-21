#include <string>
#include <assert.h>

#include "gTerminal.h"

//----------------------------------------------------------------
//constructeur
//
//gInput : le gestionnaire qui contient les entrées
//----------------------------------------------------------------
gTerminal::gTerminal(gInput* theGInput)
    {
    this->theGInput = theGInput;
    }

void gTerminal::setup()
    {
    }

void gTerminal::execute()
    {
    }

bool gTerminal::getPipeOpen()
    {
    return 0;
    }
