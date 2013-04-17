#ifndef __TYPES_ENUM__
#define __TYPES_ENUM__

typedef enum {
	k8bits, k9bits
} UARTDataCfgEnum;

typedef enum {
	kLSBFirst, kMSBFirst
} UARTSendModeEnum;

typedef enum {
	kUSCI_A0, kUSCI_A1
} UARTPortEnum;

typedef enum {

} UARTStatusFlag;

#endif
