#ifndef T_COMMANDES_A_T_H
#define T_COMMANDES_A_T_H

#include <string>


using namespace std;

class tCommandesAT {
public:
	static const string configSMS;
	static const string questWhiteList;
	static const string addP41ToWhiteList;
	static const string enableSMS;
	static const string questSMSMode;
	static const string delockPIN;
	static const string questStatePIN;
	static const string setModeText;
	static const string getSMS;
	static const string deleteSMSAll;
	static const string deleteSMSPos;
	static const string sendSMS;
	static const string goSendSMS;
	static const string endAT;
};
#endif
