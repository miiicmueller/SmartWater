#ifndef __DEF__
#define __DEF__

#define kFreq_MCLK	25000000UL
#define kFreq_SMCLK	 4000000UL
#define kFreq_ACLK	   32768UL

//ID de base pour les parametres
#define kMODE_BASE_ID 		0x0100
#define kMONTHSLIM_BASE_ID 	0x0200
#define kUNITNAME_BASE_ID 	0x0300
#define kTEMPOFFSET_BASE_ID 0x0400
#define kMEASSTAT_BASE_ID 	0x0500
#define kMPUSER_BASE_ID 	0x0600
#define kMPADMIN_BASE_ID 	0x0700
#define kAVAIL_BASE_ID 		0x0800
#define kALARMNUM_BASE_ID 	0x0900
#define kCOMPTEUR_BASE_ID 	0x0A00
#define kSIMCARD_BASE_ID 	0x0B00

#define kFREE_BASE_ID 0xFF01

#define nop()	__bis_SR_register(GIE)

//Declaration des types
typedef char SInt8;
typedef unsigned char UInt8;
typedef int SInt16;
typedef unsigned int UInt16;
typedef long SInt32;
typedef unsigned long UInt32;

typedef union
    {
    unsigned char aCharArray[sizeof(float)];
    float aFloatVal;
    } Float32;

#endif
