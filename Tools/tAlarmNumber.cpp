#include <string>
#include <assert.h>

#include "tAlarmNumber.h"
#include "Modules/mEEPROM.h"

tAlarmNumber::tAlarmNumber(mEEPROM *mEeprom, UInt16 aModeNum) {
	this->mPeriphSauv = mEeprom;

	//Configuration de la sauvegarde
	this->aId = kALARMNUM_BASE_ID + aModeNum; //Id unique
	this->aNbBytes = 15;

	//Allocation de la mémoire
	this->mPeriphSauv->malloc(this->aId, this->aNbBytes);

}

void tAlarmNumber::save() {
	//Enregistrement dans l'EEPROM
	this->mPeriphSauv->store(this->aId, this->aTelNumber);

}
void tAlarmNumber::load() {
	//Récupération des données
	this->mPeriphSauv->load(this->aId, this->aTelNumber);
}

