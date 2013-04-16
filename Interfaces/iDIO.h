#ifndef I_D_I_O_H
#define I_D_I_O_H

#include <string>
#include <assert.h>

#include "Interface.h"

class iDIO : public Interface
{
private:
	int portAddress;

	char mask;


public:
	void SetPortDirection();

};
#endif
