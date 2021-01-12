#pragma once
#include "Behaviour.h"
#include "InputObserver.h"
#include "PostMaster.h"
#include "ObjectPool.h"

class CMouseSelection;

#define ON_DEATH_TIMER 1.77f

class CPlayerControllerComponent : public CBehaviour, public IInputObserver, public IObserver
{
public:
	CPlayerControllerComponent(CGameObject& aParent);
	~CPlayerControllerComponent() override;
	void Awake() override;
	void Start() override;
	void Update() override;

	void OnEnable() override;
	void OnDisable() override;
	void ReceiveEvent(const EInputEvent aEvent) override;
	void Receive(const SMessage& aMessage) override;

private:
};