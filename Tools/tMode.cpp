#include <string>
#include <assert.h>

#include "tMode.h"
#include "Modules/mEEPROM.h"

tMode::tMode(mEEPROM *mEeprom, UInt16 aModeNum) {
	this->mPeriphSauv = mEeprom;
	this->mode = 0;

	//Configuration de la sauvegarde
	this->aId = kMODE_BASE_ID + aModeNum; //Id unique
	this->aNbBytes = 1;

	//Allocation de la mémoire
	this->mPeriphSauv->malloc(this->aId, this->aNbBytes);

}

void tMode::save() {
	UInt8 aDataTab[1];

	// Sérialisation du mode
	aDataTab[0] = this->mode;

	//Enregistrement dans l'EEPROM
	this->mPeriphSauv->store(this->aId, aDataTab);

}
void tMode::load() {
	UInt8 aDataTab[1];

	//Récupération des données
	this->mPeriphSauv->load(this->aId, aDataTab);

	// Desérialisation du mode
	this->mode = aDataTab[0];
}

