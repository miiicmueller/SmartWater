#include <string>

#include "tCommandesAT.h"

static string configSMS("AT#SMSATRUNCFG=3,1,5"); //configuration des paramètres par défaut
static string questWhiteList("AT#SMSATWL?"); // liste des numéros destinataires possibles
static string addP41ToWhiteList("AT#SMSATWL=0,1,0,\"+41*\""); // ajouter tous les numéros (de Suisse) en destinataires possibles
static string enableSMS("AT#SMSATRUN=1");
static string questSMSMode("AT#SMSATRUN?");
static string delockPIN("AT+CPIN=");
static string questStatePIN("AT+CPIN=?"); // état de la carte SIM ; savoir si elle est lockée
static string setModeText("AT+CMGF=1");
static string getSMS("AT+CMGR=");
static string deleteSMSAll("AT+CMGD=1,4");
static string deleteSMSPos("AT+CMGD=");
static string sendSMS("AT+CMGS=");
static string goSendSMS("\u001a");
static string endAT("\r");
