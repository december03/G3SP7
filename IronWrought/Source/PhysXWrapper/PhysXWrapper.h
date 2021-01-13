#pragma once

class RigidDynamicBody;
class ContactReportCallback;

namespace physx
{
	class PxDefaultAllocator;
	class PxFoundation;
	class PxPhysics;
	class PxDefaultCpuDispatcher;
	class PxScene;
	class PxMaterial;
	class PxPvd;
}

class PhysXWrapper
{
public:
	void							Init();
	void							Shutdown();
	void							Simulate(const float aDeltaTime);
	RigidDynamicBody*				CreateBody(const float aX, const float aY);

private:

	physx::PxFoundation*			myFoundation = nullptr;
	physx::PxPhysics*				myPhysics = nullptr;
	physx::PxDefaultCpuDispatcher*	myDispatcher = nullptr;
	physx::PxScene*					myScene = nullptr;
	physx::PxMaterial*				myMaterial = nullptr;
	physx::PxPvd*					myPhysicsVisualDebugger = nullptr;
	physx::PxDefaultAllocator*		myAllocator = nullptr;
	ContactReportCallback*			myContactReportCallback = nullptr;

};

