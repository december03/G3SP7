#pragma once

class CPostMaster;
class CCollisionManager;
class CDialogueSystem;
class CPopupTextService;

class CMainSingleton
{
	friend class CEngine;

public:
	static CPostMaster& PostMaster();
	static CCollisionManager& CollisionManager();
	static CPopupTextService& PopupTextService();
	static CDialogueSystem& DialogueSystem();

private:
	static CMainSingleton* ourInstance;

	CPostMaster*			myPostMaster;
	CCollisionManager*	myCollisionManager;
	CPopupTextService*	myPopupTextService;
	CDialogueSystem*		myDialogueSystem;

private:
	CMainSingleton();
	~CMainSingleton();
};

