#pragma once
#include <glm/glm.hpp>		
class Collider
{
	glm::vec3 _centre;
	glm::vec3 _extent;
	int radius;
	bool _Oncollision;
public:
	Collider();
	Collider(glm::vec3 & centre, glm::vec3 & extent);
	Collider(Collider &col);
	~Collider();
	bool onCollisionEnter(Collider & col);
	void updateColliderPosition(glm::vec3 cen, glm::vec3 _extent);
	bool isCollision();
};

