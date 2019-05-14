#include "Geometry.h"
#include "ErrorManagement.h"
#include <iostream>
#include <fstream>

using namespace std;


/*
* Constructor 
*/
Geometry::Geometry(){

	for (int i = 0;i < NUMBASICOBJECTS;i++)
	{
		_verticesData.push_back(NULL);
		
	}
	
	
	createGeometryVertex(BLUE_CUBE);
	createGeometryVertex(RED_CUBE);
	createGeometryVertex(WHITE_CUBE);
	createGeometryVertex(PURPLE_PYRAMID);
	createGeometryVertex(mainCharacter);
	createGeometryVertex(ENEMY);
	
	
}


Geometry::~Geometry(){
	restart();
}

/*
* Load the game elements from a text file
*/
void Geometry::loadGameElements(char fileName[100]){	
	/* Text format
	<number of game elements>
	<type of game element> <vec3 position> <angle> <vec3 rotation> <vec3 scale>	
	*/
	int numGameElements;
	GameObject tempObject;

	glm::vec3 vector3fElements;
	ifstream file;
	file.open(fileName,std::ios::in);
	if (file.is_open())
	{
	file >> numGameElements;
	
	std::cout << "Reading" << numGameElements << "Objects...";
	for (int i = 0; i < numGameElements;i++)
	{		
		
			
			//TODO: Read the content and add it into the data structure
			//Object Type
			 file >> tempObject._objectType ;
			//Get Position;
			 file >> tempObject._translate.x;
			 file >> tempObject._translate.y;
			 file >> tempObject._translate.z;
			 //Get angle transform
			 file >> tempObject._angle;
			 //get Translate transform
			 file >> tempObject._rotation.x;
			 file >> tempObject._rotation.y;
			 file >> tempObject._rotation.z;
			//get Scale transform
			 file >> tempObject._scale.x;
			 file >> tempObject._scale.y;
			 file >> tempObject._scale.z;
			 tempObject._textureFIle = "../06.02 - Game Engine Release 2/resources/textures/galaxy2.jpg";
			 tempObject._textureRepetion = true;
			 tempObject.col = Collider(tempObject._translate - tempObject._scale, tempObject._translate);
			
			 _listOfObjects.push_back(tempObject);
			 
		}
		file.close();
	}
	else{
		string message = "The file "+ string(fileName)+" doesn't exists";
		ErrorManagement::errorRunTime(message);
	}
	

}

void Geometry::createGeometryVertex(int objectType)
{
	switch (objectType)
	{

	case mainCharacter:
		_loadObject.loadAse("../06.02 - Game Engine Release 2/models/GeraltOfRivia.ASE", _numVertices, _verticesData);
	
		break;
	case ENEMY:
		_loadObject.loadAse("../06.02 - Game Engine Release 2/models/GeraltOfRivia.ASE", _numVertices, _verticesData);
		break;
		
 	case PURPLE_PYRAMID:
	
	
		_numVertices.push_back(PYRAMID_EDGES); // = PYRAMID_EDGES;
		_verticesData[_numVertices.size() - 1] = new Vertex[_numVertices[_numVertices.size() - 1]];//_numVertices[objectType]];
			
			//BOTTOM RECTANGLE.
			_verticesData[_numVertices.size() - 1][0].setPosition(MIN, MIN, MIN);
			_verticesData[_numVertices.size() - 1][1].setPosition(MAX, MIN, MIN);
			_verticesData[_numVertices.size() - 1][2].setPosition(MAX, MIN, MAX);

			_verticesData[_numVertices.size() - 1][0].setUVs(0, 0);
			_verticesData[_numVertices.size() - 1][1].setUVs(1, 0);
			_verticesData[_numVertices.size() - 1][2].setUVs(1, 1);

			_verticesData[_numVertices.size() - 1][0].setNormalVector(0, 0, -1);
			_verticesData[_numVertices.size() - 1][1].setNormalVector(0, 0, -1);
			_verticesData[_numVertices.size() - 1][2].setNormalVector(0, 0, -1);

			_verticesData[_numVertices.size() - 1][3].setPosition(MAX, MIN, MAX);
			_verticesData[_numVertices.size() - 1][4].setPosition(MIN, MIN, MAX);
			_verticesData[_numVertices.size() - 1][5].setPosition(MIN, MIN, MIN);

			_verticesData[_numVertices.size() - 1][3].setUVs(1, 1);
			_verticesData[_numVertices.size() - 1][4].setUVs(0, 1);
			_verticesData[_numVertices.size() - 1][5].setUVs(0, 0);

			_verticesData[_numVertices.size() - 1][3].setNormalVector(0, 0, -1);
			_verticesData[_numVertices.size() - 1][4].setNormalVector(0, 0, -1);
			_verticesData[_numVertices.size() - 1][5].setNormalVector(0, 0, -1);
			
			//LEFT
			_verticesData[_numVertices.size() - 1][6].setPosition(MIN, MIN, MIN);
			_verticesData[_numVertices.size() - 1][7].setPosition(MAX/2, MAX, MAX/2);
			_verticesData[_numVertices.size() - 1][8].setPosition(MIN, MIN, MAX);

			_verticesData[_numVertices.size() - 1][6].setUVs(0, 0);
			_verticesData[_numVertices.size() - 1][7].setUVs(0.5f, 0.5f);
			_verticesData[_numVertices.size() - 1][8].setUVs(0, 1);

			_verticesData[_numVertices.size() - 1][6].setNormalVector(-1, 0, 0);
			_verticesData[_numVertices.size() - 1][7].setNormalVector(-1, 0, 0);
			_verticesData[_numVertices.size() - 1][8].setNormalVector(-1, 0, 0);
			//RIGHT
			_verticesData[_numVertices.size() - 1][9].setPosition(MAX, MIN, MIN);
			_verticesData[_numVertices.size() - 1][10].setPosition(MAX / 2, MAX, MAX / 2);
			_verticesData[_numVertices.size() - 1][11].setPosition(MAX, MIN, MAX);

			_verticesData[_numVertices.size() - 1][9].setUVs(1, 0);
			_verticesData[_numVertices.size() - 1][10].setUVs(0.5f, 0.5f);
			_verticesData[_numVertices.size() - 1][11].setUVs(1, 1);

			_verticesData[_numVertices.size() - 1][9].setNormalVector(1, 0, 0);
			_verticesData[_numVertices.size() - 1][10].setNormalVector(1, 0, 0);
			_verticesData[_numVertices.size() - 1][11].setNormalVector(1, 0, 0);

			//FRONT
			_verticesData[_numVertices.size() - 1][12].setPosition(MIN, MIN, MIN);
			_verticesData[_numVertices.size() - 1][13].setPosition(MAX / 2, MAX, MAX / 2);
			_verticesData[_numVertices.size() - 1][14].setPosition(MAX, MIN, MIN);

			_verticesData[_numVertices.size() - 1][12].setUVs(0, 0);
			_verticesData[_numVertices.size() - 1][13].setUVs(0.5f, 0.5f);
			_verticesData[_numVertices.size() - 1][14].setUVs(1, 0);

			_verticesData[_numVertices.size() - 1][9].setNormalVector(0, 1, 0);
			_verticesData[_numVertices.size() - 1][10].setNormalVector(0, 1, 0);
			_verticesData[_numVertices.size() - 1][11].setNormalVector(0, 1, 0);

			
			//BACK
			_verticesData[_numVertices.size() - 1][15].setPosition(MIN, MIN, MAX);
			_verticesData[_numVertices.size() - 1][16].setPosition(MAX / 2, MAX, MAX / 2);
			_verticesData[_numVertices.size() - 1][17].setPosition(MAX, MIN, MAX);

			_verticesData[_numVertices.size() - 1][15].setUVs(0, 1);
			_verticesData[_numVertices.size() - 1][16].setUVs(0.5f, 0.5f);
			_verticesData[_numVertices.size() - 1][17].setUVs(1, 1);

			_verticesData[_numVertices.size() - 1][9].setNormalVector(0, -1, 0);
			_verticesData[_numVertices.size() - 1][10].setNormalVector(0, -1, 0);
			_verticesData[_numVertices.size() - 1][11].setNormalVector(0, -1, 0);
			

			break;
		
	
	default:
		_numVertices.push_back(CUBE_EDGES);// = CUBE_EDGES;
		_verticesData[_numVertices.size() - 1] = new Vertex[_numVertices[_numVertices.size() -1]];//[objectType]];
	


		//FRONT FACE
		
		_verticesData[_numVertices.size() - 1][0].setPosition(MIN, MIN, MIN);
		_verticesData[_numVertices.size() - 1][1].setPosition(MAX, MIN, MIN);
		_verticesData[_numVertices.size() - 1][2].setPosition(MIN, MAX, MIN);

		_verticesData[_numVertices.size() - 1][3].setPosition(MIN, MAX, MIN);
		_verticesData[_numVertices.size() - 1][4].setPosition(MAX, MAX, MIN);
		_verticesData[_numVertices.size() - 1][5].setPosition(MAX, MIN, MIN);


		_verticesData[_numVertices.size() - 1][0].setUVs(0, 0);
		_verticesData[_numVertices.size() - 1][1].setUVs(1, 0);
		_verticesData[_numVertices.size() - 1][2].setUVs(0, 1);

		_verticesData[_numVertices.size() - 1][3].setUVs(0, 1);
		_verticesData[_numVertices.size() - 1][4].setUVs(1, 1);
		_verticesData[_numVertices.size() - 1][5].setUVs(1, 0);

		_verticesData[_numVertices.size() - 1][0].setNormalVector(0, 1, 0);
		_verticesData[_numVertices.size() - 1][1].setNormalVector(0, 1, 0);
		_verticesData[_numVertices.size() - 1][2].setNormalVector(0, 1, 0);

		_verticesData[_numVertices.size() - 1][3].setNormalVector(0, 1, 0);
		_verticesData[_numVertices.size() - 1][4].setNormalVector(0, 1, 0);
		_verticesData[_numVertices.size() - 1][5].setNormalVector(0, 1, 0);

		//RIGHT FACE
		_verticesData[_numVertices.size() - 1][6].setPosition(MAX, MIN, MIN);
		_verticesData[_numVertices.size() - 1][7].setPosition(MAX, MAX, MIN);
		_verticesData[_numVertices.size() - 1][8].setPosition(MAX, MIN, MAX);

		_verticesData[_numVertices.size() - 1][9].setPosition(MAX, MAX, MIN);
		_verticesData[_numVertices.size() - 1][10].setPosition(MAX, MAX, MAX);
		_verticesData[_numVertices.size() - 1][11].setPosition(MAX, MIN, MAX);

		_verticesData[_numVertices.size() - 1][6].setUVs(0, 0);
		_verticesData[_numVertices.size() - 1][7].setUVs(1, 0);
		_verticesData[_numVertices.size() - 1][8].setUVs(0, 1);

		_verticesData[_numVertices.size() - 1][9].setUVs(1, 0);
		_verticesData[_numVertices.size() - 1][10].setUVs(1, 1);
		_verticesData[_numVertices.size() - 1][11].setUVs(0, 1);

		_verticesData[_numVertices.size() - 1][6].setNormalVector(1, 0, 0);
		_verticesData[_numVertices.size() - 1][7].setNormalVector(1, 0, 0);
		_verticesData[_numVertices.size() - 1][8].setNormalVector(1, 0, 0);

		_verticesData[_numVertices.size() - 1][9].setNormalVector(1, 0, 0);
		_verticesData[_numVertices.size() - 1][10].setNormalVector(1, 0, 0);
		_verticesData[_numVertices.size() - 1][11].setNormalVector(1, 0, 0);

		//LEFT FACE
		_verticesData[_numVertices.size() - 1][12].setPosition(MIN, MIN, MIN);
		_verticesData[_numVertices.size() - 1][13].setPosition(MIN, MAX, MIN);
		_verticesData[_numVertices.size() - 1][14].setPosition(MIN, MIN, MAX);

		_verticesData[_numVertices.size() - 1][15].setPosition(MIN, MAX, MIN);
		_verticesData[_numVertices.size() - 1][16].setPosition(MIN, MAX, MAX);
		_verticesData[_numVertices.size() - 1][17].setPosition(MIN, MIN, MAX);

		_verticesData[_numVertices.size() - 1][12].setUVs(0, 0);
		_verticesData[_numVertices.size() - 1][13].setUVs(1, 0);
		_verticesData[_numVertices.size() - 1][14].setUVs(0, 1);

		_verticesData[_numVertices.size() - 1][15].setUVs(1, 0);
		_verticesData[_numVertices.size() - 1][16].setUVs(1, 1);
		_verticesData[_numVertices.size() - 1][17].setUVs(0, 1);

		_verticesData[_numVertices.size() - 1][12].setNormalVector(-1, 0, 0);
		_verticesData[_numVertices.size() - 1][13].setNormalVector(-1, 0, 0);
		_verticesData[_numVertices.size() - 1][14].setNormalVector(-1, 0, 0);

		_verticesData[_numVertices.size() - 1][15].setNormalVector(-1, 0, 0);
		_verticesData[_numVertices.size() - 1][16].setNormalVector(-1, 0, 0);
		_verticesData[_numVertices.size() - 1][17].setNormalVector(-1, 0, 0);


		//BACK FACE	 

		_verticesData[_numVertices.size() - 1][18].setPosition(MIN, MIN, MAX);
		_verticesData[_numVertices.size() - 1][19].setPosition(MAX, MIN, MAX);
		_verticesData[_numVertices.size() - 1][20].setPosition(MIN, MAX, MAX);

		_verticesData[_numVertices.size() - 1][21].setPosition(MIN, MAX, MAX);
		_verticesData[_numVertices.size() - 1][22].setPosition(MAX, MAX, MAX);
		_verticesData[_numVertices.size() - 1][23].setPosition(MAX, MIN, MAX);


		_verticesData[_numVertices.size() - 1][18].setUVs(0, 0);
		_verticesData[_numVertices.size() - 1][19].setUVs(1, 0);
		_verticesData[_numVertices.size() - 1][20].setUVs(0, 1);

		_verticesData[_numVertices.size() - 1][21].setUVs(0, 1);
		_verticesData[_numVertices.size() - 1][22].setUVs(1, 1);
		_verticesData[_numVertices.size() - 1][23].setUVs(1, 0);

		_verticesData[_numVertices.size() - 1][18].setNormalVector(0, -1, 0);
		_verticesData[_numVertices.size() - 1][19].setNormalVector(0, -1, 0);
		_verticesData[_numVertices.size() - 1][20].setNormalVector(0, -1, 0);

		_verticesData[_numVertices.size() - 1][21].setNormalVector(0, -1, 0);
		_verticesData[_numVertices.size() - 1][22].setNormalVector(0, -1, 0);
		_verticesData[_numVertices.size() - 1][23].setNormalVector(0, -1, 0);

		//BOTTOM FACE
		_verticesData[_numVertices.size() - 1][24].setPosition(MIN, MIN, MIN);
		_verticesData[_numVertices.size() - 1][25].setPosition(MAX, MIN, MIN);
		_verticesData[_numVertices.size() - 1][26].setPosition(MAX, MIN, MAX);

		_verticesData[_numVertices.size() - 1][27].setPosition(MAX, MIN, MAX);
		_verticesData[_numVertices.size() - 1][28].setPosition(MIN, MIN, MAX);
		_verticesData[_numVertices.size() - 1][29].setPosition(MIN, MIN, MIN);

		_verticesData[_numVertices.size() - 1][24].setUVs(0, 0);
		_verticesData[_numVertices.size() - 1][25].setUVs(1, 0);
		_verticesData[_numVertices.size() - 1][26].setUVs(1, 1);

		_verticesData[_numVertices.size() - 1][27].setUVs(1, 1);
		_verticesData[_numVertices.size() - 1][28].setUVs(0, 1);
		_verticesData[_numVertices.size() - 1][29].setUVs(0, 0);

		_verticesData[_numVertices.size() - 1][24].setNormalVector(0, 0, -1);
		_verticesData[_numVertices.size() - 1][25].setNormalVector(0, 0, -1);
		_verticesData[_numVertices.size() - 1][26].setNormalVector(0, 0, -1);

		_verticesData[_numVertices.size() - 1][27].setNormalVector(0, 0, -1);
		_verticesData[_numVertices.size() - 1][28].setNormalVector(0, 0, -1);
		_verticesData[_numVertices.size() - 1][29].setNormalVector(0, 0, -1);

		//TOP FACE
		_verticesData[_numVertices.size() - 1][32].setPosition(MIN, MAX, MIN);
		_verticesData[_numVertices.size() - 1][31].setPosition(MAX, MAX, MIN);
		_verticesData[_numVertices.size() - 1][30].setPosition(MAX, MAX, MAX);

		_verticesData[_numVertices.size() - 1][35].setPosition(MAX, MAX, MAX);
		_verticesData[_numVertices.size() - 1][34].setPosition(MIN, MAX, MAX);
		_verticesData[_numVertices.size() - 1][33].setPosition(MIN, MAX, MIN);

		_verticesData[_numVertices.size() - 1][24].setUVs(0, 0);
		_verticesData[_numVertices.size() - 1][25].setUVs(1, 0);
		_verticesData[_numVertices.size() - 1][26].setUVs(1, 1);

		_verticesData[_numVertices.size() - 1][27].setUVs(1, 1);
		_verticesData[_numVertices.size() - 1][28].setUVs(0, 1);
		_verticesData[_numVertices.size() - 1][29].setUVs(0, 0);

		_verticesData[_numVertices.size() - 1][24].setNormalVector(0, 0, 1);
		_verticesData[_numVertices.size() - 1][25].setNormalVector(0, 0, 1);
		_verticesData[_numVertices.size() - 1][26].setNormalVector(0, 0, 1);

		_verticesData[_numVertices.size() - 1][27].setNormalVector(0, 0, 1);
		_verticesData[_numVertices.size() - 1][28].setNormalVector(0, 0, 1);
		_verticesData[_numVertices.size() - 1][29].setNormalVector(0, 0, 1);

		break;

	}
	
	for (int j = 0; j < _numVertices[_numVertices.size() - 1];j++)
	{
		
		switch (objectType)
		{
		case BLUE_CUBE:
			_verticesData[_numVertices.size() - 1][j].setColor(0, 0, 255, 255);
			break;
		case RED_CUBE:
			_verticesData[_numVertices.size() - 1][j].setColor(255, 0, 0, 255);
			break;
		case WHITE_CUBE:
			_verticesData[_numVertices.size() - 1][j].setColor(255, 255, 255, 255);
			break;
		case PURPLE_PYRAMID:
			_verticesData[_numVertices.size() - 1][j].setColor(rand()%255, rand()%255, rand()%255, 255);
			break;

		case mainCharacter:
			_verticesData[_numVertices.size() - 1][j].setColor(0,  255, 0, 255);
			break;
		

		}
	


	}
}

void Geometry::pushObject(GameObject & object)
{
	_listOfObjects.push_back(object);
}
void Geometry::eraseObject(int ID)
{
	_listOfObjects.erase(_listOfObjects.begin() + ID);
}
void Geometry::restart()
{
	for (int i = _listOfObjects.size() - 1;i >= 0;i--)
	{
		_listOfObjects.erase(_listOfObjects.begin() + i);
	}
}
void Geometry::loadGameScene()
{
	//_listOfObjects.resize(1);
	GameObject tempObject;
	//MENU
	tempObject._objectType = 2;
	tempObject._translate = glm::vec3(-45.9f, 0.0f, 0.0f);
	tempObject._angle = 0.0f;
	tempObject._rotation = glm::vec3(1.0f, 0.0f, 0.0f);
	tempObject._scale = glm::vec3(1.0f, 1.0f, 1.0f);
	tempObject._textureFIle = "../06.02 - Game Engine Release 2/resources/textures/Nilo's ADVENTURE.jpg";
	tempObject._textureID = _textureManager.getTextureID(tempObject._textureFIle);
	tempObject._textureRepetion = false;
	tempObject.col = Collider(tempObject._translate - tempObject._scale, tempObject._translate);
	_listOfObjects.push_back(tempObject);

	_listOfObjects[_listOfObjects.size() - 1]._textureFIle = "../06.02 - Game Engine Release 2/resources/textures/Nilo's ADVENTURE.jpg";
	_listOfObjects[_listOfObjects.size() - 1]._textureID = _textureManager.getTextureID(_listOfObjects[_listOfObjects.size() - 1]._textureFIle);

	//Sky
	tempObject._objectType = 2;
	tempObject._translate = glm::vec3(0.0f, 0.0f, 0.0f);
	tempObject._angle = 0.0f;
	tempObject._rotation = glm::vec3(0.0f, 0.0f, 1.0f);
	tempObject._scale = glm::vec3(1.0f, 100.0f, 100.0f);
	tempObject._textureFIle = "../06.02 - Game Engine Release 2/resources/textures/galaxy2.jpg";
	tempObject._textureID = _textureManager.getTextureID(tempObject._textureFIle);
	tempObject._textureRepetion = false;
	tempObject.col = Collider(tempObject._translate - tempObject._scale, tempObject._translate);
	_listOfObjects.push_back(tempObject);

	//ScoreObject
	tempObject._objectType = 2;
	tempObject._translate = glm::vec3(0.7f, 0.55f, 0.0f);
	tempObject._angle = 0.0f;
	tempObject._rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	tempObject._scale = glm::vec3(0.1f, 0.1f, 0.0f);
	//	tempObject._textureFIle = ;
	tempObject._textureRepetion = false;
	//tempObject.col = Collider(tempObject._translate - tempObject._scale, tempObject._translate);
	_listOfObjects.push_back(tempObject);
	
	//WINObject
	tempObject._objectType = 2;
	tempObject._translate = glm::vec3(0.0f, 0.0f, 0.0f);
	tempObject._angle = 0.0f;
	tempObject._rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	tempObject._scale = glm::vec3(0.4f, 0.1f, 0.0f);
	//	tempObject._textureFIle = ;
	tempObject._textureRepetion = false;
	//tempObject.col = Collider(tempObject._translate - tempObject._scale, tempObject._translate);
	_listOfObjects.push_back(tempObject);

	//LoseObject
	tempObject._objectType = 2;
	tempObject._translate = glm::vec3(0.0f, 0.0f, 0.0f);
	tempObject._angle = 0.0f;
	tempObject._rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	tempObject._scale = glm::vec3(0.4f, 0.1f, 0.0f);
	//	tempObject._textureFIle = ;
	tempObject._textureRepetion = false;
	//tempObject.col = Collider(tempObject._translate - tempObject._scale, tempObject._translate);
	_listOfObjects.push_back(tempObject);

	//restartObject
	tempObject._objectType = 1;
	tempObject._translate = glm::vec3(0.0f, 0.25f, 0.0f);
	tempObject._angle = 0.0f;
	tempObject._rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	tempObject._scale = glm::vec3(0.4f, 0.1f, 0.0f);
	//	tempObject._textureFIle = ;
	tempObject._textureRepetion = false;
	//tempObject.col = Collider(tempObject._translate - tempObject._scale, tempObject._translate);
	_listOfObjects.push_back(tempObject);

	//MainCharacter
	tempObject._objectType = 4;
	tempObject._translate = glm::vec3(-46.0f, 0.0f, -0.5f);
	tempObject._angle = 0.0f;
	tempObject._rotation = glm::vec3(0.0f, 1.0f, 0.0f);
	tempObject._scale = glm::vec3(0.01f, 0.01f, 0.01f);
	tempObject._textureFIle = "../06.02 - Game Engine Release 2/resources/textures/galaxy2.jpg";
	tempObject._textureID = _textureManager.getTextureID(tempObject._textureFIle);
	tempObject._textureRepetion = true;
	tempObject.col = Collider(tempObject._translate - tempObject._scale, tempObject._translate);
	_listOfObjects.push_back(tempObject);

	//Second Element
	tempObject._objectType = 2;
	tempObject._translate = glm::vec3(-1.0f, 0.0f, -1.0f);
	tempObject._angle = 0.0f;
	tempObject._rotation = glm::vec3(0.0f, 1.0f, 0.0f);
	tempObject._scale = glm::vec3(46.0f, 3.0f, 0.1f);
	tempObject._textureFIle = "../06.02 - Game Engine Release 2/resources/textures/galaxy2.jpg";
	tempObject._textureID = _textureManager.getTextureID(tempObject._textureFIle);
	tempObject.col = Collider(tempObject._translate - tempObject._scale, tempObject._translate);
	_listOfObjects.push_back(tempObject);


	//Fourth Element
	tempObject._objectType = ENEMY;
	tempObject._translate = glm::vec3(-20.0f, 1.0f, -0.5f);
	tempObject._angle = 0.0f;
	tempObject._rotation = glm::vec3(0.0f, 1.0f, 0.0f);
	tempObject._scale = glm::vec3(0.1f, 0.1f, 0.5f);
	tempObject._textureFIle = "../06.02 - Game Engine Release 2/resources/textures/galaxy2.jpg";
	tempObject._textureID = _textureManager.getTextureID(tempObject._textureFIle);
	tempObject.col = Collider(tempObject._translate - tempObject._scale, tempObject._translate);
	_listOfObjects.push_back(tempObject);
	/*_listOfObjects[_listOfObjects.size() - 1]._textureFIle = "../06.02 - Game Engine Release 2/resources/textures/galaxy2.jpg";
	_listOfObjects[_listOfObjects.size() - 1]._textureID = _textureManager.getTextureID(tempObject._textureFIle);*/




	_spawner = Spawner(_listOfObjects[PLAYER + 1]._translate - _listOfObjects[PLAYER + 1]._scale, _listOfObjects[PLAYER + 1]._translate + _listOfObjects[PLAYER + 1]._scale);
}

void Geometry::spawn()
{
	int score = 0;
	if (_spawner.trySpawn(score))
	{
		GameObject _object;
		std::random_device rd;
		std::mt19937 eng(rd());
		std::uniform_real_distribution<> coordX(_spawner.getMin().x, _spawner.getMax().x);
		std::uniform_real_distribution<> coordY(_spawner.getMin().y, _spawner.getMax().y);
		std::uniform_real_distribution<> coordZ(_spawner.getMin().z, _spawner.getMax().z);

		glm::vec3 coord(coordX(eng), coordY(eng), coordZ(eng) + 0.5f);
		_object._objectType = ENEMY;
		_object._angle = 0;
		_object._rotation = glm::vec3(0, 0, 1);
		_object._scale = glm::vec3(0.1f, 0.1f, 0.5f);
		_object._translate = coord;
		_object.col = Collider(_object._translate - _object._scale, _object._translate);
		_object._textureRepetion = true;
		_object._textureFIle = "../06.02 - Game Engine Release 2/resources/textures/galaxy2.jpg";
		_object._textureID = _textureManager.getTextureID(_object._textureFIle);
		_listOfObjects.push_back(_object);
		_listOfObjects[_listOfObjects.size() - 1]._textureFIle = "../06.02 - Game Engine Release 2/resources/textures/galaxy2.jpg";
		_listOfObjects[_listOfObjects.size() - 1]._textureID = _textureManager.getTextureID(_object._textureFIle);
	}

}

Spawner & Geometry::getSpawner()
{
	return _spawner;
	// TODO: insert return statement here
}
TextureManager & Geometry::getTextureManager()
{
	// TODO: insert return statement here
	return _textureManager;
}
/*
* Get the vertices data for an specific object
* @param objectID is the identifier of the requested object
* @return Vertex * is an array with all the vertices data
*/
Vertex * Geometry::getData(int objectID){
	return _verticesData[objectID];
}

/*
* Get the number of vertices for an specific object
* @param objectID is the identifier of the requested object
* @return int is the number of vertices
*/

int Geometry::getNumVertices(int objectID){
	return _numVertices[objectID];
}

/*
* Get the number of elements to render
*/
int Geometry::getNumGameElements() {
	return _listOfObjects.size();
}

/*
* Get the number of vertices of an specific game element
* @param objectID is the identifier of the requested object
*/
GameObject & Geometry::getGameElement(int objectID) {

	return (_listOfObjects[objectID]);
}



