#include <string>

#include "tCommandesAT.h"

using namespace std;

const char* tCommandesAT::configSMS 		= "AT#SMSATRUNCFG=3,1,5"; //configuration des param�tres par d�faut
const char* tCommandesAT::questWhiteList 	= "AT#SMSATWL?" ; // liste des num�ros destinataires possibles
const char* tCommandesAT::addP41ToWhiteList = "AT#SMSATWL=0,1,0,\"+41*\""; // ajouter tous les num�ros (de Suisse) en destinataires possibles
const char* tCommandesAT::enableSMS 		= "AT#SMSATRUN=1";
const char* tCommandesAT::questSMSMode 		= "AT#SMSATRUN?";
const char* tCommandesAT::delockPIN 		= "AT+CPIN=";
const char* tCommandesAT::questStatePIN 	= "AT+CPIN=?"; // �tat de la carte SIM ; savoir si elle est lock�e
const char* tCommandesAT::setModeText 		= "AT+CMGF=1";
const char* tCommandesAT::getSMS 			= "AT+CMGR=";
const char* tCommandesAT::deleteSMSAll 		= "AT+CMGD=1,4";
const char* tCommandesAT::deleteSMSPos 		= "AT+CMGD=";
const char* tCommandesAT::sendSMS 			= "AT+CMGS=\"";
const char* tCommandesAT::goSendSMS 		= "\u001a";
const char* tCommandesAT::endAT = "\r";

//static string tCommandesAT::configSMS = "AT#SMSATRUNCFG=3,1,5"; //configuration des param�tres par d�faut
//static string tCommandesAT::questWhiteList = "AT#SMSATWL?"; // liste des num�ros destinataires possibles
//static string tCommandesAT::addP41ToWhiteList = "AT#SMSATWL=0,1,0,\"+41*\""; // ajouter tous les num�ros (de Suisse) en destinataires possibles
//static string tCommandesAT::enableSMS = "AT#SMSATRUN=1";
//static const string tCommandesAT::questSMSMode = "AT#SMSATRUN?";
//static const string tCommandesAT::delockPIN = "AT+CPIN=";
//static const string tCommandesAT::questStatePIN = "AT+CPIN=?"; // �tat de la carte SIM ; savoir si elle est lock�e
//static const string tCommandesAT::setModeText = "AT+CMGF=1";
//static const string tCommandesAT::getSMS = "AT+CMGR=";
//static const string tCommandesAT::deleteSMSAll = "AT+CMGD=1,4";
//static const string tCommandesAT::deleteSMSPos = "AT+CMGD=";
//static const string tCommandesAT::sendSMS = "AT+CMGS=";
//static const string tCommandesAT::goSendSMS = "\u001a";
//static const string tCommandesAT::endAT = "\r";

