#pragma once
#include "iUpdateStradegy.hpp"

struct UpdateCall
{
	UpdateCall();
	~UpdateCall();
	iUpdateStradegy * _call;
	void operator()();
};

inline UpdateCall::UpdateCall(): _call(0)
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