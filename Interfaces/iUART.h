#ifndef I_U_A_R_T_H
#define I_U_A_R_T_H

#include <string>
#include <assert.h>
#include "../Def/enum_types.h"

#include "Interface.h"

// Buffer de 200 caractères
#define kSciRecBufSize ((unsigned char)(200))

//Structure du buffer tournant
typedef struct {
	char SciRecBuf[kSciRecBufSize ];
	int InIndex;
	int OutIndex;
	int ByteCount;
	bool BufferIsFull;
} USCIRecBufStruct;

class iUART: public Interface {
private:
	UARTPortEnum serialPort;
	bool isEnabled;
	USCIRecBufStruct USCIRingBuffer;

	//Variable global pour gérer l'affectations des
	// interruptions
	static iUART* UART_0;
	static iUART* UART_1;

	// Fonction d'interruption propre a chaque objet
	void interruptHandler();
	bool isBufferEmpty();

	//Interruptions handlers
	friend void USCI_A0(void);
	friend void USCI_A1(void);

public:
	iUART(UARTPortEnum aPort, UARTSendModeEnum aSendMode,
			UARTStopBitsEnum aStopBits, UARTPartityEnum aParity,
			UARTDataCfgEnum aDataCfg, int aBaudrate);
	void config(UARTSendModeEnum aSendMode, UARTStopBitsEnum aStopBits,
			UARTPartityEnum aParity, UARTDataCfgEnum aDataCfg, int aBaudrate);
	bool getStatusFlag(UARTStatusFlag aStatFlag);
	void enable();
	void disable();
	char read();
	bool write(char aData);

};
#endif
