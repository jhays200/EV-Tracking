#include <WProgram.h>
#include <Wire.h>
#include <Servo.h>
#include <TimerThree.h>
#include <DS1307.h>

//Variables
int datetime[7];  

Servo motor;
float volts, watts, amps, mph, rpm;
unsigned int throttle;
volatile unsigned long lasttime, nowtime;

//motorcontrol current power = Settings_PwmMin
volatile unsigned int CurrentPower = 1000;
volatile unsigned int Throttle = 0;

#define Settings_Acceleration 2
#define Settings_Deceleration 8
#define Settings_MaxWattage 300
#define Settings_MinMotorPWM 1000
#define Settings_MaxMotorPWM 2000
#define Settings_MinThrottle 100
#define Settings_MaxThrottle 600

void MotorControl()
{
  unsigned int RequestedPower;

  //Read the throttle value
  //Throttle.Update();
  Throttle = analogRead(0);

  if( Throttle < Settings_MinThrottle )
  {
    RequestedPower = Settings_MinMotorPWM;
  }
  else if( Throttle > Settings_MaxThrottle )
  {
    RequestedPower = Settings_MaxMotorPWM;
  }
  else
  {
    RequestedPower = map( Throttle, Settings_MinThrottle, Settings_MaxThrottle, Settings_MinMotorPWM, Settings_MaxMotorPWM );    
  }

  //TODO: RequestedPower = if(Throttle > Pedel) RequestedThrottle : RequestedPedel

  /*********
  PowerControl
  *********/
  //if( (Voltage.Scale() * Current.Scale()) > Settings_MaxWattage )
  
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
  motor.writeMicroseconds(CurrentPower);//Brake?CurrentPower:Settings_MinMotorPWM);
}

void setup()
{  
  //Setup Motor Control
  Timer3.initialize(10000); //10,000 microseconds = 1/100 second
  Timer3.attachInterrupt(MotorControl);

  Wire.begin();  

  //Camera Serial Line
  Serial.begin(4800);//57600);

  //Bluetooth Serial Line
  Serial1.begin(115200);

  //Screen Serial Line
  Serial2.begin(115200);

  //GPS Serial Line
  Serial3.begin(38200);

  //Motor Initialise
  motor.attach(9);
  motor.writeMicroseconds(Settings_MinMotorPWM);

  //Begin counting revolutions
  rpm = 0;
  nowtime = millis();
  lasttime = millis();
  attachInterrupt(0, rev, RISING);
  
  /*
  RTC.stop();
  RTC.set(DS1307_HR,12);
  RTC.set(DS1307_MIN,0);
  RTC.set(DS1307_SEC,0);
  RTC.set(DS1307_DOW,4);
  RTC.set(DS1307_MTH,5);
  RTC.set(DS1307_DATE,19);
  RTC.set(DS1307_YR,10);
  RTC.start();
  */
}

void rev()
{  
  lasttime = nowtime;
  nowtime = millis();
}

void loop()
{
  Serial2.print('\r');

  Serial2.print("RTC Date: ");
  Serial2.print(datetime[2],DEC);
  Serial2.print(":");
  Serial2.print(datetime[1],DEC);
  Serial2.print(":");
  Serial2.print(datetime[0],DEC);
  Serial2.print(" ");
  Serial2.print(datetime[5],DEC);
  Serial2.print("-");
  Serial2.print(datetime[4],DEC);
  Serial2.print("-");
  Serial2.print(datetime[6],DEC);
  Serial2.print(" PST\n\n");
  delay(50);

  Serial2.print("MotorPWM: ");
  Serial2.print(CurrentPower);
  Serial2.print('\n');
  delay(50);

  Serial2.print("RawThrot: ");
  Serial2.print(Throttle);
  Serial2.print('\n');
  delay(50);

  Serial2.print("\n Voltage: ");
  //( (5V) / (1204 steps) * read steps ) / 63.69mV 
  volts = (float)analogRead(3)*0.0766653;
  Serial2.print(volts);
  Serial2.print(" V\n");
  delay(50);  


  Serial2.print(" Current: ");
  //( (5V) / (1204 steps) * read steps ) / 36.60mV 
  amps = (float)analogRead(2)*0.13341;
  Serial2.print(amps);
  Serial2.print(" A\n");
  delay(50);

  Serial2.print("   Power: ");
  watts = volts * amps;
  Serial2.print(watts);
  Serial2.print(" W\n\n");
  delay(50);

  rpm = (float)1/(float)(millis() - lasttime ) * 60000;
  Serial2.print("    Revs: ");
  Serial2.print(rpm);
  Serial2.print(" rpm\n");
  delay(50);

  //       X rev   60 min   62 in    1 mile    miles
  // mph = ----- * ------ * ----- * -------- = -----
  //       1 min   1 hour   1 rev   63360 in   hour

  mph = 0.058712 * rpm;
  Serial2.print("WheelMPH: ");
  Serial2.print(mph);
  Serial2.print(" mph\n");
  delay(50);

  RTC.get(datetime, 1);
}

