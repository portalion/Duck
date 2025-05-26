#pragma once
#include "Cube.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "engine/Renderable.h"
#include "Camera.h"
#include "engine/Shader.h"
#include <memory>
#include "Square.h"
#include "Duck.h"

class App
{
private:
	GLFWwindow* window;
	bool isRunning = true;

	glm::mat4 projectionMatrix;
	Camera camera;
	std::unique_ptr<Shader> cubeShader;
	std::unique_ptr<Shader> waterShader;
	std::unique_ptr<Shader> duckShader;

	std::unique_ptr<Cube> cube;
	std::shared_ptr<Square> square;
	std::unique_ptr<Duck> duck;

	bool InitializeContext(float width, float height);
public:
	App();
	~App();

	void Render();
	void Update();
	void HandleInput();
	void Run();
};

