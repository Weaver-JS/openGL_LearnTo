#pragma once
#include "GameObject.h"
#include "Camera.h"
class MainShip
{
	GameObject* _ship;
	Camera* _camera;
	glm::vec3 _velocity;
public:
	MainShip();
	MainShip(GameObject & ship,Camera &cam);
	~MainShip();
};

