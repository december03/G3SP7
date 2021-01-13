#pragma once
#include <utility>
	
namespace physx
{
	class PxRigidDynamic;
	class PxPhysics;
}

class RigidDynamicBody
{
public:
							RigidDynamicBody(physx::PxPhysics& aPhysX, const float aX = 0, const float aY = 0);
	physx::PxRigidDynamic&	GetBody();
	std::pair<float, float>	GetPosition() const;
	float					GetRotation() const;

private:
	physx::PxRigidDynamic*	myBody = nullptr;
};

inline physx::PxRigidDynamic& RigidDynamicBody::GetBody()
{
	
	return *myBody;
}

