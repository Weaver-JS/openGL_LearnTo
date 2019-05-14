#include "Player.h"



Player::Player()
{
}

Player::Player(glm::vec3 & _pos, glm::vec3 & vel,Geometry & geo)
{
	_position = _pos;
	_velocity = vel;
	_playerBullets = &geo;
	score = 10000;
	win = false;
	lose = false;
}


Player::~Player()
{
}

void Player::fire()
{
	GameObject _bullet;
	_bullet._objectType = PURPLE_PYRAMID;
	_bullet._angle = 270;
	_bullet._rotation = glm::vec3(0,0, 1);
	_bullet._scale = glm::vec3(0.2f, 0.2f, 0.2f);
	_bullet._translate = _position;
	_bullet.col = Collider(_bullet._translate - _bullet._scale, _bullet._translate );
	_playerBullets->pushObject(_bullet);

	
	
}

void Player::increaseScore()
{
	score -= 100;
}

void Player::restartScore()
{
	score = 10000;
}

Geometry  Player::getGeometry()
{
	return *_playerBullets;
}

void Player::setPosition(glm::vec3 & pos)
{
	_position = pos;
}

glm::vec3 & Player::getVelocity()
{
	// TODO: insert return statement here
	return _velocity;
}

glm::vec3 & Player::getPosition()
{
	return _position;
}

int & Player::getScore()
{
	return score;
}
