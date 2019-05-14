#include "MainShip.h"



MainShip::MainShip()
{
}

MainShip::MainShip(GameObject & ship, Camera & cam)
{
	_ship = &ship;
	_camera = &cam;
	_velocity = glm::vec3(0.01f, 0.0f, 0.0f);

}


MainShip::~MainShip()
{
}
