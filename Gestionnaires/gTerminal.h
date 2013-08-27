#ifndef G_TERMINAL_H
#define G_TERMINAL_H

#include <string>
#include <assert.h>

#include "Gestionnaire.h"
#include "gInput.h"
#include "Modules/mUSB.h"
#include "Tools/tToolsCluster.h"

#define sizeMaxMode		2
#define sizeMaxMdp		21
#define sizeMaxCommand		9
#define sizeMaxParameter	21

typedef struct
    {
    bool hasCommand;
    char theMode[sizeMaxMode];
    char theMdp[sizeMaxMdp];
    char theCommand[sizeMaxCommand];
    int parametersNumber;
    char theParameters[12][sizeMaxParameter];
    } gTerminalCommand;

typedef enum
    {
    kTerminalDisconnected,
    kTerminalConnected,
    kTerminalSessionOpen
    } gTerminalStateEnum;

using namespace std;

class gTerminal: public Gestionnaire
    {
private:

    int maxSizesCommands[4];

    mUSB* theUSB;

    bool sessionOpen;

    gInput* theGInput;

    tToolsCluster* theTools;

    gTerminalCommand aCommand;

    gTerminalStateEnum aTerminalState;

    void commandsReceiver();

    char aReply[100];

public:
    //----------------------------------------------------------------
    //constructeur
    //
    //gInput : le gestionnaire qui contient les entrees
    //----------------------------------------------------------------
    gTerminal(gInput* theGInput, tToolsCluster* theTools);

    void setup();

    void execute();

    };
#endif
