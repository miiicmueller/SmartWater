#ifndef I_CPU_H
#define I_CPU_H

#include <string>
#include <assert.h>

#include "Interface.h"

class iCpu : public Interface
{
public:
	void setPowerMode(char mode);

	void setFrequency(int divider);

};
#endif
