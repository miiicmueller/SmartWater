#ifndef I_U_A_R_T_H
#define I_U_A_R_T_H

#include <string>
#include <assert.h>

#include "Interface.h"

class iUART : public Interface
{
public:
	void config(int kPort);

};
#endif
