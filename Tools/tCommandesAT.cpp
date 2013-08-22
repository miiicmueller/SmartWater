#include <string>

#include "tCommandesAT.h"

using namespace std;

UInt8 tCommandesAT::configSMS[22] = "AT#SMSATRUNCFG=3,1,5"; //configuration des param�tres par d�faut
UInt8 tCommandesAT::questWhiteList[22] = "AT#SMSATWL?"; // liste des num�ros destinataires possibles
UInt8 tCommandesAT::addP41ToWhiteList[25] = "AT#SMSATWL=0,1,0,\"+41*\""; // ajouter tous les num�ros (de Suisse) en destinataires possibles
UInt8 tCommandesAT::enableSMS[22] = "AT#SMSATRUN=1";
UInt8 tCommandesAT::questSMSMode[22] = "AT#SMSATRUN?";
UInt8 tCommandesAT::delockPIN[22] = "AT+CPIN=";
UInt8 tCommandesAT::questStatePIN[22] = "AT+CPIN?"; // �tat de la carte SIM ; savoir si elle est lock�e
UInt8 tCommandesAT::setModeText[22] = "AT+CMGF=1";
UInt8 tCommandesAT::getSMS[22] = "AT+CMGR=";
UInt8 tCommandesAT::deleteSMSAll[22] = "AT+CMGD=1,4";
UInt8 tCommandesAT::deleteSMSPos[22] = "AT+CMGD="; //effacer un SMS a une position choisie
UInt8 tCommandesAT::sendSMS[22] = "AT+CMGS=\"";
UInt8 tCommandesAT::endAT[22] = "\r";
UInt8 tCommandesAT::configBaud9600[22] = "AT+IPR=9600";

