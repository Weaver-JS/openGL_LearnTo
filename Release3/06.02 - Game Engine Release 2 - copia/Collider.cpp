#include "Collider.h"



Collider::Collider()
{
	_centre = glm::vec3(0);
	_extent = glm::vec3(0);
	_Oncollision = false;
}

Collider::Collider(glm::vec3 & centre, glm::vec3 & extent)
{
	_centre = centre;
	_extent = extent;
	radius = 1;
	_Oncollision = false;
}

Collider::Collider(Collider & col)
{
	_centre = col._centre;
	_extent = col._extent;
	_Oncollision = col._Oncollision;
	radius = col.radius;
	_Oncollision = false;
}


Collider::~Collider()
{
}

bool Collider::onCollisionEnter(Collider & col)
{
	
	/*if (abs(_centre.x - col._centre.x) > (_extent.x - col._extent.x) ||
		abs(_centre.y - col._centre.y) > (_extent.y - col._extent.y)
		|| abs(_centre.z - col._centre.z) > _extent.z - col._extent.z)
	{*/
	if ( glm::length(_centre- col._centre) < radius )
	{
		_Oncollision = true;
		col._Oncollision = true;
		return true;
	}
	
	return false;
}

void Collider::updateColliderPosition(glm::vec3 cen, glm::vec3 extent)
{
	_centre = cen;
	_extent = extent;
}

bool Collider::isCollision()
{
	return _Oncollision;
}
