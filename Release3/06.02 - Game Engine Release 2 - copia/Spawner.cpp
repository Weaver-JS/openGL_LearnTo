#include "Spawner.h"



Spawner::Spawner()
{
	_currentFrame = 0;
	timerCounter = false;
	
}

Spawner::Spawner(glm::vec3 min, glm::vec3 max)
{
	this->min = min;
	this->max = max;
	_currentFrame = 0.0f;
	_startTicks = 0.0f;
	timerCounter = false;
}

void Spawner::startTimer()
{
	if (!timerCounter)
	{
		_startTicks = (float)SDL_GetTicks();
		timerCounter = true;
	}

}

bool Spawner::trySpawn(int & score)
{
	
	if (_currentFrame > _startTicks + TimerOFFSET)
	{
		std::random_device rd;
		std::mt19937 eng(rd());
		std::uniform_real_distribution<> coordX(min.x, max.x);
		std::uniform_real_distribution<> coordY(min.y, max.y);
		std::uniform_real_distribution<> coordZ(min.z, max.z);
		
		glm::vec3 coord(coordX(eng), coordY(eng) ,0.0f);
		
		/*GameObject _object;
		_object._objectType = RED_CUBE;
		_object._angle = 0;
		_object._rotation = glm::vec3(0, 0, 1);
		_object._scale = glm::vec3(0.1f, 0.1f, 0.5f);
		_object._translate = coord;
		_object.col = Collider(_object._translate - _object._scale, _object._translate);
		 _object._textureRepetion = true;
		 _object._textureFIle = "../06.02 - Game Engine Release 2/resources/textures/galaxy2.jpg";*/
	
		
		
		//_listOfObjects->getGameElement(_listOfObjects->getNumGameElements() - 1)._textureID = texM.getTextureID(_object._textureFIle);
		timerCounter = false;
		score -= 100;
		return true;

	}
	_currentFrame = (float)SDL_GetTicks();
	return false;
}

glm::vec3 & Spawner::getMin()
{
	// TODO: insert return statement here
	return min;
}

glm::vec3 & Spawner::getMax()
{
	return max;
	// TODO: insert return statement here
}


Spawner::~Spawner()
{
}
