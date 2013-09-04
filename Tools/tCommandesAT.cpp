#include <string>

#include "tCommandesAT.h"

using namespace std;

UInt8 tCommandesAT::configSMS[22] = "AT#SMSATRUNCFG=3,1,5"; //configuration des parametres par defaut
UInt8 tCommandesAT::enableSMS[22] = "AT#SMSATRUN=1";
UInt8 tCommandesAT::enableServiceData[22] = "AT+CUSD=1"; // activation CUSD (Unstructured Supplementary Service Data), pour lire le credit
UInt8 tCommandesAT::questSMSMode[22] = "AT#SMSATRUN?";
UInt8 tCommandesAT::delockPIN[22] = "AT+CPIN=";
UInt8 tCommandesAT::questStatePIN[22] = "AT+CPIN?"; // etat de la carte SIM ; savoir si elle est lockee
UInt8 tCommandesAT::setModeText[22] = "AT+CMGF=1";
UInt8 tCommandesAT::getSMS[22] = "AT+CMGR="; //effacer un SMS a une position
UInt8 tCommandesAT::getCredit[22] = "ATD *130#"; // demande le credit
UInt8 tCommandesAT::deleteSMSAll[22] = "AT+CMGD=1,4";
UInt8 tCommandesAT::deleteSMSPos[22] = "AT+CMGD="; //effacer un SMS a une position
UInt8 tCommandesAT::sendSMS[22] = "AT+CMGS=\"";
UInt8 tCommandesAT::endAT[22] = "\r";
UInt8 tCommandesAT::configBaud9600[22] = "AT+IPR=9600";
UInt8 tCommandesAT::getStateMemory[22] = "AT+CPMS?";

