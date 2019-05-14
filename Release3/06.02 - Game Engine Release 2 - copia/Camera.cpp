#include "Camera.h"
#include <iostream>

Camera::Camera()
{
}

Camera::Camera(float aspectRatio, float FOV, float, float near, float projectionWidth, float projectionHeight, glm::vec3 & Position)
{
	_aspectRatio = aspectRatio;
	_FOV = FOV;
	_near = near;
	_projectionWidth = projectionWidth;
	_projectionHeight = projectionHeight;
	_cameraPos = Position;
	_projectionMatrix = glm::ortho(-_projectionWidth / 2, _projectionWidth / 2,
		-_projectionHeight / 2, _projectionHeight / 2, _near, _far); // Ortographic Projection Matrix
	//Perspective Projection
	_projectionMatrix = glm::perspective(_FOV, _aspectRatio, _near, _far);
	glm::vec3 cameraDirection = glm::normalize(_cameraPos -_cameraFront);
	glm::vec3 up = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
	_cameraUp = glm::cross(cameraDirection, cameraRight);
	_viewMatrix = glm::lookAt(_cameraPos, _cameraFront, _cameraUp);

	_velocity = 1.0f;
}

void Camera::setCamera(float aspectRatio, float FOV, float far, float near, float projectionWidth, float projectionHeight, glm::vec3 & Position)
{
	_aspectRatio = aspectRatio;
	_FOV = FOV;
	_far = far;
	_near = near;
	_projectionWidth = projectionWidth;
	_projectionHeight = projectionHeight;
	_cameraPos = Position;
	_cameraFront = glm::vec3(-1.0f, 0.0f, 0.0f);
	//_projectionMatrix = glm::ortho(-_projectionWidth / 2, _projectionWidth / 2,
		//-_projectionHeight / 2, _projectionHeight / 2, _near, _far); // Ortographic Projection Matrix
																	 //Perspective Projection
	//_projectionMatrix = glm::perspective(_FOV, _aspectRatio, _near, _far);
	
	glm::vec3 cameraDirection = glm::normalize(_cameraPos - _cameraFront);
	glm::vec3 up = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
	_cameraUp = glm::cross(cameraDirection, cameraRight);
	_viewMatrix = glm::lookAt(_cameraPos, _cameraFront, _cameraUp);
	_projectionMatrix = glm::perspective(_FOV, _aspectRatio, _near, _far);
	_velocity = 0.1f;
}

void Camera::setCameraPosition(glm::vec3 pos)
{
	_cameraPos += pos;
	//_cameraFront += pos;
	_cameraUp += pos;
	//glm::vec3 cameraDirection = glm::normalize(_cameraPos - _cameraFront);
	_viewMatrix = glm::lookAt(_cameraPos, _cameraFront, _cameraUp);

}

void Camera::rotateCamera(glm::vec3 angle)
{
	_cameraFront += angle;
	_cameraPos += angle;
	_viewMatrix = glm::lookAt(_cameraPos, _cameraFront, _cameraUp);
}

void Camera::changePoint(glm::vec3 & edgePoint)
{

}

void Camera::setPerspective()
{
	_projectionMatrix = glm::perspective(_FOV, _aspectRatio, _near, _far);
}

void Camera::setOrtographic()
{
	_projectionMatrix = glm::ortho(-_projectionWidth / 2, _projectionWidth / 2,
		-_projectionHeight / 2, _projectionHeight / 2, _near, _far); 
}

void Camera::goUp(float angle)
{
	//_cameraFront.z += angle;
	_cameraFront = glm::mat3(glm::vec3(cos(angle), 0.0f, sin(angle)), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(-sin(angle), 0.0f, cos(angle))) * _cameraFront ;
	

//	_cameraUp.z += angle;

	_viewMatrix = glm::lookAt(_cameraPos, _cameraFront, _cameraUp);
}

void Camera::goLeft(float angle)
{
	_cameraFront.x += angle ;
	
	//_cameraUp.y += angle;
	_viewMatrix = glm::lookAt(_cameraPos, _cameraFront, _cameraUp);
}

void Camera::goDown(float angle)
{
	_cameraFront.z += angle;
	//_cameraUp.z += angle;
	_viewMatrix = glm::lookAt(_cameraPos, _cameraFront, _cameraUp);
}

void Camera::setPosition(glm::vec3 & pos)
{
	_cameraPos = pos;
}


Camera::~Camera()
{
}

float Camera::getAspectRatio()
{
	return _aspectRatio;
}

glm::mat4 Camera::getProjectionMatrix()
{
	return _projectionMatrix;
}

glm::mat4 Camera::getViewMatrix()
{
	return _viewMatrix;
}

float Camera::getFOV()
{
	return _FOV;
}

float Camera::getFar()
{
	return _far;
}

float Camera::getNear()
{
	return _near;
}

float Camera::getProjectionWidth()
{
	return _projectionWidth;
}

float Camera::getProjectionHeight()
{
	return _projectionHeight;
}

glm::vec3 Camera::getCameraPos()
{
	return _cameraPos;
}

glm::vec3 Camera::getCameraFront()
{
	return _cameraFront;
}

glm::vec3 Camera::getCameraUp()
{
	return _cameraUp;
}

glm::vec3 Camera::getCameraDirection()
{
	return glm::normalize(_cameraPos - _cameraFront);
}

bool Camera::getPerspectiveChange()
{
	return perspectiveChange;
}

void Camera::moveForward()
{
	glm::vec3 cameraDirection = glm::normalize(_cameraPos - _cameraFront);
	_cameraPos += -_velocity * cameraDirection;


	
	

}

void Camera::moveBackward()
{
	glm::vec3 cameraDirection = glm::normalize(_cameraPos - _cameraFront);
	_cameraPos += _velocity * cameraDirection;
	
}

void Camera::strafeLeft()
{
	glm::vec3 cameraDirection = glm::normalize(_cameraPos - _cameraFront);
	glm::vec3 strafeDirection = glm::normalize( glm::cross(cameraDirection, _cameraUp));
	_cameraPos += -_velocity * strafeDirection;
	
}

void Camera::strafeRight()
{
	glm::vec3 cameraDirection = glm::normalize(_cameraPos - _cameraFront);
	glm::vec3 strafeDirection = glm::normalize(glm::cross(cameraDirection, _cameraUp));
	_cameraPos += _velocity * strafeDirection;
	
}

void Camera::moveUp()
{
	_cameraPos += _velocity * _cameraUp;
}

void Camera::moveDown()
{
	_cameraPos += -_velocity * _cameraUp;
}

void Camera::refresh()
{
	glm::vec3 cameraDirection = glm::normalize(_cameraPos - _cameraFront);
	_viewMatrix = glm::lookAt(_cameraPos, _cameraFront + cameraDirection, _cameraUp);
}
