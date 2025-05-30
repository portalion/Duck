#include "Square.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "engine/utils/GlCall.h"
#include "random"

const float Square::h = 2.f / static_cast<float>(N - 1);
const float Square::minT = 1.f/ static_cast<float>(N - 1);

RenderableMesh<PositionTextureVertexData> Square::GenerateMesh()
{
	RenderableMesh<PositionTextureVertexData> mesh;
	mesh.vertices = {
		{ { -1.f,  0.f, -1.f, 1.0f }, { 0.0f, 0.0f } },
		{ {  1.f,  0.f, -1.f, 1.0f }, { 1.0f, 0.0f } },
		{ { -1.f,  0.f,  1.f, 1.0f }, { 0.0f, 1.0f } },
		{ {  1.f,  0.f,  1.f, 1.0f }, { 1.0f, 1.0f } }
	};
	mesh.indices =
	{
		0, 1, 2, 2, 1, 3,
		0, 2, 1, 2, 3, 1,
	};
	return mesh;
}

void Square::MakeRain()
{
	if (std::rand() % 10 < 6) return;

	int i = std::rand() % N;
	int j = std::rand() % N;

	heightMap[i][j] += 0.5f;
}

void Square::UpdateHeightMap()
{
	const float dt = std::min(ImGui::GetIO().DeltaTime, 1.f/ static_cast<float>(N));
	const float A = dt * dt / h / h;
	const float B = 2 - 4 * A;

	for (int i = 1; i < N - 1; i++)
	{
		for (int j = 1; j < N - 1; j++)
		{
			prevHeightMap[i][j] = A * (heightMap[i - 1][j] + heightMap[i + 1][j] +
				heightMap[i][j - 1] + heightMap[i][j + 1]) + B * heightMap[i][j] - prevHeightMap[i][j];
			prevHeightMap[i][j] *= d[i][j];
		}
	}

	std::swap(prevHeightMap, heightMap);
}

glm::vec3 Square::CalculateNormal(int x, int y)
{
	int x1 = std::max(x - 1, 0);
	int x2 = std::min(x + 1, N - 1);
	int y1 = std::max(y - 1, 0);
	int y2 = std::min(y + 1, N - 1);

	float hL = heightMap[y][x1];
	float hR = heightMap[y][x2];
	float hD = heightMap[y2][x];
	float hU = heightMap[y1][x];

	glm::vec3 dx = glm::vec3(2.0f, 0.0f, hR - hL);
	glm::vec3 dy = glm::vec3(0.0f, 2.0f, hD - hU);

	glm::vec3 normal = glm::normalize(glm::cross(dy, dx));
	return normal;
}

float getMaxDistanceToEdge(int i, int j, int N) {
	float x = float(i) / (N - 1) * 2.0f - 1.0f;
	float y = float(j) / (N - 1) * 2.0f - 1.0f;

	float left = x + 1.0f;
	float right = 1.0f - x;
	float bottom = y + 1.0f;
	float top = 1.0f - y;

	return std::max({ left, right, top, bottom });
}

Square::Square(unsigned int t)
	:cubeTextureID{ t }
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			heightMap[i][j] = 0;
			prevHeightMap[i][j] = 0;
			d[i][j] = 0.95f * std::min(1.f, getMaxDistanceToEdge(i, j, N) / 0.2f);
		}
	}

	GLCall(glGenTextures(1, &heightTextureID));
	GLCall(glBindTexture(GL_TEXTURE_2D, heightTextureID));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//GLCall(glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, N, N));
}

void Square::BumpHeightMap(float x, float y)
{
	int i, j;
	i = static_cast<int>((x + 1.f) / 2.f * N);
	j = static_cast<int>((y + 1.f) / 2.f * N);
	glm::clamp(i, 0, N - 1);
	glm::clamp(j, 0, N - 1);

	heightMap[i][j] += .25f;
}

void Square::Update()
{
	MakeRain();
	UpdateHeightMap();
	std::vector<unsigned char> normalData(N * N * 4);
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			glm::vec3 normal = CalculateNormal(i, j);
			glm::vec3 mapped = normal * 0.5f + 0.5f;
			int index = (j * N + i) * 4;

			normalData[index + 0] = static_cast<unsigned char>(mapped.x * 255.0f);
			normalData[index + 1] = static_cast<unsigned char>(mapped.y * 255.0f);
			normalData[index + 2] = static_cast<unsigned char>(mapped.z * 255.0f);
			normalData[index + 3] = 255; // alpha
		}
	}
	
	GLCall(glBindTexture(GL_TEXTURE_2D, heightTextureID));
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, N, N, 0, GL_RGBA, GL_UNSIGNED_BYTE, normalData.data()));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
}

void Square::Render() const
{
	glActiveTexture(GL_TEXTURE0);
	GLCall(glBindTexture(GL_TEXTURE_2D, heightTextureID));
	glActiveTexture(GL_TEXTURE1);
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, cubeTextureID));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	Renderable::Render();
}
