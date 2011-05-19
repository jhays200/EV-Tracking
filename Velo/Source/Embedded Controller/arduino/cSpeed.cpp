///////////////////////////////////////////////////////////
//  cSpeed.cpp
//  Implementation of the Class cSpeed
//  Created on:      05-May-2010 3:28:59 AM
//  Original author: shawn.mcginnis
///////////////////////////////////////////////////////////
#include "cSpeed.h"

cSpeed::cSpeed()
{
    rpm = 0;
    nowtime = millis();
    lasttime = millis();
    attachInterrupt(WHEELSPEED_INT, cSpeed::Update(), RISING);
}

cSpeed::~cSpeed()
{
    throttle = analogRead(0);
}

bool cSpeed::Update()
{
    lasttime = nowtime;
    nowtime = millis();

    rpm = ((float)1 / ((float)(millis() - lasttime ))) * 60000;
    return false;
}

void* cSpeed::Read()
{
    // X rev   60 min   62 in    1 mile    miles      
    // ----- * ------ * ----- * -------- = ----- = mph
    // 1 min   1 hour   1 rev   63360 in   hour       

    mph =  0.058712 * rpm;

    return &mph;
}
