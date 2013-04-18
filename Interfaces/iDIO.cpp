#include <string>
#include <assert.h>

#include "iDIO.h"

iDIO::iDIO(char* aPortAddress, char aMask) {
	this->thePortAddress = aPortAddress;
	this->theMask = aMask;
}

void iDIO::SetPortDirection() {

}

bool iDIO::write(char aData) {
	*((this->thePortAddress) + 2) = (aData & (this->theMask));
}

char iDIO::read() {
	return 0;
}
