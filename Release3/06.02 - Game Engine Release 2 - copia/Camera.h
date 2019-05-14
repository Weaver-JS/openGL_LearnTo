#pragma once
#include <GL/glew.h>			//The OpenGL Extension Wrangler
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>			//OpenGL Mathematics 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Camera
{
private:
	float _velocity;
	float _aspectRatio; 
	glm::mat4 _projectionMatrix;//Matrix that is responsible of projection calculation
	glm::mat4 _viewMatrix; // Matrix that is responsible of viewing calculation, that consist in make the camera to be the main base.
	float _FOV; //Field of view
	float _far; // How far the camera can project.
	float _near; // How near the camera can project
	float _projectionWidth; //Width of the projection, is not the same as the width of the screen.
	float _projectionHeight; //Height of the projection, is not...
	glm::vec3 _cameraPos; //Camera position in the world.
	glm::vec3 _cameraFront; 
	glm::vec3 _cameraUp;

	
	bool perspectiveChange; //Bool that changes the perspective of the camera.
public:
	Camera();
	Camera(float aspectRatio, float FOV, float far, float near, float projectionWidth, float projectionHeight, glm::vec3 & Position);
	void setCamera(float aspectRatio, float FOV, float far, float near, float projectionWidth, float projectionHeight, glm::vec3 & Position);
	void setCameraPosition(glm::vec3 pos);
	void rotateCamera(glm::vec3 angle);
	void changePoint(glm::vec3 &edgePoint);
	void updateCamera(glm::vec3 _cameraPos, glm::vec3 & camFront, glm::vec3 &cameraUp);
	void setPerspective();
	void setOrtographic();
	void goUp(float angle);
	void goLeft(float angle);
	void goRight(float angle);
	void goDown(float angle);
	void setPosition(glm::vec3 & pos);
	float getAspectRatio();
	glm::mat4 getProjectionMatrix();
	glm::mat4 getViewMatrix();
	float getFOV();
	float getFar();
	float getNear();
	float getProjectionWidth();
	float getProjectionHeight();
	glm::vec3 getCameraPos();
	glm::vec3 getCameraFront();
	glm::vec3 getCameraUp();
	glm::vec3 getCameraDirection();

	bool getPerspectiveChange();


	//Movement Functions
	void moveForward();
	void moveBackward();
	void strafeLeft();
	void strafeRight();
	 void moveUp();
	void moveDown();
	void refresh();
	~Camera();
};

