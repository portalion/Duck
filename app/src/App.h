#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "engine/Renderable.h"
#include "Camera.h"

class App
{
private:
	GLFWwindow* window;
	bool isRunning = true;

	glm::mat4 projectionMatrix;
	Camera camera;

	bool InitializeContext(float width, float height);
public:
	App();
	~App();

	void Render();
	void Update();
	void HandleInput();
	void Run();
};

