#ifndef GESTIONNAIRE_H
#define GESTIONNAIRE_H

#include <string>
#include <assert.h>

class Gestionnaire
{
public:

	virtual void execute() = 0;

	virtual void setup() = 0;

};
#endif
