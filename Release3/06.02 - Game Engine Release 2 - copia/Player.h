#pragma once
#include "GameObject.h"
#include <vector>
#include "Geometry.h"
class Player
{
private:
	glm::vec3 _position;
	glm::vec3 _velocity;
	Geometry* _playerBullets;
	int score;
	bool win,lose;
	
public:
	Player();
	Player(glm::vec3 & _pos, glm::vec3 & vel, Geometry & geo);
	~Player();
	void fire();
	void increaseScore();
	void restartScore();
	Geometry  getGeometry();
	void setPosition(glm::vec3 & pos);
	glm::vec3 & getVelocity();
	glm::vec3 & getPosition();
	int & getScore();
	
};

