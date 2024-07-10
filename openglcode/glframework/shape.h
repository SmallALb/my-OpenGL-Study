#pragma once
#include "../globa/base.h"
#include "../globa/math.h"
#include "texture.h"

class Shape {
public:
	Shape();

	~Shape();
	
	static Shape* createBox(float size);

	static Shape* createSphere(float radius);
	
	static Shape* createPlan(float width, float heigt);

	GLuint& getVao() { return mVao; }

	uint32_t getIndicesCount() const { return mIndicesCount; }

private:
	uint32_t mIndicesCount{ 0 };
	float* mVertexBuffer{ nullptr };
	GLuint mVao{ 0 };
	GLuint mUvVbo{ 0 };
	GLuint mPosVbo{ 0 };
	GLuint mNormal{ 0 };
	GLuint mEbo{ 0 };
	GLuint mTextureID{ 0 };
public:
	glm::mat4 mModel;
};