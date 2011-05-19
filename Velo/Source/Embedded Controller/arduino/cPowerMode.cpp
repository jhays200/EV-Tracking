///////////////////////////////////////////////////////////
//  cPowerMode.cpp
//  Implementation of the Class cPowerMode
//  Created on:      05-May-2010 3:28:36 AM
//  Original author: Shawn
///////////////////////////////////////////////////////////

#include "cPowerMode.h"

cPowerMode::cPowerMode()
{

}

cPowerMode::~cPowerMode()
{

}

void cPowerMode::Update()
{
    unsigned int RequestedPower;

    //Read the throttle value
    //TODO: Throttle.Update();
    Throttle = analogRead(0);

    if( Throttle < Settings_MinThrottle )
    {
        RequestedThrottle = Settings_MinMotorPWM;
    }
    else if( Throttle > Settings_MaxThrottle )
    {
        RequestedThrottle = Settings_MaxMotorPWM;
    }
    else
    {
        RequestedThrottle = map( Throttle, Settings_MinThrottle, Settings_MaxThrottle, Settings_MinMotorPWM, Settings_MaxMotorPWM );    
    }

    //TODO: Inject power mode management 
    RequestedPower = RequestedThrottle;

    /*********
    PowerControl
    *********/
    //TODO: if( (Voltage.Scale() * Current.Scale()) > Settings_MaxWattage )
    //If you are using too much or you want less
    if( (((float)analogRead(3)*0.0766653) * ((float)analogRead(2)*0.13341)) >= Settings_MaxWattage || CurrentPower + Settings_Acceleration > RequestedPower )
    {
        CurrentPower -= Settings_Deceleration;

        //Fix underflow
        if( CurrentPower < Settings_MinMotorPWM )
        {
            CurrentPower = Settings_MinMotorPWM;
        }
    }
    //If you want more power
    else if( CurrentPower + Settings_Acceleration < RequestedPower )
    {
        CurrentPower += Settings_Acceleration;
    }

    //Set the motor power
    //TODO: Average the last 10 values to see if the change is valid
    motor.writeMicroseconds(CurrentPower); //TODO: Brake?CurrentPower:Settings_MinMotorPWM);
}

void cPowerMode::Stop()
{
    motor.writeMicroseconds(Settings_MinMotorPWM);
}