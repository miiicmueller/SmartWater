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
#define kSciRecBufReceptionSize ((unsigned char)(200))
#define kSciRecBufSize ((unsigned char)(200))
#define kSciRecBufTransmissionSize ((unsigned char)(270))

using namespace std;

typedef enum {
	k7bits, k8bits
} iUARTDataCfgEnum;

typedef enum {
	k1StBits, k2StBits
} iUARTStopBitsEnum;

typedef enum {
	kNone, kOdd, kEven
} iUARTPartityEnum;

typedef enum {
	kLSBFirst = 0, kMSBFirst = 1
} iUARTSendModeEnum;

typedef enum {
	kUSCI_A0 = 0, kUSCI_A1 = 1
} iUARTPortEnum;

typedef enum {
	kUCBUSY = 0x01,
	kUCRXERR = 0x04,
	kUCPE = 0x10,
	kUCOE = 0x20,
	kUCFE = 0x40,
	kUCLISTEN = 0x80
} iUARTStatusFlagEnum;

typedef enum {
	k300,k4800, k9600, k19200, k57600, k115200
} iUARTBaudrateEnum;

//Structure du buffer tournant
typedef struct {
	UInt8 UsciRecBuf[kSciRecBufReceptionSize ];
	UInt16 InIndex;
	UInt16 OutIndex;
	UInt8 ByteCount;
	bool BufferIsFull;
} iUARTRecBufStruct;

class iUART: public Interface {
private:
	iUARTPortEnum serialPort;
	char uartBuffer[kSciRecBufReceptionSize];
	bool isEnabled;
	bool dataReceived;

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
			iUARTDataCfgEnum aDataCfg, iUARTBaudrateEnum aBaudrate);
	~iUART();
	void config(iUARTSendModeEnum aSendMode, iUARTStopBitsEnum aStopBits,
			iUARTPartityEnum aParity, iUARTDataCfgEnum aDataCfg,
			iUARTBaudrateEnum aBaudrate);
	bool getStatusFlag(iUARTStatusFlagEnum aStatFlag);
	void enable();
	void disable();
	char read();
	bool write(char aData);
	bool sendString(char* aString);
	bool isBufferEmpty();
//	int readLine(char* aBuffer);
	void clearReceptionBuffer();
	void clearInternalSerialBuffer();
	bool retInString(char* string);
	bool readFrame(char* string);
	int availableCharToRead();
	bool readFullFrame(char* stringReceived);

	/**
	 * Fonction permettant d'obtenir les bytes re�us jusqu'au \r\n
	 *
	 * aString : chaine resortant la prochaine cha�ne de byte re�us en m�moire, jusqu'� un CRLF
	 * retour : true si une nouvelle cha�ne a ete trouvee
	 */
	bool readFrameToCRLF(char* string);

};
#endif
