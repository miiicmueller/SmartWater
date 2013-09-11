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
    char aReplySMS[300];
    char* aReplyNb;
    tCommandsUserNbEnum* aUserNb;

    //pour la reponse USB
    char aReplyUSB[300];

    //pour la mise a l'heure automatique
    bool mahAuto;

    //pour la date
    tDate* theDate;

    //pour la selection du compteur
    tCommandsUserNbEnum aUserSelect;

    //pour la surveillance de consommation
    UInt16 overrunConsumption[2]; // valeur depassee
    UInt16 overrunLimit[2]; // limite de a ne pas depasser
    bool hasOverrun[2]; // le compteur a depasse

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

    //attributs tools pour le computeConsumption et ses sous-fonctions
    UInt8 aMonth;
    UInt8 aDay;
    UInt32 aValue;
    UInt16 aLimitDay; // limite journaliere a ne pas depasser
    UInt8 j;
    bool aFullMonth; // le programme n'a pas commence au milieu de ce mois
    UInt32 aPreviousValue[3];
    UInt32 aValueBeginMonth[3];
    UInt8 aPreviousDay;

    void computeTerminal();

    void computeSMS();

    void computeConsumption();

    void computeIsFinished();

    void computeCredit();

    void saveMeasurements();

    void computeLimitDay();

    void computeLimitNextDay();

public:

    //mis a disposition des autres gestionnaires
    static gComputeMailBox theComputeMailBox;

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
