#pragma once
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <glm/glm.hpp>

class Camera
{
private:
	glm::vec3 position;
	glm::vec3 upVector;

	float radius;
	float yaw;
	float pitch;

	const float minRadius = 1.f;
	const float maxRadius = 100.f;

	void HandleZoom(ImGuiMouseButton button);
	void HandleRotation(ImGuiMouseButton button);
	void UpdatePosition();
public:
	Camera();
	glm::mat4 GetViewMatrix();
	inline glm::vec3 GetPosition() const { return position; }
	void HandleInput();
};