///////////////////////////////////////////////////////////
//  cCamera.cpp
//  Implementation of the Class cCamera
//  Created on:      05-May-2010 3:27:50 AM
//  Original author: Shawn
///////////////////////////////////////////////////////////
#include "cCamera.h"

cCamera::cCamera()
{
    //Camera Serial Line
    Serial.begin(57600);
}

cCamera::~cCamera()
{

}

bool cCamera::Update()
{
    if( camera.sync() )
    {
        if( camera.initial( CameraC328R::CT_JPEG, CameraC328R::PR_160x120, CameraC328R::JR_640x480 ) )
        {
            if( camera.setPackageSize( 64 ) )
            {
                if( camera.setLightFrequency( CameraC328R::FT_50Hz ) )
                {
                    delay(2000);
                    if( camera.snapshot( CameraC328R::ST_COMPRESSED, 0 ) )
                    {
                        //TODO: Throw "Snapshot Failed"
                    }
                    if( !camera.getJPEGPicture( CameraC328R::PT_JPEG, PROCESS_DELAY, &getJPEGPicture_callback ) )
                    {
                        //TODO: Throw "Get JPEG Failed."
                    }
                }
            }
        }
    }
    return false;
}

///**
// * This callback is called EVERY time a JPEG data packet is received.
// *
// * void getJPEGPicture_callback( uint16_t pictureSize, uint16_t packageSize, uint16_t packageCount, byte* package )
// * {
// * // packageSize is the size of the picture part of the package
// * pictureSizeCount += packageSize;
// * 
// * for( uint16_t i = 0; i < packageSize; i++ )
// * {
// * Serial.print( package[i], BYTE );
// * }
// * 
// * if( pictureSizeCount == pictureSize )
// * {
// * camera.powerOff();
// * }
// * }