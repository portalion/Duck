#include "App.h"
#include <iostream>
#include "engine/ShaderBuilder.h"
#include "Square.h"
#include <glm/gtc/matrix_transform.hpp>

App::App()
{
    const float width = 800.f;
    const float height = 600.f;

    if (!glfwInit())
    {
        isRunning = false;
        return;
    }

    window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
		isRunning = false;
        return;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Cannot initiate glew" << std::endl;
        isRunning = false;
        return;
    }

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    constexpr float fov = glm::radians(45.0f); 
    const float aspectRatio = width / height;     
    const float nearPlane = 0.1f;
    const float farPlane = 100.0f;

	projectionMatrix = glm::perspective(fov, aspectRatio, nearPlane, farPlane);
}

App::~App()
{
    glfwTerminate();
}


void App::Render()
{
}

void App::Update()
{
}

void App::HandleInput()
{
}

void App::Run()
{
    ShaderBuilder builder("resources/shaders/");
    auto defaultShader = builder.AddShader(ShaderType::Vertex, "default")
        .AddShader(ShaderType::Fragment, "default").Build();
	defaultShader.Bind();
	defaultShader.SetUniformMat4f("u_projectionMatrix", projectionMatrix);
	defaultShader.SetUniformMat4f("u_viewMatrix", camera.GetViewMatrix());
	Square square;
	square.Generate();

    while (!glfwWindowShouldClose(window) && isRunning)
    {
        glClear(GL_COLOR_BUFFER_BIT);

		HandleInput();
		Update();
        Render();
        square.Render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
