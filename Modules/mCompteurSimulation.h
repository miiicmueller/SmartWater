#ifndef M_COMPTEUR_SIMULATION_H
#define M_COMPTEUR_SIMULATION_H

#include <string>
#include <assert.h>

#include "mCompteur.h"

class mCompteurSimulation : public mCompteur
{
public:
	void sendFrame();

};
#endif
