#pragma once
#include "VertexData.h"

template<typename T>
struct VertexAttribLayout;

template<>
struct VertexAttribLayout<PositionVertexData> {
	static void Enable() {
		GLCall(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(PositionVertexData),
			(void*)offsetof(PositionVertexData, Position)));
		GLCall(glEnableVertexAttribArray(0));
	}
};

template<>
struct VertexAttribLayout<PositionColorVertexData> {
	static void Enable() {
		GLCall(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(PositionColorVertexData),
			(void*)offsetof(PositionColorVertexData, Position)));
		GLCall(glEnableVertexAttribArray(0));
		GLCall(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(PositionColorVertexData),
			(void*)offsetof(PositionColorVertexData, Color)));
		GLCall(glEnableVertexAttribArray(1));
	}
};

template<>
struct VertexAttribLayout<PositionNormalVertexData> {
	static void Enable() {
		GLCall(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(PositionNormalVertexData),
			(void*)offsetof(PositionNormalVertexData, Position)));
		GLCall(glEnableVertexAttribArray(0));
		GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(PositionNormalVertexData),
			(void*)offsetof(PositionNormalVertexData, Normal)));
		GLCall(glEnableVertexAttribArray(1));
	}
};

template<>
struct VertexAttribLayout<PositionNormalTextureVertexData> {
	static void Enable() {
		GLCall(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(PositionNormalTextureVertexData),
			(void*)offsetof(PositionNormalTextureVertexData, Position)));
		GLCall(glEnableVertexAttribArray(0));
		GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(PositionNormalTextureVertexData),
			(void*)offsetof(PositionNormalTextureVertexData, Normal)));
		GLCall(glEnableVertexAttribArray(1)); 
		GLCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(PositionNormalTextureVertexData),
			(void*)offsetof(PositionNormalTextureVertexData, TextureCoords)));
		GLCall(glEnableVertexAttribArray(2));
	}
};

template<>
struct VertexAttribLayout<PositionNormalCubeTextureVertexData> {
	static void Enable() {
		GLCall(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(PositionNormalCubeTextureVertexData),
			(void*)offsetof(PositionNormalCubeTextureVertexData, Position)));
		GLCall(glEnableVertexAttribArray(0));
		GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(PositionNormalCubeTextureVertexData),
			(void*)offsetof(PositionNormalCubeTextureVertexData, Normal)));
		GLCall(glEnableVertexAttribArray(1));
		GLCall(glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(PositionNormalCubeTextureVertexData),
			(void*)offsetof(PositionNormalCubeTextureVertexData, TextureCoords)));
		GLCall(glEnableVertexAttribArray(2));
	}
};
