#include <string>
#include <assert.h>

#include "tUnitName.h"
#include "Modules/mEEPROM.h"

tUnitName::tUnitName(mEEPROM *mEeprom, UInt16 aModeNum) {
	this->mPeriphSauv = mEeprom;

	//Configuration de la sauvegarde
	this->aId = kUNITNAME_BASE_ID + aModeNum; //Id unique
	this->aNbBytes = 20;

	//Allocation de la mémoire
	this->mPeriphSauv->malloc(this->aId, this->aNbBytes);

}

void tUnitName::save() {
	//Enregistrement dans l'EEPROM
	this->mPeriphSauv->store(this->aId, this->aName);

}
void tUnitName::load() {
	//Récupération des données
	this->mPeriphSauv->load(this->aId, this->aName);
}
