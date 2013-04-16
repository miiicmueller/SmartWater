#ifndef G_TERMINAL_H
#define G_TERMINAL_H

#include <string>
#include <assert.h>

#include "Gestionnaire.h"

class gTerminal : public Gestionnaire
{
private:
	bool pipeOpen;


public:
	bool getPipeOpen();

};
#endif
