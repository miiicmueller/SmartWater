#ifndef T_COMMANDES_A_T_H
#define T_COMMANDES_A_T_H

#include <string>


using namespace std;

class tCommandesAT {
public:
	static  char configSMS[];
	static  char configBaud19200[];
	static  char questWhiteList[];
	static  char addP41ToWhiteList[];
	static  char enableSMS[];
	static  char questSMSMode[];
	static  char delockPIN[];
	static  char questStatePIN[];
	static  char setModeText[];
	static  char getSMS[];
	static  char deleteSMSAll[];
	static  char deleteSMSPos[];
	static  char sendSMS[];
	static  char goSendSMS[];
	static  char endAT[];
};
#endif
