#pragma once
#include "Vertex.h"
#include <vector>
#include "GameObject.h"
#include "Spawner.h"
#include "TextureManager.h"
#include "ObjectLoader.h"

#define BLUE_CUBE 0
#define RED_CUBE 1
#define WHITE_CUBE 2
#define PURPLE_PYRAMID 3
#define mainCharacter 4
#define ENEMY 5
#define NUMBASICOBJECTS 5
#define MAX 1
#define MIN -1
#define CUBE_EDGES 36
#define PYRAMID_EDGES 18
#define PLAYER 6


//This class stores and manipulates all the objects loaded from the text file
class Geometry
{
	ObjectLoader _loadObject;
	std::vector<Vertex*> _verticesData;
	std::vector<int> _numVertices;//[NUMBASICOBJECTS];
	std::vector <GameObject> _listOfObjects;
	Spawner _spawner;
	TextureManager _textureManager;

	

public:
	Geometry();
	~Geometry();
	void loadGameElements(char fileName[100]);
	void createGeometryVertex(int objectType );
	Vertex * getData(int objectID);
	int getNumVertices(int objectID);
	int getNumGameElements();
	GameObject & getGameElement(int objectID);
	void pushObject(GameObject & object);
	void eraseObject(int ID);
	void restart();
	void loadGameScene(); 
	

	void spawn();
	Spawner & getSpawner();

	TextureManager &getTextureManager();
};
