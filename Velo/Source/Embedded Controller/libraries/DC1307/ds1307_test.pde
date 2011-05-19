#include <WProgram.h>
#include <Wire.h>
#include <DS1307.h> 

int rtc[7];
byte data[56];

void setup()
{
  Serial.begin(9600);
  
  RTC.stop();
  RTC.set(DS1307_SEC,1);
  RTC.set(DS1307_MIN,23);
  RTC.set(DS1307_HR,12);
  RTC.set(DS1307_DOW,1);
  RTC.set(DS1307_DATE,1);
  RTC.set(DS1307_MTH,10);
  RTC.set(DS1307_YR,7);
  RTC.start();
  
  
  for(int i=0; i<56; i++)
  {
    RTC.set_sram_byte(65,i);
  }

}

void loop()
{
  RTC.get(rtc,true);

  for(int i=0; i<7; i++)
  {
    Serial.print(rtc[i]);
    Serial.print(" ");
  }
  Serial.println();
  Serial.print(RTC.min_of_day(true));  
  Serial.println();
  delay(1000);
  //RTC.get_data(data);
  //for(int i=0; i<56; i++)
  //{
    //Serial.print(data[i]);
    //Serial.print(" ");
  //}
  
  Serial.print(RTC.get_sram_byte(29));
  Serial.println();
}