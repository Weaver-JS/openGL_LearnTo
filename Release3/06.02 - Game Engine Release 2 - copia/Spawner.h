#pragma once
#include <glm/glm.hpp>	
#include <random>
#include <SDL/SDL.h>
#define TimerOFFSET 800
class Spawner
{
private:
	glm::vec3 min;
	glm::vec3 max;
	float _startTicks;
	float _currentFrame;
	bool timerCounter;
public:
	Spawner();
	Spawner(glm::vec3 min, glm::vec3 max);
	void startTimer();
	bool trySpawn(int & score);

	glm::vec3 & getMin();
	glm::vec3 & getMax();
	~Spawner();
};

