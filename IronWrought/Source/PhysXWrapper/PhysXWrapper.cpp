#include "pch.h"
#include "PhysXWrapper.h"
#include "RigidDynamicBody.h"
#include "ContactReportCallback.h"

using namespace physx;

PxFilterFlags contactReportFilterShader(PxFilterObjectAttributes attributes0, PxFilterData filterData0,
	PxFilterObjectAttributes attributes1, PxFilterData filterData1,
	PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize)
{
	PX_UNUSED(attributes0);
	PX_UNUSED(attributes1);
	PX_UNUSED(filterData0);
	PX_UNUSED(filterData1);
	PX_UNUSED(constantBlockSize);
	PX_UNUSED(constantBlock);

	// all initial and persisting reports for everything, with per-point data
	pairFlags = PxPairFlag::eCONTACT_DEFAULT 
		| PxPairFlag::eNOTIFY_TOUCH_FOUND
		| PxPairFlag::eNOTIFY_TOUCH_PERSISTS
		| PxPairFlag::eNOTIFY_CONTACT_POINTS
		| PxPairFlag::eDETECT_CCD_CONTACT;
	return PxFilterFlag::eDEFAULT;
}

void PhysXWrapper::Init()
{
	PxDefaultErrorCallback errorCallback;

	myAllocator = new PxDefaultAllocator();
	myFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, *myAllocator, errorCallback);

	myPhysicsVisualDebugger = PxCreatePvd(*myFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
	myPhysicsVisualDebugger->connect(*transport, PxPvdInstrumentationFlag::eALL);

	myPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *myFoundation, PxTolerancesScale(), true, myPhysicsVisualDebugger);

	// All collisions gets pushed to this class
	myContactReportCallback = new ContactReportCallback();

	PxSceneDesc sceneDesc(myPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -982.f, 0.0f);
	myDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = myDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = myContactReportCallback;
	myScene = myPhysics->createScene(sceneDesc);

	PxPvdSceneClient* pvdClient = myScene->getScenePvdClient();
	if (pvdClient)
	{
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
	}

	// Create a basic setup for a scene - contain the rodents in a invisible cage
	myMaterial = myPhysics->createMaterial(0.9f, 0.4f, 0.96f);

	PxRigidStatic* groundPlane = PxCreatePlane(*myPhysics, PxPlane(0, 1, 0, 500), *myMaterial);
	myScene->addActor(*groundPlane);

	PxRigidStatic* topPlane = PxCreatePlane(*myPhysics, PxPlane(0, -1, 0, 0), *myMaterial);
	myScene->addActor(*topPlane);

	PxRigidStatic* leftWall = PxCreatePlane(*myPhysics, PxPlane(1, 0, 0, 0), *myMaterial);
	myScene->addActor(*leftWall);

	PxRigidStatic* rightWall = PxCreatePlane(*myPhysics, PxPlane(-1, 0, 0, 500), *myMaterial);
	myScene->addActor(*rightWall);
}

void PhysXWrapper::Shutdown()
{
	myMaterial->release();
	myScene->release();
	myDispatcher->release();
	myPhysics->release();
	myPhysicsVisualDebugger->release();
	myFoundation->release();
	delete myAllocator;
	myAllocator = nullptr;
}

void PhysXWrapper::Simulate(const float aDeltaTime)
{
	myScene->simulate(aDeltaTime);
	myScene->fetchResults(true);
}

RigidDynamicBody* PhysXWrapper::CreateBody(const float aX, const float aY)
{
	RigidDynamicBody* newBody = new RigidDynamicBody(*myPhysics, aX, aY);
	myScene->addActor(newBody->GetBody());

	return newBody;
}
