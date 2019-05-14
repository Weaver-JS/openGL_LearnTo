#include "matManager.h"

void matManager::createMaterialDefinitions()
{
	_materialData[PEARL].ambient = glm::vec3(0.25f, 0.20725f, 0.20725f);
	_materialData[PEARL].diffuse = glm::vec3(0.07568f, 0.61424f, 0.07568f);
	_materialData[PEARL].specular = glm::vec3(0.296648f, 0.0296648f, 0.0296648f);
	_materialData[PEARL].shininess = 0.088f;

	_materialData[SILVER].ambient = glm::vec3(0.19225f, 0.19225f, 0.19225f);
	_materialData[SILVER].diffuse = glm::vec3(0.50754f, 0.50754f, 0.50754f);
	_materialData[SILVER].specular = glm::vec3(0.508273f, 0.508273f, 0.508273f);
	_materialData[SILVER].shininess = 0.4f;

	_materialData[WHITE_RUBBER].ambient = glm::vec3(0.05f, 0.05f, 0.05f);
	_materialData[WHITE_RUBBER].diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
	_materialData[WHITE_RUBBER].specular = glm::vec3(0.7f, 0.7f, 0.7f);
	_materialData[WHITE_RUBBER].shininess = 0.78125f;


	_materialData[CHROME].ambient = glm::vec3(0.25f, 0.25f, 0.25f);
	_materialData[CHROME].diffuse = glm::vec3(0.4f, 0.4f, 0.4f);
	_materialData[CHROME].specular = glm::vec3(0.774697f, 0.774697f, 0.774697f);
	_materialData[CHROME].shininess = 0.6f;

	_materialData[GOLD].ambient = glm::vec3(0.24725f, 0.1995f, 0.0225f);
	_materialData[GOLD].diffuse = glm::vec3(0.75164f, 0.60648f, 0.22648f);
	_materialData[GOLD].specular = glm::vec3(0.628281f, 0.555802f, 0.366065f);
	_materialData[GOLD].shininess = 0.4f;

	_materialData[LIGHT].ambient = glm::vec3(1.0f, 1.0f, 1.0f);
	_materialData[LIGHT].diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	_materialData[LIGHT].specular = glm::vec3(1.0f, 1.0f, 1.0f);
	_materialData[LIGHT].shininess = 0.0f;

	_materialType[PEARL] = "PEARL";
	_materialType[SILVER] = "SILVER";
	_materialType[WHITE_RUBBER] = "WHITE_RUBBER";
	_materialType[CHROME] = "CHROME";
	_materialType[GOLD] = "GOLD";
	_materialType[LIGHT] = "LIGHT";
}

matManager::matManager()
{
	createMaterialDefinitions();
}

material matManager::getMaterialComponents(int materialID)
{
	return _materialData[materialID];
}

int matManager::getMaterialID(std::string materialName)
{

	for (int i = 0; i < NUMMATERIALS;i++)
	{

		if (materialName == _materialType[i])
			return i;
	}

	return -1;
}



