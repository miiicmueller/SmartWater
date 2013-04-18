#ifndef INTERFACE_H
#define INTERFACE_H

#include <string>
#include <assert.h>
#include <stdlib.h>
#include "../Def/def.h"

typedef enum
{
	kActive, kError, kSuspended, kClosed, kBusy
} kStatusEnum;

class Interface
{
private:
	kStatusEnum status;
public:
	Interface();
	virtual ~Interface();
	virtual bool write(char aData);
	virtual char read();
	virtual kStatusEnum getStatus();
};
#endif
