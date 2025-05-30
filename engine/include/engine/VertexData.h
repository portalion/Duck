#pragma once
#include "glm/glm.hpp"
#include "utils/GlCall.h"

struct PositionVertexData
{
	glm::vec4 Position;
};

struct PositionNormalVertexData
{
	glm::vec4 Position;
	glm::vec3 Normal;
};

struct PositionColorVertexData
{
	glm::vec4 Position;
	glm::vec4 Color;
};

struct PositionNormalTextureVertexData
{
	glm::vec4 Position;
	glm::vec3 Normal;
	glm::vec2 TextureCoords;
};

struct PositionNormalCubeTextureVertexData
{
	glm::vec4 Position;
	glm::vec3 Normal;
	glm::vec3 TextureCoords;
};

struct PositionTextureVertexData
{
	glm::vec4 Position;
	glm::vec2 TextureCoords;
};