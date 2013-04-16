#ifndef INTERFACE_H
#define INTERFACE_H

#include <string>
#include <assert.h>

#include "kStatusEnum.h"

class Interface
{
private:
	kStatusEnum status;


public:
	boolean write(char data);

	char read();

};
#endif
