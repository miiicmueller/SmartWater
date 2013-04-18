#include <string>
#include <assert.h>

#include "Interface.h"

//Constructeur de la classe mère
Interface::Interface()
{

}

kStatusEnum Interface::getStatus() {
	return this->status;
}

