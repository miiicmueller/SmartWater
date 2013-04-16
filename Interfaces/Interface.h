#ifndef INTERFACE_H
#define INTERFACE_H

#include <string>
#include <assert.h>
#include <stdlib.h>
#include "../Def/def.h"

class Interface
{
private:
	kStatusEnum status ;
public:
	Interface();
	bool write(char data);
	char read();

};
#endif
