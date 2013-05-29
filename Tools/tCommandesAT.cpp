#include <string>

#include "tCommandesAT.h"

using namespace std;

const string tCommandesAT::configSMS("AT#SMSATRUNCFG=3,1,5"); //configuration des param�tres par d�faut
const string tCommandesAT::questWhiteList("AT#SMSATWL?"); // liste des num�ros destinataires possibles
const string tCommandesAT::addP41ToWhiteList("AT#SMSATWL=0,1,0,\"+41*\""); // ajouter tous les num�ros (de Suisse) en destinataires possibles
const string tCommandesAT::enableSMS("AT#SMSATRUN=1");
const string tCommandesAT::questSMSMode("AT#SMSATRUN?");
const string tCommandesAT::delockPIN("AT+CPIN=");
const string tCommandesAT::questStatePIN("AT+CPIN=?"); // �tat de la carte SIM ; savoir si elle est lock�e
const string tCommandesAT::setModeText("AT+CMGF=1");
const string tCommandesAT::getSMS("AT+CMGR=");
const string tCommandesAT::deleteSMSAll("AT+CMGD=1,4");
const string tCommandesAT::deleteSMSPos("AT+CMGD=");
const string tCommandesAT::sendSMS("AT+CMGS=\"");
const string tCommandesAT::goSendSMS("\u001a");
const string tCommandesAT::endAT("\r");

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

