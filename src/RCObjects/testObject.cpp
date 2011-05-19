#include "RCObjects/testObject.hpp"

TestObject::TestObject():x(0)
{}

TestObject::~TestObject()
{}

double TestObject::GetX()
{
	return x;
}

void TestObject::SetX(double x)
{
	this->x = x;
}