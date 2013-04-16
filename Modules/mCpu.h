#ifndef M_CPU_H
#define M_CPU_H

#include <string>
#include <assert.h>

#include "Module.h"

class mCpu : public Module
{
public:
	void setPowerMode(char mode);

	void setFrequency(int divider);

};
#endif
