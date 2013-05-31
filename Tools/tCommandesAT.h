#ifndef T_COMMANDES_A_T_H
#define T_COMMANDES_A_T_H

#include <string>


using namespace std;

class tCommandesAT {
public:
	static const char* configSMS;
	static const char* questWhiteList;
	static const char* addP41ToWhiteList;
	static const char* enableSMS;
	static const char* questSMSMode;
	static const char* delockPIN;
	static const char* questStatePIN;
	static const char* setModeText;
	static const char* getSMS;
	static const char* deleteSMSAll;
	static const char* deleteSMSPos;
	static const char* sendSMS;
	static const char* goSendSMS;
	static const char* endAT;
};
#endif
