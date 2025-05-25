#include "App.h"
#include <iostream>
#include "engine/ShaderBuilder.h"

App::App()
{
    if (!glfwInit())
        return;

    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Cannot initiate glew" << std::endl;
    }

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
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
    while (!glfwWindowShouldClose(window) && isRunning)
    {
        glClear(GL_COLOR_BUFFER_BIT);

		HandleInput();

		Update();

        Render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
