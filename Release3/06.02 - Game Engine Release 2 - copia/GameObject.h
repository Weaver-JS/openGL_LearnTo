#pragma once
#include <glm/glm.hpp>			//OpenGL Mathematics 
#include "Collider.h"
#include <GL\glew.h>
#include <string>
struct GameObject
{
	int _objectType;
	glm::vec3 _translate;
	float _angle;
	glm::vec3 _rotation;
	glm::vec3 _scale;
	glm::vec4 _color;
	//Texture Settings
	std::string _textureFIle;
	bool _textureRepetion;
	int _textureID;
	//Texture Settings
	Collider col;
	int _materialType;


	GameObject()
	{

	}
	GameObject(const GameObject &game)
	{
	
		_objectType = game._objectType;
		_translate = game._translate;
		 _angle = game._angle;
		_rotation = game._rotation;
		_scale = game._scale;
		col = game.col;
	}
};