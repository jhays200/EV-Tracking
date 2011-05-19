#pragma once

class TestObject
{
public:
	TestObject();
	~TestObject();
	double GetX();
	void SetX(double);
private:
	double x;
};