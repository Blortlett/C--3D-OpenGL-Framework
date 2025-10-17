#pragma once
#include <glm.hpp>
#include "cInputSystem.h"
#include "cMeshModel.h";

class cObjectMover
{
private:
	cMeshModel* mMeshModel;
	float mMoveSpeed = 1.f;

	float mPreivousFrameTime;

	glm::vec3 moveDirection;


	void HandleMovement(glm::ivec2 _LatMovement, float _VertMovement, float _DeltaTime)
	{
		moveDirection = glm::vec3(0.f);

		// Calculate input direction
		moveDirection.x += _LatMovement.x;
		moveDirection.z += _LatMovement.y;
		moveDirection.y += _VertMovement;
		moveDirection *= mMoveSpeed;
		// Calculate new position
		glm::vec3 newPosition = mMeshModel->GetPosition() + moveDirection * _DeltaTime;
		
		mMeshModel->SetPosition(newPosition);
	}

public:
	cObjectMover(cMeshModel* _MeshModel)
	{ 
		mMeshModel = _MeshModel;
	}

	void Update(float _DeltaTime)
	{
		// Move Object
		glm::ivec2 LatMovement = cInputSystem::GetInstance().Get_WASD();
		float VertMovement = cInputSystem::GetInstance().Get_QE();
		HandleMovement(LatMovement, VertMovement, _DeltaTime);
	}
};
