#include "pch.h"
#include "ContactReportCallback.h"
#include <string>
#include <iostream>

void ContactReportCallback::onWake(physx::PxActor** actors, physx::PxU32 count)
{
	for (physx::PxU32 actorIndex = 0; actorIndex < count; actorIndex++)
	{
		const std::string* actorName = static_cast<std::string*>(actors[actorIndex]->userData);
		std::cout << (*actorName) << " woke up and begun exploring the world" << std::endl;
	}
}

void ContactReportCallback::onSleep(physx::PxActor** actors, physx::PxU32 count)
{
	for (physx::PxU32 actorIndex = 0; actorIndex < count; actorIndex++)
	{
		const std::string* actorName = static_cast<std::string*>(actors[actorIndex]->userData);
		std::cout << (*actorName) << " fell asleep and dreamt" << std::endl;
	}
}

void ContactReportCallback::onTrigger(physx::PxTriggerPair* pairs, physx::PxU32 count)
{
	(pairs);
	(count);
}

void ContactReportCallback::onAdvance(const physx::PxRigidBody* const* bodyBuffer, const physx::PxTransform* poseBuffer, const physx::PxU32 count)
{
	(bodyBuffer);
	(poseBuffer);
	(count);
}

void ContactReportCallback::onConstraintBreak(physx::PxConstraintInfo* constraints, physx::PxU32 count)
{
	(constraints);
	(count);
}

void ContactReportCallback::onContact(const physx::PxContactPairHeader& pairHeader, const physx::PxContactPair* pairs, physx::PxU32 nbPairs)
{
	// Walls don't uses userData. Only feedback when hamsters collide
	if (pairHeader.actors[0]->userData != nullptr && pairHeader.actors[1]->userData != nullptr)
	{
		// Implement what is to happen when two objects collide
		const std::string* firstRodent = static_cast<std::string*>(pairHeader.actors[0]->userData);
		const std::string* secondRodent = static_cast<std::string*>(pairHeader.actors[1]->userData);
		std::cout << (*firstRodent) << " puffed " << (*secondRodent) << std::endl;
	}
}
