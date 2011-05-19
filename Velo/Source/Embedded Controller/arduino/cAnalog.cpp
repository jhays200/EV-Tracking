///////////////////////////////////////////////////////////
//  cAnalog.cpp
//  Implementation of the Class cAnalog
//  Created on:      05-May-2010 3:27:32 AM
//  Original author: shawn.mcginnis
///////////////////////////////////////////////////////////

#include "cAnalog.h"



cAnalog::cAnalog(unsigned int what_pin, float scale_value)
:pin(what_pin), scale(scale_value)
{ }

cAnalog::~cAnalog(){

}

int cAnalog::GetMaximum(){

	return Maximum;
}

void cAnalog::SetMaximum(int newVal){

	Maximum = newVal;
}

int cAnalog::GetMinimum(){

	return Minimum;
}

void cAnalog::SetMinimum(int newVal){

	Minimum = newVal;
}

void Update()
{
    analogRead(pin);    
    SetLastUpdate(Kernel.Clock.GetRTC());
}

float cVoltage::Scale()
{
    Update();
    return (float)reading * scale;
}