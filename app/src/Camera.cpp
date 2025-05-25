#include "Camera.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera()
{
	position = glm::vec3(0.0f, 0.0f, 5.0f);
	target = glm::vec3(0.0f, 0.0f, 0.0f);
	upVector = glm::vec3(0.0f, 1.0f, 0.0f);
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(position, target, upVector);
}
