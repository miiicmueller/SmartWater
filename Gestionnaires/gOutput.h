#ifndef G_OUTPUT_H
#define G_OUTPUT_H

#include <string>
#include <assert.h>

#include "Gestionnaire.h"
#include "gCompute.h"
#include "mGSM.h"
#include "mRTC.h"
#include "mUSB.h"
#include "tDate.h"
#include "tToolsCluster.h"

class gOutput: public Gestionnaire
    {
public:
    //----------------------------------------------------------------
    //constructeur
    //
    //gCompute : le gestionnaire qui contient les donnees qui devront etre sorties
    //----------------------------------------------------------------
    gOutput(gCompute* theGCompute, mGSM* theGSM, mRTC* theRTC, mUSB* theUSB,
	    tToolsCluster* theTools);

    void setup();

    void execute();

    ~gOutput();

private:
    gCompute* theGCompute;
    mGSM* theGSM;
    mRTC* theRTC;
    mUSB* theUSB;
    tToolsCluster* theTools;
    };
#endif
