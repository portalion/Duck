#include "App.h"
#include <iostream>
#include "engine/ShaderBuilder.h"
#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

bool App::InitializeContext(float width, float height)
{
    if (!glfwInit())
    {
        return false;
    }

    window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return false;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Cannot initiate glew" << std::endl;
        return false;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    return true;
}

App::App()
{
    const float width = 800.f;
    const float height = 600.f;

	if (!InitializeContext(width, height))
	{
		std::cerr << "Failed to initialize application context." << std::endl; 
        isRunning = false;
		return;
	}

    glEnable(GL_CULL_FACE);

    constexpr float fov = glm::radians(45.0f); 
    const float aspectRatio = width / height;     
    const float nearPlane = 0.1f;
    const float farPlane = 200.0f;

	projectionMatrix = glm::perspective(fov, aspectRatio, nearPlane, farPlane);

    static const std::vector<std::string> faces
    {
        "resources\\textures\\cubeTextures\\posx.jpg",
        "resources\\textures\\cubeTextures\\negx.jpg",
        "resources\\textures\\cubeTextures\\posy.jpg",
        "resources\\textures\\cubeTextures\\negy.jpg",
        "resources\\textures\\cubeTextures\\posz.jpg",
        "resources\\textures\\cubeTextures\\negz.jpg",
    };
	cube = std::make_unique<Cube>(faces);
	square = std::make_unique<Square>();
    square->Generate();

    ShaderBuilder builder("resources/shaders/");
    ShaderBuilder builder2("resources/shaders/");
    cubeShader = builder.AddShader(ShaderType::Vertex, "cube")
        .AddShader(ShaderType::Fragment, "cube").BuildUnique();
	waterShader = builder2.AddShader(ShaderType::Vertex, "water")
		.AddShader(ShaderType::Fragment, "water").BuildUnique();
}

App::~App()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
}


void App::Render()
{
    cubeShader->Bind();
    cubeShader->SetUniformMat4f("u_projectionMatrix", projectionMatrix);
    cubeShader->SetUniformMat4f("u_viewMatrix", camera.GetViewMatrix());
    cubeShader->SetUniformVec1i("u_Texture", 0);
    cube->Render();

    waterShader->Bind();
    waterShader->SetUniformMat4f("u_projectionMatrix", projectionMatrix);
    waterShader->SetUniformMat4f("u_viewMatrix", camera.GetViewMatrix());
    //waterShader->SetUniformVec1i("u_Texture", 0);
    waterShader->SetUniformVec3f("viewPos", camera.GetPosition());
    square->Render();
}

void App::Update()
{
    square->Update();
}

void App::HandleInput()
{
    camera.HandleInput();
}

void App::Run()
{
	if (!isRunning)
	{
		return;
	}

    while (!glfwWindowShouldClose(window) && isRunning)
    {
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

		HandleInput();
		Update();
        Render();
		ImGui::ShowDemoWindow();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
