#pragma once
#include "iUpdateStradegy.hpp"

struct UpdateCall
{
	UpdateCall();
	UpdateCall(const UpdateCall & copy);
	~UpdateCall();
	iUpdateStradegy * _call;
	void operator()();
	UpdateCall & operator=(const UpdateCall & rhs);
};

inline UpdateCall::UpdateCall(): _call(0)
{

}

inline UpdateCall::UpdateCall(const UpdateCall & copy):_call(copy._call)
{
	
}

inline UpdateCall::~UpdateCall()
{
	delete _call;
	_call = 0;
}

inline void UpdateCall::operator()()
{
	_call->Update();
}

inline UpdateCall & UpdateCall::operator=(const UpdateCall & rhs)
{
	_call = rhs._call;
	
	return *this;
}