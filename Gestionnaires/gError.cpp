/*
 * gError.cpp
 *
 *  Created on: 6 sept. 2013
 *      Author: cyrille.savy
 */

#include "gError.h"

gError::gError()
    {

    }

void gError::setup()
    {
    for (int i = 0; i < kGErrorNbErrors; i++)
	{
	this->gErrorList[i] = true;
	}
    }

void gError::execute()
    {

    }

gError::~gError()
    {
    }

