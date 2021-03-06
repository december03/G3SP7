#include "stdafx.h"
#include "MainSingleton.h"
#include "CollisionManager.h"
#include "PopupTextService.h"
#include "DialogueSystem.h"
#include "PopupTextService.h"

CMainSingleton* CMainSingleton::ourInstance = nullptr;

CMainSingleton::CMainSingleton() {
	ourInstance = this;
	myPostMaster = new CPostMaster();
	myCollisionManager = new CCollisionManager();
	myPopupTextService = new CPopupTextService();
	myDialogueSystem = new CDialogueSystem();
}

CMainSingleton::~CMainSingleton()
{
	SAFE_DELETE(myPostMaster);
	SAFE_DELETE(myCollisionManager);
	SAFE_DELETE(myPopupTextService);
	SAFE_DELETE(myDialogueSystem);
	ourInstance = nullptr;
}

CPostMaster& CMainSingleton::PostMaster()
{
	return *ourInstance->myPostMaster;
}

CCollisionManager & CMainSingleton::CollisionManager()
{
	return *ourInstance->myCollisionManager;
}

CPopupTextService& CMainSingleton::PopupTextService()
{
	return *ourInstance->myPopupTextService;
}

CDialogueSystem& CMainSingleton::DialogueSystem()
{
	return *ourInstance->myDialogueSystem;
}
