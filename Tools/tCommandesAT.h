#ifndef T_COMMANDES_A_T_H
#define T_COMMANDES_A_T_H

#include <string>
#include "Def/def.h"

using namespace std;

class tCommandesAT
    {
public:
    static UInt8 configSMS[];
    static UInt8 configBaud9600[];
    static UInt8 enableServiceData[];
    static UInt8 questWhiteList[];
    static UInt8 addP41ToWhiteList[];
    static UInt8 enableSMS[];
    static UInt8 questSMSMode[];
    static UInt8 delockPIN[];
    static UInt8 questStatePIN[];
    static UInt8 getCredit[];
    static UInt8 setModeText[];
    static UInt8 getSMS[];
    static UInt8 deleteSMSAll[];
    static UInt8 deleteSMSPos[];
    static UInt8 sendSMS[];
    static UInt8 getStateMemory[];
    static UInt8 endAT[];
    };
#endif
