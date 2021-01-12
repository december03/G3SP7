#include "stdafx.h"
#include "PlayerControllerComponent.h"
#include "InputMapper.h"
#include "NavMeshComponent.h"
#include "AnimationComponent.h"
#include "MainSingleton.h"
#include "CircleColliderComponent.h"
#include "TriangleColliderComponent.h"
#include "TransformComponent.h"

CPlayerControllerComponent::CPlayerControllerComponent(CGameObject& aParent):
	CBehaviour(aParent)
{
}

CPlayerControllerComponent::~CPlayerControllerComponent()
{
}

void CPlayerControllerComponent::Awake()
{
}

void CPlayerControllerComponent::Start()
{
}

void CPlayerControllerComponent::Update()
{
}

void CPlayerControllerComponent::OnEnable() {}

void CPlayerControllerComponent::OnDisable() {}

void CPlayerControllerComponent::ReceiveEvent(const IInputObserver::EInputEvent /*aEvent*/)
{
}

void CPlayerControllerComponent::Receive(const SMessage& /*aMessage*/)
{

	/*switch (aMessage.myMessageType)
	{
	default:
		break;
	}*/
}
