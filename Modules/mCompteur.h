#ifndef M_COMPTEUR_H
#define M_COMPTEUR_H

#include <string>
#include <assert.h>

#include "Module.h"

class mCompteur : public Module
{
private:
	int channel;


private:
	void select();

public:
	void read();

};
#endif
