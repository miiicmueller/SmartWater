/*
 ------------------------------------------------------------
 Copyright 2003-2007 Haute Ecole ARC Ing�nierie,
 Switzerland. All rights reserved
 ------------------------------------------------------------
 Nom du fichier :  iUART.h
 Auteur et Date :  Mueller Michael 17.04.2013

 But : Interface de communication serielle UART

 ------------------------------------------------------------
 */

#ifndef I_U_A_R_T_H
#define I_U_A_R_T_H

#include <string>
#include <assert.h>
#include "../Def/def.h"

#include "Interface.h"

// Buffer de 200 caract�res
#define kSciRecBufSize ((unsigned char)(200))

using namespace std;

typedef enum
    {
    k7bits,
    k8bits
    } iUARTDataCfgEnum;

typedef enum
    {
    k1StBits,
    k2StBits
    } iUARTStopBitsEnum;

typedef enum
    {
    kNone,
    kOdd,
    kEven
    } iUARTPartityEnum;

typedef enum
    {
    kLSBFirst = 0,
    kMSBFirst = 1
    } iUARTSendModeEnum;

typedef enum
    {
    kUSCI_A0 = 0,
    kUSCI_A1 = 1
    } iUARTPortEnum;

typedef enum
    {
    kUCBUSY = 0x01,
    kUCRXERR = 0x04,
    kUCPE = 0x10,
    kUCOE = 0x20,
    kUCFE = 0x40,
    kUCLISTEN = 0x80
    } iUARTStatusFlag;

//Structure du buffer tournant
typedef struct
    {
    UInt8 UsciRecBuf[kSciRecBufSize ];
    UInt16 InIndex;
    UInt16 OutIndex;
    UInt8 ByteCount;
    bool BufferIsFull;
    } iUARTRecBufStruct;

class iUART: public Interface
    {
private:
    iUARTPortEnum serialPort;
    bool isEnabled;
    iUARTRecBufStruct USCIRingBuffer;

    //Variable global pour g�rer l'affectations des
    // interruptions
    static iUART* USCI_0;
    static iUART* USCI_1;

    // Fonction d'interruption propre a chaque objet
    void interruptHandler();

    //Interruptions handlers
    friend void USCI_A0(void);
    friend void USCI_A1(void);

public:
    iUART(iUARTPortEnum aPort, iUARTSendModeEnum aSendMode,
	    iUARTStopBitsEnum aStopBits, iUARTPartityEnum aParity,
	    iUARTDataCfgEnum aDataCfg, UInt16 aBaudrate);
    ~iUART();
    void config(iUARTSendModeEnum aSendMode, iUARTStopBitsEnum aStopBits,
	    iUARTPartityEnum aParity, iUARTDataCfgEnum aDataCfg,
	    UInt16 aBaudrate);
    bool getStatusFlag(iUARTStatusFlag aStatFlag);
    void enable();
    void disable();
    char read();
    bool write(char aData);
    bool sendString(string aString);
    bool sendString(char* aString);
    bool isBufferEmpty();
    int availableCharToRead();
    void iUART::readFullBuffer(char* aBuffer, int aCharToRead);
    void iUART::readFullBuffer(string &aBuffer);

    };
#endif
