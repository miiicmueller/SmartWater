#ifndef __INTERFACE__
#define __INTERFACE__

#include <string>
#include <assert.h>
#include <stdlib.h>
#include "../Def/def.h"

//Sert à rien, à mon avis car la classe possède déja ce système
#ifndef __kStatusEnum__
#define __kStatusEnum__

typedef enum {
	kActive, kError, kSuspended, kClosed, kBusy
} kStatusEnum;

#endif

class Interface {
private:
	kStatusEnum status;

public:
	Interface();
	virtual ~Interface();
	virtual bool write(char aData) = 0;
	virtual char read() = 0;
	kStatusEnum getStatus();
};

#endif
