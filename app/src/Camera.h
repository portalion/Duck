#pragma once
#include <glm/glm.hpp>

class Camera
{
private:
	glm::vec3 position;
	glm::vec3 target;
	glm::vec3 upVector;
public:
	Camera();
	glm::mat4 GetViewMatrix();

};