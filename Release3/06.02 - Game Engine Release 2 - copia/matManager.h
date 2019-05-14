#pragma once
#include <glm/glm.hpp>			//OpenGL Mathematics 
#include <string>

#define PEARL 0
#define SILVER 1 
#define WHITE_RUBBER 2
#define CHROME 3
#define GOLD 4
#define LIGHT 5
#define NUMMATERIALS 6

struct material {
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
};

class matManager
{
	material _materialData[NUMMATERIALS];
	std::string _materialType[NUMMATERIALS];
	void createMaterialDefinitions();
public:
	matManager();
	~matManager() {};
	material getMaterialComponents(int materialID);
	int getMaterialID(std::string materialName);
};
