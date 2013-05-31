#ifndef G_COMPUTE_H
#define G_COMPUTE_H

#include <string>
#include <assert.h>

#include "Gestionnaire.h"
#include "../Tools/tDate.h"

class gCompute : public Gestionnaire
{
private:
	char* smsToSend;

	int smsNb;

	tDate nextAlarm;

};
#endif
