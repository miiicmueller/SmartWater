#ifndef G_OUTPUT_H
#define G_OUTPUT_H

#include <string>
#include <assert.h>

#include "Gestionnaire.h"
#include "gCompute.h"

class gOutput: public Gestionnaire
    {
private:
    gCompute* theGCompute;
public:
    //----------------------------------------------------------------
    //constructeur
    //
    //gCompute : le gestionnaire qui contient les donnees qui devront etre sorties
    //----------------------------------------------------------------
    gOutput(gCompute* theGCompute);

    void setup();

    void execute();

    };
#endif
