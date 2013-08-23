#ifndef M_U_S_B_H
#define M_U_S_B_H

#include <string>
#include <assert.h>
#include "Interfaces/iUSB.h"

#include "Module.h"

class mUSB: public Module
    {
private:
    iUSB *usbPort;
    char *serialBuffer;

public:
    //constructeur et destructeur
    mUSB(volatile BYTE *bCDCDataReceived_event);
    ~mUSB();

    //methodes heritees
    void mOpen();
    void mClose();
    void mSetup();

    //methodes supplementaires
    bool getCommand(char* aChain);
    void sendReply(char* aMessage);
    bool isConnected();
    };
#endif
