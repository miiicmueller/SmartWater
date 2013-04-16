#ifndef I_A_I_H
#define I_A_I_H

#include <string>
#include <assert.h>

#include "Interface.h"

class iAI : public Interface
{
public:
	void CfgPortAI();

	void StartConversion();

	void Enable();

	void Disable();

};
#endif
