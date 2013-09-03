#ifndef G_TERMINAL_H
#define G_TERMINAL_H

#include <string>
#include <assert.h>

#include "Gestionnaire.h"
#include "gInput.h"
#include "Modules/mUSB.h"
#include "Tools/tToolsCluster.h"
#include "tCommandsAnalyzer.h"

//pour la machine d'etat du gTerminal
typedef enum
    {
    kTerminalDisconnected,
    kTerminalConnected,
    kTerminalSessionOpen
    } gTerminalStateEnum;

typedef struct
    {
    tCommandsEnum* aAction;
    char* theParameters[12];
    UInt8* theParametersNumber;
    gTerminalStateEnum* aTerminalState;
    tCommandsUserNbEnum* aUserNb;
    } gTerminalMailBox;

using namespace std;

class gTerminal: public Gestionnaire
    {
private:

    mUSB* theUSB;

    bool sessionOpen;

    gInput* theGInput;

    tToolsCluster* theTools;

    gTerminalStateEnum aTerminalState;

    tCommandsAnalyzer theAnalyzer;

public:
    //----------------------------------------------------------------
    //constructeur
    //
    //gInput : le gestionnaire qui contient les entrees
    //----------------------------------------------------------------
    gTerminal(tToolsCluster* theTools, mUSB* theUSB);

    void setup();

    void execute();

    gTerminalMailBox theTerminalMailBox;

    };
#endif
