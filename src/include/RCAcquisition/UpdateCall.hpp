#pragma once
#include "iUpdateStradegy.hpp"

struct UpdateCall
{
	UpdateCall();
	iUpdateStradegy * _call;
	void operator()();
};

inline UpdateCall::UpdateCall(): _call(0)
{

}

inline void UpdateCall::operator()()
{
	_call->Update();
}