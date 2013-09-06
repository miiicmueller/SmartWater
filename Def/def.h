#ifndef __DEF__
#define __DEF__

#define kFreq_MCLK	25000000UL
#define kFreq_SMCLK	 4000000UL
#define kFreq_ACLK	   32768UL

#define nop()	__bis_SR_register(GIE)

#define kNbDaysJanuary 31
#define kNbDaysFebruary 28
#define kNbDaysMarch 31
#define kNbDaysApril 30
#define kNbDaysMay 31
#define kNbDaysJune 30
#define kNbDaysJuly 31
#define kNbDaysAugust 31
#define kNbDaysSeptember 30
#define kNbDaysOctober 31
#define kNbDaysNovember 30
#define kNbDaysDecember 31

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
    struct
	{
	UInt16 integer;
	UInt16 decimal;
	} aFakeFloat;
    } Float32;

#endif
