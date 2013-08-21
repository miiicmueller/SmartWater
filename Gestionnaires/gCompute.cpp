#include <string>
#include <assert.h>

#include "gCompute.h"

//----------------------------------------------------------------
//constructeur
//
//gInput : le gestionnaire qui contient les entr�es
//----------------------------------------------------------------
gCompute::gCompute(gInput* theGInput)
    {
    this->theGInput = theGInput;
    }

void gCompute::setup()
    {
    }

void gCompute::execute()
    {
    this->theGInput->getCounterValue(0);
    }
