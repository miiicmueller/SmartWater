#include <string>

#include "tCommandesAT.h"

using namespace std;

char tCommandesAT::configSMS[22] = "AT#SMSATRUNCFG=3,1,5"; //configuration des param�tres par d�faut
char tCommandesAT::enableSMS[22] = "AT#SMSATRUN=1";
char tCommandesAT::enableServiceData[22] = "AT+CUSD=1"; // activation CUSD (Unstructured Supplementary Service Data), pour lire le credit
char tCommandesAT::questSMSMode[22] = "AT#SMSATRUN?";
char tCommandesAT::delockPIN[22] = "AT+CPIN=";
char tCommandesAT::questStatePIN[22] = "AT+CPIN?"; // �tat de la carte SIM ; savoir si elle est lock�e
char tCommandesAT::setModeText[22] = "AT+CMGF=1";
char tCommandesAT::getSMS[22] = "AT+CMGR="; //effacer un SMS a une position
char tCommandesAT::getCredit[22] = "ATD *130#"; // demande le credit
char tCommandesAT::deleteSMSAll[22] = "AT+CMGD=1,4";
char tCommandesAT::deleteSMSPos[22] = "AT+CMGD="; //effacer un SMS a une position
char tCommandesAT::sendSMS[22] = "AT+CMGS=\"";
char tCommandesAT::endAT[22] = "\r";
char tCommandesAT::configBaud9600[22] = "AT+IPR=9600";

