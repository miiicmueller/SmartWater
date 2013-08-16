#ifndef M_COMPTEUR_H
#define M_COMPTEUR_H



#include "Module.h"
#include "../Interfaces/iUART.h"
#include "../Interfaces/iDIO.h"
#include "../Def/def.h"



typedef enum
    {
    kMeter1,
    kMeter2,
    kMeterSimulation
    } iMeterChannel;

using namespace std;

class mCompteur: public Module
    {
private:
    UInt8 channelCodeMultiplexer;
    static iUART uart;
    static iDIO enable;
    static iDIO channelMultiplexer;

public:
    UInt32 mRead();
    void mOpen();
    void mClose();
    void mSetup();

    //constructeur
    mCompteur(iMeterChannel aChannel);

    //destructeur
    ~mCompteur();
    };
#endif
