#include <string>
#include <assert.h>

#include "tMdPAdmin.h"
#include "Modules/mEEPROM.h"

tMdPAdmin::tMdPAdmin(mEEPROM *mEeprom, UInt16 aModeNum) {
	this->mPeriphSauv = mEeprom;

	//Configuration de la sauvegarde
	this->aId = kMPADMIN_BASE_ID + aModeNum; //Id unique
	this->aNbBytes = 20;

	//Allocation de la mémoire
	this->mPeriphSauv->malloc(this->aId, this->aNbBytes);

}

void tMdPAdmin::save() {
	//Enregistrement dans l'EEPROM
	this->mPeriphSauv->store(this->aId, this->mdPAdmin);

}
void tMdPAdmin::load() {
	//Récupération des données
	this->mPeriphSauv->load(this->aId, this->mdPAdmin);
}

