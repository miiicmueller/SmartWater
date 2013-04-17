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

} UARTStatusFlag;

// ----------------------------

#endif
