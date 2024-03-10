#pragma once
#include "../globa/base.h"
#include "../globa/math.h"
#include "texture.h"

class Shape {
public:
	Shape();

	~Shape();
	
	void CreateBall(unsigned int Longitude, unsigned int Latitude, float r);

	void CreateCube(float l, float w);

	unsigned int getVao() { return mVao; }

	unsigned int getSize() { return mSize; }
private:
	glm::vec3 getPoint(float u, float v, glm::vec2& uv, float r);
private:
	unsigned int mSize{ 0 };
	float* mVertexBuffer{ nullptr };
	unsigned int mVao{ 0 };
	unsigned int mTextureID{ 0 };
public:
	glm::mat4 mModel;
};