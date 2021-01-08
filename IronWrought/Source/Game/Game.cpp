#include "stdafx.h"
#include "Game.h"

#include "MenuState.h"
#include "LoadLevelState.h"
#include "InGameState.h"
#include "PauseState.h"
#include "OptionsState.h"
#include "MainSingleton.h"
#include "PostMaster.h"

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
			CStateStack::EState::InGame,
			CStateStack::EState::PauseMenu
		},
		CStateStack::EState::InGame);
}

void CGame::InitRealGame()
{
	// Currently we wish to only have an InGame and PauseMenu state (preprod - 05 JAN)
	myStateStack.Awake(
		{
		//CStateStack::EState::BootUp,
		//CStateStack::EState::TitleScreen,
		//CStateStack::EState::MainMenu,
		//CStateStack::EState::Credits,
		//CStateStack::EState::Options,
		//CStateStack::EState::LevelSelect,
		//CStateStack::EState::Intro,
		CStateStack::EState::LoadLevel,
		CStateStack::EState::InGame,
		CStateStack::EState::PauseMenu
		},
		CStateStack::EState::BootUp);
}