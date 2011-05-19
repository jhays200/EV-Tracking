#include <iostream>
using namespace std;

//globals
int assist(0);
int speed(0);
float distance(0.0);
int time(0);
float latitude(0.0);
float longitude(0.0);
float altitude (0.0);
int tire(0);
int maxwatt(0);
int maxpwm(0);
int minpwm(0);
int maxspeed(0);
int accel(0);
int decel(0);
int minthrot(0);
int maxthrot(0);

void DrawBasics()
{
	//update assist variable


	line(230, 0, 230, 240);				//lines		//line(x1, y1, x2, y2)
	line(0, 190, 230, 190);
	line(57, 190, 57, 240);
	line(115, 190, 115, 240);
	line(172, 190, 172, 240);
	line(230, 90, 320, 90);
	line(230, 150, 320, 150);
	rect(270, 10, 10, 70);				//plus		//rect(x, y, width, height)
	rect(240, 40, 70, 10);				//plus
	rect(240, 190, 70, 10);				//minus
	text("Power Assist", 233, 93, 20);	//power assist lable
	text((int)assist, 250, 116, 20);	//power assist
	text("Main", 3, 210);				//main button text
	text("Second", 60, 210);			//second button text
	text("GPS", 118, 210);				//gps button text
	text("Settings", 175, 210);			//settings button text
}

////////////////////////////////////////////////
//	abstract state
////////////////////////////////////////////////
class State
{
public:
	virtual void Display() = 0;		//virtual display
	virtual void getValues() = 0;	//virtual getvalues
};

////////////////////////////////////////////////
//	primary concrete
////////////////////////////////////////////////
class PrimaryPage : public State
{
public:
	PrimaryPage()						//constructor
	{	}
	void Display() override				//displays primary info
	{
		this->getValues();
		DrawBasics();
		text((int)speed, 20, 50, 75);	//displays speed
		text("MPH", 180, 115);			//units for speed
		text("Main", 3, 177);			//screen label
	}
	void getValues() override			//updates primary values
	{
		//get values for primary screen
	}
};

////////////////////////////////////////////////
//	secondary concrete
////////////////////////////////////////////////
class SecondaryPage : public State
{
public:
	SecondaryPage()							//constructor
	{	}
	void Display() override					//displays secondary info
	{
		this->getValues();
		DrawBasics();
		text((float)distance, 20, 40, 50);	//displays distance for ride
		text("Miles", 180, 80);				//units for distance
		text((int)time, 20, 110, 50);		//displays time for ride
		text("Elapsed Time", 180, 150);		//units for elapsed time
		text("Secondary", 3, 177);			//screen label
	}
	void getValues() override				//updates secondary values
	{
		//get values for secondary screen
	}
};

////////////////////////////////////////////////
//	gps concrete
////////////////////////////////////////////////
class GPSPage : public State
{
public:
	GPSPage()								//constructor
	{	}
	void Display() override					//displays gps info
	{
		this->getValues();
		DrawBasics();
		text((float)latitude, 20, 40, 20);	//latitude
		text("Latitude", 180, 30);			//latitude label
		text((float)longitude, 20, 80, 20);	//longitude
		text("Longitude", 180, 70);			//longitude label
		text((float)altitude, 20, 120, 20);	//altitude
		text("Altitude", 180, 110);			//altitude label
		text("GPS", 3, 177);				//screen label
	}
	void getValues() override				//updates gps values
	{
		//get values for gps screen
	}
};

////////////////////////////////////////////////
//	settings concrete
////////////////////////////////////////////////
class SettingsPage : public State
{
public:
	SettingsPage()						//constructor
	{	}
	void Display() override				//displays settings info
	{
		this->getValues();
		DrawBasics();
		text("Tire diamater:", 20, 20);	//tire diameter label
		text((int)tire, 150, 20);		//tire diameter
		text("in", 170, 20);			//tire diameter units
		text("Max Wattage:", 20, 35);	//max wattage label
		text((int)maxwatt, 150, 35);	//max wattage
		text("W", 170, 35);				//max wattage units
		text("Min PWM:", 20, 50);		//min pwm label
		text((int)minpwm, 150, 50);		//min pwm
		text("Max PWM:", 20, 75);		//max pwm label
		text((int)maxpwm, 150, 75);		//max pwm
		text("Max Speed:", 20, 90);		//max speed label
		text((int)maxspeed, 150, 90);	//max speed
		text("MPH", 170, 90);			//max speed units
		text("Acceleration", 20, 105);	//acceleration label
		text((int)accel, 150, 105);		//acceleration
		text("Decelaration", 20, 120);	//deceleration label
		text((int)decel, 150, 120);		//deceleration
		text("Min Throttle", 20, 135);	//min throttle label
		text((int)minthrot, 150, 135);	//min throttle
		text("Max Throttle", 20, 150);	//max throttle label
		text((int)maxthrot, 150, 150);	//max throttle
		text("Settings", 3, 177);		//screen label
	}
	void getValues() override			//updates settings values
	{
		//get values for settings screen
	}
};

////////////////////////////////////////////////
//	context
////////////////////////////////////////////////
class Context
{
private:
	class State *myState;
public:
	Context()							//constructor
	{
		setState(new PrimaryPage());
	}
	void setState(State *newState)		//overrides current state with the new state
	{
		myState = newState;
	}
	void Display()						//calls the most concrete display
	{
		myState->Display();
	}
	void getValues()					//calls the most concrete get values
	{
		myState->getValues();
	}
};

////////////////////////////////////////////////
//	main
////////////////////////////////////////////////
void main()
{
	fill(255, 255, 255);		//white shapes
	background(0, 0, 0);		//black background
	stroke(255, 255, 255);		//white text

	Context CurrentScreen;		//initial display
	CurrentScreen.Display();

	while(1)
	{
		gettouch();
		if(mouseX < 230 && mouseY > 190)		//button selection coordinates
		{
			if(mouseX < 57)							//primary screen
			{
				CurrentScreen.setState(new PrimaryPage());
			}
			else if(mouseX > 57 && mouseX < 115)	//secondary screen
			{
				CurrentScreen.setState(new SecondaryPage());
			}
			else if(mouseX > 115 && mouseX < 172)	//gps screen
			{
				CurrentScreen.setState(new GPSPage());
			}
			else if(mouseX > 172 && mouseX < 230)	//settings screen
			{
				CurrentScreen.setState(new SettingsPage());
			}
		}
		else if(mouseX > 230 && mouseY < 90)	//plus assist coordinates
		{
			//++assist (+20)
		}
		else if(mouseX > 230 && mouseY > 150)	//minus assist coordinates
		{
			//--assist (-20)
		}
		
		CurrentScreen.Display();	//display current screen
	}
}