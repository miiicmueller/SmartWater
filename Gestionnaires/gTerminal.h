#ifndef G_TERMINAL_H
#define G_TERMINAL_H

#include <string>
#include <assert.h>

#include "Gestionnaire.h"
#include "gInput.h"
#include "Modules/mUSB.h"

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

typedef enum
    {
    kTerminalClose,
    kTerminalAdmin,
    kTerminalUser
    } gTerminalSessionEnum;

using namespace std;

class gTerminal: public Gestionnaire
    {
private:

    int maxSizesCommands[4];

    mUSB* theUSB;

    bool sessionOpen;

    gInput* theGInput;

    gTerminalCommand aCommand;

    gTerminalStateEnum aTerminalState;

    gTerminalSessionEnum aSessionType;

    void commandsReceiver();

    void commandsSender(char* aReply);

public:
    //----------------------------------------------------------------
    //constructeur
    //
    //gInput : le gestionnaire qui contient les entrees
    //----------------------------------------------------------------
    gTerminal(gInput* theGInput);

    void setup();

    void execute();

    };
#endif
