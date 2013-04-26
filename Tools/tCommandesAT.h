#ifndef T_COMMANDES_A_T_H
#define T_COMMANDES_A_T_H

#include <string>
#include <assert.h>

using namespace std;

class tCommandesAT
{
public:
	string configSMS = "AT#SMSATRUNCFG=3,1,5"; //configuration des param�tres par d�faut
	string questWhiteList = "AT#SMSATWL?"; // liste des num�ros destinataires possibles
	string addP41ToWhiteList = "AT#SMSATWL=0,1,0,\"+41*\""; // ajouter tous les num�ros (de Suisse) en destinataires possibles
	string enableSMS = "AT#SMSATRUN=1";
	string questSMSMode = "AT#SMSATRUN?";
	string delockPIN = "AT+CPIN=";
	string questStatePIN = "AT+CPIN=?"; // �tat de la carte SIM ; savoir si elle est lock�e
	string setModeText = "AT+CMGF=1";
	string getSMS = "AT+CMGR=";
	string deleteSMSAll ="AT+CMGD=1,4";
	string deleteSMSPos ="AT+CMGD=";
	string sendSMS = "AT+CMGS=";
	string goSendSMS = "\u001a";
	string endAT = "\r";

};
#endif
