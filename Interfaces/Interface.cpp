#include <string>
#include <assert.h>

#include "Interface.h"

//Constructeur de la classe m�re
Interface::Interface()
{

}

kStatusEnum Interface::getStatus() {
	return this->status;
}

