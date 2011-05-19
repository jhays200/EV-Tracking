#include <Wire.h>
#include <CameraC328R.h>
#include <DS1307.h>

//Variables
int datetime[7];
CameraC328R camera;

static uint16_t pictureSizeCount = 0;

/**
 * This callback is called EVERY time a JPEG data packet is received.
 */
void getJPEGPicture_callback( uint16_t pictureSize, uint16_t packageSize, uint16_t packageCount, byte* package )
{
  // packageSize is the size of the picture part of the package
  pictureSizeCount += packageSize;

  for( uint16_t i = 0; i < packageSize; i++ )
  {
    Serial.print( package[i], BYTE );
  }

  if( pictureSizeCount == pictureSize )
  {
    camera.powerOff();
  }
}

void setup() 
{  
  Wire.begin();  

  //USB Serial Line
  Serial.begin(115200);

  //Bluetooth Serial Line
  Serial1.begin(115200);

  //Camera Serial Line
  Serial2.begin(9600);

  //GPS Serial Line
  //Serial3.begin(115200);
} 

void loop() 
{
  while(!Serial1.available());
  switch(Serial1.read())
  {
  case 'D':                
    Serial1.println("Time");
    RTC.get(datetime, 1);
    for(int i=0; i<7; i++)
    {
      Serial1.print(datetime[i]);
      Serial1.print(" ");
    }
    Serial1.println();
    break;

  case 'P':
    Serial1.println("Photo");

    if( !camera.sync() )
    {
      Serial.println( "Sync failed." );
    }

    if( !camera.initial( CameraC328R::CT_JPEG, CameraC328R::PR_160x120, CameraC328R::JR_640x480 ) )
    {
      Serial.println( "Initial failed." );
    }

    if( !camera.setPackageSize( 64 ) )
    {
      Serial.println( "Package size failed." );
    }

    if( !camera.setLightFrequency( CameraC328R::FT_50Hz ) )
    {
      Serial.println( "Light frequency failed." );
    }

    // Let camera settle, per manual
    delay(2000);

    if( !camera.snapshot( CameraC328R::ST_COMPRESSED, 0 ) )
    {
      Serial.println( "snapshot failed" );
    }

    if( !camera.getJPEGPicture( CameraC328R::PT_JPEG, PROCESS_DELAY, &getJPEGPicture_callback ) )
    {
      Serial.println( "Get JPEG failed." );
      return;
    }
    break;

  default:
    Serial1.println("Unknown Command");
  }
}
