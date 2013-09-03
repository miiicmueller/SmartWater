#ifndef G_COMPUTE_H
#define G_COMPUTE_H

#include <string>
#include <assert.h>

#include "Gestionnaire.h"
#include "../Tools/tDate.h"
#include "gInput.h"
#include "gTerminal.h"
#include "mRTC.h"
#include "tCommandsAnalyzer.h"

typedef struct
    {
    //pour les reponses SMS
    char aReplySMS[100];

    //pour la reponse USB
    char aReplyUSB[100];

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

    void computeConsumption();

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

    };
#endif
