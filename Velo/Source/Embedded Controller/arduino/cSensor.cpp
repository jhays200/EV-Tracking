///////////////////////////////////////////////////////////
//  cSensor.cpp
//  Implementation of the Class cSensor
//  Created on:      05-May-2010 3:28:51 AM
//  Original author: shawn.mcginnis
///////////////////////////////////////////////////////////

#include "cSensor.h"
#include "cKernel.h"

cSensor::cSensor(){

}

cSensor::~cSensor(){

}

DateTime cSensor::GetLastUpdate(){

	return LastUpdate;
}

void cSensor::SetLastUpdate(DateTime newVal)
{
    LastUpdate = newVal;
}