#include <string>
#include <assert.h>

#include "tAvailability.h"
#include "Modules/mEEPROM.h"

tAvailability::tAvailability(mEEPROM *mEeprom, UInt16 aModeNum) {
	this->mPeriphSauv = mEeprom;

	//Configuration de la sauvegarde
	this->aId = kAVAIL_BASE_ID + aModeNum; //Id unique
	this->aNbBytes = 4; // 2 * 2 = 4

	//Allocation de la mémoire
	this->mPeriphSauv->malloc(this->aId, this->aNbBytes);

}

void tAvailability::save() {
	UInt8 aDataTab[4] = { 0 };

	//Sérialisation
	aDataTab[0] = (UInt8) this->aInterval;
	aDataTab[1] = (UInt8) (this->aInterval >> 8);
	aDataTab[2] = (UInt8) this->aTime;
	aDataTab[3] = (UInt8) (this->aTime >> 8);

	//Enregistrement dans l'EEPROM
	this->mPeriphSauv->store(this->aId, aDataTab);

}
void tAvailability::load() {
	UInt8 aDataTab[4] = { 0 };

	//Récupération des données
	this->mPeriphSauv->load(this->aId, aDataTab);

	//Desérialisation
	this->aInterval = (UInt8) aDataTab[0];
	this->aInterval |= (UInt8) aDataTab[1];
	this->aTime = (UInt8) aDataTab[2];
	this->aTime |= (UInt8) aDataTab[3];

}

