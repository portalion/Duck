#include "Duck.h"
#include <fstream>
#include <iostream>
#include "glm/gtc/matrix_transform.hpp"
#include "Texture.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

RenderableMesh<PositionNormalTextureVertexData> Duck::GenerateMesh()
{
	textureID = LoadTexture("resources/textures/ducktex.jpg");
	std::ifstream file("resources/models/duck.txt");
	RenderableMesh<PositionNormalTextureVertexData> mesh;

	int vCount;
	file >> vCount;
	for (int i = 0; i < vCount; i++)
	{
		PositionNormalTextureVertexData vertex;
		vertex.Position.w = 1.f;
		file >> vertex.Position.x >> vertex.Position.y >> vertex.Position.z;
		file >> vertex.Normal.x >> vertex.Normal.y >> vertex.Normal.z;
		file >> vertex.TextureCoords.x >> vertex.TextureCoords.y;
		mesh.vertices.push_back(vertex);
	}

	int tCount;
	file >> tCount;
	for (int i = 0; i < tCount * 3; i++)
	{
		unsigned int index;
		file >> index;
		mesh.indices.push_back(index);
	}

	return mesh;
}

Duck::Duck(std::shared_ptr<Square> water)
	:spline({ 0.0f, 0.0f, 0.0f },
		{ -0.5f, 0.0f, 0.0f },
		{ -0.5f, 0.0f, 0.5f },
		{ 0.0f, 0.0f, 0.5f },
		{ -0.95f, 0.0f, -0.95f },
		{ 0.95f, 0.0f, 0.95f }),
	water{water}
{
}

glm::mat4 Duck::GetModelMatrix() const
{
	glm::vec3 V = glm::normalize(viewDir);
	glm::vec3 D = glm::vec3(-1.0f, 0.0f, 0.0f);  // Default duck's view direction
	glm::vec3 DcrossV = glm::cross(D, V);
	float DdotV = glm::dot(D, V);
	float angle = glm::acos(DdotV);
	const float SCALE = 1.f / 1000.f; // Scale factor to fit the duck model

	glm::mat4 model =
		glm::translate(glm::mat4(1.0f), pos) *
		glm::rotate(glm::mat4(1.0f), angle, DcrossV) *
		glm::scale(glm::mat4(1.0f), glm::vec3(SCALE));

	return model;
}

void Duck::Render() const
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	Renderable::Render();
}

void Duck::Update()
{
	pos = spline.GetCurvePosition(time);
	viewDir = spline.GetCurveTangent(time);
	time += ImGui::GetIO().DeltaTime * 0.5f;
	if (time >= 1.0f) 
	{
		time = 0.0f;
		spline.GenerateSubsequentCurve();
	}

	water->BumpHeightMap(pos.z, pos.x);
}
