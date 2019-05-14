#pragma once
#include "Geometry.h"
#include "TextManager.h"
class ScoreObject
{
private:
	Geometry * _listOfObjects;
	TextManager _textMan;
	std::string _score;
public:
	ScoreObject();
	ScoreObject(Geometry & gameObject);
	~ScoreObject();
};

