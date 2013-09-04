#ifndef G_COMPUTE_H
#define G_COMPUTE_H

#include <string>
#include <assert.h>

#include "Gestionnaire.h"
#include "../Tools/tDate.h"
#include "../Def/def.h"
#include "../Modules/mCompteur.h"
#include "gInput.h"
#include "gTerminal.h"
#include "mRTC.h"
#include "tCommandsAnalyzer.h"

typedef struct
    {
    //pour les reponses SMS
    char aReplySMS[150];
    tCommandsUserNbEnum* aUserNb;

    //pour la reponse USB
    char aReplyUSB[150];

    //pour la mise a l'heure automatique
    bool mahAuto;

    //pour la simulation
    bool simulation;
    tCommandsUserNbEnum aUserSimulation;

    //pour savoir si le travail est termine
    bool isWorkFinished;
    } gComputeMailBox;

class gCompute: public Gestionnaire
    {
private:

    tToolsCluster* theTools;

    mRTC* theRTC;

    gInput* theGInput;

    gTerminal* theGTerminal;

    void computeTerminal();

    void computeSMS();

    bool computeConsumption(iMeterChannel aChannel);

    void computeIsFinished();

public:
    //mis a disposition des autres gestionnaires
    gComputeMailBox theComputeMailBox;

    //----------------------------------------------------------------
    //constructeur
    //
    //gInput : le gestionnaire qui contient les entrées
    //----------------------------------------------------------------
    gCompute(gInput* theGInput, gTerminal* theGTerminal,
	    tToolsCluster* theTools, mRTC* theRTC);

    void setup();

    void execute();

    ~gCompute();
    };
#endif
