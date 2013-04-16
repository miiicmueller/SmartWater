#ifndef T_PARAMETERS_H
#define T_PARAMETERS_H

#include <string>
#include <assert.h>

class tParameters
{
private:
	int addressEEPROM;

	int nbBytes;


private:
	void save();

public:
	void get();

	void set();

	void load();

};
#endif
