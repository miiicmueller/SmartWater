#include <string>

#include "tCommandesAT.h"

using namespace std;

const char* tCommandesAT::configSMS = "AT#SMSATRUNCFG=3,1,5"; //configuration des param�tres par d�faut
const char* tCommandesAT::questWhiteList = "AT#SMSATWL?"; // liste des num�ros destinataires possibles
const char* tCommandesAT::addP41ToWhiteList = "AT#SMSATWL=0,1,0,\"+41*\""; // ajouter tous les num�ros (de Suisse) en destinataires possibles
const char* tCommandesAT::enableSMS = "AT#SMSATRUN=1";
const char* tCommandesAT::questSMSMode = "AT#SMSATRUN?";
const char* tCommandesAT::delockPIN = "AT+CPIN=";
const char* tCommandesAT::questStatePIN = "AT+CPIN=?"; // �tat de la carte SIM ; savoir si elle est lock�e
const char* tCommandesAT::setModeText = "AT+CMGF=1";
const char* tCommandesAT::getSMS = "AT+CMGR=";
const char* tCommandesAT::deleteSMSAll = "AT+CMGD=1,4";
const char* tCommandesAT::deleteSMSPos = "AT+CMGD=";
const char* tCommandesAT::sendSMS = "AT+CMGS=\"";
const char* tCommandesAT::goSendSMS = "\u001a";
const char* tCommandesAT::endAT = "\r";
const char* tCommandesAT::configBaud19200 = "AT+IPR=9600";

