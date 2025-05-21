#pragma once
#include "glm/glm.hpp"
#include "utils/GlCall.h"

enum class VertexDataType
{
	PositionVertexData = 1,
	PositionColorVertexData = 2,
	PositionNormalVertexData = 3,
};

struct PositionVertexData
{
	glm::vec4 Position;
};

struct PositionNormalVertexData
{
	glm::vec4 Position;
	glm::vec4 Normal;
};

struct PositionColorVertexData
{
	glm::vec4 Position;
	glm::vec4 Color;
};