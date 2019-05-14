#include "ScoreObject.h"



ScoreObject::ScoreObject()
{
}

ScoreObject::ScoreObject(Geometry & gameObject)
{
	_listOfObjects = &gameObject;
	GameObject tempObject;
	SDL_Color col;
	col.r = 255;
	col.b = 255;
	col.g = 255;
	//tempObject.co_textMan.getTextureID("Score:", col);
}


ScoreObject::~ScoreObject()
{
}
