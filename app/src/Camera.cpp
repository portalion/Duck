#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

void Camera::HandleZoom(ImGuiMouseButton button)
{
	float deltaY = ImGui::GetMouseDragDelta(button).y;
	if (deltaY != 0.0f) {
		ImGui::ResetMouseDragDelta(button);

		float zoomFactor = deltaY < 0.0f ? 0.9f : 1.1f;
		radius *= zoomFactor;
		radius = glm::clamp(radius, minRadius, maxRadius);

		UpdatePosition();
	}
}

void Camera::HandleRotation(ImGuiMouseButton button)
{
	ImVec2 delta = ImGui::GetMouseDragDelta(button);
	ImGui::ResetMouseDragDelta(button);

	const float rotateSpeed = 0.005f;
	yaw -= delta.x * rotateSpeed;
	pitch -= delta.y * rotateSpeed;

	pitch = glm::clamp(pitch, -glm::half_pi<float>() + 0.01f, glm::half_pi<float>() - 0.01f);

	UpdatePosition();
}

void Camera::UpdatePosition()
{
	position.x = radius * cos(pitch) * sin(yaw);
	position.y = radius * sin(pitch);
	position.z = radius * cos(pitch) * cos(yaw);
}

Camera::Camera()
	: radius(10.0f), yaw(glm::radians(90.0f)), pitch(0.0f),
	minRadius(1.0f), maxRadius(100.0f)
{
	position = glm::vec3(0.0f, 0.0f, 5.0f);
	upVector = glm::vec3(0.0f, 1.0f, 0.0f);
	UpdatePosition();
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(position, glm::vec3(0.0f, 0.0f, 0.0f), upVector);
}

void Camera::HandleInput()
{
	if (ImGui::IsMouseDragging(ImGuiMouseButton_Right))
	{
		HandleZoom(ImGuiMouseButton_Right);
	}
	
	if (ImGui::IsMouseDragging(ImGuiMouseButton_Left))
	{
		HandleRotation(ImGuiMouseButton_Left);
	}

}
