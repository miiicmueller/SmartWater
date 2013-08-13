#include <string>

#include "tCommandesAT.h"

using namespace std;

char tCommandesAT::configSMS[22] = "AT#SMSATRUNCFG=3,1,5"; //configuration des param�tres par d�faut
char tCommandesAT::questWhiteList[22] = "AT#SMSATWL?"; // liste des num�ros destinataires possibles
char tCommandesAT::addP41ToWhiteList[25] = "AT#SMSATWL=0,1,0,\"+41*\""; // ajouter tous les num�ros (de Suisse) en destinataires possibles
char tCommandesAT::enableSMS[22] = "AT#SMSATRUN=1";
char tCommandesAT::questSMSMode[22] = "AT#SMSATRUN?";
char tCommandesAT::delockPIN[22] = "AT+CPIN=";
char tCommandesAT::questStatePIN[22] = "AT+CPIN=?"; // �tat de la carte SIM ; savoir si elle est lock�e
char tCommandesAT::setModeText[22] = "AT+CMGF=1";
char tCommandesAT::getSMS[22] = "AT+CMGR=";
char tCommandesAT::deleteSMSAll[22] = "AT+CMGD=1,4";
char tCommandesAT::deleteSMSPos[22] = "AT+CMGD=";
char tCommandesAT::sendSMS[22] = "AT+CMGS=\"";
char tCommandesAT::goSendSMS[22] = "\u001a";
char tCommandesAT::endAT[22] = "\r";
char tCommandesAT::configBaud19200[22] = "AT+IPR=9600";

