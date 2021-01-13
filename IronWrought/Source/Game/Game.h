#pragma once
#include "StateStack.h"
#include <PhysXWrapper.h>

class CGame
{
public:
	CGame();
	~CGame();

	void Init();
	bool Update();

private:

	void InitDev();
	void InitRealGame();

	CStateStack myStateStack;
	PhysXWrapper physx;
};

