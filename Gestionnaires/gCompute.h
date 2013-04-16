#ifndef G_COMPUTE_H
#define G_COMPUTE_H

#include <string>
#include <assert.h>

#include "Gestionnaire.h"
#include "tDate.h"

class gCompute : public Gestionnaire
{
private:
	string smsToSend[];

	int smsNb;

	tDate nextAlarm;

};
#endif
