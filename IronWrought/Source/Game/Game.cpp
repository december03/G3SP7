#include "stdafx.h"
#include "Game.h"
#include "InGameState.h"
#include "../Includes/PhysX-4.1/physx/include/PxActor.h"

//#include "MainSingleton.h"
//#include "PostMaster.h"

#ifdef _DEBUG
#pragma comment(lib, "Engine_Debug.lib")
#endif // _DEBUG
#ifdef NDEBUG
#pragma comment(lib, "Engine_Release.lib")
#endif // NDEBUG

CGame::CGame()
{
}

CGame::~CGame()
{
}

void CGame::Init()
{
	InitDev();
	//InitRealGame();
	physx::PxActor* actor;
	actor;
	physx.Init();
}

bool CGame::Update()
{
	bool stateStackHasUpdated = myStateStack.Update();
	CMainSingleton::PostMaster().FlushEvents();
	return stateStackHasUpdated;
}

void CGame::InitDev()
{
	myStateStack.Awake(
		{
			//CStateStack::EState::LoadLevel,
			CStateStack::EState::InGame
		},
		CStateStack::EState::InGame);
}

void CGame::InitRealGame()
{
	// Currently we wish to only have an InGame and PauseMenu state (preprod - 05 JAN)
	myStateStack.Awake(
		{
		CStateStack::EState::InGame
		},
		CStateStack::EState::InGame);
}
