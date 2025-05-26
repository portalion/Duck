#include "Duck.h"
#include <fstream>

RenderableMesh<PositionNormalTextureVertexData> Duck::GenerateMesh()
{
	std::ifstream file("resources/models/duck.txt");
	return RenderableMesh<PositionNormalTextureVertexData>();
}
