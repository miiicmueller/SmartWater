#include <string>
#include <assert.h>

#include "tTemperatureOffset.h"
#include "Modules/mEEPROM.h"

tTemperatureOffset::tTemperatureOffset(mEEPROM *mEeprom, UInt16 aModeNum) {
	this->mPeriphSauv = mEeprom;

	//Configuration de la sauvegarde
	this->aId = kTEMPOFFSET_BASE_ID + aModeNum; //Id unique
	this->aNbBytes = sizeof(float); // 4 x 8bits car on a un float

	//Allocation de la mémoire
	this->mPeriphSauv->malloc(this->aId, this->aNbBytes);

}

void tTemperatureOffset::save() {
	//Enregistrement dans l'EEPROM
	this->mPeriphSauv->store(this->aId, this->aOffset.aCharArray);

}
void tTemperatureOffset::load() {
	//Récupération des données
	this->mPeriphSauv->load(this->aId, this->aOffset.aCharArray);



}

