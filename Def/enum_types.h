/*
------------------------------------------------------------
Copyright 2003-2007 Haute Ecole ARC Ingénierie,
Switzerland. All rights reserved
------------------------------------------------------------
Nom du fichier :  enum_types.h
Auteur et Date :  Mueller Michael 17.4.2013

But : Type custom pour le programme

------------------------------------------------------------
*/

#ifndef __TYPES_ENUM__
#define __TYPES_ENUM__

// ------- ENUM UART ---------------

typedef enum {
	k7bits, k8bits
} UARTDataCfgEnum;

typedef enum {
	k1StBits, k2StBits
} UARTStopBitsEnum;

typedef enum {
	kNone, kOdd, kEven
} UARTPartityEnum;

typedef enum {
	kLSBFirst, kMSBFirst
} UARTSendModeEnum;

typedef enum {
	kUSCI_A0, kUSCI_A1
} UARTPortEnum;

typedef enum {
	kUCBUSY = 0x01,
	kUCRXERR = 0x04,
	kUCPE = 0x10,
	kUCOE = 0x20,
	kUCFE = 0x40,
	kUCLISTEN = 0x80
} UARTStatusFlag;

// ----------------------------

#endif
