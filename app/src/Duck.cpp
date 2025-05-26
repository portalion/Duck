#include "Duck.h"
#include <fstream>
#include <iostream>
#include "glm/gtc/matrix_transform.hpp"
#include "Texture.h"

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

glm::mat4 Duck::GetModelMatrix() const
{
	const float SCALE = 1.f / 1000.f; // Scale factor to fit the duck model
	return glm::scale(glm::mat4(1.0), glm::vec3(SCALE, SCALE, SCALE));
}

void Duck::Render() const
{
	glBindTexture(GL_TEXTURE_2D, textureID);
	Renderable::Render();
}
