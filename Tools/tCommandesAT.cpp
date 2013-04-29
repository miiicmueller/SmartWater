#include <string>

#include "tCommandesAT.h"

static string configSMS("AT#SMSATRUNCFG=3,1,5"); //configuration des param�tres par d�faut
static string questWhiteList("AT#SMSATWL?"); // liste des num�ros destinataires possibles
static string addP41ToWhiteList("AT#SMSATWL=0,1,0,\"+41*\""); // ajouter tous les num�ros (de Suisse) en destinataires possibles
static string enableSMS("AT#SMSATRUN=1");
static string questSMSMode("AT#SMSATRUN?");
static string delockPIN("AT+CPIN=");
static string questStatePIN("AT+CPIN=?"); // �tat de la carte SIM ; savoir si elle est lock�e
static string setModeText("AT+CMGF=1");
static string getSMS("AT+CMGR=");
static string deleteSMSAll("AT+CMGD=1,4");
static string deleteSMSPos("AT+CMGD=");
static string sendSMS("AT+CMGS=");
static string goSendSMS("\u001a");
static string endAT("\r");
